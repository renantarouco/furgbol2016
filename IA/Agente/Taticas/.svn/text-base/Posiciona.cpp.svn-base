#include "Posiciona.h"
#include <Sistema.h>

Posiciona::Posiciona(){
}

Posiciona::~Posiciona(){
}

void Posiciona::executar(Agente* agente){

    int id = agente->getId();
    agente->ativarObstaculosEq();
    agente->addAreaEqObstaculo();

    /// pegando a propria posicao caso não tenha nenhum parametro setado na jogada
    Ponto alvo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    try{
        alvo = paramPonto[0]; /// Pegando o ponto aonde o robô irá se posicionar
    }catch(exception e){
        cout << "Os parâmetros não foram setados na Tática de Posiciona." << endl << e.what() << endl;
    }

    /// setando os dados na maquina
    maqDefendePonto.setDados(alvo);

    /// executando a maquina
    maqDefendePonto.executar(agente);
}

bool Posiciona::verificarTermino(int id){
    id = 0;
    return id;
}

float Posiciona::avaliacaoEscolhaRobo(int id){

    try{
        Ponto ponto = paramPonto.at(0); /// Pegando o ponto que iremos verificar o robô mais perto dele.

        /// Pegando a posição do robô que iremos analisar
        Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

        /// Calculando a distância do robô ao ponto que queremos posicionar ele
        return squared_distance(posRobo, ponto);

    }catch(exception e){
        cout << "Os parâmetros não foram setados na Tática de Posiciona." << endl << e.what() << endl;
    }

    return 0.0;
}

int Posiciona::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE POSICIONA" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô que está mais perto do ponto que iremos colocar ele. ****/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Calculando a distância do robô à região.
        float distRoboPonto = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
        if(distRoboPonto < menorDistRoboRegiao){
            idRoboMaisPerto = _ids[i];           /// Pegando o id do robô mais perto da região.
            posVetorRobo = i;                    /// Pegando o indice do vetor para removermos depois o id do robo
            menorDistRoboRegiao = distRoboPonto; /// Setando a nova distância
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " POSICIONA: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

bool Posiciona::isAtiva(){
    return false;
}

Tatica * Posiciona::getNovaInstancia(){
    return new Posiciona;
}

void Posiciona::imprimirNome(){
    cout << "Posiciona" << endl;
}

string Posiciona::getNome()
{
    return "Posiciona";
}

float Posiciona::getLimiarAvaliacao()
{
    return 0.0;
}

