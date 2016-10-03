#ifndef CHUTAALTO_H
#define CHUTAALTO_H

#include <Skill.h>

/**
    Skill que simplesmente ativa os atuadores para um chute alto
*/
class ChutaAlto : public Skill
{
public:
    ChutaAlto();
    ~ChutaAlto();

    void executar(Agente * _agente); /// funcao que analisa o cenário para idenficar um alvon e a necessidade de ativar os diversos atuadores.
    void imprimeNome();
};

#endif // CHUTAALTO_H
