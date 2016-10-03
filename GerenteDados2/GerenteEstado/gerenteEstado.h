#ifndef GERENTEESTADO_H
#define GERENTEESTADO_H

#include "definitions.h"
#include "config.h"

#include <messages_robocup_ssl_referee.pb.h>

class GerenteEstado
{
public:
    Config* config;

    SSL_Referee pacote;
    string estadoAtual, estadoAnt;
    int idGoleiroEq, idGoleiroAdv;

    GerenteEstado(Config* _config);
};

#endif // GERENTEESTADO_H
