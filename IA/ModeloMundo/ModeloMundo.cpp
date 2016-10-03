#include "ModeloMundo.h"
#include <Sistema.h>

ModeloMundo::ModeloMundo(){
    /// criando o vetor dos robos da equipe e dos adversários
    robosEq.resize(NUM_MAX_ROBOS);
    robosAdv.resize(NUM_MAX_ROBOS);
    for(int id=0;id<NUM_MAX_ROBOS;id++){
        robosEq[id].init(id, true);
        robosAdv[id].init(id, true);
    }

    idGoleiroEq = 3;
}

ModeloMundo::~ModeloMundo(){
}

void ModeloMundo::init(){
    cout << "INICIANDO MODELO DE MUNDO" << endl;

    /// setando o tempo inicial da iteração com a hora atual
    relogio.setTempoInicial(relogio.getTempoDoDia());
    tempoIteracao = 0.0;

    // LADO ESQUERDO É O DEFAULT
    corEquipe = PacoteControle::AMARELO;
    ladoCampo = PacoteControle::ESQUERDO;
    tempoPartida=0;
    numeroUltimoFrameRecebido = -1;
    estadoAtual="halt";
    estadoAnt="";
    posBolaNormalStart = CGAL::ORIGIN;

    /// construindo o objeto que contém a descrição do campo
    campo.construir();

    /// Preenchendo o map de fatos do modelo de mundo que serao usados para escolher a melhor jogada em cada situacao de jogo
    preencheFatos();
}

void ModeloMundo::setIdGoleiro(int id){
    idGoleiroEq = id;
}

int ModeloMundo::getIdGoleiro(){
    return idGoleiroEq;
}

vector<int> ModeloMundo::getIdRobosComChute(){
    vector<int> idRobosComChute;

    BOOST_FOREACH(Robo& robo, robosEq){
        if(robo.isPresente() && robo.isTemChute() && robo.getId() != idGoleiroEq){
            idRobosComChute.push_back(robo.getId());
        }
    }

    return idRobosComChute;
}
void ModeloMundo::setRobosTemChute(map<int, bool>& robosTemChute)
{
    /// setando os robos que possuem chute
    BOOST_FOREACH(Robo& robo, robosEq){
        robo.setTemChute(robosTemChute[robo.getId()]);
    }
}

bool ModeloMundo::isLadoCampoEsquerdo(){
    return ladoCampo == PacoteControle::ESQUERDO ? true : false;
}

void ModeloMundo::preencheFatos()
{
    fatos["posse_bola"] = false;
    fatos["bola_area_eq"] = false;
    fatos["bola_area_adv"] = false;
    fatos["bola_campo_eq"] = false;
    fatos["bola_campo_adv"] = false;
    fatos["bola_cercada"] = false;
    fatos["tem_robo_marcar"] = false;
    fatos["jogo_normal"] = true;
    fatos["stop"] =false;
    fatos["penalty_shootout"] = false;
    fatos["halt"] = false;
    fatos["kickoff_eq"] = false;
    fatos["kickoff_adv"] = false;
    fatos["direct_kick_eq"] = false;
    fatos["direct_kick_adv"] = false;
    fatos["indirect_kick_eq"] = false;
    fatos["indirect_kick_adv"] = false;
    fatos["penalty_eq"] = false;
    fatos["penalty_adv"] = false;
    fatos["ready"] = false;
    fatos["bola_perto_area_eq"] = false;
    fatos["bola_perto_linha_fundo_eq"] = false;
    fatos["teste"] = false;
}

bool ModeloMundo::verificarRoboMaisProxBola(){

    /// Variaveis que serao usadas para identificar o robo mais proximo da bola
    float menorDistEq = numeric_limits<float>::infinity();
    float menorDistAdv = numeric_limits<float>::infinity();
    Ponto posBola = bola.getPosicao();

    for(int id=0;id<NUM_MAX_ROBOS;id++){

        /// Verificando se o robo esta presente na partida
        Robo* roboEq = &robosEq[id];
        if(roboEq->isPresente()){
            float distBola = squared_distance(posBola, roboEq->getPosicao());

            /// Verificando se a distancia e menor que a menor distancia encontrada
            if(distBola < menorDistEq){
                menorDistEq = distBola;
                roboEqMaisProxBola = roboEq;
            }
        }

        /// Verificando se o robo esta presente na partida
        Robo* roboAdv = &robosAdv[id];
        if(roboAdv->isPresente()){
            float distBola = squared_distance(posBola, roboAdv->getPosicao());

            /// Verificando se a distancia e menor que a menor distancia encontrada
            if(distBola < menorDistAdv){
                menorDistAdv = distBola;
                roboAdvMaisProxBola = roboAdv;
            }
        }
    }

    /// retornando se o nosso robo está mais proximo do que o outro
    return menorDistEq < menorDistAdv ? true : false;
}

