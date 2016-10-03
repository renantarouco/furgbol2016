#ifndef RECEBERPASSE_H
#define RECEBERPASSE_H

#include <MaquinaSkills.h>
#include <DefendePonto.h>
#include <Tatica.h>

/// @todo ajeitar
class ReceberPasse:public Tatica
{
public:
    ReceberPasse();

    void executar(Agente* agente);

    float getLimiarAvaliacao();
    /**
        Função que verifica quando a tática foi completada.
        Como essa tática não é ativa, então ela não possui termino só irá terminar quando a tática ativa terminar
        @param id Id do robô que está executando a tática
        @return True se tiver terminado, false senão tiver terminado
    */
    bool verificarTermino(int id);

    /**
        Função que avalia o quão bom o robô é para executar essa tática
        Iremos avaliar o robô de acordo com a distancia que ele está do alvo para se posicionar
        @param id Id do robo que iremos avaliar
        @return Distancia do robo ao alvo para se posicionar
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para receber o passe
        Iremos pegar o robô que está mais perto do alvo calculado
        @param _ids Ids dos robos disponiveis para executar essa tatica
        @return Id do robo que foi escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que analisa se a tática é ativa.
        Essa tática não é ativa, pois não tem envolvimento direto com a bola
        @return True se for ativa, false senão for ativa
    */
    bool isAtiva();

    Tatica* getNovaInstancia();

    void imprimirNome();

    string getNome();
};

#endif // RECEBERPASSE_H
