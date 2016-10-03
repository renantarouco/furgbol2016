#ifndef GIRAANTIHORARIO_H
#define GIRAANTIHORARIO_H

#include <Skill.h>

/**
    Skill que faz o robo girar em um sentido anti horário em relação a um eixo localizado em um ponto
*/
class GiraAntiHorario : public Skill
{
public:
    GiraAntiHorario();
    ~GiraAntiHorario();

    void executar(Agente * _agente); /// funcao que analisa o cenário para idenficar um alvon e a necessidade de ativar os diversos atuadores.
    void imprimeNome();
};

#endif // GIRAANTIHORARIO_H
