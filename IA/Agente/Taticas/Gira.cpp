#include "Gira.h"
#include<DefendePonto.h>
#include <Sistema.h>

Gira::Gira(){
}

Gira::~Gira(){
}

void Gira::executar(Agente* agente){
//    agente->ativarNavegador();
//    /// Pegando a própria posição do robô que irá executar o Gira
//    Ponto alvo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

//    /// Criando a maquina defende ponto para ele ficar parado na sua posição
//    return new DefendePonto(alvo, id, vector<MaquinaSkills::Parametro>(1, MaquinaSkills::GIRA_EIXO));
}

bool Gira::verificarTermino(int id){
    id = 0;
    return id;
}

float Gira::avaliacaoEscolhaRobo(int id){
    id = 0;
    return id;
}

int Gira::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE Gira" << endl;
        return -1;
    }

    int idRobo = _ids[0]; /// Id do robô que iremos usar
    _ids.erase(_ids.begin()); /// Apaga o ID por que ele já foi selecionado

    return idRobo;
}

bool Gira::isAtiva(){
    return false;
}

Tatica * Gira::getNovaInstancia(){
    return new Gira;
}

string Gira::getNome()
{
    return "Gira";
}

void Gira::imprimirNome(){
    cout << "Gira" << endl;
}
float Gira::getLimiarAvaliacao()
{
    return 0.0;
}

