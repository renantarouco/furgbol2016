#include "PosicionaPerdaBola.h"
#include <Sistema.h>

PosicionaPerdaBola::PosicionaPerdaBola(){
}

PosicionaPerdaBola::~PosicionaPerdaBola(){
}

void PosicionaPerdaBola::executar(Agente* agente){
//        agente->ativarNavegador();

    //    /// Alvo que o robô irá pra se posicionar caso a bola seja perdida.
    //    /// Calculando o alvo que o robô terá para ir caso o robô que está com a bola, perca ela.
    //    Ponto alvo = calcularAlvoPosPerdaBola(id);

    //    //cout << "Tatica Posiciona Perda Bola ID = " << id << endl;
    //    //cout << "Alvo " << alvo << endl;

    //    /// Criando a máquina de skill só para posiciona_perda_bola que iremos usar.
    //    return new DefendePonto(alvo, id);
}

bool PosicionaPerdaBola::verificarTermino(int id){
    id = 0;
    return id;
}

float PosicionaPerdaBola::avaliacaoEscolhaRobo(int id){

    /// Pegando a posição do robô que está com a bola
    Ponto posRoboComBola = Sistema::modeloMundo.getRoboEq(Sistema::avaliador.getIdDistRoboEqMaisPertoBola().first)->getPosicao();

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância do robô que está com a bola e o robô que irá se posicionar para a perda da bola.
    return squared_distance(posRoboComBola, posRobo);
}

int PosicionaPerdaBola::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE POSICIONAR PERDA BOLA" << endl;
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


    /// Analisando a posição desse robô com a dos outros robô e analisando o mais perto para pegarmos pra essa tática.
    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Variável que irá armazenar a distância entre os dois robôs que iremos compara.
        float distRoboComRoboComBola = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a nova distância adquirida é menor que a antiga, se for então iremos pegar essa nova.
        if(menorDist > distRoboComRoboComBola){
            idRoboMaisPerto = _ids[i]; /// Pegando o id do novo robô selecionado
            posVetorRobo = i;          /// Pegando a posição do vetor para depois removermos o robô.
            menorDist = distRoboComRoboComBola;      /// Setando a nova distância que foi analisada como a menor das outras.
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " POSICIONA_PERDA_BOLA: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    _ids.erase(_ids.begin() + posVetorRobo); /// Apagando o id do robô que selecionamos para essa tática.

    return idRoboMaisPerto;
}

