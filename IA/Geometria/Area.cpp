#include "Area.h"
#include <Avaliador.h>
#include <Sistema.h>

Area::Area(){
}

Area::~Area()
{
}

Arco Area::getSemiCirculoSup(){
    return semiCirculoSup;
}

Arco Area::getSemiCirculoInf(){
    return semiCirculoInf;
}

Segmento Area::getSegmentoGol(){
    return segmentoGol;
}

Segmento Area::getSegmentoArea(){
    return segmentoFrenteArea;
}

Retangulo Area::getRetanguloArea(){
    return retanguloArea;
}

void Area::construir(const Ponto &_centro){
    centro = _centro;

    /// criando o segmento que fica na linha do gol
    segmentoGol = Segmento(Ponto(centro.x(), Config::MEIO_COMPRIMENTO_GOL), Ponto(centro.x(), -Config::MEIO_COMPRIMENTO_GOL));

    /// criando circulo que será utilizado para posicionar a defesa
    distCentroAreaDefesa = Config::RAIO_SEMI_CIRCULO_AREA + 2.5*RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO;
    circuloPosicionarDefesa = Circulo(centro, distCentroAreaDefesa*distCentroAreaDefesa);

    /// Criando os circulos da aérea que serviram de base para criar os arcos da aérea
    double squared_radius = Config::RAIO_SEMI_CIRCULO_AREA*Config::RAIO_SEMI_CIRCULO_AREA;
    Circulo circuloSup(Ponto(centro.x(), Config::MEIA_LARGURA_SEGMENTO_AREA), squared_radius);
    Circulo circuloInf(Ponto(centro.x(), -Config::MEIA_LARGURA_SEGMENTO_AREA), squared_radius);

    /// verificando o lado em que a aérea se encontras
    if(centro.x() > 0.0){

        /// Criando o segmento que fica na frente da área
        segmentoFrenteArea = Segmento(Ponto(centro.x() - Config::RAIO_SEMI_CIRCULO_AREA, -Config::MEIA_LARGURA_SEGMENTO_AREA),
                                      Ponto(centro.x() - Config::RAIO_SEMI_CIRCULO_AREA, Config::MEIA_LARGURA_SEGMENTO_AREA));

        /// Criando o retângulo da área
        retanguloArea = Retangulo(Ponto(centro.x() - Config::RAIO_SEMI_CIRCULO_AREA, -Config::MEIA_LARGURA_SEGMENTO_AREA),
                                  Ponto(centro.x(), Config::MEIA_LARGURA_SEGMENTO_AREA));


        /// ATENÇÂO: Para criar um arco, precisa de um circulo e dois pontos, os pontos devem ser setado no sentido horário
        /// semicirculo superior
        semiCirculoSup = Arco(circuloSup, ArcPonto(Ponto(centro.x(), Config::MEIA_LARGURA_SEGMENTO_AREA + Config::RAIO_SEMI_CIRCULO_AREA)),  ArcPonto(segmentoFrenteArea.max()));

        /// semicirculo inferior
        semiCirculoInf = Arco(circuloInf, ArcPonto(segmentoFrenteArea.min()), ArcPonto(Ponto(centro.x(), - Config::MEIA_LARGURA_SEGMENTO_AREA - Config::RAIO_SEMI_CIRCULO_AREA)));

    }else{

        /// Criando o segmento que fica na frente da área
        segmentoFrenteArea = Segmento(Ponto(centro.x() + Config::RAIO_SEMI_CIRCULO_AREA, -Config::MEIA_LARGURA_SEGMENTO_AREA),
                                      Ponto(centro.x() + Config::RAIO_SEMI_CIRCULO_AREA, Config::MEIA_LARGURA_SEGMENTO_AREA));

        /// Criando o retângulo da área
        retanguloArea = Retangulo(Ponto(centro.x(), -Config::MEIA_LARGURA_SEGMENTO_AREA),
                                  Ponto(centro.x() + Config::RAIO_SEMI_CIRCULO_AREA, Config::MEIA_LARGURA_SEGMENTO_AREA));


        /// ATENÇÂO: Para criar um arco, precisa de um circulo e dois pontos, os pontos devem ser setado no sentido horário
        /// semicirculo superior
        semiCirculoSup = Arco(circuloSup, ArcPonto(segmentoFrenteArea.max()), ArcPonto(Ponto(centro.x(), Config::MEIA_LARGURA_SEGMENTO_AREA + Config::RAIO_SEMI_CIRCULO_AREA)));

        /// semicirculo inferior
        semiCirculoInf = Arco(circuloInf, ArcPonto(Ponto(centro.x(), -Config::MEIA_LARGURA_SEGMENTO_AREA -Config::RAIO_SEMI_CIRCULO_AREA)), ArcPonto(segmentoFrenteArea.min()));
    }
}

