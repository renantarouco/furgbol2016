#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gerenteVisao = new GerenteVisao(&config);
    gerenteEstado = new GerenteEstado(&config);
    multicast_referee = new QUdpSocket(this);
    multicast_vision = new QUdpSocket(this);
    socket_ia = new QUdpSocket(this);

    receivingVisionPacket = receivingRefereePacket = false;

    ui->wVisualizacao->config = &config;
    ui->wVisualizacao->bola = &gerenteVisao->bola;
    ui->wVisualizacao->robosEq = &gerenteVisao->robosEq;
    ui->wVisualizacao->robosAdv = &gerenteVisao->robosAdv;

    /// setando o comando inicial HALT
    pacoteReferee.set_command(SSL_Referee::HALT);
    pacoteReferee.set_packet_timestamp(1);
    pacoteReferee.set_stage(SSL_Referee::NORMAL_FIRST_HALF_PRE);
    pacoteReferee.set_command_counter(0);
    pacoteReferee.set_command_timestamp(1);

    /// setando o time amarelo
    SSL_Referee_TeamInfo* yellow_team = pacoteReferee.mutable_yellow();
    yellow_team->set_name("");
    yellow_team->set_score(0);
    yellow_team->set_red_cards(0);
    yellow_team->set_yellow_cards(0);
    yellow_team->set_timeouts(4);
    yellow_team->set_timeout_time(300000000);
    yellow_team->set_goalie(0);

    /// setando o time azul
    SSL_Referee_TeamInfo* blue_team = pacoteReferee.mutable_blue();
    blue_team->set_name("");
    blue_team->set_score(0);
    blue_team->set_red_cards(0);
    blue_team->set_yellow_cards(0);
    blue_team->set_timeouts(4);
    blue_team->set_timeout_time(300000000);
    blue_team->set_goalie(0);

    connect(multicast_referee, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorReferee(QAbstractSocket::SocketError)));
    connect(multicast_referee, SIGNAL(readyRead()), this, SLOT(readRefereeData()));

    connect(multicast_vision, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(errorVision(QAbstractSocket::SocketError)));
    connect(multicast_vision, SIGNAL(readyRead()), this, SLOT(readVisionData()));
}

MainWindow::~MainWindow()
{
    if(multicast_referee->isOpen()){
        multicast_referee->leaveMulticastGroup(config.groupReferee);
        multicast_referee->close();
    }

    if(multicast_vision->isOpen()){
        multicast_vision->leaveMulticastGroup(config.groupVision);
        multicast_vision->close();
    }

    delete multicast_referee;
    delete multicast_vision;
    delete socket_ia;
    delete gerenteVisao;
    delete gerenteEstado;
    delete ui;
}

void MainWindow::errorReferee(QAbstractSocket::SocketError error){
    QMessageBox::warning(this, "FURGbot", "Referee error");

    multicast_referee->leaveMulticastGroup(config.groupReferee);
    multicast_referee->close();
}

void MainWindow::errorVision(QAbstractSocket::SocketError error){
    QMessageBox::warning(this, "FURGbot", "Erro Vision");

    multicast_vision->leaveMulticastGroup(config.groupReferee);
    multicast_vision->close();
}

void MainWindow::on_pbStartStop_clicked()
{
    if(ui->pbStartStop->text() == "Start"){
        ui->pbStartStop->setText("Stop");

        // abrindo socket do referee
        bool res = multicast_referee->bind(QHostAddress::Any, config.portReceiveReferee, QUdpSocket::ShareAddress);
        if(!res){
            QMessageBox::warning(this, "FURGbot", "Nao foi possivel conectar no Referee");
        }

        // abrindo socket do ssl vision
        res = multicast_vision->bind(QHostAddress::Any, config.portReceiveVision, QUdpSocket::ShareAddress);
        if(!res){
            QMessageBox::warning(this, "FURGbot", "Nao foi possivel conectar na SLL-Vision");
        }

        /// conectando nos grupos multicast
        multicast_referee->joinMulticastGroup(config.groupReferee);
        multicast_vision->joinMulticastGroup(config.groupVision);

    }else{
        ui->pbStartStop->setText("Start");

        multicast_referee->leaveMulticastGroup(config.groupReferee);
        multicast_referee->close();

        multicast_vision->leaveMulticastGroup(config.groupVision);
        multicast_vision->close();
    }
}

void MainWindow::readRefereeData(){
    while(multicast_referee->hasPendingDatagrams()){
        // lendo pacote
        QByteArray datagram;
        datagram.resize(multicast_referee->pendingDatagramSize());
        multicast_referee->readDatagram(datagram.data(), datagram.size());

        pacoteReferee.ParseFromArray(datagram.data(), datagram.size());
    }
}

void MainWindow::readVisionData(){
    while(multicast_vision->hasPendingDatagrams()){
        // lendo pacote
        QByteArray datagram;
        datagram.resize(multicast_vision->pendingDatagramSize());
        multicast_vision->readDatagram(datagram.data(), datagram.size());

        SSL_WrapperPacket pacote;
        pacote.ParseFromArray(datagram.data(), datagram.size());

        // pacote de visao
        if(pacote.has_detection()){

            for(int i=0;i<4;i++){
                if(pacote.detection().camera_id() == i){
                    SSL_DetectionFrame frame;
                    frame.CopyFrom(pacote.detection());
                    gerenteVisao->processPacket(frame);
                }
            }

            /// enviando o pacote de dados para a IA
            send_packet_ia();
        }

        // pacote de geometria
        if(pacote.has_geometry()){
            //            printf("geometry detection:\n%s\n", pacote.geometry().DebugString().c_str());
        }
    }
}

void MainWindow::send_packet_ia(){
    cout << "sending packet IA" << endl;
    PacoteDados pacoteDados;

    PacoteControle *pctControle= pacoteDados.mutable_dadoscontrole();
    pctControle->set_corequipe((PacoteControle_CorEquipe)config.corEquipe);
    pctControle->set_idgoleiro(config.idGoleiro);
    pctControle->set_ladocampo((PacoteControle_LadoCampo)config.ladoCampo);

    SSL_Referee *pctEstado = pacoteDados.mutable_dadosestados();
    pctEstado->CopyFrom(pacoteReferee);

    PacoteVisao* pacoteVisao = pacoteDados.mutable_dadosvisao();
    pacoteVisao->CopyFrom(gerenteVisao->montaPacoteVisao());

    /// enviando o pacote de dados
    string buffer;
    pacoteDados.SerializeToString(&buffer);
    socket_ia->writeDatagram(buffer.c_str(), buffer.size(), config.hostAddressIA, config.portSendIA);

    printf("%s\n", pacoteDados.DebugString().c_str());
}

void MainWindow::on_rbRightColor_clicked(bool checked)
{
    if(checked){
        config.ladoCampo =  DIREITO;
    }
}

void MainWindow::on_rbLeftColor_clicked(bool checked)
{
    if(checked){
        config.ladoCampo =  ESQUERDO;
    }
}

void MainWindow::on_rbBlueColor_clicked(bool checked)
{
    if(checked){
        config.corEquipe =  Azul;
    }
}

void MainWindow::on_rbYellowColor_clicked(bool checked)
{
    if(checked){
        config.corEquipe =  Amarelo;
    }
}

void MainWindow::on_sbIDGoleiro_valueChanged(int arg1)
{
    config.idGoleiro = arg1;
}
