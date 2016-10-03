#ifndef EMPURRABOLA_H
#define EMPURRABOLA_H

#include<Skill.h>

/**
    Skill que faz o robo dar um "sprint", uma rapida corrida e uma batida na bola.
    Esta skill depende de uma nova versão do montador para poder setar uma alta velocidade em um curto espaço de tempo
*/
class EmpurraBola : public Skill
{
public:
    EmpurraBola();
    ~EmpurraBola();

    void executar(Agente * _agente);
    void imprimeNome();
};

#endif // EMPURRABOLA_H
