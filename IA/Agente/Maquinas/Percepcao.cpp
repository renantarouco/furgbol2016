#include "Percepcao.h"
#include <Sistema.h>
#include <Geometria.h>

Percepcao::Percepcao(){
}

void Percepcao::setIdRobo(int _idRobo){
    idRobo = _idRobo;
}

bool Percepcao::isAlvoGirarIgualPosRobo(const Ponto &pontoParaGirar, bool horario, int _idRobo)
{
    /// Calculando o alvo que o robo ira girar ao redor do ponto para nao bater
    Ponto alvoGirar = Sistema::avaliador.calcularAlvoGirar(pontoParaGirar, horario, _idRobo);

    /// Verificando se os alvos estao no mesmo ponto
    return squared_distance(alvoGirar, Sistema::modeloMundo.getRoboEq(_idRobo)->getPosicao()) < ConfigAvaliador::TOL_PERTENCE_ALVO*ConfigAvaliador::TOL_PERTENCE_ALVO;
}

bool Percepcao::isAlvoMudou(const Ponto& alvoMudou){

    /// Calculando a tolerância que iremos considerar do robô ter mudado de alvo dependendo da distancia entre o alvo antigo e o atual
    double tolMesmoAlvo = ConfigAvaliador::TOL_MESMO_ALVO * ConfigAvaliador::TOL_MESMO_ALVO;

    /// Calculando a distância entre os alvos
    double distAlvos = squared_distance(Sistema::modeloMundo.getRoboEq(idRobo)->getComando().getAlvoFinal(), alvoMudou);

    /// Verificando se a distância é maior que o limiar se for então o alvo foi alterado, caso contrário não foi alterado
    if(distAlvos > tolMesmoAlvo){
        return true;
    }

    return false;
}

bool Percepcao::isFrenteParaBola(){
    Vetor oriRobo = Sistema::modeloMundo.getRoboEq(idRobo)->getVetorOrientacao();
    Vetor bolaRobo(Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao(), Sistema::modeloMundo.getBola()->getPosicao());


    float angulo = Geometria::calcularAnguloVetores(oriRobo, bolaRobo);
    Vetor soma = oriRobo + bolaRobo;

    if(soma.squared_length() > bolaRobo.squared_length())
        return angulo < ConfigAvaliador::TOL_ORIENTACAO;

    return false;
}

bool Percepcao::isFrenteParaBolaDrible()
{
    Vetor oriRobo = Sistema::modeloMundo.getRoboEq(idRobo)->getVetorOrientacao();
    Vetor bolaRobo(Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao(), Sistema::modeloMundo.getBola()->getPosicao());


    float angulo = Geometria::calcularAnguloVetores(oriRobo, bolaRobo);
    Vetor soma = oriRobo + bolaRobo;

    if(soma.squared_length() > bolaRobo.squared_length())
        return angulo < 10.f*M_PI/180.f;

    return false;
}

bool Percepcao::isAlvoMarcado(const Ponto& alvo){
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao(); /// Pegando a posição atual do robo

    /// Calculando a tolerância admitada para o robô pertencer ao alvo
    double tolPertencerAlvo = ConfigAvaliador::TOL_PERTENCE_ALVO*ConfigAvaliador::TOL_PERTENCE_ALVO;

    /// Calculando a distância do robô ao alvo
    double distRoboAlvo = squared_distance(posRobo,alvo);

    /// Verificando se a distância do robô ao alvo é menor que a tolerância admitida para o robô está em cima do alvo
    if(distRoboAlvo < tolPertencerAlvo){
        return true;
    }

    return false;
}

bool Percepcao::isDentroRaioAprox(){

    /// Calculando a distância que o robô está de bola
    float squaredDistRoboBola = squared_distance(Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao(), Sistema::modeloMundo.getBola()->getPosicao());

    /// Verificando se a distância do robô é menor que a tolerância para o robô começar a virar pra ficar de frente pra bola.
    return squaredDistRoboBola < ConfigAvaliador::RAIO_APROX*ConfigAvaliador::RAIO_APROX;
}

bool Percepcao::isBolaPertoParaChute(){
    /// Calculando a distância que o robô pestá da bola
    float squaredDistRoboBola = squared_distance(Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao(), Sistema::modeloMundo.getBola()->getPosicao());

    /// Verificando se o robo esta perto da bola para chutar
    return squaredDistRoboBola < ConfigAvaliador::TOL_TOQUE * ConfigAvaliador::TOL_TOQUE;
}

