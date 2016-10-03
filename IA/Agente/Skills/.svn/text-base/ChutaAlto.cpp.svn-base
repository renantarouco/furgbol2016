#include "ChutaAlto.h"
#include <Sistema.h>
#include <Geometria.h>

ChutaAlto::ChutaAlto()
{
    tipo=Skill::CHUTA_ALTO;
}

ChutaAlto::~ChutaAlto(){

}

void ChutaAlto::executar(Agente *_agente)
{
    /// direção virado para bola
    /// variação de 0 a pi e -pi a 0;
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("CHUTA_ALTO");

    Comando comando = Sistema::modeloMundo.getRoboEq(_agente->getId())->getComando();

    //    /// Verificando a nova posicao que a bola foi chutada
    //    if(squared_distance(Sistema::modeloMundo.getBola()->getPosChutada(), Sistema::modeloMundo.getBola()->getPosicao()) > ConfigAvaliador::TOL_MESMO_ALVO*ConfigAvaliador::TOL_MESMO_ALVO){
    //        Sistema::modeloMundo.getBola()->setPosChutada(Sistema::modeloMundo.getBola()->getPosicao());
    //    }

    /// alvo do robo que ira chutar e a bola
    //    comando.setAlvoFinal(Sistema::modeloMundo.getBola()->getPosicao());
    //    comando.setDrible(true);

    //    if(robo->isTemChute()){
    //        //        comando.setDirecaoDriblador(ANTI_HORARIO);
    //    }else{
    //        //        comando.setDirecaoDriblador(HORARIO);
    //    }

    comando.setTipoChute(Comando::CHUTE_ALTO);
    comando.setDrible(false);
    comando.setAlvoFinal(Sistema::modeloMundo.getBola()->getPosicao());
    float orientacao_final = Sistema::avaliador.calcularOrientacaoPosicaoParaAlvo(robo->getPosicao(),comando.getAlvoChute());
    comando.setOrientacao(orientacao_final);

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(comando.getAlvoFinal());
    comando.setAlvo(alvoPath);

    Sistema::modeloMundo.getRoboEq(_agente->getId())->setComando(comando);
}

void ChutaAlto::imprimeNome()
{
    cout<<"Chuta alto"<<endl;
}
