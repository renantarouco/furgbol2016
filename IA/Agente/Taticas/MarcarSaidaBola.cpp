#include "MarcarSaidaBola.h"
#include <Sistema.h>
#include <Geometria.h>

MarcarSaidaBola::MarcarSaidaBola(){
    idRoboAdvMarcar = -1;
}

MarcarSaidaBola::~MarcarSaidaBola(){
}

void MarcarSaidaBola::executar(Agente* agente){
    //        agente->ativarNavegador();

    //    /// Alvo que iremos posicionar o robô para marcar um robô adversário escolhido
    //    Ponto alvo = calcularAlvoMarcarSaidaBolaRobo(id);

    //    /// Criando a Maquina de Defende Ponto para posicionar o robô.
    //    return new DefendePonto(alvo, id);
}

bool MarcarSaidaBola::verificarTermino(int id){
    id = 0;
    return id;
}

float MarcarSaidaBola::avaliacaoEscolhaRobo(int id){
    /// pegando o alvo para aonde o robô irá se posicionar
    Ponto alvo = calcularAlvoMarcarSaidaBolaRobo(id);

    /// Calculando a distância entre o robô que irá marcar e o que será marcado.
    return squared_distance(alvo, Sistema::modeloMundo.getRoboEq(id)->getPosicao());
}

int MarcarSaidaBola::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE MARCAR SAIDA BOLA" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];

        calcularAlvoMarcarSaidaBolaRobo(idRestante);

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
        cout << " MARCAR_SAIDA_BOLA: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

void MarcarSaidaBola::verificarRoboAdvMarcar(int id){

    /// Pegando os robôs com a mesma tática de MarcarSaidaBola
    vector<Robo*> robosMarcarSaidaBola = Sistema::modeloMundo.getOutrosRobosComTatica(id, "MarcarSaidaBola");

    /// Vetor com os ids dos robôs adv que já estão sendo marcados.
    vector<int> idsRobosAdvMarcados;

    /// Pegando cada robô e pegando o id do robô que eles estão marcando
    int qtRobosMarcarSaidaBola = robosMarcarSaidaBola.size();
    for(int i=0;i<qtRobosMarcarSaidaBola; i++){

        Robo* robo = robosMarcarSaidaBola[i];

        //        /// Converter a tática base para a derivada, para podermos acessar suas funções
        //        MarcarSaidaBola* marcarSaidaBola = dynamic_cast<MarcarSaidaBola*>(robo->getTaticaCorrente());

        //        /// Se o id que ele está marcando for diferente de -1, então iremos pegar o id para desconsiderarmos depois
        //        if(marcarSaidaBola->getIdRoboAdvParaMarcar() != -1)
        //            idsRobosAdvMarcados.push_back(marcarSaidaBola->getIdRoboAdvParaMarcar());

        //        delete marcarSaidaBola; /// Deletando o ponteiro
    }

    int posVetorRoboAdv; /// Posição do vetor de robôs adv da jogada que está a condição que iremos usar nessa tática.
    try{
        posVetorRoboAdv = paramInt.at(0); /// Pegando a posição do vetor de robos adv
    }catch(exception e){
        cout << "Os parâmetros não foram setados na Tática de Marcar Saida Bola." << endl << e.what() << endl;
    }

    //    cout << "Cond do robo: "<< posVetorRoboAdv << endl;

    //    /// Pegando a condição para pegar o robo adv.
    //    string condRoboAdv = Sistema::modeloMundo.getJogadaCorrente().getCondRobosAdv(posVetorRoboAdv);

    //    /// Pegando o robô adv mais próximo do nosso gol que não esteja marcado por outro robô
    //    idRoboAdvMarcar = -1;
    //    if(condRoboAdv == "robo_sem_bola"){
    //        idRoboAdvMarcar = Sistema::avaliador.getIdAdvMaisProxGolSemBola(idsRobosAdvMarcados, true);
    //    }

    //    /// Verificando se conseguimos pegar algum robo, senão tivermos conseguido é porque deu erro em alguma coisa.
    //    if(idRoboAdvMarcar == -1){
    //        cout << "WARNING: id do robô adv que iremos marcar é -1." << endl;
    //    }

    idRoboAdvMarcar = Sistema::avaliador.getIdAdvMaisProxGolSemBola(idsRobosAdvMarcados, true);
}