void Area::construir(const Ponto& _centro, float _distRoboCentro){
    centro = _centro;
    distCentroAreaDefesa = _distRoboCentro;
    circuloPosicionarDefesa = Circulo(centro, distCentroAreaDefesa*distCentroAreaDefesa);
}

vector<Ponto> Area::calcularAlvosPosicionarDefesa(int qtRobosPosicionar){

    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Bola* bola = Sistema::modeloMundo.getBola();
    Ponto posBola = bola->getPosicao();
    Reta retaDirecaoBola = Sistema::avaliador.calcularRetaDirecaoBola();

    /// Robo
    int idRoboAdvMaisPertoBola=-1;
    Reta retaRoboAdvBola;
    if(!Sistema::avaliador.isBolaNossa(idRoboAdvMaisPertoBola)){

        /// Reta é entre o robo adv mais perto da bola e a bola
        if(idRoboAdvMaisPertoBola != -1){
            /// Criando a reta do robô adv que está com a bola e a bola.
            retaRoboAdvBola = Reta(Sistema::modeloMundo.getRoboAdv(idRoboAdvMaisPertoBola)->getPosicao(), posBola);
        }else{
            cout << " Robo Adv com id -1 ! " << endl;
        }
    }

    /// Ponto onde iremos posicionar o goleiro, iremos ter como padrão o centro do gol da nossa equipe
    Ponto pontoInterseccao;

    /// Calculando o ponto de interseccao para o goleiro se posicionar,
    /// iremos dar prioridade a direcao da bola, caso nao esteja atingido o gol
    /// o vetor robo adv bola ira ser usado para posicionar o robo, caso
    /// nenhum esteja em direcao do gol iremos posicionar o robo no centro do gol
    /// Teste CBR 2013 Trocamos as prioridades
    IdDistancia idDistRoboAdv = Sistema::avaliador.getIdDistAdvMaisPertoBola();
    if(!Sistema::avaliador.isBolaNossa(idRoboAdvMaisPertoBola) && idDistRoboAdv.second < 300.0*300.0 && Geometria::isInterseccaoSegmentoReta(segmentoGol, retaRoboAdvBola, pontoInterseccao)){

        //        cout << "Reta robo bola adv" << endl;

    }else if(Geometria::isInterseccaoSegmentoReta(segmentoGol, retaDirecaoBola, pontoInterseccao)){

        //         cout << "Reta move bola" << endl;

    }else{
        /// pegando a linha de fundo de acordo campo a lado do campo da nossa equipe
        Segmento linhaFundo = Sistema::modeloMundo.isLadoCampoEsquerdo() ? campo->getLinhaFundoEsq() : campo->getLinhaFundoDir();

        if(!Sistema::avaliador.isBolaNossa(idRoboAdvMaisPertoBola) && idDistRoboAdv.second < 300.0*300.0
                && Geometria::isInterseccaoSegmentoReta(linhaFundo, retaRoboAdvBola, pontoInterseccao)){

            //             cout << "Reta robo bola adv linha fundo" << endl;

            /// Verificando se o alvo esta no gol, em cima do gol ou embaixo, de acordo com isso iremos posicionar o robo no gol, em cima ou embaixo da goleira

            if(pontoInterseccao.y() > centro.y()){
                pontoInterseccao = Ponto(pontoInterseccao.x(),  segmentoGol.max().y()-RAIO_ROBO/2.0);
            }else{
                pontoInterseccao = Ponto(pontoInterseccao.x(), segmentoGol.min().y()+RAIO_ROBO/2.0);
            }

        }else if(Geometria::isInterseccaoSegmentoReta(linhaFundo, retaDirecaoBola, pontoInterseccao)){

            //             cout << "Reta move bola linha fundo" << endl;

            /// Verificando se o alvo esta no gol, em cima do gol ou embaixo, de acordo com isso iremos posicionar o robo no gol, em cima ou embaixo da goleira
            if(pontoInterseccao.y() > centro.y()){
                pontoInterseccao = Ponto(pontoInterseccao.x(),  segmentoGol.max().y()-RAIO_ROBO/2.0);
            }else{
                pontoInterseccao = Ponto(pontoInterseccao.x(), segmentoGol.min().y()+RAIO_ROBO/2.0);
            }
        }else{
            //             cout << "Reta bola centro gol" << endl;
            pontoInterseccao = centro;
        }
    }

    /// Criando a reta que iremos fazer a interseccao com a area para indicar aonde os robos irao se posicionar
    Reta retaBolaPontoInterseccao(pontoInterseccao, posBola);

    /// @todo ajeitar para que o robó se posicione realmente no formato da area e nao de um circulo
    vector<Ponto> pontos;

    /// Pegando os pontos que fazer interseção da reta com o circulo
    vector<Ponto> pontosInterseccao;
    bool intercepta = circuloPosicionarDefesa.isInterseccaoReta(retaBolaPontoInterseccao, pontosInterseccao);

    /// Se a reta nao interseccionar o circulo iremos criar uma reta com a bola em direcao ao nosso gol para poder posicionar corretamente a defesa
    if(intercepta){

        Ponto alvo; /// Alvo aonde o robô irá se posicionar a priori

        /// Verificando se os dois pontos estão no campo iremos analisar o melhor.
        if(campo->isPontoDentro(pontosInterseccao[0]) && campo->isPontoDentro(pontosInterseccao[1])){

            /// Pegando o ponto que tem a menor distância ao nosso gol, isso indica que o ponto está mais próximo do nosso gol
            float distPonto0Bola = squared_distance(pontosInterseccao[0], posBola);
            float distPonto1Bola = squared_distance(pontosInterseccao[1], posBola);

            /// Se o nosso lado for o esquerdo iremos pegar o ponto que tem o menor x dos dois.
            if(distPonto0Bola <= distPonto1Bola){
                alvo = pontosInterseccao[0];
            }else{
                alvo = pontosInterseccao[1];
            }

            /// Se um dos pontos não está dentro do campo iremos retornar o outro ponto.
        }else{

            /// Verificando qual dos pontos esta fora do campo
            if(campo->isPontoDentro(pontosInterseccao[0])){
                alvo = pontosInterseccao[0];
            }else if(campo->isPontoDentro(pontosInterseccao[1])){
                alvo = pontosInterseccao[1];
            }
        }

        /// Se tivermos apenas um robo com a tática iremos retornar um vetor com apenas 1 posição
        if(qtRobosPosicionar == 1){
            pontos = vector<Ponto>(1, alvo);
        }else{
            pontos = calcularAlvosFinaisDefesa(alvo, qtRobosPosicionar);
        }

    }else{
        retaBolaPontoInterseccao = Reta(posBola, centro);
        circuloPosicionarDefesa.isInterseccaoReta(retaBolaPontoInterseccao, pontos);
    }

    return pontos;
}

