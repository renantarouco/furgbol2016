#include "Sistema.h"
#include <Halt.h>

ModeloMundo Sistema::modeloMundo;
Avaliador Sistema::avaliador;

Sistema::Sistema()
{
}

Sistema::~Sistema()
{
    stop();

    cout << "FINALIZANDO SISTEMA" << endl;
}

void Sistema::init(QMutex* _mBUS, CommunicationBUS* _barramentoComunicacao)
{
    cout << "INICIANDO SISTEMA" << endl;

    numAgentesAtivos = 0;
    mBUS = _mBUS;
    bus = _barramentoComunicacao;

    /// iniciando modelo de mundo
    modeloMundo.init();
    modeloMundo.setRobosTemChute(Config::ROBOS_TEM_CHUTE);

    /// iniciando gerente deliberativo
    gerenteCentral.init();

    /// setando a porta que será usada
    r_udpSocket.bind(ConfigComunicacao::PORTA_RECEBER, QUdpSocket::ShareAddress);
    connect(&r_udpSocket, SIGNAL(readyRead()), this, SLOT(processPacotes()));

    /// Variavel que ira indicar as constantes que serao usadas para calcular a velocidade dos robos
    cout << "INICIANDO AGENTES" << endl;
    agentes.resize(NUM_MAX_ROBOS);
    for(int id=0;id<NUM_MAX_ROBOS;id++){
        agentes[id].init(id, mBUS, bus);
    }
}

void Sistema::stop()
{
    cout << "FINALIZANDO SISTEMA" << endl;

    quit();
    wait();
}

void Sistema::tratarPacoteRecebido(){
    cout << "tratando pacote recebido" << endl;

    /// verificando se tem datagram pendente
    if (r_udpSocket.hasPendingDatagrams()) {

        printf("Trantando pacote recebido....\n");

        /// lendo o pacote
        datagram.clear();
        datagram.resize(r_udpSocket.pendingDatagramSize());
        r_udpSocket.readDatagram(datagram.data(), datagram.size());

        /// verificando qual foi o pacote que foi recebido
        if(ConfigComunicacao::TIPO_ROBOS == REAL || ConfigComunicacao::TIPO_ROBOS == SIMULADOR3D){

            printf("Pacote do Gerente de Dados...\n");

//            printf("%s\n", pacoteGD.DebugString().c_str());

            pacoteGD.ParseFromArray(datagram.data(), datagram.size());
            modeloMundo.coletaDados(pacoteGD);
            //KALMAN CORREÇÃO

            /// coletando os dados dos robos do simulador3D
        }else if(ConfigComunicacao::TIPO_ROBOS == SIMULADOR2D){
            //            printf("Pacote do Simulador2D...\n");

            pacoteSimulador2D.ParseFromArray(datagram.data(), datagram.size());
            modeloMundo.coletaDados(pacoteSimulador2D);
        }
    }

    cout << "finalizado com sucesso...." << endl;
}

void Sistema::processPacotes(){

    cout << "carregando constantes....." << endl;
    Config::load();
    cout << "finalizado...." << endl;

    /// função que trata o pacote recebido e seta os valores que foram recebidos nas respectivas variáveis
    tratarPacoteRecebido();

    /// Verificando se iremos precisar ou não alterar o sinal dos pontos das jogadas. Só iremos mudar quando mudarmos de lado.
    if(modeloMundo.isMudarSinalPontosJogadas()){
        gerenteCentral.mudarSinalPontosJogadas();
    }

    /// fazendo o monitoramento da jogada e analisando qual será a próxima ação a ser executada
    gerenteCentral.analisarJogada();

    /// verificando se teremos que fazer uma troca de papeis entre os robos
    if(gerenteCentral.trocarPapeisOn())
    {
        cout << "trocando papeis entre agentes...." << endl;

        papeisRobos = gerenteCentral.atribuirPapeis();
        setPapeisAgentes(papeisRobos); /// Setando a nova ordem de execução dos agentes

        /// Verificando se o estado atual do GDC é o de SELEÇÃO para escolhermos uma nova jogada
    }else if(gerenteCentral.selecaoOn())
    {
        papeisRobos = gerenteCentral.selecionarJogada(); /// Fazendo a seleção da melhor jogada e pegando um vetor dos agentes com seus papeis
        setPapeisAgentes(papeisRobos); /// Setando nos agentes os papeis
    }

    /// executando as táticas de cada agente que estiver presente no campo
    for(int id=0;id<NUM_MAX_ROBOS;id++){

        /// Executando a tática do agente
        agentes[id].executarTatica();
    }


    /** Criando o pacote para enviar para o Monitorardor */
    addPacoteMonitoradorBUS();

    iteracao++;
}

