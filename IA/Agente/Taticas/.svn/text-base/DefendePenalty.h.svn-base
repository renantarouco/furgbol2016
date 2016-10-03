#ifndef DEFENDEPENALTY_H
#define DEFENDEPENALTY_H

#include <Tatica.h>
#include <DefendePonto.h>

/// @todo ajeitar
class DefendePenalty : public Tatica
{
private:
    DefendePonto maqDefendePonto;

public:
    DefendePenalty();
    ~DefendePenalty();

    /** @todo implementar uma função para o Goleiro pegar o penalty do adversário */
    void executar(Agente* agente);

    /**
        Função que verifica quando a tática foi completada.
        Como essa tática não é ativa, então ela não possui termino só irá terminar quando a tática ativa terminar
        @param id Id do robô que está executando a tática
        @return True se tiver terminado, false senão tiver terminado
    */
    bool verificarTermino(int id);float getLimiarAvaliacao();

    /**
        Função que faz a avaliação do quão bom o robô é para executar essa tática.
        Todos os robôs terão o mesmo valor de avaliação, pois somente 1 robô poderá executar
        essa tática que é o goleiro
        @param id Id do robô que queremos avaliar
        @return Valor da avaliação feita do robô
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para executar essa tática,
        como só temos 1 robô que pode executar essa tática iremos retorna o seu id
        @param _ids Ids dos robôs que estão disponiveis para executar essa tática
        @return Id do robô que foi escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que analisa se a tática é ativa.
        Essa tática não é ativa, pois não tem envolvimento direto com a bola
        @return True se for ativa, false senão for ativa
    */
    bool isAtiva();

     string getNome();

    Tatica* getNovaInstancia();

    void imprimirNome();
};

#endif // DEFENDEPENALTY_H
