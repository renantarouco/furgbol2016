#include "DominaBola.h"
#include "Sistema.h"
DominaBola::DominaBola()
{
    tipo = Skill::DOMINA_BOLA;
}

void DominaBola::executar(Agente *_agente)
{
    /// variáveis auxiliares
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// setando o comando que o robo irá executars
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill("DOMINA_BOLA");
    Comando comando = robo->getComando();
    comando.setAlvo(vector<Ponto>(1, posBola));

    comando.setDrible(true);
    comando.setTipoChute(Comando::SEM_CHUTE);
    //    comando.setOrientacao(Sistema::avaliador.calcularOrientacaoAlvoBola(robo->getPosicao()));

    float orientacao_final = Sistema::avaliador.calcularOrientacaoPosicaoParaAlvo(robo->getPosicao(),comando.getAlvoChute());
    comando.setOrientacao(orientacao_final);

    robo->setComando(comando);
}

void DominaBola::imprimeNome()
{
    cout << "DominaBola" << endl;
}
