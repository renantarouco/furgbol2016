#include "ReceberPasse.h"
#include <Sistema.h>

ReceberPasse::ReceberPasse()
{
}

void ReceberPasse::executar(Agente* agente)
{
//        agente->ativarNavegador();
//    avaliadorRobo.setId(id);

//    Ponto alvo = paramPonto.at(0); /// pegando o alvo para se posicionar definido no arquivo da jogada
//    float raio=paramFloat.at(0);
//    Circulo regiao(alvo,raio*raio);

////    /// pegando reta direcao bola
////    Reta retaDirecaoBola = Sistema::avaliador.calcularRetaDirecaoBola();
////    Bola* bola = Sistema::modeloMundo.getBola();

////    /// calculando reta para posicionar o robo para receber o passe
////    Reta retaBolaAlvo(bola->getPosicao(), alvo);
////    Reta retaPosicionar = retaBolaAlvo.perpendicular(alvo);

////    /// caso a reta direcao bola intercepte o circulo entao iremos fazer o robo ir para aonde esta interceptando
////    vector<Ponto> pontos = interseccaoRetaCirculo(retaDirecaoBola, regiao);
////    if(pontos.size() > 1){

////        /// calculando as distancias para pegar o mais perto da bola
////        float dist0 = squared_distance(pontos[0], bola->getPosicao());
////        float dist1 = squared_distance(pontos[1], bola->getPosicao());
////        if(dist0 > dist1){
////            alvo = pontos[1];
////        }else{
////            alvo = pontos[0];
////        }
////    }else{
////        Robo* roboPasse = Sistema::modeloMundo.getOutrosRobosComTatica(id, "PasseLongo")[0];
////        Reta retaRoboBola(roboPasse->getPosicao(), bola->getPosicao());
////    }

//    /// Criando a maquina para posicionar o robô para receber o passe curto do outro robô.
//    return new DefendePonto(alvo, id);
}

float ReceberPasse::getLimiarAvaliacao()
{
    return 0.0;
}

bool ReceberPasse::verificarTermino(int id)
{
    /// pegando o robo mais proximo da bola, para analisar se o passe foi sucedido
    IdDistancia robo = Sistema::avaliador.getIdDistRoboEqMaisPertoBola();

    /// verificando se o id do robo que esta mais perto da bola é o meu se for é por que o passe foi completado
    if(id == robo.first){
        return true;
    }

    return false;
}

float ReceberPasse::avaliacaoEscolhaRobo(int id)
{
    Ponto alvo = paramPonto.at(0); /// pegando o alvo para se posicionar definido no arquivo da jogada

    /// calculando a distancia do robo ate o alvo definido na jogada para se posicionar
    return squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), alvo);
}

int ReceberPasse::getIdMelhorRobo(vector<int>& _ids)
{
    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE RECEBE PASSE CURTO" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô que está mais perto de uma região para receber um passe curto. ****/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i< _ids.size(); i++){

        /// Calculando a distância do robô à região.
        float distRoboRegiao = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
        if(menorDistRoboRegiao > distRoboRegiao){
            idRoboMaisPerto = _ids[i];                  /// Pegando o id do robô mais perto da região.
            posVetorRobo = i;                           /// Pegando o indice do vetor para removermos depois o id do robo
            menorDistRoboRegiao = distRoboRegiao; /// Setando a nova distância
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " RECEBE_PASSE_CURTO: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    _ids.erase(_ids.begin() + posVetorRobo); /// Apagando o id do robô que selecionamos para essa tática.

    return idRoboMaisPerto;
}

bool ReceberPasse::isAtiva()
{
    return false;
}

Tatica *ReceberPasse::getNovaInstancia()
{
    return new ReceberPasse;
}

string ReceberPasse::getNome(){
    return "ReceberPasse";
}

void ReceberPasse::imprimirNome()
{
    cout << "RecebePasse" << endl;
}
