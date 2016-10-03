#ifndef NAVEGADOR_H
#define NAVEGADOR_H

const unsigned PATH_PLANNING_MAX_NUM_PONTOS = 250;           /*!< Numero maximo de pontos que a arvore pode ter */
const int PATH_PLANNING_MAX_NUM_CACHE_PONTOS = 50;      /*!< Numero de pontos armazenado na cache */
const float PATH_PLANNING_MAX_TAM_SEGUIMENTOS = 400.0;  /*!< Tamanho maximo de um seguimento do path planning */
const unsigned PATH_PLANNING_NUM_SUAVISACAO_CAMINHO = 4;  /*!< Numero de vezes que o caminho é suavizado */
const int PATH_PLANNING_PROB_DIRECAO_ALVO = 10;         /*!< Probabilidade da arvore se expalhar em direção ao alvo */
const int PATH_PLANNING_PROB_DIRECAO_CACHE = 70;        /*!< Probabilidade da arvore se expalhar em direção a um ponto da cache */
const float PATH_PLANNING_TAM_EXTRA_OBSTACULO = 150;     /*!< Tamanho do raio dos obstaculos internos adicionais, este valor é somado com 2*raio_robo */
const float PATH_PLANNING_DIST_DESCONSIDERAVEL = 700;     /*!< Distancia maxiama para desconciderar um obstaculo*/
// Probabilidade de ir para direção aleatoria é 100 - (prob_alvo + prob_cache)

#include "Definitions.h"
#include "Geometria.h"
#include "KDTree.h"
#include "Robo.h"

/**
 * @brief A classe Navegador é responsavel
 * por encontrar caminhos sem colisão que
 * leva o robo de um ponto inicial a um
 * destino (aldvo).
 *  O caminho é encontrado usando um
 * algoritmo chamado RRT (R ), este
 * algoritmo utiliza uma arvore em que
 * cada nodo é um ponto no campo do jogo,
 * os nodos desta arvore é espandido
 * de forma quase aleatoria, dependendo
 * dos pesos das contantes do algoritmo.
 *  Nem sempre o caminho é encontrado,
 * para garantirmos que não vamos perder
 * muito tempo de processamento calculando
 * caminho, o algoritmo RRT é limitado,
 * ou seja, ele desiste de encontrar o
 * caminho quando atinge um limite de
 * pontos na arvore, esse limite pode
 * ser definido nas contantes do Navegador.
 * Quando o limite de pontos é atingido
 * o caminho retornado leva até o alvo final
 * mas não é garantidoque os ultimos
 * pontos do caminho estão livre
 * de colisão.
 *
 */
class Navegador
{
protected:
    bool navegadorAtivo; /// < setando se iremos ou não usar o navegador

    /*!  Atributo protegido- Armazena o ID do robo que esta usando esse Navegador.    */
    int m_ID;

    /** Numero de vezes que uma tentaiva de expancao da RRT colidiu com um obstaculo **/
    unsigned m_numFalhas;

    /*! Atributo Protegido - Armazena o raio dos obstaculos internos pre definidos, são eles,
    os robos amigos e os robos adversarios, todos eles tem o mesmo raio*/
    float raioObstaculoRobo;

    /*! Atributo Protegido - Lista de ponteiros para os obstaculos robos amigos e os
    obstaculos robos adversarios, que são atualizados constantemente*/
    list <Poligono *> m_obstaculos; /*! Obstaculos */

    /*! Atributo Protegido - Lista de ponteiros para obstaculos extras, que podem ser
    * adicionados ao pathPlanning utilizando o método adicionaObstaculo.
          \sa adicionaObstaculo(Obstaculo *novoObstaculo)
    */
    list <Poligono *> m_obstaculosExtra;

    /*! Atributo Protegido - Ponto para o alvo do path planning*/
    Ponto m_alvo;

    /*! Atributo Protegido - Ponto origem do path planning*/
    Ponto m_origem;

    /*! Atributo Protegido - Ultimo ponto calculado no path planning, retornado pelo método RRT*/
    vector<Ponto> m_caminho;

    /*! Atributo Protegido - Vetor de pontos da memoria cache*/
    vector <Ponto> m_cache;