bool Percepcao::isAnguloParaChute(float anguloChute){

    Ponto posRobo = Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao();  /// Pegando a posição do robo
    Ponto posAlvoChute = Sistema::modeloMundo.getRoboEq(idRobo)->getComando().getAlvoChute(); /// Pegando a posição do alvo
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao(); /// Pegando a posição da bola

    //    Reta retaAlvoBola(posAlvoChute, posBola);
    //    Circulo circAprox(posBola, Avaliador::RAIO_APROX * Avaliador::RAIO_APROX );

    //    vector<Ponto> pontosInter = interseccaoRetaCirculo(retaAlvoBola, circAprox);

    //    /// obrigatoriamente vao existir dois pontos de itersecção
    //    Ponto pontoMeio; /// O ponto no meio do arco onde vai ser criado.
    //    if(squared_distance(pontosInter[0], posAlvoChute) > squared_distance(pontosInter[1], posAlvoChute)){
    //        pontoMeio = pontosInter[0];
    //    }else{
    //        pontoMeio = pontosInter[1];
    //    }

    //    float raioCircAux = tan(anguloChute/2.0) * Avaliador::RAIO_APROX;
    //    cout << "raio do circulo menor de aproximacao: " << anguloChute << endl;

    //    /// agora os pontos de interseccao assumem os pontos do arco de circunferencia
    //    pontosInter = interseccaoCirculoCirculo(circAprox, Circulo(pontoMeio, raioCircAux*raioCircAux));

    //    Triangulo triangulo(posBola, pontosInter[0], pontosInter[1]); /// cria um triangulo onde o robo deve ficar para ser considerado hábil a chutar

    Vetor bolaAlvo(posBola, posAlvoChute); /// Cria Vetor Bola Alvo
    // Vetor bolaRobo(posBola, posRobo);  /// Cria Vetor Robo Bola
    Vetor roboBola(posRobo,posBola);
    //Vetor roboAlvo(posRobo,posAlvoChute); /// cria vetor robo Alvo

    /// Verifica se ele ta mais perto do alvo que a bola
    if(squared_distance(posRobo, posAlvoChute) >= squared_distance(posBola, posAlvoChute)){

        /// Iremos aumentar o angulo de chute para os robos que nao possuem chute, para eles poderem empurrar a bola ate o gol adversario
        //        if(!_temChute){
        //            anguloChute *= 1.5;
        //        }

        /// Verificando se o angulo entre os vetores é menor que o angulo usado como tolerância para chutar
        float anguloVetores = Geometria::calcularAnguloVetores(roboBola, bolaAlvo);

        if(Sistema::modeloMundo.isLadoCampoEsquerdo()){
            if(posRobo.x() > 0.0){
                return anguloVetores < anguloChute/2.0;
            }else{
                return anguloVetores < anguloChute;
            }
        }else{
            if(posRobo.x() < 0.0){
                return anguloVetores < anguloChute/2.0;
            }else{
                return anguloVetores < anguloChute;
            }
        }
    }

    //    cout << "Robo mais perto do ALvo do que a bola do alvo" << endl;
    return false;
}

bool Percepcao::isCarregarBola(){
    /// Atualizando a distância que o robo carregou a bola
    AvaliadorRobo avaliadorRobo(idRobo);
    avaliadorRobo.atualizarDistBolaCarregada();

    /// Pegando a distância que o robô carregou a bola
    float distCarregouBola = Sistema::modeloMundo.getRoboEq(idRobo)->getDistCarregouBola();

    /// Verificando se a distância que o robô carregou a bola é menor que a distância máxima
    if(distCarregouBola <= DISTANCIA_MAXIMA_CARREGANDO_BOLA)
        return true;

    return false;
}

bool Percepcao::getSentidoMaisPerto(const Ponto& alvo){
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(idRobo)->getPosicao();
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Cria dois vetores  e faz o produto vetorial dependendo do valor o sentido de giro é diferente.
    Vetor roboObjetivo(posRobo, alvo);
    Vetor roboBola(posRobo, posBola);

    /// Deixando os vetores unitarios
    roboBola = roboBola/sqrt(roboBola.squared_length());
    roboObjetivo = roboObjetivo/sqrt(roboObjetivo.squared_length());

    /// Seno > 0.0 girar horario, menor que 0.0 girar antihorario
    float seno = Geometria::produtoVetorial2D(roboBola, roboObjetivo); /// calculando o seno entre os angulos

    return seno > 0;
}

bool Percepcao::isBolaDentroCampo(){
    return Sistema::modeloMundo.getCampo()->isPontoDentro(Sistema::modeloMundo.getBola()->getPosicao());
}

bool Percepcao::isBolaChutada()
{
    /// variáveis auxiliares
    Bola* bola = Sistema::modeloMundo.getBola();
    Ponto posBola = bola->getPosicao();
    Ponto posBolaChutada = bola->getPosChutada();

    /// Verificando se a atual posicao da bola e maior que a tolerancia pra ser igual a posicao aonde ele esta antes de ser chutada
    if(squared_distance(posBola,posBolaChutada) > ConfigAvaliador::TOL_MESMO_ALVO * ConfigAvaliador::TOL_MESMO_ALVO){
        bola->setPosChutada(Ponto(6000.0,6000.0)); /// @todo verificar essa posicao se esta certo fazer isso
        return true;
    }

    return false;
}

bool Percepcao::isBolaQuaseSaindoCampo()
{
    Retangulo retangulo(Ponto(-Config::MEIO_COMPRIMENTO_CAMPO, -Config::MEIA_LARGURA_CAMPO+ 140.f), Ponto(Config::MEIO_COMPRIMENTO_CAMPO, Config::MEIA_LARGURA_CAMPO-140.f));
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    return !retangulo.has_on_bounded_side(posBola);
}

