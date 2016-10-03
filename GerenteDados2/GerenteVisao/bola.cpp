#include "bola.h"

//using namespace std;
//using namespace CGAL;

/**
 \brief Construtor do tipo Bola

*/
Bola::Bola() : posicao(2,1), velocidade (2,1){

    z = 0;

//    inicializaKalman();
}

Bola::~Bola()
{


}

///////////////////////////////////////
//Funções de Interface
///////////////////////////////////////
/**
 \brief Função para setar a posiçao da bola.

 \param _pos Nova posicao da bola.
*/
void Bola::setPosicao(const Mat_<float> & _pos){
    _pos.copyTo(posicao);
}

void Bola::predicaoKalman(){
     Mat_<double> u;
     u = kalman.statePost - Xkm1;
//    kalman.predict(u);
}

void Bola::correcaoKalman(){
    //considero como se tu tivesse atualizado a posicao e orientacao ocm os dados da SSL
    Xkm1 = kalman.statePost.clone();
//    kalman.correct(posicao);
}

void Bola::inicializaKalman(){

    /**
        \brief Função de Inicialização do Filtro de Kalman para a bola
    */

    cv::Mat_<float> X(2,1);
    cv::Mat_<float> A(2,2);
    cv::Mat_<float> B(2,2);
    cv::Mat_<float> C(2,2);
    cv::Mat_<float> P(2,2);
    cv::Mat_<float> R(2,2);
    cv::Mat_<float> Q(2,2);
    //inicialização Kalman
    kalman.init(2,2,2);


    A = cv::Mat_<float>::eye(A.size());
    B = cv::Mat_<float>::zeros(B.size());
    C = cv::Mat_<float>::eye(2,2);
    P = cv::Mat_<float>::eye(P.size());
    R = cv::Mat_<float>::eye(R.size());                 //Multiplicar valor de erro de predição (ALTO)
    Q = cv::Mat_<float>::eye(Q.size())*0.00001;         //Multiplicar pelo erro da camera (desvio padrão da lente * distancia do foco)

    X = posicao.clone();

    /* Inicializar matrizes de erro */

    kalman.statePost = X;
    kalman.transitionMatrix = A;
    kalman.controlMatrix = B;
    kalman.measurementMatrix = C;
    kalman.errorCovPost = P;
    kalman.processNoiseCov = R;
    kalman.measurementNoiseCov = Q;

}

void Bola::setPosicao(float x, float y){
    posicao[0][0] = x;
    posicao[1][0] = y;
}

/**
 \brief Função para retornar a posiçao da bola.

 \return Posição atual da bola.
*/
Mat_<float> Bola::getPosicao(){
    return posicao;
}

/**
 \brief Função para setar a altura z da bola.

 \param _z Nova altura da bola.
*/
void Bola::setZ(float _z){
    z= _z;
}

/**
 \brief Função para retornar a altura da bola.

 \return Altura atual da bola.
*/
float Bola::getZ(){
    return z;
}

/**
 \brief Função para setar a velocidade da bola.

 \param _vel Nova velocidade da bola.
*/
void Bola::setVelocidade(const Mat_<float> & _vel){
    _vel.copyTo(velocidade);
}

/**
 \brief Função para retornar a velocidade da bola.

 \return Velocidade atual da bola.
*/
Mat_ <float> Bola::getVelocidade(){
    return velocidade;
}

void Bola::setConfiabilidade(float _conf){
    confiabilidade = _conf;
}

float Bola::getConfiabilidade(){
    return confiabilidade;
}



/**
    \brief Função de Impressão
*/
ostream &operator<<(ostream &stream, Bola bola){
    stream << "Bola:" << ":"<< std::endl;
   // stream << "Posicao: " << bola.posicao << " \t z = " << bola.z << std::endl;
   // stream << "Velocidade:  " << bola.velocidade << std::endl;
    return stream;
}

#ifdef TESTE_BOLA

//compile: g++ -DTESTE_BOLA bola.cpp -o testeBola -lCGAL


//usint namespace CGAL;
//usign namespace std;

int main(){
    Bola bola;
    bola.setPosicao(Point(2,3));
    bola.setVelocidade(Vector(1,1));
    bola.setZ(0);

    cout << bola << endl;

}

#endif
