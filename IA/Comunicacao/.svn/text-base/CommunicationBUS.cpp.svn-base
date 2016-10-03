#include "CommunicationBUS.h"

CommunicationBUS::CommunicationBUS()
{
    pacoteIaMonitorador = NULL;
    pacoteSerial.resize(NUM_MAX_ROBOS,NULL);
    pacoteSim.resize(NUM_MAX_ROBOS,NULL);
}

CommunicationBUS::~CommunicationBUS()
{
    delete pacoteIaMonitorador;

    for(uint i = 0; i< NUM_MAX_ROBOS; i++){
        if(pacoteSerial[i] != NULL)
            delete pacoteSerial[i];

        if(pacoteSim[i] != NULL)
            delete pacoteSim[i];
    }
}

void CommunicationBUS::setPacoteRobo(int id, const ProtocoloSerial & protocoloSerial)
{
    pacoteSerial[id] = new ProtocoloSerial;
    *pacoteSerial[id] = protocoloSerial;
}

void CommunicationBUS::limparPacoteRobo(int id)
{
    delete pacoteSerial[id];
    delete pacoteSim[id];
}

void CommunicationBUS::setPacoteRobo(int id, const grSim_Packet & pacoteGrSim)
{
    pacoteSim[id] = new grSim_Packet;
    *pacoteSim[id] = pacoteGrSim;

}

void CommunicationBUS::carregaPacoteMonitorador(const PacoteIASimulador2D &_pacoteIaMonitorador)
{
    pacoteIaMonitorador = new PacoteIASimulador2D;
    *pacoteIaMonitorador = _pacoteIaMonitorador;
}

ProtocoloSerial* CommunicationBUS::getPacoteSerial(int id)
{
    ProtocoloSerial* pacote = NULL;   /// aloca um espaco para o pacote a ser retirado do buffer

    if( pacoteSerial[id] != NULL){    /// se o pacote nao for nulo retira do buffer realmete ( delta)
        pacote = new ProtocoloSerial;
        *pacote = *pacoteSerial[id];
        delete pacoteSerial[id];
        pacoteSerial[id] = NULL;
    }

    return pacote;
}

grSim_Packet* CommunicationBUS::getPacoteSimulador(int id)
{
    /// retorna o pacote e apaga ele do vetor
    grSim_Packet* pacote = NULL;   /// aloca um espaco para o pacote a ser retirado do buffer

    if( pacoteSim[id] != NULL){ /// se o pacote nao for nulo retira do buffer realmete ( delta)
        pacote = new grSim_Packet;
        *pacote = *(pacoteSim[id]);
        delete pacoteSim[id];
        pacoteSim[id] = NULL;
    }

    return pacote;
}

PacoteIASimulador2D* CommunicationBUS::getPacoteMonitorador()
{
    PacoteIASimulador2D* pacote = NULL;

    if(pacoteIaMonitorador != NULL){
        pacote = new PacoteIASimulador2D;
        *pacote = *pacoteIaMonitorador;

        delete pacoteIaMonitorador;
        pacoteIaMonitorador = NULL;
    }

    return pacote;
}
