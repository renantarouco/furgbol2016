#include "Circulo.h"
#include <Avaliador.h>
#include <Sistema.h>

Circulo::Circulo():CGAL::Circle_2<Circular_k>(){
}

Circulo::Circulo(const Ponto& centro, float raio):CGAL::Circle_2<Circular_k>(centro, raio){
}

Circulo::Circulo(const Ponto &p1, const Ponto &p2, const Ponto &p3):
    CGAL::Circle_2<Circular_k>(p1, p2, p3)
{
}

void Circulo::construir(const Ponto &centroObjeto, float _distRoboCentro){
    distCentroAreaDefesa = _distRoboCentro + RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO;
    (*this) = Circulo(centroObjeto, distCentroAreaDefesa * distCentroAreaDefesa);
}

vector<Ponto> Circulo::calcularAlvosPosicionarDefesa(int qtRobosPosicionar){

    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();
    Bola* bola = Sistema::modeloMundo.getBola();

    /// pegando o adversário mais proximo da bola
    int idRoboAdvMaisPertoBola = Sistema::avaliador.getIdDistAdvMaisPertoBola().first;
    Reta retaDirecaoBola;
    Ponto posRef;
    float squaredDistRoboAdvBola = 600*600.0;
    if(idRoboAdvMaisPertoBola != -1){
        squaredDistRoboAdvBola = squared_distance(Sistema::modeloMundo.getRoboAdv(idRoboAdvMaisPertoBola)->getPosicao(), bola->getPosicao());
    }

    /// Pegando os pontos que fazer interseção da reta com o circulo
    vector<Ponto> pontosInterseccao;
    vector<Ponto> pontos;
    Ponto alvo; /// Alvo aonde o robô irá se posicionar a priori

    /// verificando se tem robo adv proximo da bola
    if(squaredDistRoboAdvBola <= 500.0*500.0){
        posRef = Sistema::modeloMundo.getRoboAdv(idRoboAdvMaisPertoBola)->getPosicao();
        retaDirecaoBola = Reta(bola->getPosicao(), posRef);

        /// Pegando os pontos que fazer interseção da reta com o circulo
        bool intercepta = isInterseccaoReta(retaDirecaoBola, pontosInterseccao);

        /// Verificando se temos pelo menos duas raízes, pois estamos fazendo a interseccao com um circulo
        if(intercepta){

            /// iremos pegar o ponto que estiver mais distante do adv, isso indica para aonde ele irá chutar ou passar
            float distPonto0 = squared_distance(pontosInterseccao[0], posRef);
            float distPonto1 = squared_distance(pontosInterseccao[1], posRef);

            /// Se o nosso lado for o esquerdo iremos pegar o ponto que tem o menor x dos dois.
            if(distPonto0 > distPonto1){
                alvo = pontosInterseccao[0];
            }else{
                alvo = pontosInterseccao[1];
            }

            /// verificando se é kickoff pro adversário assim não poderemos crusar o campo pro outro lado
            bool kickoff_adv = Sistema::modeloMundo.getFatos()->at("kickoff_adv");
            kickoff_adv = kickoff_adv && ((Sistema::modeloMundo.isLadoCampoEsquerdo() && alvo.x() > 200.0) || (!Sistema::modeloMundo.isLadoCampoEsquerdo() && alvo.x() < 200.0));

            /// se o alvo não está dentro do campo iremos criar uma reta para a area da equipe e nos posicionar nela
            if(!campo->isPontoDentro(alvo) || kickoff_adv){
                posRef = campo->getAreaEq()->getCentro();
                retaDirecaoBola = Reta(bola->getPosicao(), posRef);
                bool intercepta = isInterseccaoReta(retaDirecaoBola, pontosInterseccao);

                /// iremos pegar o ponto que estiver mais distante do adv, isso indica para aonde ele irá chutar ou passar
                float distPonto0GolEq = squared_distance(pontosInterseccao[0], posRef);
                float distPonto1GolEq = squared_distance(pontosInterseccao[1], posRef);

                /// Se o nosso lado for o esquerdo iremos pegar o ponto que tem o menor x dos dois.
                if(distPonto0GolEq < distPonto1GolEq){
                    alvo = pontosInterseccao[0];
                }else{
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
            cout << "WARNING: não encontrou raízes entre a reta que corta a área e o circulo" << endl;
        }
    }else{
        posRef = campo->getAreaEq()->getCentro();
        retaDirecaoBola = Reta(bola->getPosicao(), posRef);

        bool intercepta = isInterseccaoReta(retaDirecaoBola, pontosInterseccao);

        /// Verificando se temos pelo menos duas raízes, pois estamos fazendo a interseccao com um circulo
        if(intercepta){

            /// iremos pegar o ponto que estiver mais distante do adv, isso indica para aonde ele irá chutar ou passar
            float distPonto0GolEq = squared_distance(pontosInterseccao[0], posRef);
            float distPonto1GolEq = squared_distance(pontosInterseccao[1], posRef);

            /// Se o nosso lado for o esquerdo iremos pegar o ponto que tem o menor x dos dois.
            if(distPonto0GolEq < distPonto1GolEq){
                alvo = pontosInterseccao[0];
            }else{
                alvo = pontosInterseccao[1];
            }
        }else{
            cout << "WARNING: não encontrou raízes entre a reta que corta a área e o circulo" << endl;
        }
    }

    /// Se tivermos apenas um robo com a tática iremos retornar um vetor com apenas 1 posição
    if(qtRobosPosicionar == 1){
        pontos = vector<Ponto>(1, alvo);
    }else{
        pontos = calcularAlvosFinaisDefesa(alvo, qtRobosPosicionar);
    }


    return pontos;
}

vector<Ponto> Circulo::calcularAlvosFinaisDefesa(const Ponto &alvoInicial, int qtRobosPosicionar){

    /// variáveis auxiliares
    Campo* campo = Sistema::modeloMundo.getCampo();

    /// @todo ajeitar o calcula dos alvos fazer com que cada alvo tenha um circulo e fazer isso recursivamente para o posicionamente seja perfeito
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
        if(distRobosDefesa*distRobosDefesa >= this->squared_radius()){
            cout << "Circulo para calcular os alvos da posiciona defesa e maior que o circulo da area" << endl;
            cout << "Raio do circulo para posicionar defesa: " << distRobosDefesa << endl
                 << "Raio do circulo da area: " << sqrt(this->squared_radius()) << endl;
            break;
        }

        /// Criando o circulo do alvo
        Circulo circuloAlvoInicial = Circulo(alvoInicial, distRobosDefesa*distRobosDefesa);

        /// Pegando os pontos que fazem interseccao entre os circulos
        vector<Ponto> pontosInterseccao = Geometria::interseccaoCirculoCirculo(circuloAlvoInicial, (*this));
        BOOST_FOREACH(Ponto ponto, pontosInterseccao){

            /// Verificando se o ponto está dentro do campo
            if(campo->isPontoDentro(ponto)){
                pontosPosRobos[qtPontos]=ponto;
                qtPontos++;
            }
        }

        /// Incrementando o valor do fator para a próxima iteração caso precise
        //        fator++;
        distRobosDefesa += fator*ConfigAvaliador::DIST_ROBOS_DEFESA;

        /// Iremos calcular os alvos até que um dos pontos esteje fora da área e dentro do campo
    }while(qtPontos < qtRobosPosicionar);

    return pontosPosRobos;
}

Poligono* Circulo::getNovaInstancia(){
    return new Circulo;
}

bool Circulo::isPontoDentro(const Ponto &ponto)
{
    return (!has_on_unbounded_side(ponto));
}

bool Circulo::isInterseccaoReta(const Reta &reta)
{
    vector<Objeto> intersecs;
    intersection(*this , reta , back_inserter(intersecs));

    return intersecs.size() > 1 ? true : false;
}

bool Circulo::isInterseccao(const Ponto &inicioSeg, const Ponto &fimSeg)
{
    Reta reta(inicioSeg , fimSeg);
    Retangulo retSeg( inicioSeg , fimSeg );

    vector<Objeto> intersecs;
    intersecs.reserve(2);
    unsigned int j;
    intersection(*this , reta , back_inserter(intersecs));
    for ( j = 0; j < intersecs.size(); j ++)
    {
        if(const pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> > (&(intersecs[j])))
        {
            Ponto p(ponto->first.x() , ponto->first.y() );
            if(!retSeg.has_on_unbounded_side( p ) )
                return true;
        }
    }
    return false;
}


bool Circulo::isInterseccaoReta(const Reta &reta, vector<Ponto> &pontos)
{
    pontos.clear();
    vector<Objeto> objetosInterseccao; /// Objetos que a CGAL retorna da intersesão da reta com o circulo

    /// Pegando os pontos de interseccao da reta com o circulo
    intersection(*this, reta, back_inserter(objetosInterseccao));

    /// verificando se tem objetos interseccionando
    if(objetosInterseccao.size() > 1){

        /// passando os pontos para o vetor
        pontos.reserve(objetosInterseccao.size());
        foreach(Objeto objeto, objetosInterseccao){
            if(const pair< ArcPonto, unsigned> *ponto = CGAL::object_cast< pair< ArcPonto, unsigned> >(&objeto))
                pontos.push_back(Ponto(ponto->first.x() , ponto->first.y()));
        }

        return true;
    }

    return false;
}

Ponto Circulo::getCentro()
{
    return center();
}
