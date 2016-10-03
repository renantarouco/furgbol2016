#ifndef ANDARRETO_H
#define ANDARRETO_H

#include "Tatica.h"
#include "DefendePonto.h"

/// @todo ajeitar
class AndarReto : public Tatica
{
private:
    DefendePonto maqDefendePonto;

public:
    bool alvoPosInicial;
    AndarReto();

    void executar(Agente* agente);

    bool verificarTermino(int id);

    float avaliacaoEscolhaRobo(int id);

    int getIdMelhorRobo(vector<int>& _ids);

    bool isAtiva();

    Tatica* getNovaInstancia();

     string getNome();

    void imprimirNome();

    float getLimiarAvaliacao();
};

#endif // ANDARRETO_H
