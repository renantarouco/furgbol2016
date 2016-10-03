#ifndef MARCARSAIDABOLA_H
#define MARCARSAIDABOLA_H

#include <Tatica.h>
#include <DefendePonto.h>

/// @todo ajeitar
class MarcarSaidaBola : public Tatica
{
private:
    int idRoboAdvMarcar; ///< Id do robô adv que iremos marcar a saida de bola

public:
    MarcarSaidaBola();
    ~MarcarSaidaBola();

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
        Iremos analisar de acordo com o alvo que foi calculado para o robô se posicionar para marcar a saida de bola,
        iremos calcular a distância do robô a este alvo
        @param id Id do robô que iremos avaliar
        @return Distância do robô ao alvo
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para executar esta tática.
        Iremos pegar o robô que possuir a menor distância até o ponto que calculamos
        para o robô ficar marcando a saida de bola do robo adv
        @param _ids Ids dos robos que estão disponiveis para executar a tatica
        @return Id do robo que foi escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que retorna o id do robô adv que está sendo marcado
        @return Id do robô adv que está sendo marcado
    */
    int getIdRoboAdvParaMarcar();

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
        Função que verifica qual o robô adv que iremos colocar o robô para marcar a saida de bola
        @param id Id do robô que irá marcar
    */
    void verificarRoboAdvMarcar(int id);

    /**
        Nesse método iremos calcular um alvo para o robô se pocisionar fazendo com que o robô adv não consiga passar a bola
        para o outro robô adv que o robô irá marcar.
        @param idRoboAdvMarcar Id do Robô que iremos marcar
        @return Ponto Alvo que iremos calcular para o robô se posicionar
    */
    Ponto calcularAlvoMarcarRoboReceberaPasse(int idRoboAdvMarcar);

    /**
        Função que calcula o alvo para aonde o robô irá marcar a saida de bola do adv
        @param id Id do robô que irá marcar
        @return Alvo que foi calculado para o robô se posicionar
    */
    Ponto calcularAlvoMarcarSaidaBolaRobo(int id);

    /**
        Nesse método iremos calcular um alvo para o robo ficar marcando o outro robo no nosso campo, sem passar para o campo adv.
        @param int idRoboParaMarcar Id do robô adv que teremos que marcar
        @return Ponto Alvo para o robô se posicionar.
    */
    Ponto calcularAlvoMarcarRoboForaAlcanceCampoAdv();

    /**
        Nesse método iremos calcular um alvo para o robo se posicionar pra que marque o robo adv sem que fique
        a menos de 500 mm da bola, para não levar cartão.
        @param int idRoboParaMarcar Id do robô adv que teremos que marcar
        @return Ponto Alvo para o robô se posicionar.
    */
    Ponto calcularAlvoMarcarRoboForaAlcanceBola();
};

#endif // MARCARSAIDABOLA_H
