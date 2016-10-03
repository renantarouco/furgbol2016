#include "config.h"

Config::Config()
{
    idGoleiro = 0;

    corEquipe = Amarelo;
    ladoCampo = ESQUERDO;
    fonte = SSL_VISION;

    portSendIA = 8765;
    ipSendIA = "127.0.0.1";
    hostAddressIA = QHostAddress(ipSendIA);

    portReceiveVision = 10020;//10018
    ipReceiveVision = "127.0.0.1";
    groupVision = QHostAddress(ipReceiveVision);

    portReceiveReferee = 10003;
    ipReceiveReferee = "224.5.23.1";
    groupReferee = QHostAddress(ipReceiveReferee);
}
