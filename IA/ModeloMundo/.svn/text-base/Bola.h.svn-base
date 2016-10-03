#ifndef BOLA_H
#define BOLA_H

#include "Definitions.h"

/**
    Classe contém as informações fisicas da bola, como velocidade altura e a posicão.
*/
class Bola
{
public:
    static const int RAIO_MAX = 21.5; ///< Raio da Bola

private:
    Ponto posicao; ///< Posição atual da bola
    Ponto posicaoAnt; /// Posicao da bola na interacao anterior
    Ponto posicaoChutada; /// Grava a posicao da bola quando o robô decidiu chutar
    float altura; ///< A altura onde a bola está, provavelmente não será usada
    Vetor vetorVelocidade; ///< Vetor que indica a direção da bola e a velocidade
    float velLinear; ///< modulo da velocidade linear da bola

public:
    Bola();

    /**
        Função que retorna a Posição atual da bola
        @return Posição da bola
    */
    const Ponto& getPosicao();

    const Ponto& getPosicaoAnterior();

    /**
        Função que seta a Posição atual da bola
        @param _posicao Posição da bola
    */
    void setPosicao(const Ponto &_posicao);
    void setPosicao(const Ponto &_posicao, float tempoIteracao);

    /**
        Função que retorna o Vetor de Velocidade da bola
        @return Vetor de Velocidade da bola
    */
    Vetor getVetorVelocidade();

    /**
        Função que seta o Vetor de Velocidade da bola
        @param _velocidade Vetor de Velocidade da bola
    */
    void setVetorVelocidade(const Vetor &_velocidade);

    /**
        Função que retorna a altura da bola em relação ao campo
        @return Altura da bola em relação ao campo
    */
    float getAltura();

    /**
        Função que seta a Altura da bola em relaçao ao campo
        @param _altura Altura em que a bola se encontra
    */
    void setAltura(float _altura);

    /**
        Função que verifica se a bola foi chutada ou não em um instante de tempo
        @return True se tiver sido chutada, false senão tiver sido chutada
        @todo fazer essa função
    */
    bool foiChutada();

    /**
      Metodos de acesso para setar e pegar a posicao que a bola passou a querer ser chutada
      */
    Ponto getPosChutada();

    void setPosChutada(Ponto);

    bool isPertoAreaEq();
    bool isPertoLinhaFundoEq();
};

#endif // BOLA_H
