#ifndef CONFIG_H
#define CONFIG_H

#include "definitions.h"

class Config
{
public:
    Config();

    int idGoleiro;

    CorEquipe corEquipe;
    FonteDados fonte;
    LadoCampo ladoCampo;

    QHostAddress hostAddressIA;
    QString ipSendIA;
    int portSendIA;

    QString ipReceiveVision;
    int portReceiveVision;
    QHostAddress groupVision;

    QString ipReceiveReferee;
    int portReceiveReferee;
    QHostAddress groupReferee;
};

#endif // CONFIG_H
