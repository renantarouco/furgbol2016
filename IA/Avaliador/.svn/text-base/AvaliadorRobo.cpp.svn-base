#include "AvaliadorRobo.h"
#include <Sistema.h>
#include <Geometria.h>

AvaliadorRobo::AvaliadorRobo(){
}

AvaliadorRobo::AvaliadorRobo(const AvaliadorRobo &_avaliador){
    id = _avaliador.id;
    retaSemiCirculo = _avaliador.retaSemiCirculo;
    alvoDefesaBaixo = _avaliador.alvoDefesaBaixo;
    alvoDefesaCima = _avaliador.alvoDefesaCima;
}

AvaliadorRobo::AvaliadorRobo(int _id){
    id = _id;
}

void AvaliadorRobo::setId(int _id){
    id = _id;
}

Ponto AvaliadorRobo::calcularAlvoAproximacao(const Ponto& alvo){

    /// variáveis auxiliares
    Ponto posBola =  Sistema::modeloMundo.getBola()->getPosicao();
    Ponto alvoAprox;
    float squaredRadiusCircle=ConfigAvaliador::RAIO_APROX*ConfigAvaliador::RAIO_APROX;

    //    cout << "vel. da bola: " << sqrt(Sistema::modeloMundo.getBola()->getVetorVelocidade().squared_length())/1000.0 << endl;

    /// Se o robo ja estiver dentro do raio de aproximacao nos iremos calcular um novo alvo de aproximacao de acordo com a distancia que o robo esta da bola
    float squaredDistRoboBola = squared_distance(posBola, Sistema::modeloMundo.getRoboEq(id)->getPosicao());
    if(squaredDistRoboBola < ConfigAvaliador::RAIO_APROX*ConfigAvaliador::RAIO_APROX){

        squaredRadiusCircle = squaredDistRoboBola;

        /// Verificando se o robo esta muito proximo da bola
        //        if(squaredDistRoboBola < (RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO)*(RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO)){
        //            squaredRadiusCircle = (RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO)*(RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO);
        //        }else{
        //squaredRadiusCircle = squaredDistRoboBola;
        //        }
    }else{
        squaredRadiusCircle = ConfigAvaliador::RAIO_APROX*ConfigAvaliador::RAIO_APROX;
    }

    //    cout << "lkjaklsjdkla" << endl;

    /// faz a intersecção de uma reta com um circulo e dependendo do lado do campo adversario pega o ponto com
    /// maior ou menor X.
    Reta retaAlvo(alvo, posBola);
    vector<Ponto> pontosInterseccao;

    /// calculando os pontos de interseccao entre o circulo e a reta
    Circulo circuloBola(posBola, squaredRadiusCircle);
    circuloBola.isInterseccaoReta(retaAlvo, pontosInterseccao);

    /// Calculando a distancia dos pontos ao alvo
    float dist0 = squared_distance(alvo, pontosInterseccao[0]);
    float dist1 = squared_distance(alvo, pontosInterseccao[1]);

    /// Pegando o ponto mais longe do alvo que sera o alvo de aproximacao do robo
    alvoAprox = dist0 < dist1 ? pontosInterseccao[1] : pontosInterseccao[0];

    /// pegando o ultimo alvo do robo
    Ponto _alvoAnterior = Sistema::modeloMundo.getRoboEq(id)->getComando().getAlvoFinal();

    /// Verificando se os alvos podem ser considerados os mesmos, se puderem não iremos precisar calcular um novo alvo
    if(_alvoAnterior != CGAL::ORIGIN){
        if(squared_distance(_alvoAnterior, alvoAprox) < ConfigAvaliador::TOL_PERTENCE_ALVO*ConfigAvaliador::TOL_PERTENCE_ALVO){
            alvoAprox = _alvoAnterior;
        }
    }

    //    cout << "jlakjskdlja" << endl;

    return alvoAprox;
}

