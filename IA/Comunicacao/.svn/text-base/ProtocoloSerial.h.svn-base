#ifndef PROTOCOLOSERIAL_H
#define PROTOCOLOSERIAL_H

#include "Comando.h"
#include "Definitions.h"


/**
  \class ProtocoloSerial

    \brief  Classe responsável pela organização e serialização do pacote de envio serial
  */

class ProtocoloSerial
{
public:

    ProtocoloSerial();

    void setId(unsigned char _id);
    void limpaPacote();


    void setVelocidadePercentualRodas(int numRoda, unsigned char _vel);
    void setVelocidadePercentualRodas(vector <unsigned char> _vel);

    void setDirecaoRodas(int numRoda, Direcao _dir);
    void setDirecaoRodas(vector<Direcao> _dir);

    void setVelocidadePercentualDriblador(unsigned char _vel);
    void setDirecaoDriblador(Direcao _dir);

    void setTipoChute(Comando::TipoChute _tipoChute);

    void setNivelChute(unsigned char _nivelPercentual);

    void setEnableDrible(bool _enable);

    void setEnableChute(bool _enable);

    void serializa(vector <unsigned char> & buffer) const;

    friend ostream & operator<<(ostream & out, ProtocoloSerial pct);


private:
    unsigned char id;
    vector <unsigned char> velocidadePercentualRodas;
    unsigned char velocidadePercentualDriblador;
    vector <Direcao> direcaoRodas;
    Direcao direcaoDriblador;
    Comando::TipoChute tipoChute;
    unsigned char nivelChute;
    unsigned char enableChute;
    bool enableDrible;


    //para o modelo cinemático

    float raio;                     //Raio do Robo
    float raioDaRoda;               //Raio da roda do robo

    cv::Mat_ <float> matrizRotacao;     //Matriz para transformar o sist de coordenadas do global para o do robo
    cv::Mat_ <float> M;                 //Matriz de transformação de velocidades vx,vy,vgiro para as rodas
    cv::Mat_ <float> pInvM;             //Matriz pseudo inversa da matriz M

    static const int VEL_MAX_RODAS = 126;   //!< DESCOBRIR ESSE VALOR
};

#endif // PROTOCOLOSERIAL_H