void ModeloMundo::atualizarFatos(){

    /// variáveis auxiliares
    Ponto posBola = bola.getPosicao();

    /// verificando se a bola está perto da area da equipe
    fatos["bola_perto_area_eq"] = bola.isPertoAreaEq();

    /// verificando se a bola está perto da linha de fundo
    fatos["bola_perto_linha_fundo_eq"] = bola.isPertoLinhaFundoEq();

    /// Verificando se o adversario possue mais de 2 robos para que possamos marcar um robo, caso contrario iremos posicionar o robo na defesa
    fatos["tem_robo_marcar"] = qtRobosAdvPresentes > 2;

    /// funcao que analisa o id dos dois robos mais proximos da bola e retorna se a posse de bola é nossa ou não
    fatos["posse_bola"] = verificarRoboMaisProxBola();

    /// verificando se a bola está no campo da equipe
    fatos["bola_campo_eq"] = Sistema::avaliador.isPontoLadoEq(posBola);
    if(fatos["bola_campo_eq"]){

        /// verificando se a bola está dentro da area
        fatos["bola_area_eq"] = campo.getAreaEq()->isPontoDentro(posBola);

        /// setando os outros como false
        fatos["bola_area_adv"] = false;
        fatos["bola_campo_adv"] = false;
    }else{

        /// verificando se a bola está no campo adv
        fatos["bola_campo_adv"] = Sistema::avaliador.isPontoLadoAdv(posBola);
        if(fatos["bola_campo_adv"]){
            fatos["bola_area_adv"] = campo.getAreaAdv()->isPontoDentro(posBola);

            fatos["bola_area_eq"] = false;
        }
    }

    /// verificando se tem muitos robos adv perto da bola e perto do nosso gol
    if(fatos["posse_bola"] && fatos["bola_campo_eq"] && Sistema::avaliador.getNumAdvPertoPonto(posBola, 600.0) > 1)
        fatos["bola_cercada"] = true;
}

void ModeloMundo::resetaFatos(){
    map<string,bool>::iterator it;

    for(it = fatos.begin(); it != fatos.end(); it++)
        (*it).second = false;
}

PacoteControle::CorEquipe ModeloMundo::getCorEquipe()
{
    return corEquipe;
}

Campo *ModeloMundo::getCampo()
{
    return &campo;
}

vector<Robo*> ModeloMundo::getOutrosRobosComTatica(int _id, string _nomeTatica){

    /// Robôs presentes com a mesma tática
    vector<Robo*> robosComMesmaTatica;

    /// Pegando o id dos robos menos o do goleiro
    for(int idRobo = 0; idRobo < NUM_MAX_ROBOS; idRobo++){
        Robo* roboEq = &robosEq[idRobo];

        /// Verificando se o robô não tem o mesmo id que o passado como parâmetro e se possue a mesma tática corrente
        if((roboEq->isPresente()) && (idRobo != idGoleiroEq) && (idRobo != _id) && (roboEq->getNomeTaticaCorrente() == _nomeTatica)){
            robosComMesmaTatica.push_back(roboEq);
        }
    }

    return robosComMesmaTatica;
}

int ModeloMundo::getQtRobosEqPresentes()
{
    return qtRobosEqPresentes;
}

int ModeloMundo::getQtRobosAdvPresentes()
{
    return qtRobosAdvPresentes;
}

bool ModeloMundo::isEqAmarelo()
{
    return corEquipe == PacoteControle::AMARELO;
}

vector<int>* ModeloMundo::getIdRobosMenosGoleiro()
{
    return &idRobosEqMenosGoleiro;
}

