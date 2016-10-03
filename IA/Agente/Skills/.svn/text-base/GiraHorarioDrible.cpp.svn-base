#include "GiraHorarioDrible.h"
#include "Sistema.h"

GiraHorarioDrible::GiraHorarioDrible()
{
    tipo = Skill::GIRA_HORARIO_DRIBLE;

}

void GiraHorarioDrible::executar(Agente *_agente)
{
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill(string("GIRA_HORARIO_DRIBLE"));

    Comando comando = robo->getComando();
    comando.setDrible(true);
    comando.setDirecaoDriblador(HORARIO);
    comando.setTipoChute(Comando::SEM_CHUTE);
//    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoPosicaoParaAlvo(Sistema::modeloMundo.getCentroGolAdv(), robo->getPosicao()));

//    Vetor alvo(Sistema::modeloMundo.getCentroGolAdv() - robo->getPosicao());
    Vetor alvo(Ponto(0.f,0.f) - robo->getPosicao());
    alvo = alvo/ sqrt(alvo.squared_length());

//    comando.setAlvo(Sistema::modeloMundo.getBola()->getPosicao());
    comando.setAlvo(robo->getPosicao() + alvo * 200.f);
//    comando.setAlvoFinal(Sistema::modeloMundo.getBola()->getPosicao());
    comando.setAlvoFinal(robo->getPosicao() + alvo * 200.f);

    comando.setOrientacao(robo->getOrientacao() + 0.3f);

    robo->setComando(comando);
}

void GiraHorarioDrible::imprimeNome()
{
    cout << "GiraHorarioDrible" << endl;
}
