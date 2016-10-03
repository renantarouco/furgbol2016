#ifndef MONTADOR_H
#define MONTADOR_H

#include <opencv/cv.h>

#include <ProtocoloSerial.h>
#include <grSim_Packet.pb.h>
#include <Relogio.h>
#include <ConfigComunicacao.h>
#include <ConfigMontador.h>

/**
 * O montador é a parte da arquitetura onde se preocupa em passar alvos direçoes e comandos para pacotes definidos para o robo a serem enviados pela serial.
 */
class Montador
{

private:
    /// pacotes usados para nos comunicar com os robos
    ProtocoloSerial pacoteSerial;

    /**
      O modelo cinamatico esta associado a uma equação que permite
      decompor a velocidade do robo a partir de um sistema de cordenadas
      inercial externo ao robô em velocidades de rotação para cada roda.

      Uma equação que permite relacionar a postura do robô relativa ao sistema
      interno com a postura em relação ao sistema de coordenadas externo é a seguinte:

      Er = R(theta) Eo.

      Esta equação diz que ao aplicar uma rotação no eixo do robo no sistema interno é possivel se
      obter a postura do robo em relação ao sitema determinado  ( precisaria de uma translação ????)

      Er esta associado ao vetor velocidade x e y de cada roda e sua velocidade angular theta
      As equações para cada roda que podem ser representadas em matrizes são:

      xn = r*Qn*cos(p)  yn = -r*Qn*sen(p)  theta = -(r/L) * Qn

      com os sinais alterando em relação ao referencial de rotacao da roda.

      onde r é o raio da roda, p é o angulo de acao das rodas e Qn é a velocidade de rotacao das rodas
      O conjunto de equações das rodas pode ser representado por uma multiplicação de uma matriz (M) 4x3 e
      um vetor(n) contendo as velocidades de rotação que seriam

      Er = M * n

                |cos(p) cos(p) -cos(p) -cos(p)|
      e  M = r* |sin(p) -sin(p) -sin(p) sin(p)|
                |-1/L   -1/L    -1/L    -1/L  |

         n = [ q1,q2,q3,q4 ]

         Substituindo

         M*n = R(theta) * Eo


      Para a nosso caso queremos obter o n dado a posicao do robo.
      para isso basta isolar n na equação que teremos

      n = M^-1 * R(theta) * Eo

      M é um valor constante para o robo e pode ser calculado pela pseudo inversa
      R é um valor facilmente calculavel e E é a postura do robo.
    */
    void inicializaModeloCinematico2014();
    void inicializaModeloCinematico();

    cv::Mat_<float> pInvM;
    cv::Mat_<float> M;
    cv::Mat_<float> R;
    cv::Mat_<float> velRodas;
    int id;

    Relogio tempo;
    bool enableChute;
    float thetaAnterior;

public:
    Montador();

    void setId(int _id);

    //    void calculaVelSemControle();
    //    void calculaVelControleSKUBA_new();
    //    void calculaVelControleSKUBA();
    //    void calculaVelControleP();

    void calculaVelLinear();
    void calculaVelRodas();

    //    void calculaVelRodasAdv(int _id);
    //    void ajustaVelocidades();

    ProtocoloSerial criaPacoteSerial();
    grSim_Packet criaPacoteGrSim();

    double vel_atual, vel_ant;
    double velAngularAtual;
};
#endif
