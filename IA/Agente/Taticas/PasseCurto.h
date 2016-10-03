#ifndef PASSECURTO_H
#define PASSECURTO_H

#include <Tatica.h>
#include <MoveBola.h>
#include <DefendePonto.h>

/// @todo ajeitar
class PasseCurto : public Tatica
{
public:
    PasseCurto();
    ~PasseCurto();

    void executar(Agente* agente);float getLimiarAvaliacao();

    /**
        Função que verifica quando a Tática foi finalizada.
        Iremos analisar se o robô que executa a tática tocou na bola
        @param id Id do robô que executa a tática
        @return True se tiver terminado, false senão tiver terminado
    */
    bool verificarTermino(int id);

    /**
        Função que avalia o quão bom o robô é para executar está tática
        Iremos avaliar o robo de acordo com a distância do robô a bola
        @param id Id do robo que iremos avaliar
        @return Distância do robô a bola
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robo para executar está tática
        Iremos pegar o robô que tiver mais perto da bola
        @param _ids Ids dos robôs disponiveis para executar a tática
        @return Id do robô que foi escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que verifica se a tática é ativa.
        Essa tática é ativa, pois tem envolvimento direto com a bola
        @return True se for ativa, false senão for ativa
    */
    bool isAtiva();

    Tatica* getNovaInstancia();

    void imprimirNome();

    string getNome();
};

#endif // PASSECURTO_H