    /*! Numero de vezes que o caminho atual foi re-utilizado */
    unsigned m_idadeCaminho;

    vector<char> m_obstaculosRoboEqAtivados;
    vector<char> m_obstaculosRoboAdvAtivados;

    void atualizaObstaculosInterno();

    void deletaObstaculosInterno();

    void deletaObstaculosExterno();

    void deletaObstaculosExternoDentroAlvo();

    Ponto escolhaAlvo( );

    bool extenda(Ponto & MaisProximo, Ponto &fim, Ponto &pontoFinalSeguimentoLimitado );

    bool colisao( Ponto &inicio, Ponto &fim );

    bool colisaoSimplificada( Ponto &inicio, Ponto &fim );

    bool obstaculoContemPonto(Ponto &A , Poligono** obs = 0x0);

    void inicializaCache();

    void inicializaNavegador();

    void normaliza(unsigned n);

    bool eh_necessarioCalcularNovoCaminhoReta(const Ponto &origem, const Ponto &alvo);

    bool eh_necessarioCalcularNovoCaminho();

    KDNodo *expandeRRT(KDTree & arvore);

    void constroeCaminho(KDTree & arvore, KDNodo *ultimoNodo);

    bool calcularCaminhoDireto();

    void calculaCaminho(const Ponto &origem, const Ponto &alvo);

public:
    Navegador();

    Navegador(const Navegador &nav);

    Navegador(int MeuID);

    ~Navegador();

    /** função que ativa o calculo do path planning */
    void ativar();

    /** FUnção que desativa o calculo do path planning */
    void desativar();

    static bool limitaSegmento(const Ponto &inicio, Ponto &fim , float tamSeg, Ponto &fimSegCalculado);

    static Ponto pontoAleatorio();

    Ponto pontoAleatorioSemColisao();

    void setId(int Id);

    Ponto getUltimoAlvoCalculado();

    const vector<Ponto> & getUltimosAlvosCalculado();

    Ponto RRT (Ponto origem, Ponto alvo);

    Ponto RRT ( Ponto alvo);

    vector<Ponto> pontosRRT(Ponto alvo);

    vector<Ponto> pontosRRT(Ponto origem, Ponto alvo);

    /* Manipulacao de obstaculos */
    void adicionaObstaculo(Poligono *novoObstaculo);

    void apagaObstaculos();

    void ativaObstaculoRoboAdv(unsigned id);
    void ativaObstaculoRoboEq(unsigned id);

    void desativaObstaculoRoboAdv(unsigned id);
    void desativaObstaculoRoboEq(unsigned id);
    void ativaTodosObstaculosRobos();

    void ativaObstaculosRobosEq();
    void ativaObstaculosRobosAdv();
    void desativaObstaculosRobosEq();
    void desativaObstaculosRobosAdv();

    /* ----- */

    PacotePathPlanning criaPacotePathPlanning();

    static bool estaoProximos(const Ponto &orig , const Ponto &m_alvo , float tolerancia);
    bool eh_necessarioCalcularNovoCaminhoReta();
};

#endif // NAVEGADOR_H


//// Teste do navegador

//// Para executar esse teste é necessario instalar a biblioteca allegro 4.2
//// para visualizar os pontos retornados pelo navegador
//// tambem é necessario incluir no .pro a biblioteca LIBS += `allegro-config --libs`
//// no caso do linux. E descomentar os comentarios no inicio do Navegador.cpp

//#include <allegro.h>
//#include "Sistema.h"
//#include "Navegador.h"

////Configuracoes da tela
//// Tamanho da janela
//#define MAX_X         756
//#define MAX_Y         506

//// Tamanho virtual da tela (scrolling)
//#define V_MAX_X 0
//#define V_MAX_Y 0

//#define COLOR_BITS    desktop_color_depth()
//#define VIDEO_CARD    GFX_AUTODETECT_WINDOWED

//#define DIGI_CARD     DIGI_SB16
//#define MIDI_CARD     MIDI_SB_OUT
//#define ESCALA 9

//BITMAP *img;
//float velocidade[5];

//int campo2allegro_x(float x)
//{
//    return (int) (x + Config::COMPRIMENTO_CAMPO/2) / ESCALA;
//}