void ModeloMundo::coletaDados(const PacoteDados& pacoteEntrada)
{

    /// lendo os dados das posições dos robos
    if(pacoteEntrada.has_dadoscontrole()){
        coletaDadosControle(pacoteEntrada.dadoscontrole());
    }

    /// lendo os dados do estado do jogo caso tivermos que usar o juiz
    if(pacoteEntrada.has_dadosestados() && ConfigComunicacao::USAR_REFEREE){
        coletaDadosEstados(pacoteEntrada.dadosestados());
    }

    /// lendo os dados das posições dos robos
    if(pacoteEntrada.has_dadosvisao()){
        coletaDadosVisao(pacoteEntrada.dadosvisao());
    }

    /// atualizando os fatos do mundo toda vez que chega um pacote
    atualizarFatos();
}

void ModeloMundo::coletaDados(const PacoteIASimulador2D& pacoteEntrada)
{
    tempoIteracao = relogio.getTempoPassado(); /// pegando o tempo entre dois recebimentos de pacotes, esse é o delay da IA + VISÃO
    relogio.setTempoInicial(relogio.getTempoDoDia());

    /// Se o valor antigo do lado do campo for diferente do atual, então iremos mudar o lado do campo e alterar o valor dos pontos nas jogadas.
    if(ladoCampo != pacoteEntrada.ladocampo()){

        /// função que troca o lado do nosso gol
        campo.trocarLado();

        /// Setar valor da flag como true para poder mudar o sinal.
        mudarSinal = true;

        /// setando o novo lado do campo
        ladoCampo = (PacoteControle::PacoteControle::LadoCampo) pacoteEntrada.ladocampo();
    }

    /// setando o id dos goleiros das equipes
    idGoleiroEq = 0;
    idGoleiroAdv = 0;

    /// setando a cor da equipe
    corEquipe = (PacoteControle::CorEquipe) pacoteEntrada.corequipe();

    /// Deixa todos os robos como ausentes e so poem como presentes os que chegarem neste pacote
    idRobosEqMenosGoleiro.clear();
    for(int id = 0; id < NUM_MAX_ROBOS; id++){
        robosEq[id].dontPresent();
        robosAdv[id].dontPresent();
    }

    /// setando os dados dos robos da equipe
    qtRobosEqPresentes = pacoteEntrada.robos_size();
    for(int i = 0; i < qtRobosEqPresentes; i++){

        /// pegando o pacote do robo que foi detectado pela visão e setando a posicao e orientação
        PacoteRoboIA pacoteRobo = pacoteEntrada.robos(i);
        int idRobo = pacoteRobo.id();
        robosEq[idRobo].setDados(Ponto(pacoteRobo.x(), pacoteRobo.y()), pacoteRobo.orientation());

        /// inserindo no vetor os ids dos robos presentes menos o id do goleiro
        if(idRobo != idGoleiroEq)
            idRobosEqMenosGoleiro.push_back(idRobo);
    }

    /// setando os dados dos robos adversarios
    qtRobosAdvPresentes = pacoteEntrada.robosadv_size();
    for(int i = 0; i < qtRobosAdvPresentes; i++){

        /// pegando o pacote do robo adv e setando os dados da posicao e orientação
        PacoteRobo pacoteRobo = pacoteEntrada.robosadv(i);
        int roboId = pacoteRobo.id();
        robosAdv[roboId].setDados(Ponto(pacoteRobo.x(),pacoteRobo.y()), pacoteRobo.orientation());
    }

    delayGerenteDados = 0.0;
    numeroUltimoFrameRecebido = 1;

    /// coletando dados da bola
    coletaDadosBola(pacoteEntrada.bola());

    /// setando os dados do referee
    coletaDadosEstados(pacoteEntrada.dadosestados());

    /// atualizando os fatos do mundo toda vez que chega um pacote
    atualizarFatos();
}


