#include "Montador.h"

#include "Sistema.h"

Montador::Montador(){

    vel_atual=vel_ant=0.0;
    velAngularAtual=0.0;
    enableChute = true;
    thetaAnterior=0.0;
    pacoteSerial.setNivelChute(15);

    inicializaModeloCinematico();

    //cout << "Dentro do montador id " << id <<  "******************************"<<endl;
}

void Montador::setId(int _id){
    id = _id;
    pacoteSerial.setId(id);
}

void Montador::inicializaModeloCinematico2014(){

    //! Estas medidas estão em metros.

    /// O raio da roda é utilizado para determinar as velocidades das rodas e o raio do robo
    /// para se obter a velocidade angular do robo
    float raioDaRoda = 0.0275;
    //    float raio = 0.085;
    float raioRobo = 0.080;


    //--------MODELO CINEMÁTICO DO ROBO-----------
    float alpha1, alpha2;

    //angulos de ataque das rodas
    alpha1 = 45.0*M_PI/180.0;   //45°
    alpha2 = 37.0*M_PI/180.0;   //37°

    /// no nosso caso usamos uma mesma orientação com o sistema externo e interno.
    R = cv::Mat_<float>::eye(3,3);

    //inicializa a matriz M
    /// Aqui é quando inicializamos a matriz M especificado utilizando os valores do robo
    M = cv::Mat_<float>(3,4);
    M[0][0] = -cos(alpha1);     M[0][1] = -cos(alpha2);     M[0][2] =  cos(alpha2);      M[0][3] = cos(alpha1);
    M[1][0] =  sin(alpha1);     M[1][1] = -sin(alpha2);     M[1][2] = -sin(alpha2);      M[1][3] = sin(alpha1);
    M[2][0] = -1/raioRobo;          M[2][1] = -1/raioRobo;          M[2][2] =  -1/raioRobo;          M[2][3] = -1/raioRobo;

    M = raioDaRoda * M;     //isto é feito para calcular a velocidade angular das rodas posteriormente, e não a linear

    //calcula a matriz pseudo-inversa da matriz M

    /// essa matriz deve ser invertida e para isso o calculo da pseudo inversa da biblioteca open cv é realizado.
    pInvM = M.inv(cv::DECOMP_SVD);
}

void Montador::inicializaModeloCinematico(){

    //! Estas medidas estão em metros.

    /// O raio da roda é utilizado para determinar as velocidades das rodas e o raio do robo
    /// para se obter a velocidade angular do robo
    float raioDaRoda = 0.0275;
    //    float raio = 0.085;
    float raioRobo = 0.0825;


    //--------MODELO CINEMÁTICO DO ROBO-----------
    float alpha1, alpha2;

    //angulos de ataque das rodas
    alpha1 = 45.0*M_PI/180.0;   //45°
    alpha2 = 37.0*M_PI/180.0;   //37°

    /// no nosso caso usamos uma mesma orientação com o sistema externo e interno.
    R = cv::Mat_<float>::eye(3,3);

    //inicializa a matriz M
    /// Aqui é quando inicializamos a matriz M especificado utilizando os valores do robo
    M = cv::Mat_<float>(4,3);
    M[0][0] = -cos(alpha1);     M[0][1] = sin(alpha1);     M[0][2] = -raioRobo;
    M[1][0] = -cos(alpha2);     M[1][1] = -sin(alpha2);    M[1][2] = -raioRobo;
    M[2][0] =  cos(alpha2);     M[2][1] = -sin(alpha2);    M[2][2] = -raioRobo;
    M[3][0] =  cos(alpha1);     M[3][1] = sin(alpha1);     M[3][2] = -raioRobo;

    M = (1.0/raioDaRoda) * M;     //isto é feito para calcular a velocidade angular das rodas posteriormente, e não a linear

    //calcula a matriz pseudo-inversa da matriz M

    /// essa matriz deve ser invertida e para isso o calculo da pseudo inversa da biblioteca open cv é realizado.
    pInvM = M; //.inv(cv::DECOMP_SVD);
}