IntPonto AvaliadorRobo::calcularAlvoParaChutarGol(){

    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Ponto centroGolAdv = campo->getAreaAdv()->getCentro();
    Bola* bola = Sistema::modeloMundo.getBola();

    /// Verificando se o robô está dentro da área para chute
    if(!campo->isPontoDentroAreaChute(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), true)){

        /// A principio utilizando uma estrategia simplificada para o alvo de aproximação
        /// O método pode futuramente ser refinado dependendo da posição do robo.

        float score = 0.0; /// Variável que iremos usar para analisar o quanto bom é o alvo
        float scoreCentro = 0.0; /// Variável que iremos usar para analisar o quanto bom é o alvo Central do gol
        /// Pegando as posições dos robôs que iremos analisar
        Segmento segmentoBolaGolAdv = Segmento(bola->getPosicao(), centroGolAdv);
        vector<Ponto> posRobos = Sistema::avaliador.getRobosEntrePontos(vector<int>(1, id), vector<int>(),
                                                                        segmentoBolaGolAdv, 1000.0);

        /// Calculando o quão bom é o alvo que iremos escolher
        scoreCentro = Sistema::avaliador.analisarScoreAlvo(bola->getPosicao(), centroGolAdv, posRobos, true);

        /// @todo dependendo do score e do grau de precisão dos robos tentar outros alvos dentro da goleira.
        IntPonto alvo = calcularMelhorAlvoPosicionarOuChutar(bola->getPosicao(), centroGolAdv, 300, 301,Tatica::PONTUACAO_LIMITE_CHUTE);
        score = alvo.first;

        if(scoreCentro < score) /// Assim feito para poder calcular tambem o score para o centro do gol
            score = scoreCentro;

        return IntPonto(int(score), centroGolAdv);
    }

    //        cout << "Alvo centro do gol" << endl;

    /// Definindo que o robô não poderá chutar pois ele não está dentro da área para chute
    return IntPonto(301, centroGolAdv);
}

