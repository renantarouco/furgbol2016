#ifndef GIRA_H
#define GIRA_H

#include<MaquinaSkills.h>
#include<Tatica.h>

/// @todo ajeitar
class Gira :public Tatica{
public:
    Gira();
    ~Gira();

    void executar(Agente* agente);

    /**
        Função que verifica quando a tática foi completada.
        Como essa tática não é ativa, então ela não possui termino só irá terminar quando a tática ativa terminar
        @param id Id do robô que está executando a tática
        @return True se tiver terminado, false senão tiver terminado
    */
    bool verificarTermino(int id);float getLimiarAvaliacao();

    /**
        Função que avalia o quão bom o robô é para executar essa tática
        Todos os robôs irão possuir o mesmo valor de avaliação para essa tática
        @param id Id do robô que será avaliado
        @return Valor padrão para todos os robôs
    */
    float avaliacaoEscolhaRobo(int id);

    /**
        Função que pega o melhor robô do conjunto de robos disponiveis.
        Iremos pegar o primeiro, pois nessa tática qualquer robo está bom para executar ela
        @param _ids Ids dos robos disponiveis para executar a tatica
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
 string getNome();

    void imprimirNome();
};


#endif // GIRA_H