ProtocoloSerial Montador::criaPacoteSerial(){
    pacoteSerial.limpaPacote();
    Comando comando = Sistema::modeloMundo.getRoboEq(id)->getComando();

    /// calculando a velocidade do robo
    calculaVelLinear();

    /// aplicando o modelo cinematico para saber a velocidade angular de cada roda
    calculaVelRodas();

    for(int i=0;i<4;i++){
        pacoteSerial.setVelocidadePercentualRodas(i,(char)(fabs(velRodas[i][0])/ConfigMontador::MAX_VEL_RODAS*100));
        pacoteSerial.setDirecaoRodas(i, velRodas[i][0] < 0 ? HORARIO : ANTI_HORARIO);
    }

    pacoteSerial.setDirecaoDriblador(comando.getDirecaoDrible());
    pacoteSerial.setEnableDrible(comando.isUsaDrible());
    // pacote.setVelocidadePercentualDriblador(0); mudei para linha de cima. Luan
    pacoteSerial.setTipoChute(comando.getTipoChute());
    pacoteSerial.setEnableChute(comando.getTipoChute() != Comando::SEM_CHUTE);

    return pacoteSerial;
}

grSim_Packet Montador::criaPacoteGrSim(){

    grSim_Packet pacoteGrSim;

    /// calculando a velocidade do robo
    calculaVelLinear();

    cv::Mat_ <float> velRobo(3,1);

    Robo *robo = Sistema::modeloMundo.getRoboEq(id);

    //copia para uma matriz do opencv
    velRobo[0][0] = robo->getVelocidade().x();     //velocidade em x
    velRobo[1][0] = robo->getVelocidade().y();      //velocidade em y
    velRobo[2][0] = robo->getVelAngular();       //velocidade angular

    float orientacao = robo->getOrientacao();
    R[0][0] = cos(orientacao);       R[0][1] = sin(orientacao);
    R[1][0] = -sin(orientacao);      R[1][1] = cos(orientacao);

    //aplicação do modelo cinemático do robô
    velRobo = R*velRobo;

    pacoteGrSim.mutable_commands()->set_isteamyellow(Sistema::modeloMundo.isEqAmarelo());
    pacoteGrSim.mutable_commands()->set_timestamp(0);

    grSim_Robot_Command *comandos = pacoteGrSim.mutable_commands()->add_robot_commands();

    comandos->set_id(id);

    Comando::TipoChute tipoChute = robo->getComando().getTipoChute();

    if(tipoChute == Comando::SEM_CHUTE){
        comandos->set_kickspeedx(0);
        comandos->set_kickspeedz(0);
    }else if(tipoChute == Comando::CHUTE_BAIXO){
        comandos->set_kickspeedx(6);
        comandos->set_kickspeedz(0);
    }else if(tipoChute == Comando::CHUTE_ALTO){
        comandos->set_kickspeedx(2);
        comandos->set_kickspeedz(3);
    }

    comandos->set_wheelsspeed(false);
    comandos->set_spinner(robo->getComando().isUsaDrible());
    comandos->set_veltangent(velRobo[0][0]);
    comandos->set_velnormal(velRobo[1][0]);
    comandos->set_velangular(velRobo[2][0]);

    return pacoteGrSim;
}

