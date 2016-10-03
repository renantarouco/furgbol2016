#include "Limpa.h"
#include "Sistema.h"

Limpa::Limpa(){
}

Limpa::~Limpa(){
}

void Limpa::executar(Agente* agente){
    int id = agente->getId();
    avaliadorRobo.setId(id);
    agente->ativarObstaculosEq();

    /// Calculando um alvo longe da nossa area para chutar a bola
    Ponto alvoChutar = calcularAlvoChuteLongaDist(id);

    /// Calculando o angulo que iremos ter para poder limpar a bola (tirar a bola de perto)
    float anguloChutar = Sistema::avaliador.calcularAnguloAbertura(alvoChutar, ConfigAvaliador::DIST_ANGULO_LIMPAR);

    /// Calculando o alvo de aproximacao pro robo poder chutar a bola pra longe
    Ponto alvoAprox = avaliadorRobo.calcularAlvoAproximacao(alvoChutar);

    /// setando os dados na maquina
    maqMoveBola.setDados(alvoAprox, alvoChutar, anguloChutar, vector<MaquinaSkills::Parametro>(1, MaquinaSkills::CHUTE_ALTO));

    /// executando a maquina
    maqMoveBola.executar(agente);
}

bool Limpa::verificarTermino(int id) {
    //    if(Sistema::modeloMundo.getRobo(id)->getComando().temChute()){
    //        chutou = true;
    //    }
    //    if(chutou && Sistema::modeloMundo.getBola()->foiChutada()){
    //        return true;
    //    }
    id = 0;
    return id;
}

float Limpa::avaliacaoEscolhaRobo(int id){

    /// Pegando a posição da bola
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância do robô a bola
    return squared_distance(posBola,posRobo);
}

int Limpa::getIdMelhorRobo(vector<int>& _ids){
    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0 ) {
        cout << "SEM ROBOS PARA ESCOLHER MELHOR NA TATICA DE LIMPA" << endl;
        return -1;
    }
    /// Se não tiver ids é porque deu erro se tiver apenas um ID o melhor papel é o unico que sobrou
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin());
        return idRestante;
    }

    /** O melhor robô para essa tática é o robô que está mais perto da região que queremos posicionar ele*/
    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posicao = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDist = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    //    /// Se nao tiver robos com chute iremos analisar o mais proximo da bola
    //    vector<int> idRobosComChute = Sistema::modeloMundo.getIdRobosComChute();
    //    if(idRobosComChute.empty()){

    /// Procura o robo com a menor distancia
    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Verificando se o robô pode tocar na bola
        if(Sistema::modeloMundo.getRoboEq(_ids[i])->isTocarBola()){

            /// Calculando a distância do robo a bola.
            float distRoboBola = avaliacaoEscolhaRobo(_ids[i]);

            /// Verificando se a distância que encontramos é menor que a anterior.
            if(distRoboBola < menorDist){
                menorDist = distRoboBola;     /// Setando a nova menor distância encontrada
                idRoboMaisPerto =_ids[i]; /// Pegando o id do robô que tem a menor distancia
                posicao=i;                /// Pegando a posição do vetor para removermos o robô do vetor
            }
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " LIMPA: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }
    _ids.erase(_ids.begin() + posicao);

    //        /// Se tiver robo com chute iremos analisar quais dos robos que possuem chute mais proximos da bola
    //    }else{

    ////        cout << "Entrou aqui" << endl;

    //        for(unsigned int i = 0; i < idRobosComChute.size(); i++){

    //            /// Verificando se o robô pode tocar na bola
    //            //            if(Sistema::modeloMundo.getRoboEq(idRobosComChute[i])->isTocarBola() && Sistema::modeloMundo.getRoboEq(idRobosComChute[i])->isPresente()){

    //            if(Sistema::modeloMundo.getRoboEq(idRobosComChute[i])->isPresente()){

    //                /// Calculando a distância do robo a bola.
    //                float distRoboBola = avaliacaoEscolhaRobo(idRobosComChute[i]);

    //                /// Verificando se a distância que encontramos é menor que a anterior.
    //                if(distRoboBola < menorDist){
    //                    menorDist = distRoboBola;     /// Setando a nova menor distância encontrada
    //                    idRoboMaisPerto = idRobosComChute[i]; /// Pegando o id do robô que tem a menor distancia
    //                    posicao=i;                /// Pegando a posição do vetor para removermos o robô do vetor
    //                }
    //            }
    //        }

    //        /// Se o id for diferente de -1 e porque escolheu um robo valido pra posicionar, caso contrario e porque nao tem robo com chute no campo entao iremos pegar os outros robos
    //        if(idRoboMaisPerto == -1) {
    ////            cout << "Nao tem robos com chute no campo" << endl;

    //            for(unsigned int i = 0; i < _ids.size(); i++){

    //                /// Calculando a distância do robô à região.
    //                float distRoboPonto = avaliacaoEscolhaRobo(_ids[i]);

    //                /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
    //                if(menorDist > distRoboPonto){
    //                    idRoboMaisPerto = _ids[i];           /// Pegando o id do robô mais perto da região.
    //                    posicao = i;                    /// Pegando o indice do vetor para removermos depois o id do robo
    //                    menorDist = distRoboPonto; /// Setando a nova distância
    //                }
    //            }

    //            /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    //            if(idRoboMaisPerto == -1) {
    //                cout << " LIMPA: AVISO ROBO MAIS PERTO É -1" << endl;
    //                return -1;
    //            }
    //            _ids.erase(_ids.begin() + posicao);

    //            /// Caso tenha sido selecionado o id iremos remover do vetor principal
    //        }else{

    //            vector<int>::iterator it = _ids.begin();
    //            for(it = _ids.begin(); it != _ids.end(); it++){
    //                if((*it) == idRoboMaisPerto){
    //                    _ids.erase(it);
    //                    break;
    //                }
    //            }
    //        }
    //    }

    return idRoboMaisPerto;
}

Ponto Limpa::calcularAlvoChuteLongaDist(int id){
    /// variáveis auxiliares
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();
    Ponto centroGolAdv = Sistema::modeloMundo.getCampo()->getAreaAdv()->getCentro();

    /// Instanciando o avaliadorRobo para ser usado
    avaliadorRobo.setId(id);

    /// Calculando um alvo longe da nossa área para afastar a bola
    IntPonto robo = avaliadorRobo.calcularMelhorAlvoPosicionarOuChutar(posBola, centroGolAdv, 300, Config::LARGURA_CAMPO/2, Tatica::PONTUACAO_LIMITE_CHUTE);
    return robo.second;
}

bool Limpa::isAtiva(){
    return true;
}

Tatica* Limpa::getNovaInstancia(){
    return new Limpa;
}

void Limpa::imprimirNome(){
    cout << " Limpa " << endl;
}

string Limpa::getNome()
{
    return "Limpa";
}

float Limpa::getLimiarAvaliacao()
{
    return 100000.0;
}

