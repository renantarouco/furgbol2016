#ifndef POSICIONACHUTE_H
#define POSICIONACHUTE_H

#include <Tatica.h>
#include <DefendePonto.h>
#include <Geometria.h>

/// @todo ajeitar
class PosicionaChute : public Tatica {

public:
    PosicionaChute();
    ~PosicionaChute();

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
        Função que avalia o quão bom o robô é para executar esta tática
        Iremos avaliar o robô de acordo com a distância que ele está do alvo aonde ele irá se posicionar
        @param id Id do robô que irá ser avaliado
        @return Distância do robô a região
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para executar esta tática
        Iremos pegar o robô que estiver mais perto do alvo calculado para se posicionar
        @param _ids Ids dos robos disponiveis para executar esta tática
        @return Id do robô que foi escolhido
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

private:

    /**
        Função que verifica qual é a melhor região para se posicionar de um conjunto de regiões
        Iremos analisar de acordo com a quantidade de robos que estão dentro dela
        @param id Id do robô que irá executar esta tática
        @return Região escolhida para se posicionar
    */
    Circulo verificarMelhorRegiao(int id);

    /**
        Função que calcula o alvo que o robô irá se posicionar para poder chutar posteriormente
        @param id Id do robô que irá se posicionar
        @return Alvo calculado para se posicionar
    */
    Ponto calcularAlvoRoboRegiao(int id);
};

#endif // POSICIONACHUTE_H
