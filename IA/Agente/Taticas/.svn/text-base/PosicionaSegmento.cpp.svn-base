#include "PosicionaSegmento.h"
#include <Sistema.h>
#include <Geometria.h>

PosicionaSegmento::PosicionaSegmento(){
}

PosicionaSegmento::~PosicionaSegmento(){
}

void PosicionaSegmento::executar(Agente* agente){
//        agente->ativarNavegador();

//    /// Pegando o alvo que teremos ou não intersecção com o robô que está com a bola.
//    Ponto alvo = calcularAlvoNoSegmento(id);

//    /// Criando a máquina para o robô se posicionar no alvo calculado defendendo o nosso gol de um chute
//    return new DefendePonto(alvo, id);
}

bool PosicionaSegmento::verificarTermino(int id){
    id = 0;
    return id;
}

float PosicionaSegmento::avaliacaoEscolhaRobo(int id){

    Ponto alvo = calcularAlvoNoSegmento(id); /// Calculando o alvo no segmento para o robo se posicionar

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância do robô ao segmento
    return squared_distance(alvo, posRobo);
}

int PosicionaSegmento::getIdMelhorRobo(vector<int>& _ids){

    /// Verificando se não temos robôs para serem selecionados, senão não tivermos então há algum problema.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE POSICIONAR PERDA BOLA" << endl;
        return -1;
    }

    /// Verificando se só tem um robô para ser selecionado, se for então iremos pegar ele mesmo.
    if(_ids.size() == 1){
        int idRobo = _ids[0];         /// Pegando o único robô que restou no vetor;
        _ids.erase(_ids.begin());     /// Removendo esse robô do vetor para não podermos selecionar ele em outra tática.
        return idRobo;
    }

    /** Iremos pegar o robô que está mais perto do segmento que queremos posicionar o robô. ******/

    int idRoboMaisPerto = -1;   /// Variável que irá armazenar o id do robô selecionado para a tática.
    int posVetorRobo = -1;      /// Variável que irá armazenar a posição que iremos remover do vetor dos robôs.
    float menorDist = numeric_limits<float>::infinity();       /// Variável que irá armazenar a distância do robô com o segmento.

    /// Analisando a distância de todos os robôs com o segmento e pegando o mais perto do segmento.
    for(unsigned int i = 0; i < _ids.size(); i++){

        int distRoboSegmento = avaliacaoEscolhaRobo(_ids[i]);  /// Calculando a distância do robô com o segmento

        /// Verificando se a distância anterior é maior que a nova distância calculada.
        if(menorDist > distRoboSegmento){
            idRoboMaisPerto = _ids[i]; /// Pegando o id do robô que possui uma distância menor do segmento
            menorDist = distRoboSegmento;      /// Setando na menor distância a nova distância calculada.
            posVetorRobo = i;          /// Setando a posição do vetor que iremos remover o robô selecionado.
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " POSICIONA_SEGMENTO: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

Ponto PosicionaSegmento::calcularAlvoNoSegmento(int id){

    Segmento segmento; /// Segmento que iremos posicionar o robô.
    string condicao;   /// Condição que o robô irá executar (desviar do robô que está com a bola ou não).
    try{
        segmento = Segmento(paramPonto.at(0), paramPonto.at(1));  /// Criando um segmento com os pontos passados no arquivo.
        condicao = paramString.at(0);                          /// Pegando a condição de desviarmos da bola ou não.
    }catch(exception e){
        cout << "Os parâmetros não foram setados na Tática de PosicionaSegmento." << endl << e.what() << endl;
        abort();
    }

    Reta retaRoboComBola;  /// Reta do robô mais perto da bola com a bola.
    Ponto posRobo;         /// Ponto que irá indicar a posição do robô mais perto da bola.

    /// Pegando os robos da equipes mais perto da bola
    IdDistancia roboEq = Sistema::avaliador.getIdDistRoboEqMaisPertoBola();
    IdDistancia roboAdv = Sistema::avaliador.getIdDistAdvMaisPertoBola();

    /// Verificando qual distâncias é a menor e pegando a posição do robô para construirmos a reta do robô com a bola.
    if(roboEq.second < roboAdv.second){
        posRobo = Sistema::modeloMundo.getRoboEq(roboEq.first)->getPosicao();
    }else{
        posRobo = Sistema::modeloMundo.getRoboEq(roboAdv.first)->getPosicao();
    }

    /// Criando a reta com o robô mais perto da bola.
    retaRoboComBola = Reta(posRobo, Sistema::modeloMundo.getBola()->getPosicao());

    /// Pegando o ponto que a reta faz interseção com o segmento
    Ponto pontoInterseccao;

    /// Fazendo a interseccao do segmento com a reta
    bool intercepta = Geometria::isInterseccaoSegmentoReta(segmento, retaRoboComBola, pontoInterseccao);

    /// Verificando se iremos ou não interceptar o robô que está com a bola.
    if(condicao == "desviar_robo_com_bola"){

        /// Verificando se a reta tem interseção com o segmento senão tiver então iremos pegar o ponto qualquer do segmento.
        if(!intercepta){

            /// Se não existe ponto de interseccao da reta com o segmento iremos analisar a posição do robô e mandar ele ir
            /// para o ponto máximo ou minimo do segmento para se posicionar.

            /// Se o robô já estiver no segmento iremos retorna a posição dele, senão iremos pegar um ponto do segmento
            if(!segmento.has_on(Sistema::modeloMundo.getRoboEq(id)->getPosicao())){

                /// Distâncias do robô ao ponto maximo e minimo do segmento
                float distRoboPontoMaxSeg = squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), segmento.max());
                float distRoboPontoMinSeg = squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), segmento.min());

                /// Iremos pegar o ponto que estiver mais próximo do robô
                if(distRoboPontoMaxSeg <= distRoboPontoMinSeg)
                    return segmento.max();

                return segmento.min();
            }

            /// Retornando a posição do robô para ele ficar parado.
            return Sistema::modeloMundo.getRoboEq(id)->getPosicao();
        }

        /// Verificando se o ponto acima do ponto de interseçao é um ponto do segmento, se for retornaremos ele.
        if(segmento.has_on(Ponto(pontoInterseccao.x(), pontoInterseccao.y() + RAIO_ROBO/2.0)))
            return Ponto(pontoInterseccao.x(), pontoInterseccao.y() + RAIO_ROBO/2.0);

        /// Verificando se o ponto abaixo do ponto de interseção é um ponto do segmento, se for retornaremos ele.
        if(segmento.has_on(Ponto(pontoInterseccao.x(), pontoInterseccao.y() - RAIO_ROBO/2.0)))
            return Ponto(pontoInterseccao.x(), pontoInterseccao.y() - RAIO_ROBO/2.0);
    }

    return Ponto(pontoInterseccao.x(), pontoInterseccao.y()); /// Ponto de interseção da retaRoboComBola com o segmento
}

bool PosicionaSegmento::isAtiva(){
    return false;
}

Tatica * PosicionaSegmento::getNovaInstancia(){
    return new PosicionaSegmento;
}

string PosicionaSegmento::getNome(){
    return "PosicionaSegmento";
}

void PosicionaSegmento::imprimirNome(){
    cout << "PosicionaSegmento" << endl;
}

float PosicionaSegmento::getLimiarAvaliacao()
{
    return 0.0;
}