Ponto MarcarSaidaBola::calcularAlvoMarcarSaidaBolaRobo(int id){

    /// Verificando o robô adv que será marcado
    verificarRoboAdvMarcar(id);

    string condParamTatica; /// Condicao para calcular o alvo
    try{
        condParamTatica = paramString.at(0); /// Pegando a posição do vetor de robos adv
    }catch(exception e){
        cout << "O parametro para calcular o alvo na Tática de Marcar Saida Bola nao foi setado." << endl << e.what() << endl;
    }

    Ponto alvo(0.0, 0.0); /// Alvo que calculamos para o robô se posicionar

    /// Analisando qual é a condição para pegar o robô adv de acordo com a condição.
    if(condParamTatica == "nao_ultrapassar_campo_eq"){
        /// Calculando um alvo que intercepta o passe para esse robô que iremos marcar.
        alvo = calcularAlvoMarcarRoboForaAlcanceCampoAdv();

    }else if(condParamTatica == "pode_ultrapassar_campo_eq"){
        /// Calculando um alvo que intercepta o passe para esse robô que iremos marcar.
        alvo = calcularAlvoMarcarRoboForaAlcanceBola();
    }

    return alvo;
}

Ponto MarcarSaidaBola::calcularAlvoMarcarRoboForaAlcanceCampoAdv(){

    /// Pegando a posição do robo que iremos marcar
    Ponto posRoboAdvParaMarcar = Sistema::modeloMundo.getRoboAdv(idRoboAdvMarcar)->getPosicao();

    Ponto alvo; /// Alvo que iremos calcular para marcar o robô

    /// Valor do x do alvo aonde o robô irá se pocisionar para marcar o outro
    float x = ConfigAvaliador::DIST_MARCAR_SAIDA_BOLA + ConfigAvaliador::TOL_PERTENCE_ALVO;

    /// Verificando qual o nosso lado do campo para posicionarmos o robô no alvo correto do campo
    if(Sistema::modeloMundo.isLadoCampoEsquerdo()){
        alvo = Ponto(-x, posRoboAdvParaMarcar.y());
    }else{
        alvo = Ponto(x, posRoboAdvParaMarcar.y());
    }

    /// Calculando o raio da região ao redor da bola onde teremos que posicionar o robô fora dessa regiao
    float raioRegiao = ConfigAvaliador::DIST_ROBOS_BOLA_JOGO_PARADO * ConfigAvaliador::DIST_ROBOS_BOLA_JOGO_PARADO;

    /// Criando um circulo da região central do campo para verificarmos se o alvo está dentro
    /// dessa área se tiver iremos calcular outro alvo
    Circulo circuloRegiaoCentral(Ponto(0,0), raioRegiao);

    /// Verificando se o ponto está dentro do circulo
    if(circuloRegiaoCentral.has_on_bounded_side(alvo)){

        /// Verificando o lado do campo para setar o x correto
        if(Sistema::modeloMundo.isLadoCampoEsquerdo()){
            alvo = Ponto(alvo.x() - ConfigAvaliador::DIST_ROBOS_BOLA_JOGO_PARADO, alvo.y());
        }else{
            alvo = Ponto(alvo.x() + ConfigAvaliador::DIST_ROBOS_BOLA_JOGO_PARADO, alvo.y());
        }
    }

    return alvo;
}

