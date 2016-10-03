#ifndef COMUNICADOR_H
#define COMUNICADOR_H

#include "Serial.h"
#include "CommunicationBUS.h"
#include "Relogio.h"
#include "Config.h"
#include "Definitions.h"

#include <QThread>
#include <QMutex>
#include <QUdpSocket>

/**
 * Comunica com os outros processos e com o robo
 */
class Comunicador : public QThread
{
private:
    bool jogando; ///< agora o comunicador também pode ser parado pela interface quando o jogo tiver terminado.

    /// Objetos usados para enviar os dados para o monitorador, simulador e para os robos pela serial
    QUdpSocket s_udpSocket; ///< Objeto usado para enviar pacotes
    Serial transSerial;

    QMutex* mBUS; ///< Mutex usado para controlar o acesso no objeto barramento que é compartilhado entre as thread Comunicador e Sistema
    CommunicationBUS* bus; ///< Barramento usado para setar os pacotes

public:
    Comunicador();

    /**
        Função que inicializa as variáveis necessárias para comunicação
    */
    void init(QMutex* _mBUS, CommunicationBUS * _barramentoComunicacao);
    void stop();

    /** Função que tem o loop da thread da comunicação da IA com os outros sistemas*/
    void run();

    /// funções que envia cada pacote especifico até o destino
    void send(const PacoteIASimulador2D& _pacoteMonitorador);
    void send(const grSim_Packet& _pacoteSimulador);
    void send(const ProtocoloSerial& _pacoteRobo);
};
#endif
