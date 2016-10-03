#ifndef MARCAR_H
#define MARCAR_H

#include "Tatica.h"
#include "DefendePonto.h"

/**
    Tatica responsável por fazer o robô marcar um robô que está próximo do nosso gol ou que receberá um passe.
*/
class Marcar : public Tatica
{
private:
    int idAdvMarcar; ///< Id do robô que estamos marcando
    float scoreAdvReceberaPasse; ///< Score do robô que estamos marcando para interceptar o passe
    DefendePonto maqDefendePonto;

    vector<int> getRobosAdvEstaoSendoMarcados(int id);

    /**
        Nesse método iremos calcular um alvo para o robô se pocisionar fazendo com que o robô adv não consiga passar a bola
        para o outro robô adv que o robô irá marcar.
        @param idRoboAdvMarcar Id do Robô que iremos marcar
        @return Ponto Alvo que iremos calcular para o robô se posicionar
    */
    Ponto calcularAlvoMarcarRoboReceberaPasse(int idRoboAdvMarcar);

    /**
        Função que calcula o alvo que o robô terá que ir para poder marcar o robô selecionado
        @param id Id do robô que irá marcar
        @return Alvo para aonde o robô irá para poder marcar
    */
    Ponto calcularAlvoRoboAdvParaMarcar(int id);

    /**
        Nesse método iremos calcular um alvo para o robô se posicionar com que impessa que o outro robô tenha uma
        interseccao com o nosso gol.
        @param id Id do robo que irá marcar
        @return Ponto Alvo para o robô se posicionar.
    */
    Ponto calcularAlvoMarcarRoboContraChute(int id);

    /**
        Nesse método iremos pegar o id do robô adv que está melhor posicionado para receber um passe.
        @param id Id do robô adv que iremos marcar.
        @param scorePasse Score do robô que estamos marcando
        @return Id do robo adv que sera marcado
    */
    void getIdAdvReceberaPasse(int id);

public:
    Marcar();
    ~Marcar();

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
        Função que avalia o quão bom o robô é para executar esta tática.
        Iremos avaliar primeiro identificando qual robô adv será marcado e depois calculando a distância
        desse robô que queremos avaliar ao robô adv que será marcado
        @param id Id do robô que será avaliado
        @return Distância do robô da equipe ao robô que será marcado
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que escolhe o melhor robô para marcar o robô que escolhemos para marcar.
        Iremos pegar o robô que está mais perto do robô adv que será marcado
        @param _ids Ids dos robôs que estão disponiveis para executar a tática
        @return Id do robô que foi escolhido
    */
    int getIdMelhorRobo(vector<int>& _ids);

    /**
        Função que retorna o id do robô adv que será marcado
        @return Id do robô adv escolhido para ser marcado
    */
    int getIdAdvMarcando();

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
#endif // MARCAR_H
