#include "KDTree.h"

KDTree::KDTree()
{
    raiz = 0x0;
    nodoMProximo = 0x0;
    menorDistancia = 0.0;
    nNodos = 0;
}

KDTree::~KDTree()
{
    clear();
}

KDNodo* KDTree::m_busca(KDNodo *nodo, KDNodo *nRaiz)
{
    if(nodo->cordenada(nRaiz->m_discri ) > nRaiz->cordenada( nRaiz->m_discri ) )
    {
        if(nRaiz->m_maior != 0x0)
            return m_busca(nodo, nRaiz->m_maior);
        else
            return nRaiz;
    }//else:

    if(nRaiz->m_menor != 0x0)
        return m_busca(nodo, nRaiz->m_menor);
    //else
        return nRaiz;
}

KDNodo* KDTree::busca(KDNodo *nodo, KDNodo *nRaiz)
{
    if(nodo == 0x0)
    {
        cout << "KDTree: Erro ao buscar nodo, nodo nulo" << endl;
        return 0x0;
    }
    if(nRaiz == 0x0)
    {
        if(raiz == 0x0)
        {
            cout << "KDTree: Erro ao buscar nodo, arvore vazia" << endl;
            return nodo;
        }
        nRaiz = raiz;
    }
    return m_busca(nodo , nRaiz);
}

void KDTree::adiciona(KDNodo *novoNodo)
{
    nNodos++;
    if(raiz == 0x0)
    {
        raiz = novoNodo;
        return;
    }

    KDNodo *pai = busca(novoNodo);

    novoNodo->m_pai = pai;
    novoNodo->m_discri = (pai->m_discri+1)%novoNodo->dim();

    if(novoNodo->cordenada(pai->m_discri) > pai->cordenada(pai->m_discri))
    {
        pai->m_maior = novoNodo;
    }else
    {
        pai->m_menor = novoNodo;
    }
}
unsigned KDTree::size()
{
    return nNodos;
}
void KDTree::clear()
{
//    cout << "Deletado Raiz" << endl;
    delete raiz;
    nNodos = 0;
    raiz = 0x0;
    nodoMProximo = 0x0;
//    cout << "Fim clear" << endl;
}

void KDTree::imprime()
{
    raiz->imprimeNodos();
}

float KDTree::distancia(KDNodo *a, KDNodo *b)
{
    float soma = 0.0, t;
    for(unsigned i = 0 ; i < a->dim() ; i++)
    {
        t = a->cordenada(i) - b->cordenada(i);
        soma += t*t;
    }
    return soma;
}

void KDTree::vizinhoRamo(KDNodo *nodo, KDNodo *ultimoNodo)
{
    float novaDist;
    float distEixo[ultimoNodo->dim()];
    unsigned i;
    KDNodo *n = ultimoNodo;

    while(n != 0x0)
    {
//        cout << "Analizando 2 [ " << n->cordenada(0) << " , " << n->cordenada(1) << " ]" << endl;
        novaDist = 0.0;
        for(i = 0 ; i < n->dim() ; i++)
        {
            distEixo[i] = n->cordenada(i) - nodo->cordenada(i);
            distEixo[i] *= distEixo[i];
            novaDist += distEixo[i];
        }

        if(novaDist < menorDistancia)
        {
            menorDistancia = novaDist;
            nodoMProximo = n;
        }

        if(distEixo[n->m_discri] < menorDistancia)
        {
            if(nodo->cordenada(n->m_discri) > n->cordenada(n->m_discri))
            {
                if(n->m_menor != 0x0) // Procura pelo outro lado da arvore
                {
//                    KDNodo *oi = n->m_menor;
//                    cout << "Procurando pelo outro lado 2 [ " << oi->cordenada(0) << " , " << oi->cordenada(1) << " ]"<<endl;
                    vizinhoRamo(nodo, n->m_menor);
                }
                n = n->m_maior;
            }else
            {
                if(n->m_maior != 0x0)
                {
//                    KDNodo *oi = n->m_maior;
//                    cout << "Procurando pelo outro lado 2 [ " << oi->cordenada(0) << " , " << oi->cordenada(1) << " ]"<<endl;
                    vizinhoRamo(nodo, n->m_maior);
                }
                n = n->m_menor;
            }
        }else
        {
            if(nodo->cordenada(n->m_discri) > n->cordenada(n->m_discri))
            {
                n = n->m_maior;
            }else
            {
                n = n->m_menor;
            }
        }
    }
}

void KDTree::vizinho(KDNodo *nodo, KDNodo *ultimoNodo)
{
    KDNodo *n = ultimoNodo;
    float novaDist;
    float distEixo[ultimoNodo->dim()];
    unsigned i;
    while(n != 0x0)
    {
//        cout << "Analizando [ " << n->cordenada(0) << " , " << n->cordenada(1) << " ]" << endl;
        novaDist = 0.0;
        for(i = 0 ; i < n->dim() ; i++)
        {
            distEixo[i] = n->cordenada(i) - nodo->cordenada(i);
            distEixo[i] *= distEixo[i];
            novaDist += distEixo[i];
        }
        if(novaDist < menorDistancia)
        {
            menorDistancia = novaDist;
            nodoMProximo = n;
        }

        if(distEixo[n->m_discri] < menorDistancia)
        {
//            cout << "Procurando por outro lado a partir de " << n->cordenada(0) << " , " << n->cordenada(1) <<endl;
            if(nodo->cordenada(n->m_discri) > n->cordenada(n->m_discri))
            {
                if(n->m_menor != 0x0) // Procura pelo outro lado da arvore
                {
//                    KDNodo *oi = n->m_menor;
//                    cout << "Procurando pelo outro lado [ " << oi->cordenada(0) << " , " << oi->cordenada(1) << " ]"<<endl;
                    vizinhoRamo(nodo, n->m_menor);
                }
            }else
            {
                if(n->m_maior != 0x0)
                {
//                    KDNodo *oi = n->m_maior;
//                    cout << "Procurando pelo outro lado [ " << oi->cordenada(0) << " , " << oi->cordenada(1) << " ]"<<endl;
                    vizinhoRamo(nodo, n->m_maior);
                }
            }
        }
        n = n->m_pai;
    }
}

KDNodo * KDTree::maisProximo(KDNodo *nodo)
{
    nodoMProximo = busca(nodo);
    menorDistancia = distancia(nodo, nodoMProximo);
    vizinho(nodo, nodoMProximo);
    return nodoMProximo;
}

KDNodo * KDTree::getRaiz()
{
    return raiz;
}
