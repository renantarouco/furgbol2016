#include "EmpurraBola.h"
#include <Sistema.h>

EmpurraBola::EmpurraBola(){
    tipo = Skill::EMPURRA_BOLA;
}

EmpurraBola::~EmpurraBola(){
}

void EmpurraBola::executar(Agente * _agente)
{
    /// Variáveis auxiliares
    Ponto centroGolAdv = Sistema::modeloMundo.getCampo()->getAreaAdv()->getCentro();
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());

    /// setando o nome da Skill que está sendo executada
    robo->setNomeSkill("EMPURRA_BOLA");
    Comando comando = robo->getComando();

    /// Alvo do robo sera a bola
    comando.setAlvoFinal(Sistema::modeloMundo.getBola()->getPosicao());
    comando.setDrible(true);
    comando.setDirecaoDriblador(HORARIO);
    comando.setTipoChute(Comando::SEM_CHUTE);

    /// O robo vira para o gol
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoPosicaoParaAlvo(robo->getPosicao(), centroGolAdv));

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(comando.getAlvoFinal());
    comando.setAlvo(alvoPath);

    robo->setComando(comando);
}

void EmpurraBola::imprimeNome()
{
    cout << "EmpurraBola" << endl;
}
