#include "GiraAntiHorario.h"
#include <Sistema.h>

GiraAntiHorario::GiraAntiHorario(){
    tipo = Skill::GIRA_ANTI_HORARIO;
}

GiraAntiHorario::~GiraAntiHorario(){
}

void GiraAntiHorario::executar(Agente * _agente)
{

//    imprimeNome();

    // DIRECAO BOLA
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("GIRA_ANTI_HORARIO");

    /// Calculando o novo alvo que o robô irá para poder conseguir girar ao redor do alvo
    Ponto alvo = Sistema::avaliador.calcularAlvoGirar(Sistema::modeloMundo.getBola()->getPosicao(), false, _agente->getId());

    Comando comando = robo->getComando();
    comando.setAlvo(alvo);
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoAlvoBola(comando.getAlvoFinal()));

//    const vector<Ponto> &alvoPath = _agente->geraAlvosPathPlanning(comando.getAlvoFinal());
//    comando.setAlvo(comando.getAlvoChute());

    robo->setComando(comando);
}

void GiraAntiHorario::imprimeNome(){
    cout << " GiraAntiHorario " << endl;
}