vector<Ponto> Area::calcularAlvosPosicionarDefesaFrente(int qtRobosPosicionar){

    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Bola* bola = Sistema::modeloMundo.getBola();
    Ponto posBola = bola->getPosicao();

    /// Robo
    int idRoboAdvMaisPertoBola=Sistema::modeloMundo.getIdGoleiroAdv();
    cout<<idRoboAdvMaisPertoBola<<"<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"<<endl;
    Reta retaRoboAdvBola;
     /// Reta é entre o robo adv mais perto da bola e a bola
    if(idRoboAdvMaisPertoBola != -1){
        /// Criando a reta do robô adv que está com a bola e a bola.
        retaRoboAdvBola = Reta(Sistema::modeloMundo.getRoboAdv(idRoboAdvMaisPertoBola)->getPosicao(),posBola);
    }else{
        cout << " Robo Adv com id -1 ! " << endl;
    }


    /// Ponto onde iremos posicionar o goleiro, iremos ter como padrão o centro do gol da nossa equipe
    Ponto interseccao = CGAL::ORIGIN;
    vector<Ponto> pontos;
    pontos.clear();
    pontos.resize(3);

    /// Calculando o ponto de interseccao para o goleiro se posicionar,
    /// iremos dar prioridade a direcao da bola, caso nao esteja atingido o gol
    /// o vetor robo adv bola ira ser usado para posicionar o robo, caso
    /// nenhum esteja em direcao do gol iremos posicionar o robo no centro do gol
    /// Teste CBR 2013 Trocamos as prioridades
    if(Geometria::interseccaoRetaSemiCirculo(semiCirculoSup, retaRoboAdvBola, interseccao)){
        pontos[0] = interseccao;
        cout<<'('<<interseccao.x()<<", "<<interseccao.y()<<')'<<endl;
        cout<<"SUPERIORRRRRRRRRR"<<endl;
        /// verificando se intersecciona o semicirculo inferior
    }
    if(Geometria::interseccaoRetaSemiCirculo(semiCirculoInf, retaRoboAdvBola, interseccao)){
        pontos[1] = interseccao;
        cout<<"INFERIORRRRRRRRRR"<<endl;
        /// verificando se intersecciona o segmento da frente da area
    }
    if(Geometria::isInterseccaoSegmentoReta(segmentoFrenteArea, retaRoboAdvBola, interseccao)){
        pontos[2] = interseccao;
        cout<<"MEIOOOOOOOOOOOO"<<endl;
    }

    Ponto alvo = pontos[0];
    double menorDist = sqrt(pow((alvo.x()-posBola.x()), 2)+pow((alvo.y()-posBola.y()), 2));
    for(int i=0;i<pontos.size();i++){
        double dist = sqrt(pow((pontos[i].x()-posBola.x()), 2)+pow((pontos[i].y()-posBola.y()), 2));
        if(dist<menorDist){
            alvo = pontos[i];
        }
    }

    pontos.resize(1);
    pontos[0] = alvo;

    return pontos;

}