void ModeloMundo::coletaDadosVisao(const PacoteVisao &pacoteVisao)
{
    //    cout << " INICIO LEITURA DADOS VISAO" << endl;

    int numFramePacote = pacoteVisao.numeroframe();
    if(numFramePacote > numeroUltimoFrameRecebido){

        if ( numFramePacote > numeroUltimoFrameRecebido+1){
            cout << "Perdeu " << numFramePacote - numeroUltimoFrameRecebido -1 << " frames " << endl;
        }

        numeroUltimoFrameRecebido = pacoteVisao.numeroframe();

        /// setando que os robos não estão presentes inicialmente
        idRobosEqMenosGoleiro.clear();
        for(int id = 0; id<NUM_MAX_ROBOS; id++){
            robosEq[id].dontPresent();
            robosAdv[id].dontPresent();
        }

        /// analisando os pacotes dos robos que foram encontrados no campo
        qtRobosEqPresentes = pacoteVisao.robosequipe_size();
        for(int i = 0; i < qtRobosEqPresentes; i++){

            /// pegando o pacote do robo da equipe
            PacoteRobo pacoteRobo = pacoteVisao.robosequipe(i);
            int idRobo = pacoteRobo.id();
            robosEq[idRobo].setDados(Ponto(pacoteRobo.x(), pacoteRobo.y()), pacoteRobo.orientation());

            //            cout << "robo " << idRobo << ", " << robosEq[idRobo].getPosicao().x() << " " << robosEq[idRobo].getPosicao().y() << endl;

            /// inserindo no vetor os ids dos robos presentes menos o id do goleiro
            if(idRobo != idGoleiroEq)
                idRobosEqMenosGoleiro.push_back(idRobo);
        }

        /// analisando os pacotes dos robos adv que foram encontrados no campo
        qtRobosAdvPresentes = pacoteVisao.robosadversarios_size();
        for(int i = 0; i < qtRobosAdvPresentes; i++){

            /// pegando o pacote do robo adv e setando a posicao e orientação
            PacoteRobo pacoteRobo = pacoteVisao.robosadversarios(i);
            int idRobo = pacoteRobo.id();
            robosAdv[idRobo].setDados(Ponto(pacoteRobo.x(),pacoteRobo.y()), pacoteRobo.orientation());
        }

        delayGerenteDados = pacoteVisao.delay();
        //        cout << "delay " << delayGerenteDados << endl;
        numeroUltimoFrameRecebido = pacoteVisao.numeroframe();
        //cout << "numero ultimo frame" << numeroUltimoFrameRecebido << endl;
        //cout << "Coletando dado Bola " << endl;
        coletaDadosBola(pacoteVisao.bola());

        //        robos[idGoleiro]->setPresenca(true);
    }

    //    cout << " FIM LEITURA DADOS VISAO" << endl;
}


