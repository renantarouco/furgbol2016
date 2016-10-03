#include "GiraEixo.h"
#include<Sistema.h>

GiraEixo::GiraEixo()
{
    tipo = Skill::GIRA_EIXO;
}

GiraEixo::~GiraEixo()
{
}

void GiraEixo::executar(Agente * _agente)
{
    /// direção virado para bola
    Robo* robo = Sistema::modeloMundo.getRoboEq(_agente->getId());
    robo->setNomeSkill(string("GIRA_EIXO"));

    Comando comando = robo->getComando();
    comando.setAlvoFinal(robo->getPosicao());
    comando.setOrientacao(((rand()%360)*M_PI)/180);
    comando.setDrible(false);
    comando.setTipoChute(Comando::SEM_CHUTE);

    const vector<Ponto> &alvoPath = _agente->calcAlvosFromPathPlanning(comando.getAlvoFinal());
    comando.setAlvo(alvoPath);

    Sistema::modeloMundo.getRoboEq(_agente->getId())->setComando(comando);

}
void GiraEixo::imprimeNome()
{
    cout <<"Gira no EIxo" << endl;
}

