#ifndef ROBO_H
#define ROBO_H

#include "definitions.h"

class Robo
{
public:
    //! Construtor
    Robo(int id = 0,bool equipe=true);
    ~Robo();

    // Funções de Interface
    //Posicao
    void setPosicao(Mat_<float> & _pos);
    void setPosicao(float x, float y,float theta);
    Mat_ <float> getPosicao();

    void setConfiabilidade(float _conf);
    float getConfiabilidade();

    //Velocidade Linear
    void setVelocidade(Mat_<float> & _vel);
    Mat_<float> getVelocidade();

    //Id
    void setId(int _id);
    int getId();

    bool foiAchado();

    void incrementaContadorNaoAchado();
    void incrementaContadorAchado();

    //Função de Impressão
    friend ostream &operator<<(ostream &stream, Robo robo);

    void predicaoKalman();
    void correcaoKalman();


private:

    void inicializaKalman();
    Mat_<float> posicao;
    Mat_<float> velocidade;

    Mat_<float> Xkm1; //utilizado para estimar velocidade de robôs adversários

    cv::KalmanFilter kalman;

    int id;         //id do robô
    bool time;      //time, true = equipe, false = adversário

    float confiabilidade;

    int contFramesNaoAchado;
    int contFramesAchado;

    bool achado;

};

#endif // ROBO_H