Ponto AvaliadorRobo::calcularAlvoCarregarBola(const Ponto& destinoCarregamento){
    /// variáveis auxiliares
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();
    Ponto centroGolAdv = Sistema::modeloMundo.getCampo()->getAreaAdv()->getCentro();

    /// Se a bola esta no meio
    Ponto finalReta;

    /// Se a bola esta nos triangulos

    /// Criando os triangulos
    Ponto pontoSuperiorGoleira(centroGolAdv.x(), Config::MEIO_COMPRIMENTO_GOL+20);
    Ponto pontoInferiorGoleira(centroGolAdv.x(), -Config::MEIO_COMPRIMENTO_GOL-20);
    Ponto pontoCantoSuperior(centroGolAdv.x(), Config::MEIA_LARGURA_CAMPO);
    Ponto pontoCantoInferior(centroGolAdv.x(), -Config::MEIA_LARGURA_CAMPO);

    Ponto pontoSuperiorMeio;
    Ponto pontoInferiorMeio;
    if(Sistema::modeloMundo.isLadoCampoEsquerdo()){
        pontoSuperiorMeio = Ponto(Config::MEIA_LARGURA_CAMPO, (Config::LARGURA_CAMPO+1350)/2);
        pontoInferiorMeio = Ponto(0,-((Config::LARGURA_CAMPO+1350)/2));
    }else{
        pontoSuperiorMeio = Ponto(0,(Config::LARGURA_CAMPO+1350)/2);
        pontoInferiorMeio = Ponto(0,-((Config::LARGURA_CAMPO+1350)/2));
    }

    Triangulo tSuperior(pontoSuperiorGoleira, pontoCantoSuperior, pontoSuperiorMeio);
    Triangulo tInferior(pontoInferiorGoleira, pontoCantoInferior, pontoInferiorMeio);

    /// Se a bola esta no triangulo superior ou inferior
    if(tSuperior.has_on_bounded_side(posBola) || tInferior.has_on_bounded_side(posBola)){
        finalReta = Ponto(0.0,0.0);
    }else{

        //        /// Se a bola esta no meio
        //        if(posBola.y() < 600 && posBola.y() > -600){
        //            /// caclulando o alvo que ira fazer parte do segmento criado entre este alvo e o gol para o robo ir até esse segmento
        //            finalReta = calcularMelhorAlvoPosicionarOuChutar(Sistema::modeloMundo.getCentroGolAdv(), Ponto(posBola.x(), 0),
        //                                                             500, Config::LARGURA_CAMPO, Tatica::PONTUACAO_LIMITE_CHUTE/2.0).first;
        //        }else{

        //            Ponto ponto(0.0,0.0);

        //            /// Se a bola esta na parte superior
        //            if(posBola.y() > 600){
        //                ponto = Ponto(posBola.x(), Config::MEIA_Config::LARGURA_CAMPO);

        //            }else{ /// Se a bola esta na aprte inferior
        //                ponto = Ponto(posBola.x(), -Config::MEIA_Config::LARGURA_CAMPO);
        //            }

        //            finalReta = calculaMelhorAlvoPosicionarOuChutarInferior(Sistema::modeloMundo.getCentroGolAdv(), ponto,
        //                                                                    500, Config::LARGURA_CAMPO, Tatica::PONTUACAO_LIMITE_CHUTE/2.0).first;
        //        }

        Ponto ponto(0.0,0.0);

        /// Se a bola esta na parte superior
        if(posBola.y() > 600){
            ponto = Ponto(posBola.x(), Config::MEIA_LARGURA_CAMPO);

        }else{ /// Se a bola esta na aprte inferior
            ponto = Ponto(posBola.x(), -Config::MEIA_LARGURA_CAMPO);
        }

        /// calculando o alvo que será o final da reta
        IntPonto alvo = calculaMelhorAlvoPosicionarOuChutarInferior(centroGolAdv, ponto, 500, Config::LARGURA_CAMPO, Tatica::PONTUACAO_LIMITE_CHUTE/2.0);
        finalReta = alvo.second;
    }

    /// calcula o segmento onde o robo vai levar o melhor ponto
    Reta retaAlvo(destinoCarregamento, finalReta);

    /// Calcula o ponto medio do segmento onde vai ser iniciado o calculo.
    Ponto medioSegmento((destinoCarregamento.x() + finalReta.x())/2.0,(destinoCarregamento.y() + finalReta.y())/2.0);

    /// Calcula o deslocamento maximo da reta na funcao
    float deslocMaximo = sqrt(squared_distance(finalReta,destinoCarregamento))/2;

    IntPonto alvo = calcularMelhorAlvoPosicionarOuChutar(posBola, medioSegmento, retaAlvo, 100, deslocMaximo, Tatica::PONTUACAO_LIMITE_CHUTE/2.0);
    return alvo.second;
}

IntPonto AvaliadorRobo::calcularMelhorAlvoPosicionarOuChutar(const Ponto &pontoFixo, const Ponto & alvoPosicionarOuChutar, float deslocamento, float deslocMaximo,int scoreCorte){

    float menorScore = numeric_limits<float>::infinity(); /// Esse valor é usado para não analisarmos os scores acima desse valor.
    float score;                  /// Valor do score que iremos retornar
    Ponto alvo;                   /// Ponto que temos que posicionar o robô para poder efetuar o chute.
    Ponto melhorAlvo;             /// Calcula o melhor alvo a ser retornado

    /** Nesse for iremos fazer a iteração de um jeito com que ele fique variando os lados do campo que ele irá
        analisar de modo que fica uma coisa do tipo: 1, -1, 2, -2, 3, -3, ....*/
    //cout << " Na calculaMelhorAlvoPosicionarOuChutar " << endl;
    for(int i = 1; i * deslocamento < deslocMaximo; i++){
        /// Esse fato iremos multiplicar pelo deslocamento para que possamos e aumentando o deslocamento em y que temos que fazer
        int fator;

        if(i % 2 != 0) fator = -((i + 1)/2); /// Se o resto da divisão de i e 2 for diferente de zero indica que iremos analisar o valor abaixo do destinoInicial
        else fator = (i + 1)/2;            /// Senão iremos analisar os pontos acima do destinoInicial

        //cout << fator*deslocamento << endl;
        /// Criando um novo alvo com base no deslocamento multiplicado pelo fator
        alvo = Ponto(alvoPosicionarOuChutar.x(), alvoPosicionarOuChutar.y() + fator * deslocamento);

        /// Pegando as posições dos robôs para analisar
        vector<Ponto> posRobos = Sistema::avaliador.getRobosEntrePontos(vector<int>(1, id), vector<int>(),
                                                                        Segmento(alvo, pontoFixo), 1000);
        /// Calculando o score com base nesses dois pontos
        score = Sistema::avaliador.analisarScoreAlvo(alvo, pontoFixo, posRobos, true);
        //cout << " SCORE " << score << endl;
        /// Se o score for menor que o valor setado anteriormente então iremos substutiur o menor score encontrado
        if(menorScore > score){
            melhorAlvo = alvo;
            menorScore = score;
        }

        /// Se o score calculado foi menor que o limite para chute, então iremos pegar esse ponto que calculamos
        if(score < scoreCorte)
            break;
    }
    //cout << " Retornando o alvo de score " << menorScore << endl;
    /// Ponto com o melhor alvo e score calculados
    return IntPonto(int(menorScore), melhorAlvo);
}