//int campo2allegro_y(float y)
//{
//    return (int) (MAX_Y - (y + Config::LARGURA_CAMPO/2) / ESCALA);
//}

//float allegro2campo_x(int x)
//{
//    return (float) (x * ESCALA - Config::COMPRIMENTO_CAMPO/2);
//}

//float allegro2campo_y(int y)
//{
//    return (float) ((MAX_Y -y) * ESCALA - Config::LARGURA_CAMPO/2 );
//}

//void iniciaAllegro()
//{
//    allegro_init();
//    install_mouse();
//    install_keyboard();
//    install_timer();

//    set_color_depth(COLOR_BITS );

//    if (set_gfx_mode(VIDEO_CARD, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y) < 0)
//        return ;

//    img = create_bitmap(screen->w , screen->h);
//    rectfill(img, 0, 0, img->w, img->h, 0xffffff);
//    show_os_cursor(2);
//}

//void desenhaCaminho(const vector<Ponto>& caminho)
//{
//    unsigned i;
//    Ponto ultimoPonto = Sistema::modeloMundo.getRoboEq(0)->getPosicao();
//    for( i = 0 ; i < caminho.size() ; i++)
//    {
//        fastline(img,
//                 campo2allegro_x(ultimoPonto.x()), campo2allegro_y(ultimoPonto.y()),
//                 campo2allegro_x(caminho[i].x()), campo2allegro_y(caminho[i].y()),
//                 0x00ffff);

//        circlefill(img,
//                 campo2allegro_x(caminho[i].x()), campo2allegro_y(caminho[i].y()),
//                 3, 0x0);

//        ultimoPonto = caminho[i];
////        cout << caminho[i] << endl;
//    }
//}

//void definePosicaoDosRobos()
//{
//    Robo *robo;
//    Ponto posicao;
//    for(unsigned i = 0 ; i < 5 ; i++)
//    {
//        robo = Sistema::modeloMundo.getRoboEq(i);
//        posicao = Navegador::pontoAleatorio();

//        robo->setPosicao(posicao);
//        robo->setPresenca(true);
//        robo->setAlvoFinal(Navegador::pontoAleatorio());
//        velocidade[i] = 8.f + rand()%20;

////        if(i != 0)
////            circlefill(img, campo2allegro_x(posicao.x()) , campo2allegro_y(posicao.y()) , RAIO_ROBO/ESCALA , 0x0000ff );
//    }
//}

//void movimentaRobos(const Ponto & pathAlvo)
//{
//    Robo *robo;
//    Ponto posicao, alvo;
//    for(unsigned i = 0 ; i < 5 ; i++)
//    {
//        robo = Sistema::modeloMundo.getRoboEq(i);

//        posicao = robo->getPosicao();

//        if(i != 0)
//            alvo = robo->getAlvoFinal();
//        else
//            alvo = pathAlvo;

//        if(Navegador::estaoProximos(posicao , robo->getAlvoFinal(), velocidade[i] + 10.f))
//        {
//            alvo = Navegador::pontoAleatorio();
//            robo->setAlvoFinal(alvo);
//        }

//        Navegador::limitaSegmento(posicao , alvo , velocidade[i], posicao);

//        robo->setPosicao(posicao);

//        if(i != 0)
//            circlefill(img, campo2allegro_x(posicao.x()) , campo2allegro_y(posicao.y()) , RAIO_ROBO/ESCALA , 0x0000ff );

//    }
//}

//int main()
//{
//    Navegador teste(0);
////    srand(time(NULL));
//    Relogio rel;
//    rel.setTempoInicial(rel.getTempoDoDia());
//    double t, maxT = -999, minT = 999;

//    iniciaAllegro();
//    definePosicaoDosRobos();

//    blit(img, screen ,  0 , 0 , 0 , 0 , screen->w , screen->h);

//    Robo *r = Sistema::modeloMundo.getRoboEq(0);
//    readkey();
//    while(!key[KEY_ESC])
//    {
//        rel.setTempoInicial(rel.getTempoDoDia());
//        const vector<Ponto>& caminho = teste.pontosRRT(r->getAlvoFinal());
//        t = rel.getTempoPassado();
//        if(t > maxT) maxT = t;
//        if(t < minT) minT = t;
//        cout << "tMax = " << maxT << "s tMin = " << minT << "s t = " << t <<'s' << endl ;