void Montador::calculaVelLinear(){
    Robo * robo = Sistema::modeloMundo.getRoboEq(id);
    Comando comando = robo->getComando();
    const vector<Ponto>& alvos = comando.getAlvos();

    /// velocidade que o robo obteve na iteracao
    double moduloVel = 0.0; /// velocidade que o robo teoricamete ira assumir
    double tempoIteracao = tempo.getTempoPassado();  /// tempo de iteração em segundos
//    double velIteracao = sqrt((robo->getPosicao() - robo->getPosicaoAnt()).squared_length())/(tempoIteracao*1000.0); /// m/s

    ConfigSkill config_skill = ConfigMontador::CONFIG_SKILLS[robo->getSkill()];

    //    cout << ConfigMontador::aceleracao_ << endl;

    /// Calcula a distancia do robo ate o proximo alvo e depois calcula o resto do
    /// caminho a partir do tamanho do segmento definido pelo Path planning
    double distAlvo = sqrt(squared_distance(robo->getPosicao(),alvos[0]));

    /// se tiver mais de 1 alvo no path planning teremos que calcular o tamanho total dos segmentos
    if(alvos.size() > 1)
        distAlvo += PATH_PLANNING_MAX_TAM_SEGUIMENTOS*(alvos.size()-1);

    distAlvo /= 1000.0; /// convertendo para metros

    //    cout << "vel ideal: "<< vel_atual_ << endl;
    //    cout << "vel real: " << velIteracao << endl << endl;
    //    cout << "erro: " << vel_atual_ - velIteracao << endl;

    //    vel_atual_ = velIteracao;


    //    if(robo->getId()==1){
    //        cout << "Tempo interacao = " << tempoIteracao << endl;

    //        cout << "Vel interacao= " << velIteracao << endl;
    //        //    cout << vel_atual_ << endl;
    //        cout << "aceleracao = " << (vel_atual_-vel_ant_)/tempoIteracao << endl;

    //        cout << "dist alvo= " << distAlvo << endl;
    //    }

    /// se a distancia ate o alvo for menor que a distancia para parar, iremos comecar a diminuir a velocidade do robo
    //    if(vel_atual_ < config_skill.max_vel_aprox){
    //        cout << "entrando " << ConfigMontador::aceleracao_ << endl;
    //        moduloVel = vel_atual_ + ConfigMontador::aceleracao_*tempoIteracao;

    //        /// Verificando se a velocidade passa da maxima velocidade linear definida
    //        if(moduloVel >= config_skill.max_vel_linear){
    //            moduloVel=config_skill.max_vel_linear;
    //            cout << "entrando aqui " << config_skill.max_vel_linear << endl;
    //        }

    //    }else
    //    {

    /// Equacao de Torriceli para encontrar a distancia para comecar a parar
    double distComecarParar = (vel_atual*vel_atual - config_skill.max_vel_aprox*config_skill.max_vel_aprox)/(2.0*ConfigMontador::DESACELERACAO);

    //    double distComecarParar = (velIteracao*velIteracao - config_skill.max_vel_aprox*config_skill.max_vel_aprox)/(2.0*ConfigMontador::desaceleracao_);

    //    if(robo->getId()==1)cout << "Dist Parar= " << distComecarParar << endl;

    if(distAlvo > distComecarParar){
        moduloVel = vel_atual + ConfigMontador::ACELERACAO*tempoIteracao;

        /// Verificando se a velocidade passa da maxima velocidade linear definida
        if(moduloVel >= config_skill.max_vel_linear){
            moduloVel=config_skill.max_vel_linear;
        }

    }else {
        moduloVel = vel_atual - ConfigMontador::DESACELERACAO*tempoIteracao;

        /// Setando o modulo da velocidade caso fique menor do que a velocidade de aproximacao
        if(moduloVel <= config_skill.max_vel_aprox){
            moduloVel = config_skill.max_vel_aprox;
        }
    }

    //    if(robo->getId()==1)cout << "ModuloVel= " << moduloVel << endl << endl;
    //    }

    /// Calculando a orientacao final do robo
    Vetor orientacao = robo->getVetorOrientacao();
    Vetor orientacaoFinal = robo->getComando().getVetOrientacaoFinal();
    float res = Geometria::produtoVetorial2D(orientacao, orientacaoFinal);
    float theta = Geometria::calcularAnguloVetores(orientacao, orientacaoFinal);

    // Calculando o angulo entre os vetores da orientacao e da direcao pra saber para aonde ele deve girar
    float velAngular = ConfigMontador::P_GIRO*theta;
    if(velAngular >= config_skill.max_vel_angular){
        velAngular = config_skill.max_vel_angular;
    }else if (velAngular < config_skill.min_vel_angular){
        velAngular = config_skill.min_vel_angular;
    }

    if(res < 0)
        velAngular = -velAngular;

    robo->setVelAngular(velAngular);

    /// Calcular o vetor direcao unitario
    Vetor vetorDirecao(alvos[0] - robo->getPosicao());
    float modVetorDirecao = sqrt(vetorDirecao.squared_length());

    /// Verificando se o modulo e diferente de zero, caso seja iremos calcular o vetor e setar o modulo nele mesmo
    if(fabs(modVetorDirecao) > 0.001){
        vetorDirecao = vetorDirecao/modVetorDirecao;
        vetorDirecao = Vetor(vetorDirecao.x()*moduloVel, vetorDirecao.y()*moduloVel);
    }else{
        vetorDirecao = Vetor(0.0, 0.0);
    }
    robo->setVelocidade(vetorDirecao);

    /// Setando o tempo inicial e a velocidade atual
    tempo.setTempoInicial(tempo.getTempoDoDia());

    //    vel_ant_ = vel_atual_;
    vel_atual = moduloVel;

    cout << "velocidade linear: " << vel_atual << endl;
    cout << "velocidade angular: " << velAngular << endl;
}

