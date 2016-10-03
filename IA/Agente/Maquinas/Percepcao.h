#ifndef PERCEPCAO_H
#define PERCEPCAO_H

#include "Definitions.h"

class Percepcao
{
private:
    int idRobo; ///< Id do robô que está fazendo a percepção do Modelo de Mundo

public:
    Percepcao();

    static const int DISTANCIA_MAXIMA_CARREGANDO_BOLA = 490; ///< Distância máxima que o robô pode carregar a bola

    bool isAlvoGirarIgualPosRobo(const Ponto &pontoParaGirar, bool horario, int _idRobo);

    /**
        Função que seta o valor do id do robo que iremos efetuar as percepções do mundo
        @param _idRobo Id do robo que iremos efetuar as percepções
    */
    void setIdRobo(int _idRobo);

    /**
        Funçao que verifica se o alvo passado como parâmetro foi alterado para outro alvo
        @param alvoMudou Alvo que queremos analisar se foi mudado
        @return True se o alvo mudou, false não tiver mudado
    */
    bool isAlvoMudou(const Ponto& alvoMudou);

    /**
        Nesse metódo iremos verificar se o robô está de frente para a bola ou não.
        @return bool Retornaremos true se estiver de frente para a bola, e false senão estiver de frente.
    */
    bool isFrenteParaBola();

    /**
        Nesse metódo iremos verificar se o robô está de frente para a bola para ligar o driblador.
        @return bool Retornaremos true se estiver de frente para a bola, e false senão estiver de frente.
    */
    bool isFrenteParaBolaDrible();

    /**
        Função que diz se dois alvos são iguais, considerando a nossa tolerancia isso é necessário pois o alvo
        se trata de um ponto infinitesimal e o robo teria deficuldade de perceber que está na posição onde deveria.
        @param alvo Ponto que sera analisado se o robo esta em cima dele
        @return Retorna true se estiver no alvo, e false senão estiver no alvo
    */
    bool isAlvoMarcado(const Ponto& alvo);

    /**
        Nesse método iremos verificar se o robô está perto o suficiente para girar pra poder ficar de frente pra bola.
        @return bool Retorna true se estiver dentro do raio e false senão estiver dentro do raio.
    */
    bool isDentroRaioAprox();

    /**
        Nesse método iremos verificar se o robô está a uma certa distância de tolerância da bola, para ele poder chutar.
        @return bool Retorna true se estiver perto e false senão estiver perto.
    */
    bool isBolaPertoParaChute();

    /**
        Função que verifica se o robô está com um ângulo bom para chutar
        @param anguloChute Angulo que o robô está atualmente em relação a bola
        @return True se estiver com um angulo bom para chute, false se não estiver com um angulo bom
    */
    bool isAnguloParaChute(float anguloChute);

    /**
        Função que verifica se o robô poderá carregar a bola ou não
        @return True se poder carregar, false senão poder carregar
    */
    bool isCarregarBola();

    /**
        Verifica qual o sentido que precisa girar em um eixo para chegar mais perto a um alvo
        @param alvo Alvo que que queremos analisar a orientação do robô para identificarmos para que lado girar
    */
    bool getSentidoMaisPerto(const Ponto& alvo);

    /**
        Função que verifica se a bola está dentro do campo ou não
        @return True se a bola estiver, false senão estiver
    */
    bool isBolaDentroCampo();

    /**
      Função para verificar se ocorreu uma movimentação significativa na bola
      */
    bool isBolaChutada();

    /**
      Verfica se a bola esta quase saindo do campo pelas laterais
    */
    bool isBolaQuaseSaindoCampo();

    /**
      Verifica se a bola esta dentro da area adversaria
    */
    bool isBolaDentroAreaAdv();

};

#endif // PERCEPCAO_H