IntPonto AvaliadorRobo::calcularMelhorAlvoPosicionarOuChutar(const Ponto &pontoFixo, const Ponto &alvoPosicionarOuChutar, const Reta &retaDeslocamento, float deslocamento, float deslocMaximo,int scoreCorte){

    float menorScore = numeric_limits<float>::infinity(); /// Esse valor é usado para não analisarmos os scores acima desse valor.
    float score;                  /// Valor do score que iremos retornar
    Ponto alvo;                   /// Ponto que temos que posicionar o robô para poder efetuar o chute.
    Ponto melhorAlvo;           /// Calcula o melhor alvo a ser retornado
    /** Nesse for iremos fazer a iteração de um jeito com que ele fique variando os lados do campo que ele irá
        analisar de modo que fica uma coisa do tipo: 1, -1, 2, -2, 3, -3, ....*/

    //cout << " Na calculaMelhorAlvoPosicionarOuChutar " << endl;
    for(int i = 1; i * deslocamento < deslocMaximo; i++){

        /// Esse fato iremos multiplicar pelo deslocamento para que possamos e aumentando o deslocamento em y que temos que fazer
        int fator;

        if(i % 2 != 0) fator = -((i + 1)/2); /// Se o resto da divisão de i e 2 for diferente de zero indica que iremos analisar o valor abaixo do destinoInicial
        else fator = (i + 1)/2;              /// Senão iremos analisar os pontos acima do destinoInicial

        //cout << fator*deslocamento << endl;
        /// Pega o ponto na reta que está a um deslocamento do destino Inicial que passamos.
        alvo = Geometria::calcularPontoEmRetaComDesloc(alvoPosicionarOuChutar, retaDeslocamento, fator * deslocamento);

        /// Pegando as posições dos robôs para analisar
        vector<Ponto> posRobos = Sistema::avaliador.getRobosEntrePontos(vector<int>(1, id), vector<int>(),Segmento(alvo, pontoFixo), 1000.0);

        /// Calculando o score com base nesses dois pontos
        score = Sistema::avaliador.analisarScoreAlvo(alvo, pontoFixo, posRobos,true);
        //cout << " SCORE " << score << endl;
        /// Se o score for menor que o valor setado anteriormente então iremos substutiur o menor score encontrado
        if(menorScore > score){
            melhorAlvo = alvo;
            menorScore = score;
        }

        /// Se o score calculado foi menor que o limite para chute, então iremos pegar esse ponto que calculamos
        if(score < float(scoreCorte))
            break;
    }

    //cout << " Retornando o alvo de score " << menorScore << endl;
    /// Ponto com o melhor alvo e score calculados
    return IntPonto(int(menorScore), melhorAlvo);
}

