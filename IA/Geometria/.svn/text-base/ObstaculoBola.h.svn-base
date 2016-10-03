#ifndef OBSTACULOBOLA_H
#define OBSTACULOBOLA_H

#include <Poligono.h>

class ObstaculoBola : public Poligono
{
public:

    static const float TAMANHO_EXTRA;

    ObstaculoBola();
    ~ObstaculoBola();

    void construir(const Ponto &centroObjeto, float _distRoboCentro);

    vector<Ponto> calcularAlvoPosicionar(int qtRobosPosicionar);

    vector<Ponto> calcularAlvosFinais(const Ponto &alvoInicial, int qtRobosPosicionar);

    Poligono * getNovaInstancia();

    bool isPontoDentro(const Ponto &ponto);

    bool isInterseccao(const Ponto &inicioSeg, const Ponto &fimSeg);

    Ponto getCentro();
};

#endif // OBSTACULOBOLA_H
