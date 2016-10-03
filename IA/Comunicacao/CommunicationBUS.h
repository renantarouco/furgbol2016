#ifndef BARRAMENTOCOMUNICACAO_H
#define BARRAMENTOCOMUNICACAO_H

#include "ProtocoloSerial.h"
#include "grSim_Packet.pb.h"
#include "mensagem_ia_simulador2D.pb.h"

class CommunicationBUS
{
private:
    vector<ProtocoloSerial*> pacoteSerial;  ///< vetor de pacotes contendo um para cada robo para enviar aos robos
    vector<grSim_Packet*> pacoteSim; ///< vetor de pacotes contendo um para cada robo para enviar ao simulador
    PacoteIASimulador2D* pacoteIaMonitorador;  /// Pacote que sera enviado ao monitorador, também a uma taxa determinada

public:
    CommunicationBUS();
    ~CommunicationBUS();

    void setPacoteRobo(int id, const ProtocoloSerial&);
    void limparPacoteRobo(int id);
    void setPacoteRobo(int id, const grSim_Packet&);
    void carregaPacoteMonitorador(const PacoteIASimulador2D& _pacoteIaMonitorador);

    ProtocoloSerial* getPacoteSerial(int id);
    grSim_Packet* getPacoteSimulador(int id);
    PacoteIASimulador2D* getPacoteMonitorador();
};

#endif // BARRAMENTOCOMUNICACAO_H
