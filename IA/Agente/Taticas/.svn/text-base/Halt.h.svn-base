#ifndef HALT_H
#define HALT_H

#include "Tatica.h"
#include "DefendePonto.h"

/**
    Tatica responsável por fazer todos os robôs ficarem parados.
*/
class Halt : public Tatica
{
private:
    DefendePonto maqDefendePonto;

public:
    Halt();
    ~Halt();

    void executar(Agente* agente);

    /**
        Função que verifica quando a tática foi completada.
        Como essa tática não é ativa, então ela não possui termino só irá terminar quando a tática ativa terminar
        @param id Id do robô que está executando a tática
        @return True se tiver terminado, false senão tiver terminado
    */
    bool verificarTermino(int id);float getLimiarAvaliacao();

    float avaliacaoEscolhaRobo(int id);

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
};

#endif // HALT_H
