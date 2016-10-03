#ifndef SISTEMA_H
#define SISTEMA_H

#include "GerenteDeliberativoCentral.h"
#include "Agente.h"
#include "Avaliador.h"
#include "CommunicationBUS.h"
#include "Relogio.h"
#include "ModeloMundo.h"
#include "DefendePonto.h"
#include "Chuta.h"
#include "Carregador.h"
#include "Definitions.h"

#include <QUdpSocket>

/*!
 * Classe que controla a execução do programa através de comandos da interface
 */

class Sistema : public QThread {
    Q_OBJECT

public:
    static ModeloMundo modeloMundo; /// instancia do modelo de mundo que vai ser global a todos os modulos
    static Avaliador avaliador; ///< Objeto usado para fazer avaliações da estratégia em relação ao time todo e não apenas para um determinado robo

private:
    GerenteDC gerenteCentral; ///< Objeto do gerente deliberativo usada para controlar a estrategia da equipe
    vector<Agente> agentes; /// O número de agentes depende de quantos foram enviados pelo gerente de dados
    unsigned int numAgentesAtivos;   /// < Variável contém o número de agentes em atividade para um dado momento na partida.

    QUdpSocket r_udpSocket; ///< receptor usado para receber pacotes de outros processos
    QMutex* mBUS; ///< mutex usado para controlar o acesso do objeto bus
    CommunicationBUS*  bus; ///< Barramento utilizado para comunicar a thread principal com a thread de comunicação.

    /// variáveis auxiliares usadas na execução do sistema
    Relogio relogio;
    map<int, vector< Tatica*> > papeisRobos;
    int iteracao;
    PacoteIASimulador2D pacoteSimulador2D;
    PacoteDados pacoteGD;
    QByteArray datagram;

public slots:
    void processPacotes();

public:
    Sistema();
    ~Sistema();

    void init(QMutex* _mBUS, CommunicationBUS* _barramentoComunicacao);

    void stop();

    void tratarPacoteRecebido();
    void addPacoteMonitoradorBUS();

    void run();

    /// Funções set
//    void setPosicoesAgentes(const vector<int> posicoes);
    void setPapeisAgentes(map<int, vector<Tatica*> > & papeis);
};

#endif // SISTEMA_H