void ModeloMundo::coletaDadosEstados(const SSL_Referee &pacoteEstados){

    //    cout << " INICIO LEITURA DADOS ESTADOS" << endl;

    /// setando o id do goleiro da equipe e do adversário
    if(corEquipe == PacoteControle::AMARELO){
        idGoleiroEq = pacoteEstados.yellow().goalie();
        idGoleiroAdv = pacoteEstados.blue().goalie();
    }else{
        idGoleiroEq = pacoteEstados.blue().goalie();
        idGoleiroAdv = pacoteEstados.yellow().goalie();
    }

    /// Verificando qual o estado atual da partida
    switch(pacoteEstados.command()){
    case SSL_Referee::FORCE_START:
        estadoAtual = "jogo_normal";
        break;

    case SSL_Referee::STOP:
        estadoAtual = "stop";
        break;

    case SSL_Referee::PREPARE_KICKOFF_BLUE:

        if(corEquipe == PacoteControle::AZUL){ /// verificando qual time nos somos
            estadoAtual = "kickoff_eq";
        }else{

            /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
            if(estadoAtual != "jogo_normal"){
                estadoAtual = "kickoff_adv";
            }
        }
        break;

    case SSL_Referee::PREPARE_KICKOFF_YELLOW:

        if(corEquipe == PacoteControle::AMARELO){ /// verificando qual time nos somos
            estadoAtual = "kickoff_eq";
        }else{

            /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
            if(estadoAtual != "jogo_normal"){
                estadoAtual = "kickoff_adv";
            }
        }
        break;

    case SSL_Referee::PREPARE_PENALTY_BLUE:

        ConfigMontador::DESACELERACAO = 0.9;
        if(corEquipe == PacoteControle::AZUL){ /// verificando qual time nos somos
            estadoAtual = "penalty_eq";
        }else{
            estadoAtual = "penalty_adv";
        }
        break;

    case SSL_Referee::PREPARE_PENALTY_YELLOW:

        if(corEquipe == PacoteControle::AMARELO){ /// verificando qual time nos somos
            estadoAtual = "penalty_eq";
        }else{
            estadoAtual = "penalty_adv";
        }
        break;

    case SSL_Referee::DIRECT_FREE_BLUE:
        if(corEquipe == PacoteControle::AZUL){ /// verificando qual time nos somos
            estadoAtual = "direct_kick_eq";
        }else{
            /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
            if(estadoAtual != "jogo_normal"){
                estadoAtual = "direct_kick_adv";
            }
        }

        break;

    case SSL_Referee::DIRECT_FREE_YELLOW:
        if(corEquipe == PacoteControle::AMARELO){ /// verificando qual time nos somos
            estadoAtual = "direct_kick_eq";
        }else{

            /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
            if(estadoAtual != "jogo_normal"){
                estadoAtual = "direct_kick_adv";
            }
        }

        break;

    case SSL_Referee::INDIRECT_FREE_BLUE:

        if(corEquipe == PacoteControle::AZUL){ /// verificando qual time nos somos
            estadoAtual = "indirect_kick_eq";
        }else{

            /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
            if(estadoAtual != "jogo_normal"){
                estadoAtual = "indirect_kick_adv";
            }
        }

        break;

    case SSL_Referee::INDIRECT_FREE_YELLOW:

        if(corEquipe == PacoteControle::AMARELO){ /// verificando qual time nos somos
            estadoAtual = "indirect_kick_eq";
        }else{

            /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
            if(estadoAtual != "jogo_normal"){
                estadoAtual = "indirect_kick_adv";
            }
        }

        break;

    case SSL_Referee::NORMAL_START:

        /// se o estado anterior for jogo_normal é por que o normal start já foi executado, caso contrário o normal start não foi executado
        if(estadoAtual != "jogo_normal"){
            estadoAtual = "ready";
        }

        break; /// dando return para que não seja setado que o estado anterior não é o normal start

    default:
        estadoAtual="halt";
        ConfigMontador::DESACELERACAO = 1;
        break;
    }

    /// verificando se a bola se moveu
    if(estadoAtual=="ready" || estadoAtual =="indirect_kick_adv" || estadoAtual =="direct_kick_adv"){

        /// Verificando se o estado anterior é o normal start se for iremos verificar se a bola andou mais do que o limite
        if(posBolaNormalStart != CGAL::ORIGIN){
            double dist = squared_distance(bola.getPosicao(), posBolaNormalStart);

            if(dist > 50.0*50.0){ /// verificando se a bola andou mais do que 5 cm
                fatos["jogo_normal"] = true;
                estadoAtual = "jogo_normal";
                posBolaNormalStart = CGAL::ORIGIN;
            }

            /// caso não seja o normal start iremos pegar a posicao da bola no momento, para posteriormente verificar se ela andou
            /// o bastante para classificar o estado como jogo_normal
        }else{
            posBolaNormalStart = bola.getPosicao();
        }
    }

    /// Setando todos os fatos como false a não ser o estado atual
    map<string, bool>::iterator it;
    for(it = fatos.begin(); it != fatos.end(); it++){
        it->second = false;
    }
    fatos[estadoAtual] = true;

    /// caso o estado atual seja o ready não podemos descartar o estado anterior, pois servirá para definir a jogada a ser executada
    if(estadoAtual == "ready" && estadoAnt != ""){
        fatos[estadoAnt] = true;
    }else{
        if(estadoAtual == "ready" && estadoAnt=="")
            estadoAtual = "jogo_normal", fatos["jogo_normal"]=true, fatos["ready"]=false;

        estadoAnt = estadoAtual; /// setando o estado anterior como atual
    }

    //    cout << " FIM LEITURA DADOS ESTADOS" << endl;
}

