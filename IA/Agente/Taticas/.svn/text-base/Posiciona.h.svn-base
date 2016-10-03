#ifndef POSICIONA_H
#define POSICIONA_H

#include <Tatica.h>
#include <DefendePonto.h>

/**
    Classe responsável por posicionar os robôs em uma posição absoluta no campo.
*/
class Posiciona : public Tatica
{
private:
    DefendePonto maqDefendePonto;

public:
    Posiciona();
    ~Posiciona();

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
        Iremos avaliar o robô de acordo com a distância que ele está do ponto que é para se posicionar
        @param id Id do robô que iremos avaliar
        @return Distância do robô ao ponto
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para executar esta tática
        Iremos pegar o robô que estiver mais próximo do ponto
        @param _ids Ids dos robôs disponiveis para executar esta tática
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
};

#endif // POSICIONA_H
