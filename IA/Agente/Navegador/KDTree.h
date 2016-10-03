#ifndef KDTREE_H
#define KDTREE_H

#include "KDNodo.h"

using namespace std;

class KDTree
{
private:

    KDNodo *raiz;
    float menorDistancia;
    float distancia(KDNodo *a , KDNodo *b);

    KDNodo *nodoMProximo;
    KDNodo * m_busca(KDNodo* nodo , KDNodo* nRaiz);

    void vizinho(KDNodo* nodo, KDNodo *ultimoNodo);
    void vizinhoRamo(KDNodo* nodo, KDNodo *ultimoNodo);
    unsigned nNodos;

public:
    KDTree();
    ~KDTree();

    KDNodo * busca(KDNodo* nodo , KDNodo* nRaiz = 0x0);

    void adiciona(KDNodo *novoNodo);
    KDNodo* maisProximo(KDNodo *nodo);
    KDNodo* getRaiz();
    unsigned size();
    void clear();

    void imprime();
};

#endif // KDTREE_H
