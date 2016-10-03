#include "PosicionaChute.h"
#include <Sistema.h>

PosicionaChute::PosicionaChute(){
}

PosicionaChute::~PosicionaChute(){
}

void PosicionaChute::executar(Agente* agente){
//        agente->ativarNavegador();

//    /// @todo implementar nessa tatica uma forma  do robo analisar se outro robo com mesma tatica esta se posicionando no mesmo lugar
//    /// e analisar se o robo que ira chutar esta em uma das regioes caso esteje iremos pegar a regiao que o robo esta chutando esta mais longe
//    /// e ponderar de acordo com o numero de robos naquela regiao

//    /// Calculando o alvo para aonde o robô irá se posicionar para efetuar um chute
//    Ponto alvo = calcularAlvoRoboRegiao(id);

//    /// Criando a máquina de skill só para nos posicionarmos em um região para chutarmos posteriormente.
//    return new DefendePonto(alvo, id);
}

bool PosicionaChute::verificarTermino(int id){
    id = 0;
    return id;
}

float PosicionaChute::avaliacaoEscolhaRobo(int id){
    Ponto alvo = calcularAlvoRoboRegiao(id);  /// Pegando o alvo para aonde o robô irá se posicionar para o chute

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao(); /// Pegando a posição do robô

    /// Calculando a distância do robô ao ponto central da região
    return squared_distance(posRobo, alvo);
}

int PosicionaChute::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE POSICIONA CHUTE" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para executar essa tática é o robô mais próximo da melhor região escolhida*/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i< _ids.size(); i++){

        /// Calculando a distância do robô à região.
        float distRoboRegiao = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
        if(distRoboRegiao < menorDistRoboRegiao){
            idRoboMaisPerto = _ids[i];            /// Pegando o id do robô mais perto da região.
            posVetorRobo = i;                     /// Pegando o indice do vetor para removermos depois o id do robo
            menorDistRoboRegiao = distRoboRegiao; /// Setando a nova distância
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " POSICIONA_CHUTE: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

Circulo PosicionaChute::verificarMelhorRegiao(int id){
    int quantRobosMelhorRegiao = 11; /// Quantidade de robôs na melhor região encontrada.
    float menorDist = numeric_limits<float>::infinity(); /// Variável que irá armazenar a menor distancia encontrada
    int numRegioes; /// Número de regioes que iremos analisar e pegar a melhor

    Circulo melhorRegiao; /// Circulo que corresponde a melhor regiao encontrada

    /// Colocando um excessão para o caso os parâmetros da tática não existam
    try{
        numRegioes = paramInt.at(0);    /// Pegando o número de regiões que iremos analisar

        /// Se tivermos apenas uma região para analisar iremos usar ela mesmo.
        if(numRegioes == 1){
            float raioRegiao = paramFloat.at(0); /// Pegando o raio da regiao
            melhorRegiao = Circulo(paramPonto.at(0), raioRegiao*raioRegiao); /// retornando a região encontrada

        }else{
            Ponto centroRegiao; /// Variavel que irá armazenar o centro da regiao
            float raioRegiao = 0.0; /// Variável que irá armazenar o raio da regiao

            /// Se tivermos mais de uma região para analisar iremos ver qual a melhor região que se aplica a situação.
            for(int i = 0; i < numRegioes; i++){

                Ponto centro = paramPonto.at(i); /// Pegando o centro da região analisada
                float raio = paramFloat.at(i); /// Pegando o raio da região analisada

                /// Pegando a quantidade de robôs nessa região.
                int qtRobosRegiao = avaliadorRobo.getQtRobosRegiao(centro, raio);

                /// Verificando qual das regiões o robô está mais perto
                float distRoboRegiao = squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), centro);

                /// Verificando se a quantidade de robôs encontradas na região é menor que a na região anterior.
                /// Se for iremos subtistituir os valores da região e da quant de robôs.
                if(qtRobosRegiao < quantRobosMelhorRegiao || (qtRobosRegiao == quantRobosMelhorRegiao && distRoboRegiao < menorDist)){
                    centroRegiao = centro;
                    raioRegiao = raio;
                    quantRobosMelhorRegiao = qtRobosRegiao;
                    menorDist = distRoboRegiao;
                }
            }

            melhorRegiao = Circulo(centroRegiao, raioRegiao*raioRegiao);
        }

    }catch(exception e){
        cout << "Os parâmetros não foram setados na Tática de PosicionaChute." << endl << e.what() << endl;
    }

    return melhorRegiao;
}

Ponto PosicionaChute::calcularAlvoRoboRegiao(int id){
    Circulo melhorRegiao;
    try{

        if(!paramString.empty()){

            string param = paramString.at(0);
            if(param == "falta"){

            }

        }else{
            melhorRegiao = verificarMelhorRegiao(id); /// Verificando a melhor região para se posicionar
        }

    }catch(exception ex){
        cout << "Erro ao pegar o parametro para posicionar o robo para chute" << endl;
    }

    melhorRegiao = verificarMelhorRegiao(id); /// Verificando a melhor região para se posicionar

    /// Calculando o alvo dentro da melhor região escolhida.
    avaliadorRobo.setId(id);
    return avaliadorRobo.calculaAlvoRegiaoInterceptaGolAdv(melhorRegiao.center(), sqrt(melhorRegiao.squared_radius()));
}

bool PosicionaChute::isAtiva(){
    return false;
}

Tatica* PosicionaChute::getNovaInstancia(){
    return new PosicionaChute;
}

void PosicionaChute::imprimirNome(){
    cout << "PosicionaChute" << endl;
}

string PosicionaChute::getNome()
{
    return "PosicionaChute";
}

float PosicionaChute::getLimiarAvaliacao()
{
    return 0.0;
}



