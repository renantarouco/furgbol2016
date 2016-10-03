#ifndef LIMPA_H
#define LIMPA_H

#include "Tatica.h"
#include "MoveBola.h"

/**
    Tatica responsável por fazer o robô chutar a bola para longe de onde ele está no momento.
    A ideia desta tática é primeiro o robo tentar chutar a gol e depois, caso esteja bloqueado o robo deve tentar chutar
    em outros pontos
    @todo Avaliar a necessidade de ver se o alvo gerado está ocupado , pode ser necessário roubar a bola antes
    @todo Botar uma flag que depende se o alvo ja foi determinado , se ele ja foi determinado
    @todo So trocar o alvo caso ocorra mudancas drasticas no score.
*/
class Limpa : public Tatica
{
private:
    bool chutou;
    MoveBola maqMoveBola;

    Ponto calcularAlvoChuteLongaDist(int id);
    Ponto calcAlvoAproximacao(int id, const Ponto& alvo);

public:
    Limpa();
    ~Limpa();

    void executar(Agente* agente);

    float getLimiarAvaliacao();

    /**
        Função que verifica quando a tática foi finalizada
        Essa tática só será finalizada quando o robô tocar na bola
        @param id Id do robô que está executando a tática
        @return True se tiver terminada, false senão tiver terminada
        @todo Implementar a função para verificar quando o robô chutou a bola
    */
    bool verificarTermino(int id);

    /**
        Função que avalia o quão bom o robô é para executar esta tática
        Iremos avaliar o robo de acordo com a distância que ele está da bola
        @param id Id do robo que será avaliado
        @return Distancia do robô a bola
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robo para executar essa tática
        Iremos pegar o robo que estiver mais perto da bola
        @param _ids Ids dos robos disponiveis para executar essa tatica
        @return Id do robo escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que verifica se a tática é ativa.
        Essa tática é ativa, pois tem envolvimento direto com a bola
        @return True se for ativa, false senão for ativa
    */
    bool isAtiva();

    Tatica* getNovaInstancia();

    void imprimirNome();

    string getNome();
};

#endif // LIMPA_H