void Montador::calculaVelRodas(){
    cv::Mat_ <float> velRobo(3,1);

    Robo *robo = Sistema::modeloMundo.getRoboEq(id);
    //cout << "orientacao = " << orientacao << endl;

    //copia para uma matriz do opencv
    velRobo[0][0] = robo->getVelocidade().x();     //velocidade em x
    velRobo[1][0] = robo->getVelocidade().y();      //velocidade em y
    velRobo[2][0] = robo->getVelAngular();       //velocidade angular
    //    cout <<  "Vel ang = " << velRobo[2][0] << endl;

    float orientacao = robo->getOrientacao();
    R[0][0] = cos(orientacao);       R[0][1] = sin(orientacao);
    R[1][0] = -sin(orientacao);      R[1][1] = cos(orientacao);

    //aplicação do modelo cinemático do robô
    velRodas = pInvM*R*velRobo;

    float velMaxRodaAtual = ConfigMontador::MAX_VEL_RODAS;
    float fator = velMaxRodaAtual / ConfigMontador::MAX_VEL_RODAS;

    //    cout << velMaxRodaAtual << endl;
    //    cout << fator << endl;

    //seleciona a maior das velocidades entre as rodas
    for(int i=0;i<4;i++){
        if(fabs(velRodas[i][0]) > velMaxRodaAtual){
            velRodas[i][0] = velRodas[i][0]/fator;
            //            velMaxRodaAtual = fabs(velRodas[i][0]);
        }
    }

    /// TODO colocar isso depois
    //                ajustaVelocidades();
}

//float Montador::calculaVelAngular(Ponto alvoFinal, Ponto posRobo, Vetor orientacao, Vetor direcao)
//{
//    float distanciaAlvo = sqrt(squared_distance(alvoFinal, posRobo));

//    float res = produtoVetorial2D(orientacao,direcao);

//    float denomidador = sqrt(orientacao.squared_length())*sqrt(direcao.squared_length());
//    float theta;
//    if (denomidador != 0){
//        theta= asin(fabs(res)/denomidador);
//    }else{
//        theta = 0;
//    }

//    float velAngular = 0.0;

//    if(distanciaAlvo < 800){

//        velAngular =  Pgiro*theta;
//        if(velAngular > MAX_VEL_ANGULAR){
//            velAngular = MAX_VEL_ANGULAR;
//        }else{
//            if (velAngular < MIN_VEL_ANGULAR){
//                velAngular =MIN_VEL_ANGULAR;

//                //cout << " SETOU VELOCIDADE MINIMA DE GIRO" << endl;
//            }
//        }
//        if(res < 0){
//            velAngular =  -velAngular;
//        }
//    }

//    return velAngular;
//}
