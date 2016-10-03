#ifndef GERENTEVISAO_H
#define GERENTEVISAO_H

#include <messages_robocup_ssl_detection.pb.h>
#include <messages_robocup_ssl_geometry.pb.h>
#include <messages_robocup_ssl_wrapper.pb.h>
#include <mensagem_gerente_visao.pb.h>

#include "definitions.h"
#include "config.h"
#include "bola.h"
#include "robo.h"

class GerenteVisao
{
public:
    Bola bola;
    vector<Robo> robosEq; //Robos da Equipe
    vector<Robo> robosAdv; //Robos Adversários

    Config* config;

    int numFrameVisao;

    GerenteVisao(Config* _config);
    ~GerenteVisao();

    void setIdRoboEq(int numRobo, int id);
    void setIdRoboAdv(int numRobo, int id);

    void processPacket(const SSL_DetectionFrame &frameCam);

    PacoteVisao montaPacoteVisao();
};

#endif // GERENTEVISAO_H
