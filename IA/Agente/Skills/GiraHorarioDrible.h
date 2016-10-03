#ifndef GIRAHORARIODRIBLE_H
#define GIRAHORARIODRIBLE_H

#include "Skill.h"


class GiraHorarioDrible : public Skill
{
public:
    GiraHorarioDrible();

    void executar(Agente *_agente);

    void imprimeNome();

};

#endif // GIRAHORARIODRIBLE_H