IntPonto AvaliadorRobo::calculaMelhorAlvoPosicionarOuChutarSuperior(const Ponto &pontoFixo, const Ponto & alvoPosicionarOuChutar, float deslocamento, float deslocMaximo,int scoreCorte){

    float menorScore = numeric_limits<float>::infinity(); /// Esse valor é usado para não analisarmos os scores acima desse valor.
    float score;                  /// Valor do score que iremos retornar
    Ponto alvo;                   /// Ponto que temos que posicionar o robô para poder efetuar o chute.
    Ponto melhorAlvo;             /// Calcula o melhor alvo a ser retornado
    /** Nesse for iremos fazer a iteração de um jeito com que ele fique variando os lados do campo que ele irá
        analisar de modo que fica uma coisa do tipo: 1, -1, 2, -2, 3, -3, ....*/
    //cout << " Na calculaMelhorAlvoPosicionarOuChutar " << endl;
    for(int i = 1; i * deslocamento < deslocMaximo; i++){
        /// Esse fato iremos multiplicar pelo deslocamento para que possamos e aumentando o deslocamento em y que temos que fazer
        /// Senão iremos analisar os pontos acima do destinoInicial

        //cout << i*deslocamento << endl;
        /// Criando um novo alvo com base no deslocamento multiplicado pelo fator
        alvo = Ponto(alvoPosicionarOuChutar.x(), alvoPosicionarOuChutar.y() + i * deslocamento);

        /// Pegando as posições dos robôs para analisar
        vector<Ponto> posRobos = Sistema::avaliador.getRobosEntrePontos(vector<int>(1, id), vector<int>(),
                                                                        Segmento(alvo, pontoFixo), 1000);
        /// Calculando o score com base nesses dois pontos
        score = Sistema::avaliador.analisarScoreAlvo(alvo, pontoFixo, posRobos, true);
        ///cout << " SCORE " << score << endl;
        /// Se o score for menor que o valor setado anteriormente então iremos substutiur o menor score encontrado
        if(menorScore > score){
            melhorAlvo = alvo;
            menorScore = score;
        }

        /// Se o score calculado foi menor que o limite para chute, então iremos pegar esse ponto que calculamos
        if(score < scoreCorte)
            break;
    }
    //cout << " Retornando o alvo de score " << menorScore << endl;
    /// Ponto com o melhor alvo e score calculados
    return IntPonto(int(menorScore), melhorAlvo);
}

IntPonto AvaliadorRobo::calculaMelhorAlvoPosicionarOuChutarInferior(const Ponto &pontoFixo, const Ponto &alvoPosicionarOuChutar, float deslocamento, float deslocMaximo, int scoreCorte){

    float menorScore = numeric_limits<float>::infinity(); /// Esse valor é usado para não analisarmos os scores acima desse valor.
    float score;                  /// Valor do score que iremos retornar
    Ponto alvo;                   /// Ponto que temos que posicionar o robô para poder efetuar o chute.
    Ponto melhorAlvo;             /// Calcula o melhor alvo a ser retornado
    /** Nesse for iremos fazer a iteração de um jeito com que ele fique variando os lados do campo que ele irá
        analisar de modo que fica uma coisa do tipo: 1, -1, 2, -2, 3, -3, ....*/
    //cout << " Na calculaMelhorAlvoPosicionarOuChutar " << endl;
    for(int i = 1; i * deslocamento < deslocMaximo; i++){
        /// Esse fato iremos multiplicar pelo deslocamento para que possamos e aumentando o deslocamento em y que temos que fazer
        int fator = -1*i;
        //cout << deslocamento << endl;
        //cout << fator*deslocamento << endl;
        /// Criando um novo alvo com base no deslocamento multiplicado pelo fator
        alvo = Ponto(alvoPosicionarOuChutar.x(), alvoPosicionarOuChutar.y() + fator * deslocamento);

        /// Pegando as posições dos robôs para analisar
        vector<Ponto> posRobos = Sistema::avaliador.getRobosEntrePontos(vector<int>(1, id), vector<int>(),
                                                                        Segmento(alvo, pontoFixo), 1000);
        /// Calculando o score com base nesses dois pontos
        score = Sistema::avaliador.analisarScoreAlvo(alvo, pontoFixo, posRobos, true);
        //cout << " SCORE " << score << endl;
        /// Se o score for menor que o valor setado anteriormente então iremos substutiur o menor score encontrado
        if(menorScore > score){
            melhorAlvo = alvo;
            menorScore = score;
        }

        /// Se o score calculado foi menor que o limite para chute, então iremos pegar esse ponto que calculamos
        if(score < scoreCorte)
            break;
    }
    //cout << " Retornando o alvo de score " << menorScore << endl;
    /// Ponto com o melhor alvo e score calculados
    return IntPonto(int(menorScore), melhorAlvo);
}

