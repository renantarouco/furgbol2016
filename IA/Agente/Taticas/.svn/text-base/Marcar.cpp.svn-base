#include "Marcar.h"
#include <Sistema.h>
#include <Geometria.h>

Marcar::Marcar(){
    idAdvMarcar = -1;
    scoreAdvReceberaPasse = -1.0;
}

Marcar::~Marcar(){
}

void Marcar::executar(Agente* agente){
    int id = agente->getId();
    agente->ativarObstaculosEq();
    agente->ativarObstaculosAdv();
    agente->addAreaEqObstaculo();
    agente->addBolaComoObstaculo(500.0);

    /// Pegando o id do robô adversário que iremos marcar
    Ponto alvo = calcularAlvoRoboAdvParaMarcar(id);

    //    agente->getNavegador()->ativaObstaculoRobosAdv();

    /// setando os dados da maquina
    maqDefendePonto.setDados(alvo);

    /// executando a maquina
    maqDefendePonto.executar(agente);
}

bool Marcar::verificarTermino(int id){
    id = 0;
    return id;
}

float Marcar::avaliacaoEscolhaRobo(int id){

    /// Calculando o alvo que o robô irá se posicionar para marcar o robô adv
    Ponto alvo = calcularAlvoRoboAdvParaMarcar(id);

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância entre os dois pontos
    return squared_distance(alvo, posRobo);
}

