#ifndef BOLA_H
#define BOLA_H

#include "definitions.h"

class Bola
{
public:
    //! Construtor
    Bola();
    ~Bola();
    // Funções de Interface
    //Posicao
    void setPosicao(const Mat_<float>  & _pos);
    void setPosicao(float x, float y);
    Mat_<float> getPosicao();

    //PosZ
    void setZ(float _z);
    float getZ();

    //Velocidade
    void setVelocidade(const Mat_<float> & _vel);
    Mat_<float> getVelocidade();

    void setConfiabilidade(float _conf);
    float getConfiabilidade();

    //Função de Impressão
    friend ostream &operator<<(ostream &stream, Bola bola);
    void predicaoKalman();
    void correcaoKalman();


private:

    void inicializaKalman();

    Mat_<float> Xkm1; //Usada para estimar velocidade

    float confiabilidade;
    Mat_<float> posicao;
    float z; //! Colocar junto no Ponto posicao?
    Mat_ <float> velocidade;
    cv::KalmanFilter kalman;
};

#endif // BOLA_H
