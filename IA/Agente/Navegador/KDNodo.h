#ifndef KDNODO_H
#define KDNODO_H

#include <iostream>
#include <Definitions.h>

using namespace std;

class KDNodo
{
private:
    KDNodo *m_menor;
    KDNodo *m_maior;
    KDNodo *m_pai;
    unsigned m_discri;

public:
    Ponto p;
    KDNodo *RRTRef;


    KDNodo(float x , float y , KDNodo *RRTref=0x0 , KDNodo *pai =0x0, KDNodo *menor=0x0 , KDNodo *maior=0x0, unsigned discriminante=0);

    ~KDNodo();

    float cordenada(unsigned k);

    unsigned dim();

    KDNodo * nodoMaior();

    KDNodo * nodoMenor();

    KDNodo * nodoPai();

    unsigned discriminante();

    /* A partir daqui todos métodos são recursivos */

    /* Se o nodo for igual, adiciona como menor*/
    void adicionaNodo(KDNodo *novoNodo);

    void adicionaMaior(KDNodo *maior);

    void adicionaMenor(KDNodo *menor);

    KDNodo * maisProximo( KDNodo *nodo);

    void excluiTodosNodos();

    void imprimeNodo();

    /* Leitura da arvore em ordem */
    void imprimeNodos();

    friend class KDTree;
};

#endif // KDNODO_H
