#include "ViraParaAlvo.h"
#include "Robo.h"
#include "Sistema.h"

ViraParaAlvo::ViraParaAlvo()
{
    tipo = Skill::VIRA_PARA_BOLA;
}

void ViraParaAlvo::setAlvoParaVirar(const Ponto &alvo)
{

    m_alvo = alvo;

}

void ViraParaAlvo::executar(Agente *_agente)
{
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill(string("VIRA_PARA_ALVO"));

    Comando comando = robo->getComando();
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);
    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoPosicaoParaAlvo(robo->getPosicao(),m_alvo));

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(comando.getAlvoFinal());
    comando.setAlvo(alvoPath);

    robo->setComando(comando);
}

void ViraParaAlvo::imprimeNome()
{
    cout << "ViraParaAlvo" << endl;
}