Ponto AvaliadorRobo::calculaAlvoRegiaoInterceptaGolAdv(const Ponto &ponto, const float& raio){

    /// variáveis auxiliares
    Ponto centroGolAdv = Sistema::modeloMundo.getCampo()->getAreaAdv()->getCentro();

    /// Criando a reta do gol adversário com o ponto central da região, onde o robô irá se posicionar.
    Reta retaCentroGolAdvPontoRegiao = Reta(centroGolAdv, ponto);

    /// Pegando a reta que é perpendicular a reta do gol adversário e do centro da região.
    /// Essa é a reta que iremos posicionar o robô em uma melhor posição.
    Reta retaDeslocamento = retaCentroGolAdvPontoRegiao.perpendicular(ponto);

    /// Calculando o melhor ponto da reta que iremos posicionar o robô, um ponto que faça interseção com o gol adversário.
    IntPonto alvo = calcularMelhorAlvoPosicionarOuChutar(centroGolAdv, ponto, retaDeslocamento, RAIO_ROBO, raio, Tatica::PONTUACAO_LIMITE_CHUTE);
    return alvo.second;
}

int AvaliadorRobo::getQtRobosRegiao(const Ponto& centro, const float& raio){

    Circulo circuloRegiao(centro, raio*raio);
    int qtRobos=0;
    vector<Robo>* robosEq = Sistema::modeloMundo.getRobosEq();
    vector<Robo>* robosAdv = Sistema::modeloMundo.getRobosAdv();

    /// analisando todos os robos
    for(int id=0;id<NUM_MAX_ROBOS;id++){

        /// verificando se o robo está presente e se o id dele é diferente do robo que está fazendo a avaliação
        Robo roboEq = robosEq->at(id);
        if(roboEq.isPresente() && id != this->id){

            /// Se a distância da posição do robô ao centro da região for menor ou igual ao raio, então o robô está dentro da região.
            if(circuloRegiao.has_on_bounded_side(roboEq.getPosicao()))
                qtRobos++;
        }

        /// verificando se o robo está presente
        Robo roboAdv = robosAdv->at(id);
        if(roboAdv.isPresente()){

            /// Se a distância da posição do robô ao centro da região for menor ou igual ao raio, então o robô está dentro da região.
            if(circuloRegiao.has_on_bounded_side(roboAdv.getPosicao()))
                qtRobos++;
        }
    }

    return qtRobos;
}

void AvaliadorRobo::atualizarDistBolaCarregada(){

    Robo* robo = Sistema::modeloMundo.getRoboEq(id);
    Ponto posAntRobo = robo->getPosicaoAnt(); /// Pegando a ultima posição do robo
    Ponto posAtualRobo = robo->getPosicao(); /// Pegando a posição atual do robo
    float distBolaCarregada = robo->getDistCarregouBola(); /// Pegando a distância que o robô carregou a bola

    /// Calculando a distância do robo a bola
    float distRoboBola = squared_distance(posAtualRobo, Sistema::modeloMundo.getBola()->getPosicao());

    /// Calculando a tolerância que o robô precisa estar perto da bola para identificar que ele continua carregando a bola
    float tolCarregarBola = ConfigAvaliador::TOL_TOQUE * ConfigAvaliador::TOL_TOQUE;

    /// Se a distancia for menor indica que o robô continua carregando a bola, caso contrário não está mais carregando a bola
    if(distRoboBola <= tolCarregarBola){
        distBolaCarregada += sqrt(squared_distance(posAtualRobo, posAntRobo));
    }else{
        distBolaCarregada = 0;
    }

    /// Setando a distância que o robo carregou a bola
    robo->setDistCarregouBola(distBolaCarregada);
}