//        circlefill(img ,
//                   campo2allegro_x(r->getAlvoFinal().x()), campo2allegro_y(r->getAlvoFinal().y()),
//                   (PATH_PLANNING_DISTANCIA_DESCONSIDERAVEL-PATH_PLANNING_TAM_EXTRA_OBSTACULO-RAIO_ROBO)/ESCALA , 0xff0000);
//        circlefill(img ,
//                   campo2allegro_x(r->getPosicao().x()), campo2allegro_y(r->getPosicao().y()),
//                   RAIO_ROBO/ESCALA , 0xffff00);

//        desenhaCaminho(caminho);
//        movimentaRobos(caminho[0]);

//        blit(img, screen ,  0 , 0 , 0 , 0 , screen->w , screen->h);
//        rectfill(img , 0 , 0 , img->w, img->h , 0xffffff);
//        rest(30);
//    }

//    readkey();
//}



//// Teste do navegador com aceleracao

//// Para executar esse teste é necessario instalar a biblioteca allegro 4.2
//// para visualizar os pontos retornados pelo navegador
//// tambem é necessario incluir no .pro a biblioteca LIBS += `allegro-config --libs`
//// no caso do linux. E descomentar os comentarios no inicio do Navegador.cpp

//#include <allegro.h>
//#include "Sistema.h"
//#include "Navegador.h"

////Configuracoes da tela
//// Tamanho da janela
//#define MAX_X         756
//#define MAX_Y         506

//// Tamanho virtual da tela (scrolling)
//#define V_MAX_X 0
//#define V_MAX_Y 0

//#define COLOR_BITS    desktop_color_depth()
//#define VIDEO_CARD    GFX_AUTODETECT_WINDOWED

//#define DIGI_CARD     DIGI_SB16
//#define MIDI_CARD     MIDI_SB_OUT
//#define ESCALA 9

//BITMAP *img;
//float modVelocidade[5];
//Ponto velocidade[5];
//Ponto aceleracao[5];

//float atrito = 0.96f;

//int campo2allegro_x(float x)
//{
//    return (int) (x + Config::COMPRIMENTO_CAMPO/2) / ESCALA;
//}

//int campo2allegro_y(float y)
//{
//    return (int) (MAX_Y - (y + Config::LARGURA_CAMPO/2) / ESCALA);
//}

//float allegro2campo_x(int x)
//{
//    return (float) (x * ESCALA - Config::COMPRIMENTO_CAMPO/2);
//}

//float allegro2campo_y(int y)
//{
//    return (float) ((MAX_Y -y) * ESCALA - Config::LARGURA_CAMPO/2 );
//}

//void iniciaAllegro()
//{
//    allegro_init();
//    install_mouse();
//    install_keyboard();
//    install_timer();

//    set_color_depth(COLOR_BITS );

//    if (set_gfx_mode(VIDEO_CARD, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y) < 0)
//        return ;

//    img = create_bitmap(screen->w , screen->h);
//    rectfill(img, 0, 0, img->w, img->h, 0xffffff);
//    show_os_cursor(2);
//}

//void desenhaCaminho(const vector<Ponto>& caminho)
//{
//    unsigned i;
//    Ponto ultimoPonto = Sistema::modeloMundo.getRoboEq(0)->getPosicao();
//    for( i = 0 ; i < caminho.size() ; i++)
//    {
//        fastline(img,
//                 campo2allegro_x(ultimoPonto.x()), campo2allegro_y(ultimoPonto.y()),
//                 campo2allegro_x(caminho[i].x()), campo2allegro_y(caminho[i].y()),
//                 0x00ffff);

//        circlefill(img,
//                 campo2allegro_x(caminho[i].x()), campo2allegro_y(caminho[i].y()),
//                 3, 0x0);

//        ultimoPonto = caminho[i];
////        cout << caminho[i] << endl;
//    }
//}

