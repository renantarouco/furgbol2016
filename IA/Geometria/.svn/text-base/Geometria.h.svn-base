#ifndef GEOMETRIA_H
#define GEOMETRIA_H

#include "Area.h"

#include <boost/math/complex.hpp>
#include <cmath>

class Geometria{
private:
//    float MIN_DIST_GOL = 3*RAIO_ROBO + TOL_PERTENCE_ALVO;

public:
    Geometria();

    static float produtoVetorial2D(Vetor u, Vetor v);

    /// o angulo calculado sera sempre de 0 a 180 !!!
    static float calcularAnguloVetores(Vetor u, Vetor v);

    static bool colisao(Ponto &A, Ponto &B, Circulo circ);

    /**
        @brief dada uma reta e um ponto nesta reta , calcula um ponto na propria reta com o deslocamento
        passado como parametro.
        @param Ponto um ponto na reta.
        @param Reta a reta onde vai ser calculado o ponto.
        @param float distancia de afastamento do ponto gerado com o ponto passado.

        Observações ao usar a função.
        Retas Crescentes:
        Deslocamento positivo implica em um deslocamento positivo em x e y ou seja o ponto se move para cima direita.
        Deslocamento negativo implica em um deslocamento negativo em x e y ou seja o ponto se move para baixo esquerda.
        Retas Decrescente:
        Deslocamento positivo implica em um deslocamento positivo em x e negativo em y o ponto se move para baixo direta
        Deslocamento negativo implica em um deslocamento negativo em x e positivo em y o ponto se move para cima e para esquerda.
    */
    static Ponto calcularPontoEmRetaComDesloc(const Ponto &pontoNaReta, const Reta &reta, float distAfastamento);

    /**
        Nesse método iremos verificar se a reta passada como parâmetro intercepta o gol em algum ponto.
        @param segmento Segmento da frente da area da goleira da nossa equipe
        @param const Reta& reta Reta que iremos verificar se intercepta o gol em algum ponto.
        @return bool Retorna true se interceptar e false senão interceptar.
    */
    static bool isInterseccaoSegmentoReta(const Segmento& segmento, const Reta& reta); /// Interna , verifica

    /**
        Nesse método iremos calcular o ponto de interseção entre o segmento e a reta passada como parâmetros.
        @param Segmento& segmento Linha que iremos analisar
        @param Reta& reta Reta que iremos analisar
        @return bool Retorna se tem alguma intersecao entre os objetos
    */
    static bool isInterseccaoSegmentoReta(const Segmento& segmento, const Reta& reta, Ponto& interseccao);

    /**
        Nesse método iremos verificar se a reta passada como parâmetro intercepta o semicirculo passado como parâmetro também.
        @param const Arco& semiCirculo Arco que iremos analisar se a reta intercepta-o.
        @param Reta& reta Reta que iremos analisar se intercepta o semiCirculo.
        @param Ponto& ponto Ponto em que a reta intercepta o semicirculo.
        @return bool Retorna true se a reta intercepta o arco e false senão intercepta o arco.
    */
    static bool interseccaoRetaSemiCirculo(const Arco& semiCirculo, const Reta& reta, Ponto& interseccao);

    /**
        Função que calcula os pontos que fazem interseccao entre os circulos
        @param circulo1
        @param circulo2
        @return Pontos que fazem interseccao entre os circulos
    */
    static vector<Ponto> interseccaoCirculoCirculo(const Circulo& circulo1, const Circulo& circulo2);
};

#endif // GEOMETRIA_H
