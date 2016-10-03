#ifndef ROUBABOLA_H
#define ROUBABOLA_H

#include <Tatica.h>
#include <MoveBola.h>

/// @todo ajeitar
class RoubaBola : public Tatica
{

public:
    RoubaBola();
    ~RoubaBola();

    void executar(Agente* agente);
    float getLimiarAvaliacao();
    /**
        Função que verifica quando a tática foi finalizada
        Iremos analisar pela posse de bola, quando a posse de bola passar a ser nossa
        então indica que conseguimos roubar a bola do adversário
        @param id Id do robo que está executando a tática
        @return True se tiver finalizada, false senão tiver
    */
    bool verificarTermino(int id);

    /**
        Função que avalia o quão bom o robô é para executar essa tática
        Iremos avaliar de acordo com a distância que ele está do robô adv que está com a bola
        @param id Id do robô que irá ser avaliado
        @return Distância do robo ao robo adv que está com a bola
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para executar essa tática
        Iremos pegar o robo que estiver mais perto do robo adv que está com a bola
        @param _ids Ids dos robos que estao disponiveis para executar essa tática
        @return Id do robo que foi escolhido
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

#endif // ROUBABOLA_H
