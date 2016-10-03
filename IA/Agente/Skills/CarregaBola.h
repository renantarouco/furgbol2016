#ifndef CARREGABOLA_H
#define CARREGABOLA_H

#include<Skill.h>

/**
    Skill onde o robo, com drible ligado leva a bola para um alvo especificado.
*/
class CarregaBola : public Skill
{
public:
    CarregaBola();
    ~CarregaBola();

    void executar(Agente * _agente);
    void imprimeNome();
};

#endif // CARREGABOLA_H
