#ifndef DOMINABOLA_H
#define DOMINABOLA_H


#include <Skill.h>

class DominaBola : public Skill
{
public:
    DominaBola();
    void executar(Agente * _agente);
    void imprimeNome();

};

#endif // DOMINABOLA_H