vector<Ponto> Area::calcularAlvosFinaisDefesa(const Ponto &alvoInicial, int qtRobosPosicionar){
    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();

    vector<Ponto> pontosPosRobos(qtRobosPosicionar%2==1 ? qtRobosPosicionar : qtRobosPosicionar+1); /// Criando o vetor com o tamanho de acordo com a quantidade de robos que irao se posicionar
    pontosPosRobos[0] = alvoInicial;
    int qtPontos = 1;

    /// Pegando o campo e a área da equipe para verificarmos quais pontos estão fora do campo e dentro da área para excluirmos
    float distRobosDefesa = ConfigAvaliador::DIST_ROBOS_DEFESA;

    /// Se a quantidade de robos for impar iremos posicionar 1 robo no centro
    int fator = 1;
    if(qtRobosPosicionar % 2 == 1){
        fator = 1;
    }
    distRobosDefesa = fator*ConfigAvaliador::DIST_ROBOS_DEFESA;

    do{
        /// Isso nao pode acontecer
        if(distRobosDefesa*distRobosDefesa >= circuloPosicionarDefesa.squared_radius()){
            cout << "Circulo para calcular os alvos da posiciona defesa e maior que o circulo da area" << endl;
            cout << "Raio do circulo para posicionar defesa: " << distRobosDefesa << endl
                 << "Raio do circulo da area: " << sqrt(circuloPosicionarDefesa.squared_radius()) << endl;
            break;
        }

        /// Criando o circulo do alvo
        Circulo circuloAlvoInicial = Circulo(alvoInicial, distRobosDefesa*distRobosDefesa);

        /// Pegando os pontos que fazem interseccao entre os circulos
        vector<Ponto> pontosInterseccao = Geometria::interseccaoCirculoCirculo(circuloAlvoInicial, circuloPosicionarDefesa);
        BOOST_FOREACH(Ponto ponto, pontosInterseccao){

            /// Verificando se o ponto está dentro do campo
            if(campo->isPontoDentro(ponto)){
                pontosPosRobos[qtPontos]=ponto;
                qtPontos++;
            }
        }

        /// Incrementando o valor do fator para a próxima iteração caso precise
        distRobosDefesa += fator*ConfigAvaliador::DIST_ROBOS_DEFESA;

        /// Iremos calcular os alvos até que um dos pontos esteje fora da área e dentro do campo
    }while(qtPontos < qtRobosPosicionar);

    return pontosPosRobos;
}

