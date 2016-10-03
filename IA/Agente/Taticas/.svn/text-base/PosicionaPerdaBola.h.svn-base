#ifndef POSICIONAPERDABOLA_H
#define POSICIONAPERDABOLA_H

#include <Tatica.h>
#include <DefendePonto.h>

/// @todo ajeitar
class PosicionaPerdaBola : public Tatica
{

public:
    PosicionaPerdaBola();
    ~PosicionaPerdaBola();

    void executar(Agente* agente);
float getLimiarAvaliacao();
    /**
        Função que verifica quando a tática foi completada.
        Como essa tática não é ativa, então ela não possui termino só irá terminar quando a tática ativa terminar
        @param id Id do robô que está executando a tática
        @return True se tiver terminado, false senão tiver terminado
    */
    bool verificarTermino(int id);

    float avaliacaoEscolhaRobo(int id);

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
        @todo revisar bem essa função
    */
    Ponto calcularAlvoPosPerdaBola(int id);
};

#endif // POSICIONAPERDABOLA_H
