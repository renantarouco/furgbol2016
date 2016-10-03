#include "CarregaBola.h"
#include <Sistema.h>

CarregaBola::CarregaBola(){
    tipo = Skill::CARREGA_BOLA;
}

CarregaBola::~CarregaBola(){

}

void CarregaBola::executar(Agente* _agente){

    /// direção virado para bola
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("CARREGA_BOLA");

    Comando comando = robo->getComando();

    comando.setDrible(false);
    comando.setTipoChute(Comando::CHUTE_BAIXO);
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoAlvoBola(robo->getPosicao()));

    comando.setAlvo(_agente->calcAlvosFromPathPlanning(comando.getAlvoFinal()));

    //    comando.setVelDeslocamento(Avaliador::VEL_CARREGA_BOLA); /// setando a velocidadde de deslocamento desejada
    //    comando.setVelAproximacao(0.0);

    //    comando.setOrientacao(robo->getOrientacao());

    //    if(_agente->isNavegadorAtivo()){
    //        if(_agente->isNavegadorPronto() || Sistema::modeloMundo.getRobo(_agente->getId())->isAlvoMudou()){
    //            comando.setAlvo(_agente->geraAlvoPathPlanning(comando.getAlvo()));
    //        }
    //    }

    robo->setComando(comando);
}

void CarregaBola::imprimeNome(){
    cout << "CarregaBola" << endl;
}
