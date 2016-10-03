#ifndef CHUTE_H
#define CHUTE_H

#include "Tatica.h"
#include "MoveBola.h"

/**
    Tatica de chute a gol, avalia melhor posição e e prepara para chutar.
    @todo NAO ESQUECER DE ANALISAR USO DE HISTERESIS,
    @todo Botar uma flag que depende se o alvo ja foi determinado, se ele ja foi determinado,
    @todo So trocar o alvo caso ocorra mudancas drasticas no score.
*/
class Chute : public Tatica
{
private:
    bool chutou;
    MoveBola maqMoveBola;

public:
    Chute();
    ~Chute();

    float getLimiarAvaliacao();

    /** @todo Avaliar a necessidade de ver se o alvo gerado está ocupado, pode ser necessário roubar a bola antes */
    void executar(Agente* agente);

    /**
        Função que verifica quando a tática termina.
        Iremos analisar se terminou quando o robô tiver chutado a bola
        @param id Id do robô que está executando a tática
        @return True se tiver terminado, false senão tiver terminado
        @todo Analisar isso e pedir velocidade da bola pro GD ou calcular eu mesmo.
    */
    bool verificarTermino(int id);

    /**
        Função que avalia o quão bom o robô com o id respectivo é para executar essa tática.
        Iremos avaliar de acordo com a distância que o robô está da bola,
        que justamente é o melhor robô para chutar a bola
        @param id ID do robô que iremos avaliar
        @return Distância do robô a bola
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que pega o Id do melhor para executar essa tática.
        Iremos pegar o robô que tiver a menor distância até a bola e que possa tocar na bola
        @param _ids Ids dos robôs disponiveis para executar essa tatica
        @return Id do robô que foi escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que verifica se a tática é ativa.
        Essa tática é ativa, pois tem envolvimento direto com a bola
        @return True se for ativa, false senão for ativa
    */
    bool isAtiva();

     string getNome();

    Tatica* getNovaInstancia();

    void imprimirNome();
};

#endif // CHUTE_H