Ponto PosicionaPerdaBola::calcularAlvoPosPerdaBola(int id){

    //    int distLinhaLateral; /// Distância de uma das laterais do campo que o robô terá que ficar.
    //    int distLinhaFundo;   /// Distância de uma das laterais do fundo do campo que o robõ terá que ficar.
    //    try{
    //         distLinhaLateral = paramInt.at(0); /// Pegando o parâmetro da distância lateral.
    //         distLinhaFundo = paramInt.at(1);   /// Pegando a distância da linha de fundo que o robõ terá que ficar
    //    }catch(exception e){
    //        cout << "Os parâmetros não foram setados na Tática de PosicionaPerdaBola." << endl << e.what() << endl;
    //        abort();
    //    }

    //    /// Pegando a posição do robô que está com a bola.
    //    Ponto posRoboComBola = Sistema::modeloMundo.getRobo(Sistema::avaliador.roboEqMaisPertoBola().first)->getPosicao();

    //    /// Variável que iremos usar para armazenar o valor de qual lado iremos colocar o robô que irá se posicionar
    //    /// emcima ou embaixo do robô que está com a bola.
    //    bool roboFicaEmbaixo;

    //    /** Verificando se o robô com a bola está em cima ou embaixo, dependendo disso iremos colocar o robô na posição oposto,
    //        se estiver no meio, iremos determinar uma posição arbitrária*/

    //    /// Verificando se o robô está embaixo do lado do campo
    //    if(posRoboComBola.y() < -Avaliador::TOL_PERTENCE_MEIO - RAIO_ROBO - Avaliador::TOL_PERTENCE_ALVO){

    //        roboFicaEmbaixo = false; /// O robô ficará emcima do robô que está com a bola.

    //    /// Verificando se o robô está em cima do lado do campo.
    //    }else if(posRoboComBola.y() > Avaliador::TOL_PERTENCE_MEIO + RAIO_ROBO + Avaliador::TOL_PERTENCE_ALVO){

    //        roboFicaEmbaixo = true;  /// O robô ficará embaixo do robô que está com a bola.

    //    /// Se o robô estiver na tolerância do meio, então iremos analisar o lado que tem menos robôs.
    //    }else{

    //        /// Pegando a quantidade de robôs que estão emcima do robô que está com a bola.
    //        int quantRobosEmcima = Sistema::modeloMundo.getQuantRobosAreaCampoFrenteRoboComBola(id, 1);
    //        /// Pegando a quantidade de robôs que estão embaixo do robô que está com a bola.
    //        int quantRobosEmbaixo = Sistema::modeloMundo.getQuantRobosAreaCampoFrenteRoboComBola(id, 0);

    //        /// Verificando se a quantidade de robôs que estão em cima é maior que a quantidade de robôs que estão embaixo.
    //        if(quantRobosEmcima < quantRobosEmbaixo){
    //            roboFicaEmbaixo = false; /// O robô ficará embaixo do robô que está com a bola.

    //        /// Verificando se a quantidade de robôs que estão embaixo é maior que a quantidade de robôs que estão emcima.
    //        }else if(quantRobosEmbaixo < quantRobosEmcima){
    //            roboFicaEmbaixo = true; /// O robô ficará emcima do robô que está com a bola.

    //        }else{ /// Se a quantidade de robôs emcima e embaixo for o mesmo então iremos posicionar o robô em um lado mais próximo.

    //            /// Verificando qual o lado é mais perto para o robô se posicionar
    //            if(Sistema::modeloMundo.getRobo(id)->getPosicao().y() > 0){
    //                roboFicaEmbaixo = false;
    //            }else{
    //                roboFicaEmbaixo = true;
    //            }
    //        }
    //    }

    //    /// Coordenadas do alvo do robô
    //    /// Pegando a coordenada em x do alvo que o robô tem que estar.
    //    int x =  Sistema::modeloMundo.getRobo(Sistema::avaliador.roboEqMaisPertoBola().first)->getPosicao().x();
    //    int y; /// Coordenada em y do alvo.

    //    /// Analisando qual lado iremos ficar emcima ou embaixo do campo para calcularmos o y do Ponto
    //    if(roboFicaEmbaixo){
    //        y = distLinhaLateral -(Config::LARGURA_CAMPO/2.0);
    //    }else{
    //        y = (Config::LARGURA_CAMPO/2.0) - distLinhaLateral;
    //    }

    //    /// Verificar o lado do campo para calcularmos o x do ponto
    //    if(Sistema::modeloMundo.getLadoCampo() == Direito){
    //        x = Config::MEIO_Config::COMPRIMENTO_CAMPO - distLinhaFundo;
    //    }else{
    //        x = distLinhaFundo - Config::MEIO_Config::COMPRIMENTO_CAMPO;
    //    }

    //    /// Ponto no qual iremos nos posicionar.
    //    Ponto pontoFinal = Ponto(x,y);

    //    /// Criando a reta onde iremos analisar um ponto dela para posicionarmos o robô
    //    Reta retaDeslocamento(pontoFinal, Ponto(0, y));

    //    /// Alvo onde iremos começar a posicionar o robô
    //    Ponto alvoInicial = Ponto(x/2,y);

    //    /// Calculando qual é o melhor ponto da reta para nos posicionarmos caso perdemos a bola
    //    avaliadorRobo = AvaliadorRobo(id); /// Instanciando o avaliadorRobo para poder ser usado
    //    Ponto pontoPosicionar = avaliadorRobo.calcularMelhorAlvoPosicionarOuChutar(Sistema::modeloMundo.getCentroGolEq(), alvoInicial, retaDeslocamento,
    //                                                                150.0, sqrt(squared_distance(pontoFinal, Ponto(0,y))), 100).first;
    //    return Ponto(x,y);

    return Sistema::modeloMundo.getRoboEq(id)->getPosicao();
}

bool PosicionaPerdaBola::isAtiva(){
    return false;
}

Tatica* PosicionaPerdaBola::getNovaInstancia(){
    return new PosicionaPerdaBola;
}

string PosicionaPerdaBola::getNome(){
    return "PosicionaPerdaBola";
}

void PosicionaPerdaBola::imprimirNome(){
    cout << "PosicionaPerdaBola" << endl;
}

float PosicionaPerdaBola::getLimiarAvaliacao()
{
    return 0.0;
}