int Marcar::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE MARCAR" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];

        calcularAlvoRoboAdvParaMarcar(idRestante);

        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô que está mais perto do robô adv que será marcado. ****/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboAoRoboParaMarcar = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Calculando a distância do robô ao robô que iremos marcar
        float distRoboAoRoboParaMarcar = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
        if(menorDistRoboAoRoboParaMarcar > distRoboAoRoboParaMarcar){
            idRoboMaisPerto = _ids[i];                                /// Pegando o id do robô mais perto da região.
            posVetorRobo = i;                                         /// Pegando o indice do vetor para removermos depois o id do robo
            menorDistRoboAoRoboParaMarcar = distRoboAoRoboParaMarcar; /// Setando a nova distância
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " MARCAR: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

vector<int> Marcar::getRobosAdvEstaoSendoMarcados(int id){

    /// pegando os robos que também irão marcar alguém
    vector<Robo*> robosComTatica = Sistema::modeloMundo.getOutrosRobosComTatica(id, "Marcar");
    int qtRobosComTatica = robosComTatica.size();

    vector<int> idAdvsMarcados;
    for(int i=0;i<qtRobosComTatica;i++){
        Robo* robo = robosComTatica[i];

        /// Converter a tática base para a derivada, para podermos acessar suas funções
        Marcar* marcar = dynamic_cast<Marcar*>(robo->getTaticaCorrente());

        /// Se o id que ele está marcando for diferente de -1, então iremos pegar o id para desconsiderarmos depois
        if(marcar->getIdAdvMarcando() != -1)
            idAdvsMarcados.push_back(marcar->getIdAdvMarcando());
    }

    return idAdvsMarcados;
}

Ponto Marcar::calcularAlvoRoboAdvParaMarcar(int id){

    /// pegando os ids dos robos adv que estão sendo marcado por outros robos da nossa equipe
    vector<int> idAdvsMarcados = getRobosAdvEstaoSendoMarcados(id);
    if(!idAdvsMarcados.empty())
        cout << id << " marcados: "<< idAdvsMarcados[0] << endl;

    /// Pegando os parâmetros da tática de marcar para podermos usá-los para selecionar o robô que iremos marcar
    try{
        //        /// Pegando que tipo de robo iremos marcar
        //        string quemMarcar = paramString.at(0);

        //                /// Pegando o robô adv melhor colocado para receber um passe
        //                if(quemMarcar == "recebera_passe"){
        //                    getIdAdvReceberaPasse(id);

        //                    /// Pegando o robô mais próximo do nosso gol.
        //                }else if(quemMarcar == "mais_proximo_nosso_gol_sem_bola"){
        //                    idAdvMarcar = Sistema::avaliador.getIdAdvMaisProxGolSemBola(idAdvsMarcados, false);
        //                }

        /// @todo fazer com que ele pegue ou o que recebere o passe ou o que estiver mais proximo
        idAdvMarcar = Sistema::avaliador.getIdAdvMaisProxGolSemBola(idAdvsMarcados, true);

        /// Verificando se conseguimos pegar algum robo, senão tivermos conseguido é porque deu erro em alguma coisa.
        if(idAdvMarcar == -1){
            cout << "WARNING: id do robô adv que iremos marcar é -1, temos que trocar de Tática." << endl;
            return Sistema::modeloMundo.getRoboEq(id)->getPosicao();
        }

        /// Pegando como iremos fazer a marcação
        string tipoMarcacao = paramString.at(1);

        /// Calculando um alvo pra evitar que o robo que esta sendo marcado receba um passe do cara que esta com a bola
        if(tipoMarcacao == "passe"){
            return calcularAlvoMarcarRoboReceberaPasse(idAdvMarcar);

            /// Calculando um alvo pro robo se posicionar pra evitar o chute do robo que esta sendo marcado
        }else if(tipoMarcacao == "chute"){
            return calcularAlvoMarcarRoboContraChute(id);
        }

    }catch(exception ex){
        cout << "WARNING: Nao foi possivel pegar os parametros da tatica Marcar" << endl;
    }

    return Sistema::modeloMundo.getRoboEq(id)->getPosicao();
}

Ponto Marcar::calcularAlvoMarcarRoboReceberaPasse(int idRoboAdvMarcar){

    /// Variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Ponto posAdvMarcar = Sistema::modeloMundo.getRoboAdv(idRoboAdvMarcar)->getPosicao();
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Criando a reta com o robo que sera marcado com a bola para poder identificar o melhor ponto para interceptar o passe de outro robo
    Reta retaAdvBolaComAdvMarcar(posBola, posAdvMarcar);

    /// Criando um circulo ao redor do robô com quatro vezes o raio do robô que será onde iremos posicionar o robô que irá marcar
    Circulo circuloMarcacao;
    circuloMarcacao.construir(posAdvMarcar, ConfigAvaliador::RAIO_APROX_MARCACAO);

    /// Caso nao seje possivel calcular o alvo iremos pegar a posicao do robo adv e mandar nosso robo incomodar ele
    Ponto alvo = posAdvMarcar;

    /// Pegando os pontos de interseccao da reta do robo adv
    vector<Ponto> pontosInterseccao;
    bool intercepta = circuloMarcacao.isInterseccaoReta(retaAdvBolaComAdvMarcar, pontosInterseccao);
    if(intercepta){

        /// Pegando as distâncias dos pontos encontrados ao robô que está com a bola
        float distPonto0 = squared_distance(pontosInterseccao[0], posBola);
        float distPonto1 = squared_distance(pontosInterseccao[1], posBola);

        /// Verificando qual dos dois pontos está mais próximo do robô que está com a bola
        if(distPonto0 < distPonto1){
            alvo = pontosInterseccao[0]; /// Pegando o ponto 0
        }else{
            alvo = pontosInterseccao[1]; /// Pegando o ponto 1
        }
    }

    return alvo;
}


Ponto Marcar::calcularAlvoMarcarRoboContraChute(int id){

    /// variáveis auxiliares
    Robo* roboAdvMarcar = Sistema::modeloMundo.getRoboAdv(idAdvMarcar);
    Campo* campo = Sistema::modeloMundo.getCampo();
    Area* areaEq = campo->getAreaEq();
    Ponto centroGolEq = areaEq->getCentro();

    /// @todo colocar um histeresis para o robo nao ficar alterando muito de robo

    /// Criando a reta do robô adv com o centro do nosso gol
    Reta retaAdvCentroGol(roboAdvMarcar->getPosicao(), centroGolEq);

    /// Criando um circulo ao redor do robô com quatro vezes o raio do robô que será onde iremos posicionar o robô que irá marcar
    Circulo circuloRoboAdv(roboAdvMarcar->getPosicao(), RAIO_ROBO*RAIO_ROBO);

    /// Pegando os pontos de interseccao da reta do robo adv
    vector<Ponto> pontosInterseccao;
    bool intercepta = circuloRoboAdv.isInterseccaoReta(retaAdvCentroGol, pontosInterseccao);

    /// É o ponto que fica entre o robô e o nosso gol
    Ponto alvo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    if(intercepta){

        /// Calculando a distancia dos pontos ate o nosso gol e iremos pegar o que esta mais proximo
        float distPonto0 = squared_distance(pontosInterseccao[0], centroGolEq);
        float distPonto1 = squared_distance(pontosInterseccao[1], centroGolEq);

        /// Verificando qual dos dois pontos está mais próximo do robô que está com a bola
        alvo = distPonto0 < distPonto1 ? pontosInterseccao[0] : pontosInterseccao[1];

        /// Se o alvo estiver dentro da area iremos mandar o robo ir empurar o adv pra dificultar o passe ou chute dele
        if(areaEq->isPontoDentro(alvo)){
            alvo = roboAdvMarcar->getPosicao();
            //            alvo = Sistema::avaliador.calcularAlvoMarcarRoboReceberaPasse(idAdvMarcar);
        }
    }else{
        cout << "WARNING: Erro ao calcular a posicao do robo para marcar adv contra chute.Menos de dois pontos de interseccao entre reta incidente e circulo de aproximacao" << endl;
    }

    /// Retornando o alvo calculado para posicionar o robô para bloquear o chute do robô adv.
    return alvo;
}

void Marcar::getIdAdvReceberaPasse(int id){

    //    /// Pegando a posição do robô que está com a bola
    //    int idAdvComBola = Sistema::avaliador.getIdDistAdvMaisPertoBola().first;
    //    Ponto posRoboAdvComBola = Sistema::modeloMundo.getRoboAdv()->getPosicao(idAdvComBola);
    //    Campo campo = Sistema::avaliador.getCampo();
    //    Area areaEq = campo.getAreaEq();

    //    int idRoboAdvReceberaPasse = -1; /// Id do robô adv que está melhor posicionado para receber passe
    //    float menorScore = numeric_limits<float>::infinity(); /// Valor do menor score encontrado.
    //    float menorDist = numeric_limits<float>::infinity();  /// Menor distância do robô ao nosso gol

    //    BOOST_FOREACH(Robo* robo, Sistema::modeloMundo.getRobosAdv()){

    //        /// Verificando se o robo esta presente e se o id dele e diferente do robo que esta mais perto da bola
    //        if(robo->isPresente() && robo->getId() != idAdvComBola){
    //        }

    //    }

    //    /// Analisando o score de cada robô e pegando o que tem menor score.
    //    for(int i = 0; i < Sistema::modeloMundo.getQtRobosAdvPresente(); i++){

    //        /// Não iremos pegar o robô que está mais perto da bola, e iremos pegar um robô que não está dentro da área.
    //        if(i != Sistema::avaliador.getIdDistAdvMaisPertoBola().first && !areaEq.isPontoDentro(Sistema::modeloMundo.getRoboAdv(i)->getPosicao()) &&
    //                campo.isPontoDentro(Sistema::modeloMundo.getRoboAdv(i)->getPosicao())){

    //            /// Vetor dos robôs adv que serão desconsiderados
    //            vector<int> idsRobosAdv(2);
    //            idsRobosAdv.push_back(Sistema::avaliador.getIdDistAdvMaisPertoBola().first);
    //            idsRobosAdv.push_back(i);

    //            /// Pegando as posições dos robôs que iremos analisar, e passando os robôs que iremos desconsiderar
    //            vector<Ponto> posRobos = Sistema::modeloMundo.getPosRobosEntrePontoInicialEAlvo(vector<int>(1, id), idsRobosAdv,
    //                                                                                            Segmento(posRoboAdvComBola,
    //                                                                                            Sistema::modeloMundo.getRoboAdv(i)->getPosicao()), 1000.0);

    //            /// Calculando o score do robô e não iremos considerar esse robô e nem o robô que irá marcar ele.
    //            float score = Sistema::avaliador.analisarScoreAlvo(posRoboAdvComBola, Sistema::modeloMundo.getRoboAdv(i)->getPosicao(), posRobos, false);

    //            /// Pegando a distancia do robô ao centro do nosso gol
    //            float distRoboAoCentroGolEq = sqrt(squared_distance(Sistema::modeloMundo.getRoboAdv(i)->getPosicao(), Sistema::modeloMundo.getCentroGolEq()));

    //            /// Verificando se o score calculado é menor que o score anterior.
    //            /// Se o score for menor que 300 e a distância do robô ao centro do nosso gol for menor que o outro
    //            /// iremos pegar o novo robô.
    //            if((score < 300 && distRoboAoCentroGolEq < menorDist) || (menorScore >= 300 && score < menorScore)){
    //                idRoboAdvReceberaPasse = i;        /// Pegando o id do robô adv com melhor score para receber passe.
    //                menorScore = score;                /// Setando o novo score
    //                menorDist = distRoboAoCentroGolEq; /// Setando a nova distância do robô mais perto do nosso gol
    //            }
    //        }
    //    }

    //    /// Se o id do robô que estavamos marcando for -1 é porque não estavamos marcando ninguem, então iremos pegar o robô com menor score
    //    /// Se o id do robô que pegamos for o mesmo do id do robo que estavamos marcando então iremos pegar ele mesmo.
    //    /// Se a diferença de scores entre o robô que estava marcando e o robô que escolhi for maior que a tolerância para mudar, e se
    //    /// o novo score calculado for menor que o anterior e se o score for menor que 300, então iremos pegar o novo robô para marcar.
    //    if(idAdvMarcar == -1 || idAdvMarcar == idRoboAdvReceberaPasse ||
    //       (abs(scoreAdvReceberaPasse - menorScore) > Avaliador::HIST_SCORE_MUDAR_MARCACAO && menorScore < scoreAdvReceberaPasse && menorScore < 300)){
    //        idAdvMarcar = idRoboAdvReceberaPasse; /// Pegando o novo robô que iremos marcar
    //        scoreAdvReceberaPasse = menorScore;    /// Pegando o score desse robô
    //    }
}

int Marcar::getIdAdvMarcando(){
    return idAdvMarcar;
}

bool Marcar::isAtiva(){
    return false;
}

Tatica* Marcar::getNovaInstancia(){
    return new Marcar;
}

void Marcar::imprimirNome(){
    cout << " Marcar " << endl;
}

string Marcar::getNome()
{
    return "Marcar";
}

float Marcar::getLimiarAvaliacao()
{
    return 0.0;
}

