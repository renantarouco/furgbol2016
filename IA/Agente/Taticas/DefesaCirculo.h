#ifndef DEFESACIRCULO_H
#define DEFESACIRCULO_H

#include "Tatica.h"
#include "DefendePonto.h"
#include "Circulo.h"
#include "Bola.h"
#include "Agente.h"
#include "Robo.h"

class DefesaCirculo : public Tatica
{
private:
    DefendePonto maqDefendePonto; ///< máquina de estados usada para executar a tática
    Circulo circuloPosicionar; ///< Objeto em que iremos usar como referência do posicionando da defesa
    string objetoPosicionar; ///< nome do objeto que iremos posicionar a defesa
    string nomeTatica;

    Ponto calcularAlvoPosDefesa(int id);

public:
    DefesaCirculo();
    ~DefesaCirculo();

    /**
            Método que executa a tática.
            @param int id É o identificador do robô a executar a tática.
            @param AvaliadorRobo* avaliadorRobo Iremos usar essa variável para analisar a situação do robô com o modelo de mundo.
            @return MaquinaSkills* Retorna a maquina de skills que irá ser usada para executar essa tática.
        */
    void executar(Agente* agente);

    /**
            Verifica o término da tática, é feita juntamente com o módulo executor.
            @param int id É o identificador do robô a executar a tática.
            @return bool Retorna se foi terminada ou não.
        */
    bool verificarTermino(int id);

    /**
            Funcao que retorna um score utilizado para avaliar o melhor robo para fazer
            esta jogada.
        */
    float avaliacaoEscolhaRobo(int id);

    /**
            Nesse método iremos analisar qual o melhor robô que se aplica a essa tática, de acordo com o modelo de mundo.
            @param vector<int>& _ids Vetor com os ids dos robôs que estão sem táticas.
            @return int Id do melhor robô para a tática.
        */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
            Método que responde se a tática em questão está ativa.
            @return bool Retorna se a tática é ativa ou não.
        */
    bool isAtiva();

    /**
            Nesse método iremos criar uma nova instancia da tática usada no momento.
            @return Tatica* retorna a nova instancia da tática.
        */
    Tatica* getNovaInstancia();

    /**
            Função para debug que imprime o nome de cada tática.
        */
    void imprimirNome();

    string getNome();

    float getLimiarAvaliacao();

};

#endif // DEFESACIRCULO_H