//void definePosicaoDosRobos()
//{
//    Robo *robo;
//    Ponto posicao;
//    for(unsigned i = 0 ; i < 5 ; i++)
//    {
//        robo = Sistema::modeloMundo.getRoboEq(i);
//        posicao = Navegador::pontoAleatorio();

//        robo->setPosicao(posicao);
//        robo->setPresenca(true);
//        robo->setAlvoFinal(Navegador::pontoAleatorio());
//        modVelocidade[i] = 8.f + rand()%20;

////        if(i != 0)
////            circlefill(img, campo2allegro_x(posicao.x()) , campo2allegro_y(posicao.y()) , RAIO_ROBO/ESCALA , 0x0000ff );
//    }
//}

//void movimentaRobos(const Ponto & pathAlvo)
//{
//    Robo *robo;
//    Ponto posicao, alvo;
//    for(unsigned i = 0 ; i < 5 ; i++)
//    {
//        robo = Sistema::modeloMundo.getRoboEq(i);

//        posicao = robo->getPosicao();

//        if(i > 0)
//        {
//            alvo = robo->getAlvoFinal();
//            alvo = Ponto( alvo.x() - posicao.x() , alvo.y() - posicao.y());

//            float modAlvo = sqrt(alvo.x()*alvo.x()+alvo.y()*alvo.y());

//            velocidade[i] = Ponto((alvo.x()/modAlvo) * modVelocidade[i] , (alvo.y() /modAlvo) * modVelocidade[i] );
//        }
//        else
//        {
//            alvo = Ponto( pathAlvo.x() - posicao.x() , pathAlvo.y() - posicao.y());

//            float modAlvo = sqrt(alvo.x()*alvo.x() + alvo.y()*alvo.y()),
//                  modAceleracao = 5.f;

//            aceleracao[i] = Ponto( (alvo.x()/modAlvo) * modAceleracao , (alvo.y() /modAlvo) * modAceleracao );

//            velocidade[i] = Ponto(
//                        (velocidade[i].x() + aceleracao[i].x()) * atrito,
//                        (velocidade[i].y() + aceleracao[i].y()) * atrito
//                            );

//            modVelocidade[i] = sqrt(velocidade[i].x()*velocidade[i].x() + velocidade[i].y()+velocidade[i].y());
//        }


//        if(Navegador::estaoProximos(posicao , robo->getAlvoFinal(), PATH_PLANNING_MAX_TAM_SEGUIMENTOS))
//        {
//            alvo = Navegador::pontoAleatorio();
//            robo->setAlvoFinal(alvo);
//        }

//        robo->setPosicao(Ponto( posicao.x() + velocidade[i].x() , posicao.y() + velocidade[i].y() ));

//        if(i > 0)
//        {
//            circlefill(img, campo2allegro_x(posicao.x()) , campo2allegro_y(posicao.y()) , RAIO_ROBO/ESCALA , 0x0000ff );
//        }

//    }
//}

//int main()
//{
////    srand(time(NULL));
//    Relogio rel;
//    Navegador teste(0);

//    rel.setTempoInicial(rel.getTempoDoDia());
//    double t, maxT = -999, minT = 999;

//    iniciaAllegro();
//    definePosicaoDosRobos();

//    blit(img, screen ,  0 , 0 , 0 , 0 , screen->w , screen->h);

//    Robo *r = Sistema::modeloMundo.getRoboEq(0);
////    Agente *a = &( (* Sistema::getAgentes())[0]);

//    readkey();
//    while(!key[KEY_ESC])
//    {
//        if(mouse_b)
//        {
//            Ponto ObstaculoVirtual(allegro2campo_x(mouse_x), allegro2campo_y(mouse_y));
//            teste.adicionaObstaculo(new Circulo(ObstaculoVirtual, 500*500));
//            circlefill(img, mouse_x , mouse_y , 500/ESCALA , 0x00ffff );

//        }
//        rel.setTempoInicial(rel.getTempoDoDia());
//        const vector<Ponto>& caminho = teste.pontosRRT(r->getAlvoFinal());
//        t = rel.getTempoPassado();
//        if(t > maxT) maxT = t;
//        if(t < minT) minT = t;
//        cout << "tMax = " << maxT << "s tMin = " << minT << "s t = " << t <<'s' << endl ;

