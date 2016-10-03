#ifndef MANTEMPOSICAO_H
#define MANTEMPOSICAO_H

#include<Skill.h>

/**
    Skill que mantem o robo parado , exatamente parado. Esta skill faz isso fazendo o robo ir para posicao onde ele está na orientação onde ele está.
*/
class MantemPosicao : public Skill
{
public:
    MantemPosicao();
    ~MantemPosicao();

    void executar(Agente* _agente);
    void imprimeNome();
};

#endif // MANTEMPOSICAO_H
