#ifndef OBSTACULO_H
#define OBSTACULO_H
#include<Definitions.h>
#include"Geometria.h"

class Obstaculo
{
public:
    virtual ~Obstaculo()=0 ;
    virtual bool contemPonto(Ponto p) = 0;
    virtual bool intersecta(Ponto &A , Ponto &B) = 0;
    virtual Obstaculo* copia() = 0;
    virtual Ponto getPosicao() = 0;
    virtual void diminuiRaio(float valor) = 0; /*! Este método tem efeito apenas no CirculoObstaculo */
};


class CirculoObstaculo : public Obstaculo
{
private:
    Circulo circ;
public:

    CirculoObstaculo(Ponto p, float raio);
    CirculoObstaculo(Circulo &c);
    ~CirculoObstaculo();
    bool contemPonto(Ponto p);
    bool intersecta(Ponto &A , Ponto &B);
    Obstaculo* copia();
    Ponto getPosicao();
    void diminuiRaio(float valor);

};

#endif // OBSTACULO_H
