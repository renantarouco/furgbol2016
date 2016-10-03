#include "VaiParaBola.h"
#include <Sistema.h>

VaiParaBola::VaiParaBola()
{
    tipo=Skill::VAI_PARA_BOLA;
}

VaiParaBola::~VaiParaBola(){
}

void VaiParaBola::executar(Agente * _agente)
{
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("VAI_PARA_BOLA");

    Comando comando = robo->getComando();

    //    Ponto alvoPath;
    //    if(_agente->isNavegadorAtivo() &&  _agente->isNavegadorPronto()){
    //        cout << " Chamou o path planning " << endl;
    //        alvoPath = _agente->geraAlvoPathPlanning(comando.getAlvoFinal());
    //        cout << "Alvo " << alvoPath << endl;
    //    }
    //    Ponto alvo = alvoPath;

    Ponto alvo = Sistema::modeloMundo.getBola()->getPosicao();

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(alvo);
    comando.setAlvo(alvoPath);
    //    comando.setAlvo(alvo);

    //comando.setDirecao(Sistema::avaliadorRobo[_agente->getId()].calculaDirecaoRoboViradoBola());
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);

    comando.setAlvoFinal(alvo);
    comando.setOrientacao(robo->getOrientacao());

    robo->setComando(comando);
    //return Comando(Sistema::modeloMundo.getBola()->getPosicao(),0,false,false,Comando::SEM_CHUTE);
}

void VaiParaBola::imprimeNome(){
    cout << "VaiParaBola" << endl;
}


