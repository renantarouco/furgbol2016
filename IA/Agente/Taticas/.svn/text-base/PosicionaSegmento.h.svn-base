#ifndef POSICIONASEGMENTO_H
#define POSICIONASEGMENTO_H

#include <Tatica.h>
#include <DefendePonto.h>

/// @todo ajeitar
class PosicionaSegmento : public Tatica
{

public:
    PosicionaSegmento();
    ~PosicionaSegmento();

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
        Função que avalia o quão bom o robô é para executar essa tatica
        Iremos avaliar o robo de acordo com a distancia que ele está do alvo para se posicionar
        @param id Id do robo que iremos avaliar
        @return Distancia do robo ao alvo para se posicioanar
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robo para executar essa tática
        Iremos pegar o robo que estiver mais perto do alvo para se posicionar
        @param _ids Ids dos robos que estão disponiveis para executar essa tática
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

    string getNome();

    void imprimirNome();

private:

    /**
        Função que calcula o alvo para o robo se posicionar no segmento
        @param id Id do robo que irá se posicionar
        @return Alvo que foi calculado para se posicionar
    */
    Ponto calcularAlvoNoSegmento(int id);
};

#endif // POSICIONASEGMENTO_H
