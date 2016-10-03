#ifndef DEFENDEGOL_H
#define DEFENDEGOL_H

#include "Tatica.h"
#include "DefendePonto.h"
#include "MoveBola.h"

/**
    Classe com as funções para o jogador ficar defendendo o nosso gol do time adversário.
*/
class DefendeGol : public Tatica
{
private:
    DefendePonto maqDefendePonto;

public:
    DefendeGol();
    ~DefendeGol();

    /**
        Se a bola estiver proximá da nossa área, o goleiro ficará na intersecção da bola com o gol
        com uma proximidade do gol, se a bola estiver longe da nossa área aproximamos para perto o goleiro
        da defesa circulo.
        @return Ponto O alvo que caculamos para o goleiro
        @todo Revisar essa função, verificar porque o goleiro sempre fica no centro do gol
    */
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

private:

//    /**
//        Dado um ponto do interseccao calcula um alvo deslocado em uma reta com
//        a distancia de afastamento passada. A reta utilizada é perpendicular a reta tangente no semi circulo
//        e perpendicular ao segmento na area.
//        @param Ponto um ponto de interseccao de onde será calculada a distancia
//        @param float a distancia de afastamento
//    */
//    Ponto calcularAlvoAfast(const Ponto& pontoInterseccao, float distAfastamento);
};

#endif // DEFENDEGOL_H
