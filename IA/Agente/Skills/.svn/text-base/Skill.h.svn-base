#ifndef SKILL_H
#define SKILL_H

#include <AvaliadorRobo.h>
#include <Comando.h>

class Agente;

/**
   A skill é uma habilidade baixo nível de um robo que gera um comando.
   Ela é reativa , devendo chamar o modulo avaliador na parte de "percepção() " para decidir se transita ou se gera um comando.
 */
class Skill
{
public:
    enum TipoSkill{
        CHUTA = 0,
        CARREGA_BOLA = 1,
        VAI_PARA_BOLA = 2,
        VIRA_PARA_BOLA = 3,
        VAI_PARA_ALVO = 4,
        MANTEM_POSICAO = 5,
        PASSA_POR_TRAS = 6,
        GIRA_EIXO = 7,
        GIRA_HORARIO = 8,
        GIRA_ANTI_HORARIO = 9,
        EMPURRA_BOLA = 10,
        VIRA_PARA_ALVO = 11,
        GIRA_HORARIO_DRIBLE = 12,
        CHUTA_ALTO = 13,
        DOMINA_BOLA = 14
    };

protected:
    TipoSkill tipo;

public:
    Skill();
    virtual ~Skill() = 0;
    virtual void executar(Agente * _agente) = 0; /// funcao que analisa o cenário para idenficar um alvon e a necessidade de ativar os diversos atuadores.
    virtual void imprimeNome() = 0;
    TipoSkill getTipo();
};
#endif