void Sistema::addPacoteMonitoradorBUS(){
    if(ConfigComunicacao::ENVIA_MONITORADOR){
        cout << "enviando pacote monitorador" << endl;

        PacoteIASimulador2D pacoteMonitorador;

        /// setando o nome da jogada que está sendo executada
        pacoteMonitorador.set_jogada(gerenteCentral.getNomeJogadaAtual().c_str());
        pacoteMonitorador.set_corequipe((PacoteIASimulador2D::CorEquipe) modeloMundo.getCorEquipe());
        pacoteMonitorador.set_ladocampo((PacoteIASimulador2D::LadoCampo) modeloMundo.getLadoCampo());

        /// criando o pacote da bola
        Ponto posBola = modeloMundo.getBola()->getPosicao();
        PacoteBola* bola = pacoteMonitorador.mutable_bola();
        bola->set_x(posBola.x());
        bola->set_y(posBola.y());

        //        /// setando os fatos que estão habilitados no modelo de mundo
        //        map<string, bool>* fatos = modeloMundo.getFatos();
        //        for (map<string,bool>::iterator it= fatos->begin() ; it != fatos->end(); it++ )
        //        {
        //            if((*it).second==true) pacoteMonitorador.add_fatosdomundo((*it).first);
        //        }

        /// adicionando os robos da equipe e os adversários no pacote
        vector<Robo>* robosEq = modeloMundo.getRobosEq();
        vector<Robo>* robosAdv = modeloMundo.getRobosAdv();
        for(int id = 0; id < NUM_MAX_ROBOS; id++){
            Robo* robo = &robosEq->at(id);
            if(robo->isPresente()){

                /// setando os dados do robo
                PacoteRoboIA* pacoteRobo = pacoteMonitorador.add_robos();
                pacoteRobo->set_id(robo->getId());
                pacoteRobo->set_x(robo->getPosicao().x());
                pacoteRobo->set_y(robo->getPosicao().y());
                pacoteRobo->set_orientation(robo->getOrientacao());
                pacoteRobo->set_velx(robo->getVelocidade().x()); /// conferir esse vetor enviado
                pacoteRobo->set_vely(robo->getVelocidade().y());
                pacoteRobo->set_alvox(robo->getComando().getAlvoFinal().x());
                pacoteRobo->set_alvoy(robo->getComando().getAlvoFinal().y());
                pacoteRobo->set_skill(robo->getSkill());
                pacoteRobo->set_tatica(robo->getTaticaCorrente()->getNome());
                pacoteRobo->set_vel_ang(robo->getVelAngular());

                /// setando o chute do robo
                Comando::TipoChute tipoChute = robo->getComando().getTipoChute();
                if(tipoChute == Comando::SEM_CHUTE){
                    pacoteRobo->set_chute_baixo(0.0);
                    pacoteRobo->set_chute_alto(0.0);
                }else if(tipoChute == Comando::CHUTE_BAIXO){
                    pacoteRobo->set_chute_baixo(1.0);
                    pacoteRobo->set_chute_alto(0.0);
                }else if(tipoChute == Comando::CHUTE_ALTO){
                    pacoteRobo->set_chute_baixo(0.0);
                    pacoteRobo->set_chute_alto(1.0);
                }

                /// setando se o drible está ligado ou não
                pacoteRobo->set_drible_ligado(robo->isTemDrible());

                /// copiando os alvos do path planning
                pacoteRobo->mutable_pathplanning()->CopyFrom(robo->getPacotePathPlanning());
            }

            /// criando o pacote do robo adv
            Robo* roboAdv = &robosAdv->at(id);
            if(roboAdv->isPresente()){
                PacoteRobo * pacoteRoboAdv = pacoteMonitorador.add_robosadv();
                pacoteRoboAdv->set_id(roboAdv->getId());
                pacoteRoboAdv->set_x(roboAdv->getPosicao().x());
                pacoteRoboAdv->set_y(roboAdv->getPosicao().y());
                pacoteRoboAdv->set_orientation(roboAdv->getOrientacao());
            }
        }

        //        printf("%s\n", pacoteMonitorador.DebugString().c_str());

        /// setando pacote no barramento
        mBUS->lock();
        bus->carregaPacoteMonitorador(pacoteMonitorador);
        mBUS->unlock();

        cout << "pacote enviado com sucesso" << endl;
    }
}

void Sistema::run()
{
    cout << "STARTING SISTEMA" << endl;

    iteracao = 1;

    /// executando o loop da thread
    exec();
}

//void Sistema::setPosicoesAgentes(const vector<int> posicoes)
//{
//    for(int id=0;id<NUM_MAX_ROBOS;id++){
//        if(agentes[id].isPresente()){
//            agentes[id].setPosicao(posicoes[id]);
//        }
//    }
//}

void Sistema::setPapeisAgentes(map<int, vector<Tatica*> > & papeis){

    /// Setando os papeis dos robos em cada agente para serem executados
    for(int id = 0; id < NUM_MAX_ROBOS; id++){
        if(agentes[id].isPresente()){
            agentes[id].setPapel(papeis[id]);
        }else{
            agentes[id].limparFilaTaticas();
        }
    }
}
