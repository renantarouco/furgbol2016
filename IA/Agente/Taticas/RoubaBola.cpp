#include "RoubaBola.h"
#include <Sistema.h>

RoubaBola::RoubaBola(){
}


RoubaBola::~RoubaBola(){
}

void RoubaBola::executar(Agente* agente){
//    agente->ativarNavegador();

    //    /// Pegando o alvo que será o gol adversário para levar a bola até lá
    //    Ponto alvo = Sistema::modeloMundo.getBola()->getPosicao();

    //    /// Criando a maquina move bola para fazer o robô pegar a bola do outro e levar para o gol adversário
    //    vector<MaquinaSkills::Parametro> parametros(2);
    //    parametros[0] = MaquinaSkills::SEM_CHUTE;

    //    Ponto alvoAprox = calcAlvoAproximacao(id, alvo);
    //    return new MoveBola(alvoAprox, alvo, id, parametros);
}

bool RoubaBola::verificarTermino(int id){
    return Sistema::avaliador.isBolaNossa();
}

float RoubaBola::avaliacaoEscolhaRobo(int id){

    /// Pegando a posição do robô que está com a bola
    Ponto posRoboAdvComBola = Sistema::modeloMundo.getRoboAdv(Sistema::avaliador.getIdDistAdvMaisPertoBola().first)->getPosicao();

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância do robô com o robô adv que está com a bola.
    return squared_distance(posRoboAdvComBola, posRobo);
}

int RoubaBola::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE ROUBA BOLA" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô mais perto do que está com a bola. ****/

    int idRoboMaisPerto = -1; /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;    /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDist = numeric_limits<float>::infinity();     /// Variável que iremos usar para armazenar a distância entre os robôs

    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Verificando se o robô que iremos analisar pode tocar na bola
        if(Sistema::modeloMundo.getRoboEq(_ids[i])->isTocarBola()){

            /// Variável que irá armazenar a distância entre os dois robôs que iremos compara.
            float distRoboComRoboAdvComBola = avaliacaoEscolhaRobo(_ids[i]);

            /// Verificando se a nova distância adquirida é menor que a antiga, se for então iremos pegar essa nova.
            if(menorDist > distRoboComRoboAdvComBola){
                idRoboMaisPerto = _ids[i]; /// Pegando o id do novo robô selecionado
                posVetorRobo = i;          /// Pegando a posição do vetor para depois removermos o robô.
                menorDist = distRoboComRoboAdvComBola;      /// Setando a nova distância que foi analisada como a menor das outras.
            }
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " ROUBA_BOLA: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    _ids.erase(_ids.begin() + posVetorRobo); /// Apagando o id do robô que selecionamos para essa tática.

    return idRoboMaisPerto;
}

bool RoubaBola::isAtiva(){
    return true;
}

Tatica * RoubaBola::getNovaInstancia(){
    return new RoubaBola;
}

string RoubaBola::getNome(){
    return "RoubaBola";
}

void RoubaBola::imprimirNome(){
    cout << "RoubaBola" << endl;
}

float RoubaBola::getLimiarAvaliacao()
{
    return 0.0;
}
