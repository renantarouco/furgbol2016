#include "robo.h"


/**
 \brief Construtor do tipo Robo

 \param _id Id do Robo.
*/
Robo::Robo(int _id, bool equipe){

    id = _id;
    time = equipe;

    contFramesNaoAchado = contFramesAchado = 0;

    posicao = Mat_<float>(3,1);
    velocidade = Mat_<float>(3,1);

    achado = false;

    inicializaKalman();
}

Robo::~Robo()
{

}

///////////////////////////////////////
//Funções de Interface
///////////////////////////////////////
/**
 \brief Função para setar a posiçao do robo.

 \param _pos Nova posicao do robo.
*/
void Robo::setPosicao(Mat_<float> &_pos){
    posicao = _pos.clone();
}

void Robo::setPosicao(float x, float y, float theta){
    posicao[0][0] = x;
    posicao[1][0] = y;
    posicao[2][0] = theta;
}

/**
 \brief Função para retornar a posiçao do robo.

 \return Posição atual da bola.
*/
Mat_<float> Robo::getPosicao(){
    return posicao;
}


void Robo::setConfiabilidade(float _conf){
    confiabilidade = _conf;
}



float Robo::getConfiabilidade(){
    return confiabilidade;
}


/**
 \brief Função para retornar a orientacao do bola.

 \return Altura atual da bola.
*/
//float Robo::getOrientacao(){
//    return orientacao;
//}

/**
 \brief Função para setar a velocidade linear do robo.

 \param _vel Nova velocidade do robo.
*/
void Robo::setVelocidade(Mat_<float> &_vel){
    velocidade = _vel;
}

/**
  \brief Função para setar o id do robo

  \param _id Novo id do robo
*/
void Robo::setId(int _id){
    id=_id;
}

/**
 \brief Função para retornar o id do robo.

 \return Id atual do robo.
*/
int Robo::getId(){
    return id;
}

bool Robo::foiAchado(){
    return achado;
}

void Robo::incrementaContadorNaoAchado(){   //REVISAR
    contFramesNaoAchado++;

    ///
    if(contFramesNaoAchado > NUM_FRAMES_NAO_ACHADO){
        achado = false;
        contFramesAchado = 0;
    }
}

void Robo::incrementaContadorAchado(){      //REVISAR
    contFramesAchado++;

    if(contFramesAchado > NUM_FRAMES_ACHADO){
        achado = true;
        contFramesNaoAchado = 0;
    }
}

void Robo::predicaoKalman(){

    cv::Mat_<float> u(3,1);

    if (time)
    {
    /*LUAN ADICIONAR CONTROLE AQUI*/
        u = velocidade.clone();
    }
    else
    {
    //Calcula controle através da velocidade atingida entre frames
        u = kalman.statePost - Xkm1;
    }

  //  kalman.predict(u);
}

void Robo::correcaoKalman(){
    //considero como se tu tivesse atualizado a posicao e orientacao com os dados da SSL

    Xkm1 = kalman.statePost.clone();
//    kalman.correct(posicao);


}

void Robo::inicializaKalman() { // true = nosso time, false = time adversário


    /**
        \brief Função de incialização do filtro de Kalman para os robôs
    **/

    cv::Mat_<float> X;  //Matriz de estados
    cv::Mat_<float> A;  //Matriz de transição de estados
    cv::Mat_<float> B;  //Matriz de controle
    cv::Mat_<float> C;  //Matriz de mapeamento da observação
    cv::Mat_<float> P;  //Matriz de covariância do erro
    cv::Mat_<float> R;  //Matriz de erro da odometria(previsão)
    cv::Mat_<float> Q;  //Matriz de erro da observação

    kalman.init(3,3,3);
    X = posicao.clone();
    A = cv::Mat_<float>::eye(3,3);
    B = cv::Mat_<float>::eye(3,3);
    C = cv::Mat_<float>::eye(3,3);
    P = cv::Mat_<float>::eye(3,3);
    R = cv::Mat_<float>::eye(3,3);       //Multiplicar pelo valor de erro da odometria (desvio padrão da moviemntação)
    Q = cv::Mat_<float>::eye(3,3)*0.00001;       //Multiplicar pelo erro da camera (desvio padrão da lente)

//    if (equipe)
//    {
//        R = R*0.01;
//        R(2,2) = 1.0;
//    }

    kalman.statePost = X;
    kalman.transitionMatrix = A;
    kalman.controlMatrix = B;
    kalman.measurementMatrix = C;
    kalman.errorCovPost = P;
    kalman.processNoiseCov = R;
    kalman.measurementNoiseCov = Q;
}

/**
    \brief Função de Impressão
*/
ostream &operator<<(ostream &stream, Robo robo){
    stream << "Robo:" << ":"<< std::endl;
    stream << "Id: " << robo.id << std::endl;
    stream << "Achado: " << robo.achado << std::endl;
    stream << "Posicao: (" << robo.posicao[0][0] << ", " << robo.posicao[1][0] << ")" << std::endl;
    stream << "Orientacao: "<< robo.posicao[2][0] << std::endl;
    stream << "VelLinear: (" << robo.velocidade[0][0] << " , " << robo.velocidade[1][0] << ")" << std::endl;
    stream << "VelAngular: " << robo.velocidade[2][0] << std::endl;
    return stream;
}


#ifdef TESTE_ROBO

//compile: g++ -DTESTE_ROBO robo.cpp -o testeRobo -lcv


//usint namespace CGAL;
//usign namespace std;

int main(){
    vector <Robo> robos;

    for(int i=0;i<5;i++){
        robos.push_back(Robo());
    }

    for(int i=0;i<5;i++){
        robos[i].setPosicao(i,i,i);
    }

    for(int i=0;i<5;i++){
        std::cout << robos[i] << std::endl;
    }





    return 0;

}

#endif
