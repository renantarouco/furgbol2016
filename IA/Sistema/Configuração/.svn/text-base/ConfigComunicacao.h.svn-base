#ifndef CONFIGCOMUNICACAO_H
#define CONFIGCOMUNICACAO_H

#include "Definitions.h"

/**
  Guarda configurações de comunicação com IPS e portas.

*/
class ConfigComunicacao
{

public:
    ConfigComunicacao();

    static TipoRobos TIPO_ROBOS;
    static string DISPOSITIVO_SERIAL;

    static bool USAR_REFEREE;
    static bool ENVIA_MONITORADOR;

    static int NUM_PACOTES_SERIAL;
    static int NUM_PACOTES_SIMULADOR;
    static int NUM_PACOTES_MONITORADOR;

    static int REP_PACOTES_SERIAL;///< número de vezes que iremos repetir o processo de envio dos pacotes para a serial
    static int REP_PACOTES_MONITORADOR; ///< número de vezes que iremos repetir o processo de envio dos pacotes para o monitorador

    static Address ADDRESS_SIMULADOR;
    static Address ADDRESS_MONITORADOR;

    static int PORTA_RECEBE_GD;
    static int PORTA_RECEBER;

    static void load(string pathConfig=PATH_CONFIG);
};

#endif // CONFIGCOMUNICACAO_H