Ponto MarcarSaidaBola::calcularAlvoMarcarRoboForaAlcanceBola(){

    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Ponto centroGolEq = campo->getAreaEq()->getCentro();
    Robo* roboAdvMarcar = Sistema::modeloMundo.getRoboAdv(idRoboAdvMarcar);
    Bola* bola = Sistema::modeloMundo.getBola();

    Ponto alvo; /// É o ponto que fica entre o robô e o nosso gol

    /// Criando a reta do robô adv com o centro do nosso gol
    Reta retaRoboAdvCentroGol(roboAdvMarcar->getPosicao(), centroGolEq);

    /// Criando um circulo ao redor do robô com quatro vezes o raio do robô que será onde iremos posicionar o robô que irá marcar
    Circulo circuloRoboAdv(roboAdvMarcar->getPosicao(), (RAIO_ROBO*2)*(RAIO_ROBO*2));

    /// Pegando os pontos de interseccao da reta do robo adv
    vector<Ponto> pontosInterseccao;
    bool intercepta = circuloRoboAdv.isInterseccaoReta(retaRoboAdvCentroGol, pontosInterseccao);

    /// Se não tivermos pontos ou se tivermos apenas um ponto é porque o calculo está errado.
    if(intercepta){

        /// Circulo ao redor da bola para verificarmos se o robô está dentro dele
        Circulo circuloRegiaoBola(bola->getPosicao(), 500*500);

        /// Verificando qual dos pontos está dentro do circulo ou não.
        if(circuloRegiaoBola.has_on_bounded_side(pontosInterseccao[0]) && circuloRegiaoBola.has_on_bounded_side(pontosInterseccao[1])){
            cout << "WARNING: calculando um alvo para marcar dentro da região da bola" << endl;
            abort();

        }else if(circuloRegiaoBola.has_on_bounded_side(pontosInterseccao[0])){
            alvo = pontosInterseccao[1];

        }else if(circuloRegiaoBola.has_on_bounded_side(pontosInterseccao[1])){
            alvo = pontosInterseccao[0];

        }else{

            /// Pegando as distâncias dos pontos encontrados ao robô que está com a bola
            float distPonto0CentroGolEq = squared_distance(pontosInterseccao[0], centroGolEq);
            float distPonto1CentroGolEq = squared_distance(pontosInterseccao[1], centroGolEq);

            /// Verificando qual dos dois pontos está mais próximo do robô que está com a bola
            if(distPonto0CentroGolEq < distPonto1CentroGolEq){
                alvo = pontosInterseccao[0]; /// Pegando o ponto 0
            }else{
                alvo = pontosInterseccao[1]; /// Pegando o ponto 1
            }

            /// Verificando se o alvo está dentro da área da nossa equipe se estiver iremos pegar um ponto que intercepte
            /// o passe do robô adv que está com a bola para esse robô.
            if(campo->isPontoDentroAreaEq(alvo)){

                /// Calculando um novo alvo para o robô se posicionar fazendo com que não permita o robô receber a bola.
                alvo = calcularAlvoMarcarRoboReceberaPasse(idRoboAdvMarcar);
            }
        }

    }

    /// Retornando o alvo calculado para posicionar o robô para bloquear o chute do robô adv.
    return alvo;
}

Ponto MarcarSaidaBola::calcularAlvoMarcarRoboReceberaPasse(int idRoboAdvMarcar){

    /// Variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Ponto posAdvMarcar = Sistema::modeloMundo.getRoboAdv(idRoboAdvMarcar)->getPosicao();
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Criando a reta com o robo que sera marcado com a bola para poder identificar o melhor ponto para interceptar o passe de outro robo
    Reta retaAdvBolaComAdvMarcar(posBola, posAdvMarcar);

    /// Criando um circulo ao redor do robô com quatro vezes o raio do robô que será onde iremos posicionar o robô que irá marcar
    Circulo circuloMarcacao(posAdvMarcar, ConfigAvaliador::RAIO_APROX_MARCACAO*ConfigAvaliador::RAIO_APROX_MARCACAO);

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

        /// Se o alvo que foi calculado estiver dentro da area entao iremos pegar a posicao do robo adv pra dificultar o passe
        if(campo->isPontoDentroAreaEq(alvo))
            alvo = posAdvMarcar;

    }else{
        cout << "WARNING: Menos de dois pontos interseccionam a reta robo para marcar com o circulo de marcacao." << endl;
    }

    return alvo;
}

int MarcarSaidaBola::getIdRoboAdvParaMarcar(){
    return idRoboAdvMarcar;
}

bool MarcarSaidaBola::isAtiva(){
    return false;
}

Tatica * MarcarSaidaBola::getNovaInstancia(){
    return new MarcarSaidaBola;
}

void MarcarSaidaBola::imprimirNome(){
    cout << " MarcarSaidaBola " << endl;
}

string MarcarSaidaBola::getNome()
{
    return "MarcarSaidaBola";
}

float MarcarSaidaBola::getLimiarAvaliacao()
{
    return 0.0;
}

