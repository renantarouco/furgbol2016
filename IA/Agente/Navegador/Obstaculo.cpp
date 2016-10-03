#include <Sistema.h>
#include<Obstaculo.h>


Obstaculo::~Obstaculo()
{

}


CirculoObstaculo::CirculoObstaculo(Ponto p, float raio)
{
    circ = Circulo(p, raio*raio);
}

CirculoObstaculo::CirculoObstaculo(Circulo &c)
{
    circ = c;
}

CirculoObstaculo::~CirculoObstaculo()
{

}

bool CirculoObstaculo::contemPonto(Ponto p)
{
    return (!circ.has_on_unbounded_side(p));
}

bool CirculoObstaculo::intersecta(Ponto &A , Ponto &B)
{
    Reta reta(A , B);
    Retangulo retSeg( A , B );

    vector<Objeto> intersecs;
    intersecs.reserve(2);
    unsigned int j;
    intersection(circ , reta , back_inserter(intersecs));
    for ( j = 0; j < intersecs.size(); j ++)
    {
        if(const pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> > (&(intersecs[j])))
        {
            Ponto p(ponto->first.x() , ponto->first.y() );
            if(!retSeg.has_on_unbounded_side( p ) )
                return true;
        }
    }
    return false;
}

Obstaculo *CirculoObstaculo::copia()
{
    return new CirculoObstaculo(circ);
}

Ponto CirculoObstaculo::getPosicao()
{
    return circ.center();
}

void CirculoObstaculo::diminuiRaio(float valor)
{
    circ = Circulo(circ.center() , circ.squared_radius() - valor*valor);
}