Poligono* Area::getNovaInstancia(){
    return new Area;
}

bool Area::isPontoDentro(const Ponto &ponto){

    /// Verificando se o ponto está dentro do retângulo da área se tiver retorna true.
    if(retanguloArea.has_on_bounded_side(ponto)){
        //        cout << "r" << endl;
        return true;
    }

    /// Calculando a distância do ponto aos centros dos semicirculos
    float dist = squared_distance(semiCirculoSup.center(), ponto);
    if(semiCirculoSup.squared_radius() >= dist){
        //        cout << "sup" << endl;
        return true;
    }

    /// Calculando a distância do ponto aos centros dos semicirculos
    dist = squared_distance(semiCirculoInf.center(), ponto);
    if(semiCirculoInf.squared_radius() >= dist){
        //        cout << "inf" << endl;
        return true;
    }

    /// Se nenhuma das condições acima forem satisfeitas é porque o ponto não está dentro da nossa área.
    return false;
}

bool Area::isInterseccaoReta(const Reta &reta)
{
    return do_intersect(segmentoFrenteArea, reta) || do_intersect(semiCirculoSup, reta) || do_intersect(semiCirculoInf, reta);
}

bool Area::isInterseccaoReta(const Reta &reta, vector<Ponto> &pontos)
{
    pontos.clear();
    pontos.resize(1);
    Ponto interseccao = CGAL::ORIGIN;

    /// verificando se intersecciona o semicirculo superior
    if(Geometria::interseccaoRetaSemiCirculo(semiCirculoSup, reta, interseccao)){
        pontos[0] = interseccao;
        cout<<'('<<interseccao.x()<<", "<<interseccao.y()<<')'<<endl;
        cout<<"SUPERIORRRRRRRRRR"<<endl;
        return true;

        /// verificando se intersecciona o semicirculo inferior
    }else if(Geometria::interseccaoRetaSemiCirculo(semiCirculoInf, reta, interseccao)){
        pontos[0] = interseccao;
        cout<<"INFERIORRRRRRRRRR"<<endl;
        return true;

        /// verificando se intersecciona o segmento da frente da area
    }else if(Geometria::isInterseccaoSegmentoReta(segmentoFrenteArea, reta, interseccao)){
        pontos[0] = interseccao;
        cout<<"MEIOOOOOOOOOOOO"<<endl;
        return true;
    }

    return false;
}

bool Area::isInterseccao(const Ponto &inicio, const Ponto &fim)
{
    Reta reta(inicio, fim);
    return do_intersect(segmentoFrenteArea, reta) || do_intersect(semiCirculoSup, reta) || do_intersect(semiCirculoInf, reta);
}

Ponto Area::getCentro()
{
    return centro;
}
