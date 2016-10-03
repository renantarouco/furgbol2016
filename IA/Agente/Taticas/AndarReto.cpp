#include "AndarReto.h"
#include <Sistema.h>

AndarReto::AndarReto()
{
    alvoPosInicial = true;
}

void AndarReto::executar(Agente* agente)
{
//    int id = agente->getId();
//    avaliadorRobo.setId(id);

//    Ponto posInicial;
//    Ponto posFinal;
//    try{
//        posInicial = paramPonto[0]; /// Pegando o ponto aonde o robô irá se posicionar
//        posFinal = paramPonto[1]; /// Pegando o ponto aonde o robô irá se posicionar
////        cout << posFinal.x() << " " << posFinal.y() <<endl;
//    }catch(exception e){
//        cout << "Os parâmetros não foram setados na Tática de Posiciona." << endl << e.what() << endl;
//        abort();
//    }

//    Ponto alvo;
//    if(squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), posInicial) <= ConfigAvaliador::TOL_PERTENCE_ALVO*ConfigAvaliador::TOL_PERTENCE_ALVO && alvoPosInicial){
//        alvo = posFinal;
//        alvoPosInicial =false;
//    }else if(squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), posFinal) <= ConfigAvaliador::TOL_PERTENCE_ALVO*ConfigAvaliador::TOL_PERTENCE_ALVO && !alvoPosInicial){
//        alvo = posInicial;
//        alvoPosInicial=true;
//    }else if(alvoPosInicial){
//        alvo = posInicial;
//    }else if(!alvoPosInicial){
//        alvo = posFinal;
//    }

//    return new DefendePonto(alvo, id);
}

bool AndarReto::verificarTermino(int id)
{
//    id = 0;
//    return id;
}

float AndarReto::avaliacaoEscolhaRobo(int id)
{
//    Ponto ponto;
//    try{
//        ponto = paramPonto.at(0); /// Pegando o ponto que iremos verificar o robô mais perto dele.
//    }catch(exception e){
//        cout << "Os parâmetros não foram setados na Tática de Posiciona." << endl << e.what() << endl;
//        abort();
//    }

//    /// Pegando a posição do robô que iremos analisar
//    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

//    /// Calculando a distância do robô ao ponto que queremos posicionar ele
//    return squared_distance(posRobo, ponto);
}

int AndarReto::getIdMelhorRobo(vector<int>& _ids)
{
//    /// Se não tiver ids é porque deu erro.
//    if(_ids.size() == 0) {
//        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE POSICIONA" << endl;
//        return -1;
//    }

//    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
//    if(_ids.size() == 1){
//        int idRestante = _ids[0];
//        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
//        return idRestante;
//    }

//    /** O melhor robô para essa tática, é o robô que está mais perto do ponto que iremos colocar ele. ****/

//    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
//    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
//    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

//    for(unsigned int i = 0; i < _ids.size(); i++){

//        /// Calculando a distância do robô à região.
//        float distRoboPonto = avaliacaoEscolhaRobo(_ids[i]);

//        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
//        if(distRoboPonto < menorDistRoboRegiao){
//            idRoboMaisPerto = _ids[i];           /// Pegando o id do robô mais perto da região.
//            posVetorRobo = i;                    /// Pegando o indice do vetor para removermos depois o id do robo
//            menorDistRoboRegiao = distRoboPonto; /// Setando a nova distância
//        }
//    }

//    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
//    if(idRoboMaisPerto == -1) {
//        cout << " ANDAR_RETO: AVISO ROBO MAIS PERTO É -1" << endl;
//        return -1;
//    }

//    /// Apagando o id do robô que selecionamos para essa tática.
//    _ids.erase(_ids.begin() + posVetorRobo);

//    return idRoboMaisPerto;
}

bool AndarReto::isAtiva()
{
    return false;
}

Tatica *AndarReto::getNovaInstancia()
{
    return new AndarReto;
}

void AndarReto::imprimirNome()
{
    cout << "Andar Reto" << endl;
}

float AndarReto::getLimiarAvaliacao()
{
    return 0.0;
}

string AndarReto::getNome()
{
    return "AndarReto";
}
