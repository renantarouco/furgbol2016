#include "ViraParaBola.h"
#include <Sistema.h>

ViraParaBola::ViraParaBola()
{
    tipo=Skill::VIRA_PARA_BOLA;
}

ViraParaBola::~ViraParaBola(){
}

void ViraParaBola::executar(Agente * _agente)
{
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill(string("VIRA_PARA_BOLA"));

    Comando comando = robo->getComando();
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoAlvoBola(robo->getPosicao()));

//    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(robo->getPosicao());
//    comando.setAlvo(alvoPath);
//    comando.setAlvoFinal(Sistema::modeloMundo.getBola()->getPosicao());
    robo->setComando(comando);
}

void ViraParaBola::imprimeNome()
{
    cout << "ViraParaBola" << endl;
}
