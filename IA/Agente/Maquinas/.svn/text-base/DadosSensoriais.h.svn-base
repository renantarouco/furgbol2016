#ifndef DADOSSENSORIAIS_H
#define DADOSSENSORIAIS_H

#include "Definitions.h"

/**
    São os dados coletados que propiciam a ativação de uma skill ou não
*/
class DadosSensoriais
{
public:
    DadosSensoriais();

    friend ostream& operator<<(ostream& os, const DadosSensoriais& a);
    friend class MaquinaSkills;
    friend class MoveBola;
    friend class DefendePonto;
    friend class Percepcao;

private:
    bool deFrenteParaBola; ///< Indica se o robô está ou não de frente pra bola
    bool deFrenteParaBolaDrible; ///< Indica se o robô está ou não de frente pra bola para usar o driblador
    bool noAlvoMarcado; ///< Indica se o robô está ou não no Alvo em que é pra estar
    bool bolaPertoParaChute; ///< Indica se a bola está perto o suficiente do robô para poder ser chutada
    bool dentroRaioAprox; ///< Indica se o robô está no alvo aproximado do Alvo
    bool comAnguloDeChute; ///< Indica se o robô possui um bom angulo de abertura para chutar a bola
    bool alvoMudou; ///< Indica se o alvo do robô foi alterado de uma iteração para outra
    bool carregarBola; ///< Indica se o robô pode carregar a bola ou não
    bool girarHorario; ///< Indica se o robô deve girar no sentido horario
//    bool girarAntiHorario; ///< Indica se o robô deve girar no sentido anti-horario
    bool manterPosicao; ///< Indica se o robô irá manter a posição atual em que ele se encontra
    bool bolaMoveu; /// < Utiliza a posicao anterior da bola para ver se a bola se moveu o suficiente para tentar uma nova aproximação
    bool alvoGirarIgualPosRobo; /// Indica se o alvo que o robo ira girar e igual ao alvo atual que ele esta se for entao o robo ira chutar ou ira empurrar a bola
    bool bolaSaindoPelaLateral; /// Indica quando a bola esta quase saindo pela lateral do campo
};

#endif // DADOSSENSORIAIS_H
