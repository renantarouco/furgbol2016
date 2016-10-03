#include "MantemPosicao.h"
#include <Sistema.h>

MantemPosicao::MantemPosicao(){
    tipo=Skill::MANTEM_POSICAO;
}

MantemPosicao::~MantemPosicao(){
}

void MantemPosicao::executar(Agente * _agente){
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("MANTEM_POSICAO");

    Comando comando = Sistema::modeloMundo.getRoboEq(_agente->getId())->getComando();
    comando.setOrientacao(robo->getOrientacao());
    comando.setAlvoFinal(robo->getPosicao());
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(comando.getAlvoFinal());
    comando.setAlvo(alvoPath);

    Sistema::modeloMundo.getRoboEq(_agente->getId())->setComando(comando);
}

void MantemPosicao::imprimeNome()
{
    cout << "MantemPosicao" << endl;
}
