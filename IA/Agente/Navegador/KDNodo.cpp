#include "KDNodo.h"


KDNodo::KDNodo(float x, float y, KDNodo *RRTref, KDNodo *pai, KDNodo *menor, KDNodo *maior, unsigned discriminante)
{
    m_pai = pai;
    m_menor = menor;
    m_maior = maior;
    m_discri = discriminante;
    p = Ponto(x , y);
    RRTRef = RRTref;
}

KDNodo::~KDNodo()
{
    if(m_menor != 0x0)
    {
        delete m_menor;
        m_menor = 0x0;
    }
    if(m_maior != 0x0)
    {
        delete m_maior;
        m_maior = 0x0;
    }
//    cout << "Morri ! " << m_menor << " , " << m_maior << endl;
}

float KDNodo::cordenada(unsigned k)
{
    if(k == 0)
        return p.x();
    else
        return p.y();
}

unsigned KDNodo::dim()
{
    return 2;
}

KDNodo* KDNodo::nodoMaior()
{
    return m_maior;
}

KDNodo * KDNodo::nodoMenor()
{
    return m_menor;
}

KDNodo* KDNodo::nodoPai()
{
    return m_pai;
}

unsigned KDNodo::discriminante()
{
    return m_discri;
}


void KDNodo::adicionaNodo(KDNodo *novoNodo)
{
    if(novoNodo->cordenada(m_discri) > cordenada(m_discri))
    {
        adicionaMaior(novoNodo);
    }else
    {
        adicionaMenor(novoNodo);
    }
}

void KDNodo::adicionaMaior(KDNodo *maior)
{
    if(m_maior == 0x0)
    {
        maior->m_pai = this;
        maior->m_discri = (m_discri+1)% maior->dim();
        m_maior = maior;
    }else
    {
        m_maior->adicionaNodo(maior);
    }
}

void KDNodo::adicionaMenor(KDNodo *menor)
{
    if(m_menor == 0x0)
    {
        menor->m_pai = this;
        menor->m_discri = (m_discri+1)% menor->dim();
        m_menor = menor;
    }else
    {
        m_menor->adicionaNodo(menor);
    }
}

void KDNodo::excluiTodosNodos()
{
    m_menor->excluiTodosNodos();
    m_maior->excluiTodosNodos();
    delete this;
}

void KDNodo::imprimeNodo()
{
    cout << "D = ( " << m_discri << " ) ; [ " << cordenada(0);
    for(unsigned i = 1; i < dim() ; i++)
    {
        cout << " , " << cordenada(i);
    }
    cout << " ]" << endl;
}

void KDNodo::imprimeNodos()
{
    imprimeNodo();
    if(m_menor != 0x0)
    {
        m_menor->imprimeNodos();
    }

    if(m_maior != 0x0)
    {
        m_maior->imprimeNodos();
    }
}
