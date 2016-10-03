#include "GiraHorario.h"
#include <Sistema.h>

GiraHorario::GiraHorario() {
    tipo = Skill::GIRA_HORARIO;
}

GiraHorario::~GiraHorario() {
}

void GiraHorario::executar(Agente * _agente){

    // DIRECAO BOLA
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill(string("GIRA_HORARIO"));

    /// Calculando o novo alvo que o robô irá para poder conseguir girar ao redor do alvo
    Ponto alvo = Sistema::avaliador.calcularAlvoGirar(Sistema::modeloMundo.getBola()->getPosicao(), true, _agente->getId());

    /// Calculando um novo alvo de aproximacao
    Comando comando = robo->getComando();
    comando.setAlvo(alvo);
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoAlvoBola(comando.getAlvoFinal()));

//    const vector<Ponto> &alvoPath = _agente->geraAlvosPathPlanningcomando.getAlvoFinal());
//    comando.setAlvo(comando.getAlvoChute());

    robo->setComando(comando);
}

void GiraHorario::imprimeNome()
{
    cout << " GiraHorario " << endl;
}