void ModeloMundo::coletaDadosControle(const PacoteControle &pacoteControle)
{
    //    cout << " INICIO LEITURA DADOS CONTROLE" << endl;

    /// Se o valor antigo do lado do campo for diferente do atual, então iremos mudar o lado do campo e alterar o valor dos pontos nas jogadas.
    if(pacoteControle.ladocampo() != ladoCampo){

        /// trocando o lado da nossa equipe no campo
        campo.trocarLado();

        /// Setar valor da flag como true para poder mudar o sinal.
        mudarSinal = true;

        /// setando o novo lado do campo
        ladoCampo = pacoteControle.ladocampo();
    }

    /// setando a cor da equipe
    corEquipe = pacoteControle.corequipe();

    //    /// setando o id do goleiro
//    idGoleiroEq = pacoteControle.idgoleiro();

    //    cout << " FIM LEITURA DADOS CONTROLE" << endl;
}

void ModeloMundo::coletaDadosBola(const PacoteBola &pacoteBola)
{
    /// setando a posicao e o tempo da iteracao para pordemos calcular a velocidade atual da bola entre os dois frames
    //    bola.setPosicao(Ponto(pacoteBola.x(), pacoteBola.y()), tempoIteracao);
    bola.setPosicao(Ponto(pacoteBola.x(), pacoteBola.y()));

    /// se a altura da bola
    bola.setAltura(pacoteBola.z());
}

int ModeloMundo::getIdGoleiroAdv()
{
    return idGoleiroAdv;
}

map<string,bool>* ModeloMundo::getFatos()
{
    return &fatos;
}

Robo* ModeloMundo::getRoboEq(int _id)
{
    if(_id >= NUM_MAX_ROBOS || _id < 0 ){
        cout <<  " ERRO id invalido na get ROBO " << endl;
        return NULL;
    }

    // cout << " Pegou Robo " << _id << endl;
    return &robosEq[_id];
}

Robo* ModeloMundo::getRoboAdv(int _id)
{
    if(_id > NUM_MAX_ROBOS || _id < 0 ){
        cout <<  " ERRO id invalido na get ROBO " << endl;
        return NULL;
    }

    return &robosAdv[_id];
}

Bola* ModeloMundo::getBola()
{
    return &bola;
}
PacoteControle::PacoteControle::LadoCampo ModeloMundo::getLadoCampo()
{
    return ladoCampo;
}

vector<Robo>* ModeloMundo::getRobosEq()
{
    return &robosEq;
}

vector<Robo>* ModeloMundo::getRobosAdv()
{
    return &robosAdv;
}

void ModeloMundo::setMudarSinalPontosJogadas(bool _mudarSinal){
    this->mudarSinal = _mudarSinal;
}

bool ModeloMundo::isMudarSinalPontosJogadas(){
    return mudarSinal;
}

int ModeloMundo::getIdRoboAtivo(){

    /// analisando qual dos robos da equipe está com a tatica ativa
    BOOST_FOREACH(Robo& robo, robosEq){
        if(robo.isPresente() && robo.getTaticaCorrente()->isAtiva()){
            return robo.getId();
        }
    }

    cout << " Sem robos ativos no momento " << endl;
    return -1;
}

int ModeloMundo::getIdRoboNaoPodeTocarBola()
{
    return -1;
}

void ModeloMundo::PontoDentroAreaAdv(Ponto& alvo)
{
    Area *areaAdv = this->getCampo()->getAreaAdv();
    Ponto pbola = bola.getPosicao();
    if(areaAdv->isPontoDentro(pbola)){
        Segmento seg= areaAdv->getSegmentoArea();
        Ponto pbola = bola.getPosicao();
        //Ponto depoisBola= Ponto(pbola.x());
        Robo goleiroadv = robosAdv[0];
        Ponto pgoleiroadv= goleiroadv.getPosicao();
        Reta reta= Reta(pgoleiroadv,pbola);
        Objeto inter= CGAL::intersection(reta,seg);
        //alvo= Ponto(0,0);
        //cout<<"-------------------------------------------------------"<<inter.<<"------------------------------------------------------------------"<<endl;
        /*for(i=0;seg.point(i)!=seg.end();i++){
            cout<<"BOLA X:"<<(int)pbola.x()<<endl;
            cout<<"PONTO X:"<<(int)seg.point(i).x()<<endl;

        }*/

    }
}

bool ModeloMundo::isBolaDentroAreaAdv()
{
    Area areaAdv = *campo.getAreaAdv();
    return areaAdv.isPontoDentro(bola.getPosicao());
}
