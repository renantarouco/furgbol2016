#include "Halt.h"
#include "Sistema.h"

Halt::Halt(){
}

Halt::~Halt(){
}

void Halt::executar(Agente* agente){

    int id = agente->getId();

    /// calculando o alvo que o robo irá
    Ponto alvo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// setando os dados na maquina
    vector<MaquinaSkills::Parametro> parametros(2);
    parametros[0] = MaquinaSkills::FICAR_PARADO;
    parametros[1] = MaquinaSkills::NAO_GIRA;
    maqDefendePonto.setDados(alvo, parametros);

    /// executando a maquina
    maqDefendePonto.executar(agente);
}

bool Halt::verificarTermino(int id){
    id = 0;
    return id;
}

bool Halt::isAtiva(){
    return false;
}

float Halt::avaliacaoEscolhaRobo(int id){
    id = 0;
    return id;
}

int Halt::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE HALT" << endl;
        return -1;
    }

    int idRobo = _ids[0]; /// Id do robô que iremos usar
    _ids.erase(_ids.begin()); /// Apaga o ID por que ele já foi selecionado
    return idRobo;
}

Tatica * Halt::getNovaInstancia(){
    return new Halt;
}

string Halt::getNome()
{
    return "Halt";
}

void Halt::imprimirNome(){
    cout << "Halt" << endl;
}

float Halt::getLimiarAvaliacao()
{
    return 0.0;
}
