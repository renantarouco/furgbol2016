#include "VaiParaAlvo.h"
#include <Sistema.h>

VaiParaAlvo::VaiParaAlvo(){
    tipo = Skill::VAI_PARA_ALVO;
}

VaiParaAlvo::~VaiParaAlvo(){
}

void VaiParaAlvo::executar(Agente* _agente){

    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("VAI_PARA_ALVO");
    Comando comando = robo->getComando();

//    imprimeNome();

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(comando.getAlvoFinal());
    comando.setAlvo(alvoPath);

//    cout << "Alvo do path " << alvoPath << endl;
//    cout << "Alvo final " << comando.getAlvoFinal() << endl;

    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoAlvoBola(comando.getAlvoFinal()));
//    comando.setOrientacao(robo->getOrientacao());

    //    imprimeNome();

    robo->setComando(comando);
}

void VaiParaAlvo::imprimeNome()
{
    cout << "VaiParaAlvo" << endl;
}
