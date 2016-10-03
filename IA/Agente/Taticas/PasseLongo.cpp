#include "PasseLongo.h"
#include <Sistema.h>

PasseLongo::PasseLongo(){

}

PasseLongo::~PasseLongo(){

}

void PasseLongo::executar(Agente* agente){
//        agente->ativarNavegador();

//    avaliadorRobo.setId(id);

//    Robo* roboReceberaPasse = Sistema::modeloMundo.getOutrosRobosComTatica(id, "ReceberPasse")[0];

//    vector<MaquinaSkills::Parametro> parametros;
//    parametros.push_back(Sistema::modeloMundo.getRoboEq(id)->isTemChute() ? MaquinaSkills::TEM_CHUTE : MaquinaSkills::SEM_CHUTE);

//    /// Calculando o alvo de aproximacao que o robo ira se posicionar para ir para o alvo corretamente
//    Ponto alvoAprox = calcAlvoAproximacao(id, roboReceberaPasse->getPosicao());

//    /// Verificando se iremos chutar em algum outro lugar senao o gol adversario
//    float anguloChute = Sistema::avaliador.calcularAnguloAbertura(roboReceberaPasse->getTaticaCorrente()->getParamPonto()[0], roboReceberaPasse->getTaticaCorrente()->getParamFloat()[0]);

//    return new MoveBola(alvoAprox, roboReceberaPasse->getTaticaCorrente()->getParamPonto()[0], id, parametros, anguloChute);
}

bool PasseLongo::verificarTermino(int id){

    /// se a distancia da posicao atual com a posicao anterior for maior do que 5 cm quer dizer que a bola foi passada
    if(squared_distance(Sistema::modeloMundo.getBola()->getPosicao(), Sistema::modeloMundo.getBola()->getPosicaoAnterior()) > 500.0*500.0){
        cout << "bola passada :)" << endl;
        return true;
    }

    return false;
}

float PasseLongo::avaliacaoEscolhaRobo(int id){

    /// Pegando a posição da bola para compararmos com as posiçoes dos outros robôs
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância entre os dois pontos
    return squared_distance(posBola, posRobo);
}

int PasseLongo::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE PASSE CURTO" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô que está mais perto da bola. ****/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Verificando se o robô que iremos analisar pode tocar na bola
        if(Sistema::modeloMundo.getRoboEq(_ids[i])->isTocarBola()){

            /// Calculando a distância do robô à região.
            float distRoboBola = avaliacaoEscolhaRobo(_ids[i]);

            /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
            if(menorDistRoboRegiao > distRoboBola){
                idRoboMaisPerto = _ids[i];                  /// Pegando o id do robô mais perto da região.
                posVetorRobo = i;                           /// Pegando o indice do vetor para removermos depois o id do robo
                menorDistRoboRegiao = distRoboBola; /// Setando a nova distância
            }
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " PASSE_CURTO: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

bool PasseLongo::isAtiva(){
    return true;
}

Tatica * PasseLongo::getNovaInstancia(){
    return new PasseLongo;
}

void PasseLongo::imprimirNome(){
    cout << "PasseLongo" << endl;
}

string PasseLongo::getNome()
{
    return "PasseLong";
}

float PasseLongo::getLimiarAvaliacao()
{
    return 0.0;
}