//        circlefill(img ,
//                   campo2allegro_x(r->getAlvoFinal().x()), campo2allegro_y(r->getAlvoFinal().y()),
//                   (PATH_PLANNING_DISTANCIA_DESCONSIDERAVEL-PATH_PLANNING_TAM_EXTRA_OBSTACULO-RAIO_ROBO)/ESCALA , 0xff0000);
//        circlefill(img ,
//                   campo2allegro_x(r->getPosicao().x()), campo2allegro_y(r->getPosicao().y()),
//                   RAIO_ROBO/ESCALA , 0xffff00);

//        desenhaCaminho(caminho);
//        movimentaRobos(caminho[0]);

//        blit(img, screen ,  0 , 0 , 0 , 0 , screen->w , screen->h);
//        rectfill(img , 0 , 0 , img->w, img->h , 0xffffff);
//        rest(30);
//    }

//    readkey();
//}

////============= Teste do navegador com IA JUNTO  ==============================

//// Para executar esse teste é necessario instalar a biblioteca allegro 4.2
//// para visualizar os pontos retornados pelo navegador
//// tambem é necessario incluir no .pro a biblioteca LIBS += `allegro-config --libs`
//// no caso do linux. E descomentar os comentarios no inicio do Navegador.cpp

//#include <allegro.h>


//#include<IUSistema.h>
//#include <QCoreApplication>


////Configuracoes da tela
//// Tamanho da janela
//#define MAX_X         756
//#define MAX_Y         506

//// Tamanho virtual da tela (scrolling)
//#define V_MAX_X 0
//#define V_MAX_Y 0

//#define COLOR_BITS    desktop_color_depth()
//#define VIDEO_CARD    GFX_AUTODETECT_WINDOWED

//#define DIGI_CARD     DIGI_SB16
//#define MIDI_CARD     MIDI_SB_OUT
//#define ESCALA 9

//BITMAP *img;

//int campo2allegro_x(float x)
//{
//    return (int) (x + Config::COMPRIMENTO_CAMPO/2) / ESCALA;
//}

//int campo2allegro_y(float y)
//{
//    return (int) (MAX_Y - (y + Config::LARGURA_CAMPO/2) / ESCALA);
//}

//float allegro2campo_x(int x)
//{
//    return (float) (x * ESCALA - Config::COMPRIMENTO_CAMPO/2);
//}

//float allegro2campo_y(int y)
//{
//    return (float) ((MAX_Y -y) * ESCALA - Config::LARGURA_CAMPO/2 );
//}

//void iniciaAllegro()
//{
//    allegro_init();
//    install_mouse();
//    install_keyboard();
//    install_timer();

//    set_color_depth(COLOR_BITS );

//    if (set_gfx_mode(VIDEO_CARD, MAX_X, MAX_Y, V_MAX_X, V_MAX_Y) < 0)
//        return ;

//    img = create_bitmap(screen->w , screen->h);
//    rectfill(img, 0, 0, img->w, img->h, 0xffffff);
//    show_os_cursor(2);
//}

//int main(int argc, char *argv[])
//{
//    QCoreApplication a(argc, argv);
//    iniciaAllegro();

//    /// Alocando as variaveis
//    IUSistema* iuSistema = new IUSistema;
//    Config* config = iuSistema->getConf();
//    Carregador* carregador = iuSistema->getCarregador();

//    /// Carregando as jogadas da Pasta Playbook
//    if(carregador->pegarNomeArquivosJogadas(config->getPathPlaybook())){
//        carregador->setNomeJogadasEscolhidas(carregador->getNomeArquivosJogadas());
//        carregador->carregarJogadasEscolhidas();

//        /// Verificando se foi completada o carregamento das jogadas
//        if(carregador->isCarregamentoSemErro()){
//            iuSistema->inicia(); /// Iniciando o sistema
//        }else{
//            cout << "Nao foi possivel carregar os arquivos das jogadas. Jogadas com erro" << endl;
//        }
//    }else{
//        cout << "Nao foi possivel pegar o nome dos arquivos das jogadas" << endl;
//    }

//    return a.exec();
//}
