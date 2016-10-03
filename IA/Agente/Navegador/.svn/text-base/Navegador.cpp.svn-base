//#include <allegro.h>
#include "Navegador.h"
#include <Sistema.h>
#include <stack>

// ==== Utilizado no codigo de teste ====
//#define MAX_X         756
//#define MAX_Y         506
//#define ESCALA 9

//extern BITMAP *img;
//int campo2allegro_x(float x);
//int campo2allegro_y(float y);
//float allegro2campo_x(int x);
//float allegro2campo_y(int y);
// ======================================

/**
*  O método protegido atualizaObstaculosInterno.
*  Atualiza a posição dos obstáculos interno, os robos.
*/
void Navegador::atualizaObstaculosInterno()
{
    deletaObstaculosInterno();
    Circulo *c;

    //    cout << "Pego posição dos outros robôs" << endl;
    vector<Robo>* robosEq = Sistema::modeloMundo.getRobosEq();
    vector<Robo>* robosAdv = Sistema::modeloMundo.getRobosAdv();

    for(int id=0; id< NUM_MAX_ROBOS;id++){

        /// verificando se o robo está presente
        Robo* roboEq = &robosEq->at(id);
        if(roboEq->isPresente()){

            /// Verificando se o id do robo e diferente do id do robo que esta executando o path planning
            if(id != m_ID && m_obstaculosRoboEqAtivados[id])
            {
                if(squared_distance(m_alvo , roboEq->getPosicao()) > PATH_PLANNING_DIST_DESCONSIDERAVEL*PATH_PLANNING_DIST_DESCONSIDERAVEL )
                {
                    c = new Circulo(roboEq->getPosicao(), raioObstaculoRobo*raioObstaculoRobo);
                    //                circlefill(img, campo2allegro_x(c->center().x()) , campo2allegro_y(c->center().y()) , sqrt(c->squared_radius())/ESCALA , 0x00ff00 );

                    m_obstaculos.push_back(c);
                    //                cout << "RoboEq " << robo->getId() << " atualizado" << endl;
                }
            }
        }

        /// Verificando se o robo esta presente no campo
        Robo* roboAdv = &robosAdv->at(id);
        if(roboAdv->isPresente() && m_obstaculosRoboAdvAtivados[id])
        {
            if(squared_distance(m_alvo , roboAdv->getPosicao()) > PATH_PLANNING_DIST_DESCONSIDERAVEL*PATH_PLANNING_DIST_DESCONSIDERAVEL )
            {
                c = new Circulo(roboAdv->getPosicao(), raioObstaculoRobo*raioObstaculoRobo);
                //                circlefill(img, campo2allegro_x(c->center().x()) , campo2allegro_y(c->center().y()) , sqrt(c->squared_radius())/ESCALA , 0x00ff00 );

                m_obstaculos.push_back(c);
                //                cout << "RoboEq " << robo->getId() << " atualizado" << endl;
            }
        }
    }
}

/** O método protegido deletaObstaculos.
*  Deleta todos obstaculos internos, os robos.
* Este metodo é chamado a cada interacao
*/
void Navegador::deletaObstaculosInterno()
{
    //    cout << "Deletando Obstaculos" << endl;
    if(!m_obstaculos.empty())
    {
        list<Poligono*>::iterator i;
        for(i = m_obstaculos.begin() ; i != m_obstaculos.end() ; i++)
        {
            //            cout << "Interacao" << endl;
            delete *i;
        }
        m_obstaculos.clear();
        //        cout << "Fim do deleta" << endl;
    }

}

void Navegador::deletaObstaculosExterno()
{
    if(!m_obstaculosExtra.empty())
    {
        list<Poligono*>::iterator i;
        for(i = m_obstaculosExtra.begin() ; i != m_obstaculosExtra.end() ; i++)
        {
            delete *i;
        }
        m_obstaculosExtra.clear();
    }
}


/**
 * @brief
 *  Remove do navegador os obstaculos que estão
 * colidindo com o alvo, destino do caminho
 */
void Navegador::deletaObstaculosExternoDentroAlvo()
{
    if(!m_obstaculosExtra.empty())
    {
        list<Poligono*>::iterator i = m_obstaculosExtra.begin();
        while( i != m_obstaculosExtra.end())
        {
            if((*i)->isPontoDentro(m_alvo))
            {
                delete (*i);
                i = m_obstaculosExtra.erase(i);
            }else
            {
                i++;
            }
        }
    }
}

/** O método protegido escolhaAlvo.
*
*     Este método retorna um ponto que pode ser o Alvo do path planning, um ponto aleatório ou,
*  um ponto aleatório armazenado na cache. A probabilidade da escolha de um desses pontos depende
*  das constantes:
*
*  PATH_PLANNING_PROB_DIRECAO_ALVO - Probabilidade de escolher o alvo
*  PATH_PLANNING_PROB_DIRECAO_CACHE - Probabilidade de escolher um ponto aleatório da cache.
*
*  A probabilidade de escolher um ponto aleatório é 100 - ( PATH_PLANNING_PROB_DIRECAO_ALVO + PATH_PLANNING_PROB_DIRECAO_CACHE)
*
*  As probabilidades estão em porcentagen, ou seja, variam de 0 a 100.
*/

Ponto Navegador::escolhaAlvo( )
{
    int p = rand() %100;
    int i = rand() %PATH_PLANNING_MAX_NUM_CACHE_PONTOS;

    if( p < PATH_PLANNING_PROB_DIRECAO_ALVO)
    {
        return m_alvo;
    }
    else if( p < PATH_PLANNING_PROB_DIRECAO_ALVO + PATH_PLANNING_PROB_DIRECAO_CACHE)
    {
        Ponto p = m_cache[i];
        //        circlefill(img ,
        //                   campo2allegro_x(p.x()), campo2allegro_y(p.y()), 3, 0xff0000);
        return p;
    }else
    {
        Ponto p = pontoAleatorio();
        // circlefill(img ,
        //            campo2allegro_x(p.x()), campo2allegro_y(p.y()), 3, 0x00ff00);
        return	p;
    }

}



/**
 * @brief
 *  Recebe um seguimento definido por dois pontos (inicio, fim),
 * calcula um seguimento que começa em ini e possui a mesma
 * direcao, mas com tamanho definido nas configurações do
 * Navegador.
 * @param inicio - Inicio do seguimento
 * @param fim
 * @param pontoFinalSeguimentoLimitado
 * @return Ponto
 */
bool Navegador::extenda (Ponto &inicio, Ponto &fim, Ponto &pontoFinalSeguimentoLimitado )
{
    limitaSegmento(inicio , fim,  PATH_PLANNING_MAX_TAM_SEGUIMENTOS, pontoFinalSeguimentoLimitado);
    if(obstaculoContemPonto(pontoFinalSeguimentoLimitado) )
        return false;
    return true;
}


/**
 * @brief
 * Recebe um seguimento definido por dois pontos
 * (inicio, fim) e verifica se esse seguimento
 * possui alguma intersecção com algum obstaculo
 * do Navegador.
 * @param inicio - Inicio do seguimento
 * @param fim - Fim do seguimento
 * @return bool - true se existe colisao, false
 * caso contrario.
 */
bool Navegador::colisao(Ponto &inicio, Ponto &fim)
{
    //    cout << "Testando colisões" << endl;
    list < Poligono* >::iterator it;
    //    cout << "Entrando no for" << endl;
//    Reta reta(inicio, fim);

    for(it = m_obstaculos.begin() ; it != m_obstaculos.end() ; it ++)
    {
        if((*it)->isInterseccao(inicio, fim))
        {
            cout << inicio << " " << fim << " ";
            cout << "Colisão interno = true" << endl;
            return true;
        }
    }
    for(it = m_obstaculosExtra.begin() ; it != m_obstaculosExtra.end() ; it ++)
    {
        if((*it)->isInterseccao(inicio, fim))
        {
            cout << "Colisão extra = true" << endl;
            return true;
        }
    }

    //    cout << "Colisão = false" << endl;
    return false;
}



/**
 * @brief Recebe um segmento definido por dois pontos
 * (inicio, fim) e verifica se existe colisão do
 * seguimento com algum obstaculo interno
 * do navegador.
 *  Preocupado com a eficiencia do algoritmo, foi feito
 * uma simplificação no calculo de colisoes com osbtaculos,
 * as colisões são calculadas apenas verficando se o
 * o ponto inicial e o ponto final do seguimento estão
 * dentro de algum obstaculo. Esta simplificação foi
 * feita assumindo que o tamanhos dos segmentos que
 * seram testados são bem menores que o raio dos obstaculos,
 * portanto este metodo funciona apenas para seguimentos
 * pequenos, bem menores que o raio dos obstaculo.
 * @param inicio - ponto de inicio do seguimento
 * @param fim - ponto final do seguimento
 * @return bool - true se existe colisao, false caso
 * contrario.
 */
bool Navegador::colisaoSimplificada( Ponto &inicio, Ponto &fim)
{
    //    cout << "Testando colisões" << endl;
    list < Poligono* >::iterator i;
    //    cout << "Entrando no for" << endl;

    for(i = m_obstaculos.begin() ; i != m_obstaculos.end() ; i ++)
    {
        if((*i)->isPontoDentro(inicio) || (*i)->isPontoDentro(fim))
        {
            //            cout << "Colisão = true" << endl;
            return true;
        }
    }
    for(i = m_obstaculosExtra.begin() ; i != m_obstaculosExtra.end() ; i ++)
    {
        if((*i)->isPontoDentro(inicio) || (*i)->isPontoDentro(inicio))
        {
            //            cout << "Colisão = true" << endl;
            return true;
        }
    }

    //    cout << "Colisão = false" << endl;
    return false;
}


/** O método protegido obstaculoContemPonto.
  * Varifica se um ponto esta dentro de algum obstaculo, se estiver, esse obstaculo é retornado por referência em obs
    \param A ponto que se quer testar.
    \param obs É opcional,é retornado por referencia o primeiro obstaculo que contem o ponto A, pode ser um obstaculo internor (os robos) ou externo (adicionado).
    \return Retorna true se algum obstaculo contiver o ponto, ou false caso contrario.
  * Se nenhum obstaculo conter o ponto, a referencia obs não é alterada. O parâmetro obs é opicional.
    \sa adicionaObstaculo(Obstaculo *novoObstaculo)
*/
bool Navegador::obstaculoContemPonto(Ponto &A , Poligono** obs)
{
    list <Poligono*>::iterator i;

    for (i = m_obstaculos.begin(); i != m_obstaculos.end() ; i++)
    {
        if((*i)->isPontoDentro(A))
        {
            if(obs != 0x0)
                (*obs) = *i;
            return true;
        }
    }
    for (i = m_obstaculosExtra.begin(); i != m_obstaculosExtra.end() ; i++)
    {
        if((*i)->isPontoDentro(A))
        {
            if(obs != 0x0)
                (*obs) = *i;
            cout << "COLISAO EXTERNA!!" << endl;
            return true;
        }
    }
    return false;
}


/** O método protegido inicializaCache.
 *
 * Atribui pontos aleatórios que estão dentro do campo na memória cache utilizando o método pontoAleatorio()
 *  \sa pontoAleatorio()
*/
void Navegador::inicializaCache()
{
    int i;
    for(i = 0; i < PATH_PLANNING_MAX_NUM_CACHE_PONTOS ; i++)
    {
        m_cache[i] = pontoAleatorio();
    }
}


/** O método protegido inicializaNavegador.
 * Inicializa todos atributos do navegador, inicializa a cache com pontos alatórios com o método inicializaCache(),
 * define uma semente para o gerador de numeros aleatorios.
    \sa inicializaCache()
*/
void Navegador::inicializaNavegador()
{
    /// setando que o navegador ira iniciar desativado
    navegadorAtivo = false;

    //    srand(time(NULL));
    m_obstaculosRoboEqAtivados.resize(NUM_MAX_ROBOS, true);
    m_obstaculosRoboAdvAtivados.resize(NUM_MAX_ROBOS, true);

    raioObstaculoRobo = 2*RAIO_ROBO+PATH_PLANNING_TAM_EXTRA_OBSTACULO;
    m_cache.resize(PATH_PLANNING_MAX_NUM_CACHE_PONTOS+5);
    inicializaCache();
    m_idadeCaminho = 0;
}


/**
 * @brief
 *  Este metodo suavisa o caminho calculando a media
 * dos primeiros n pontos do caminho.
 *  A média definida no ponto i, é a media entre
 * os pontos i-1 e i+1.
 * @param n - numero de pontos que sera suavisado
 * se n for maior que o numero de pontos do
 * caminho, sera suavisado todos os pontos
 * do caminho.
 */
void Navegador::normaliza(unsigned n)
{
    if(n > m_caminho.size())
        n = m_caminho.size();

    float x = m_origem.x(), y = m_origem.y();
    for(unsigned i = 1; i < n ; i++)
    {
        x = (x + m_caminho[i].x()) / 2.f;
        y = (y + m_caminho[i].y()) / 2.f;

        m_caminho[i-1] = Ponto(x, y);
    }
}

/**
 * @brief
 *  Verifica se é necessario calcular um novo caminho
 * para o alvo desejado.
 *  A origem sempre é a posicao inicial do robo.
 * @param pAlvo - Alvo, ponto de destino do caminho
 * @return bool - true se é necessario calcular um novo
 * caminho, false se o caminho calculado na interacao
 * anterior pode ser re-aproveitado.
 */
bool Navegador::eh_necessarioCalcularNovoCaminhoReta()
{
    // Se possui uma resposta da interacao anterior, e o alvo anterior é o mesmo dessa intercao
    if(m_caminho.size() > 0 && estaoProximos(m_caminho.back() , m_alvo, 10.0) )
    {
        // Verifica se a origem esta longe do destino e se existe uma colisao de algum obstaculo com a solucao da interacao anterior
        if(estaoProximos(m_origem , m_caminho[0] , 50.0) == false && colisao(m_origem , m_caminho[0]) == false )
        {
            cout << "Não há colisão e a origem e alvo não esta proxima" << endl;
            return false; // Nao é necessario recalcular a trajetoria
        }
    }
    return true; // É preciso recalcular o caminho
}


bool Navegador::eh_necessarioCalcularNovoCaminho()
{
    if(m_caminho.size() == 0)
    {
        m_idadeCaminho = 0;
        return true;
    }

    // Se o caminho for pequeno, sempre recalcula
    if(m_caminho.size() < 5)
    {
        m_idadeCaminho = 0;
        return true;
    }

    if(!estaoProximos(m_caminho.back() , m_alvo, 50.0))
    {
        return true;
    }

    // Remove um subcaminho atingido
    if(estaoProximos(m_origem, m_caminho[0], PATH_PLANNING_MAX_TAM_SEGUIMENTOS))
        m_caminho.erase(m_caminho.begin());

    // Verifica todos pontos do caminho
    float x = m_origem.x(), y = m_origem.y();
    for(unsigned i = 1; i < m_caminho.size() ; i++)
    {
        if(m_idadeCaminho < PATH_PLANNING_NUM_SUAVISACAO_CAMINHO)
        {
            x = (x + m_caminho[i].x()) / 2.f;
            y = (y + m_caminho[i].y()) / 2.f;
            m_caminho[i-1] = Ponto(x, y);
        }

        if(obstaculoContemPonto(m_caminho[i-1]))
        {
            m_idadeCaminho = 0;
            return true;
        }
    }
    m_idadeCaminho++;
    return false;
}


/**
 * @brief Este metodo é o loop principal do algoritmo RRT, ele
 * expande a arvore em direção ao alvo de forma quase aleatoria,
 * dependendo dos pesos do algoritmo.
 *  O loop termina quando o número de nodos da arvore atingir um
 * limite maximo de nodo, neste caso o caminho é dificil de ser traçado
 * pelo algoritmo, e devido as limitações de tempo de execução
 * não poderemos seguir explorando a arvore e o caminho mais
 * proximo da solução sera retornado, quando o número de falhas
 * atingir um limite maximo, uma falha acontece quando um ponto
 * é descartado pelo algoritmo por colidir com algum obstaculo
 * tentando expandir a arvore, ou quando a RRT consegue chegar
 * no alvo (encontrou o caminho completo).
 *
 * @param Arvore - Arvore que sera expandida
 * @return KDNodo - Retorna o ultimo nodo adicionado na arvore
 */

KDNodo* Navegador::expandeRRT(KDTree &arvore)
{
    Ponto  novoPonto;
    KDNodo nodoTrajetoria(0,0);
    KDNodo *nodoMaisProximo;
    KDNodo *ultimoNodo;
    m_numFalhas = 0;

    while(arvore.size() < (uint)PATH_PLANNING_MAX_NUM_PONTOS && m_numFalhas < PATH_PLANNING_MAX_NUM_PONTOS/2 )
    {
        // Escolhe um ponto aleatorio que nao esteja em um obstaculo
        nodoTrajetoria.p = escolhaAlvo();

        // Busca na KD-Tree o nodo com o ponto geometricamente mais proximo
        nodoMaisProximo = arvore.maisProximo(&nodoTrajetoria);

        // Se o mais proximo for o proprio ponto
        if(nodoMaisProximo->p == nodoTrajetoria.p)
            continue; // Busca outro ponto

        // Se consegui extender a RRT sem colidir
        if(extenda(nodoMaisProximo->p , nodoTrajetoria.p, novoPonto))
        {
            //            cout << "PATH_PLANNING" << m_ID << "::Criando novo Nodo " << nodoMaisProximo->p << " -> " << novoPonto << endl;
            //circlefill(img ,
            //           campo2allegro_x(novoPonto.x()), campo2allegro_y(novoPonto.y()), 2, 0x0);
            //fastline(img ,
            //         campo2allegro_x(nodoMaisProximo->p.x()) , campo2allegro_y(nodoMaisProximo->p.y()),
            //         campo2allegro_x(novoPonto.x()), campo2allegro_y(novoPonto.y()), 0xff0000);
            //         readkey();
            // Cria um nodo como extensão do nodo mais proximo, com o ponto extendido
            ultimoNodo = new KDNodo(novoPonto.x() , novoPonto.y() , nodoMaisProximo);

            //            cout << "PATH_PLANNING" << m_ID << "::Adicionando novo Nodo" << endl;

            // Adiciona o nodo na arvore
            arvore.adiciona(ultimoNodo);

            // Se chegou no destino
            if(squared_distance( novoPonto, m_alvo) < PATH_PLANNING_MAX_TAM_SEGUIMENTOS*PATH_PLANNING_MAX_TAM_SEGUIMENTOS )
            {
                //                cout << "PATH_PLANNING" << m_ID << "::Caminho completo" << endl;
                break;
            }
        }else
        {
            // Expencao da RRT colidiu com um obstaculo
            //            cout << "PATH_PLANNING" << m_ID << ":: Falha de caminho" << endl;
            m_numFalhas++;
        }
    }

    // Retorna o ultimo nodo adicionado na arvore
    return ultimoNodo;
}


/**
 * @brief
 *  Constroe um caminho a partir de um nodo
 * da arvore, o caminho é construido no atributo m_caminho.
 * @param arvore - Arvore com os pontos explorados.
 * @param ultimoNodo - Nodo com o ponto final do caminho.
 */
void Navegador::constroeCaminho(KDTree &arvore, KDNodo *ultimoNodo)
{
    // Se a arvore não tem nodos
    if(arvore.size() <= 2) // Revisar esse 2, pq nao 1?
    {
        cout << "PATH PLANNING:: Caminho direto" << endl;
        // O caminho é direto para o alvo
        // so o alvo pertence ao caminho
        m_caminho.push_back(m_alvo);

        cout << "Caminho reto, arvore vazia" << endl;
        return ;
    }

    /*  O ultimoNodo é o ultimo nodo adiconado da arvore,
      * se o caminho foi encontrado, a arvore possui
      * menos nodos que o limite de nodos e o ultimoNodo é
      * o ultimo ponto do caminho, caso contrario
      * o ultimo nodo foi apenas o ultimo nodo inserido
      * antes de estourar o limite de nodos, neste caso
      * deve-se encontrar o caminho mais proximo
      * do alvo, buscando o nodo mais proximo do
      * alvo na KD-Tree.
    */

    // Se a arvore atingiu limite de nodos (nao encontrou o caminho)
    if(arvore.size() == PATH_PLANNING_MAX_NUM_PONTOS)
    {
        KDNodo nodoAlvo(m_alvo.x(), m_alvo.y());

        // Pega o nodo mais proximo do alvo
        ultimoNodo = arvore.maisProximo(&nodoAlvo);
    }

    // Coloca o ultimo nodo, o alvo do caminho encerrando a construção da arvore
    ultimoNodo = new KDNodo(m_alvo.x() , m_alvo.y() , ultimoNodo);
    arvore.adiciona(ultimoNodo);

    // Construindo o caminho a partir do nodo mais da ponta da arvore
    // acessando seus ancestrais até chegar no nodo raiz que possui
    // o ponto inicial do caminho

    stack<Ponto> pilha;

    // Enquanto o nodo tiver pai (constroe o caminho iguinorando o nodo raiz origem)
    while(ultimoNodo->RRTRef != 0x0)
    {
        // Para cada nodo que pertence ao caminho
        //        cout << "PATH PLANNING:: Construindo caminho " << ultimoNodo->p << endl;

        // Salva o ponto na cache do algoritmo
        m_cache[rand() % PATH_PLANNING_MAX_NUM_CACHE_PONTOS] = ultimoNodo->p;


        pilha.push(ultimoNodo->p);
        ultimoNodo = ultimoNodo->RRTRef;
    }

    while(!pilha.empty())
    {
        m_caminho.push_back(pilha.top());
        pilha.pop();
    }

    return ;
}


/**
 * @brief
 *  Este metodo tenta calcular o caminho direto da origem ao
 * destino utilizando uma reta.
 * @return bool - true se conseguiu calcular o caminho,
 * false caso contrario.
 */
bool Navegador::calcularCaminhoDireto()
{
    if(!colisao(m_origem, m_alvo))
    {
        m_caminho.push_back(m_alvo);
        return true;
    }
    return false;
}


/**
 * @brief
 *  Calcula o caminho para o robo
 * @param origem - Origem do caminho
 * @param destino - Destino do caminho
 * @return const vector<Ponto> - Pontos do caminho
 */
void Navegador::calculaCaminho(const Ponto &origem, const Ponto &alvo)
{
    // adicionaObstaculo(new Circulo(Ponto(0.f,0.f) , 1500*1500));

    // Estapa exencial do algoritmo
    // Atualiza alvo e origem
    m_origem = origem;
    m_alvo = alvo;

    //    circlefill(img, campo2allegro_x(0) , campo2allegro_y(0) , 1000/ESCALA , 0x00ffff );

    // Atualiza a posicao dos obstaculos internos
    atualizaObstaculosInterno(); // A Origem tem que estar atualizazada para chamar este metodo

    // Deleta obstaculos em cima do alvo
    deletaObstaculosExternoDentroAlvo(); // m_alvo tem que estar definido!

    // Se for necessario calcular um novo caminho
    if(eh_necessarioCalcularNovoCaminho())
    {
        //        circlefill(img , campo2allegro_x(origem.x()), campo2allegro_y(origem.y()), RAIO_ROBO/ESCALA , 0xffff00);
        //        circlefill(img , campo2allegro_x(alvo.x()), campo2allegro_y(alvo.y()), 10 , 0x00ff00);
        // O metodo chamado acima atualiza m_origem e m_alvo e obstaculos internos
        // quando retorna true

        // Apaga a ultima solucao
        m_caminho.clear();

        // Se a origem esta proximo do alvo
        if(estaoProximos(origem, alvo, 40.0))
        {   // Não é calculado nenhum caminho
            Sistema::modeloMundo.getRoboEq(m_ID)->setPacotePathPlanning(criaPacotePathPlanning());
            m_caminho.push_back(alvo);
            return ;
        }

        /* === Testando se a origem do caminho esta dentro de um obstaculo ===
         *  Se a origem estiver dentro de um obstaculo, o algoritmo
         * calcula um caminho para sair do obstaculo pela direção oposta a que
         * ele entrou. Este ponto é calculado prolongando um
         * segmento de reta que começa no centro do obstaculo colidido
         * e anda em direção a origem do caminho, o ponto final desse seguimento
         * de tamanho (RaioRobo + TAMEXTRAOBSTACULO + 10) sera inserido no caminho
         * calculado pelo algoritmo.
         */
        Poligono *colidente;
        if(obstaculoContemPonto(m_origem , &colidente))
        {
            Vetor direcaoSaida = m_origem - colidente->getCentro();
            direcaoSaida = direcaoSaida/ sqrt(direcaoSaida.squared_length());

            Ponto extendido = m_origem + direcaoSaida* (RAIO_ROBO*2 + PATH_PLANNING_TAM_EXTRA_OBSTACULO + PATH_PLANNING_MAX_TAM_SEGUIMENTOS);

            m_caminho.push_back(extendido);
            m_caminho.push_back(alvo);

            //cout << "Caminho origem dentro de obstaculo" << endl;
            return ;
        }

        // Tenta calcular o alvo diretamente com ma reta
        if(calcularCaminhoDireto())
        {
            // Se conseguir, retorna o alvo direto como caminho
            //cout << "Alvo direto" << endl;
            return ;
        }

        // Cria a arvore para encontrar o caminho
        KDTree arvore;
        KDNodo *ultimoNodo = 0x0;

        // Adiciona a origem como raiz da arvore
        arvore.adiciona(new KDNodo(m_origem.x(),m_origem.y()));

        // Expande a arvore em direcao ao alvo usando o algoritmo RRT
        ultimoNodo = expandeRRT(arvore);

        // Constroe o caminho a partir da arvore
        constroeCaminho(arvore, ultimoNodo);
    }

    //cout << "Alvo anterior" << endl;

    return ;
}


/** O construtor padrão.
 *
 *  Iniciliza os atributos do Navegador sem saber o ID, apenas chamando o método inicializaNavegador().
 *  Para calcular o path planning é necessario que o ID do robo esteja definido utilizando o método setId().
    \sa inicializaNavegador() , setId().
*/
Navegador::Navegador()
{
    inicializaNavegador();
}

/** O construtor de cópia.
 *   Construtor de cópia do navegador, copia o ID, o alvo, e o ultimo ponto calculado, os demais parâmetros são
 * inicializados com o método inicializaNavegador().
    \sa inicializaNavegador()
*/
Navegador::Navegador(const Navegador &nav)
{
    m_ID = nav.m_ID;
    m_alvo = nav.m_alvo;
    m_caminho = nav.m_caminho;
    m_origem = nav.m_origem;
    inicializaNavegador();
    //    /* Copia dos Obstaculos Externo*/
    //    list<Obstaculo*>::iterator i;
    //    for(i = nav.ObstaculosExtra.begin() ; i != nav.ObstaculosExtra.end() ; i++)
    //    {
    //        ObstaculosExtra.push_back((*i)->copia());
    //    }
}

/** O construtor com passagem do ID.
 *
 *  Inicializa os atributos com o método inicializaNavegador() e seta o ID.
    \sa inicializaNavegador()
 */

Navegador::Navegador(int MeuID)
{
    m_ID = MeuID;
    inicializaNavegador();
}


/** O destrutor.
  *
  * Deleta todos obstáculos dinâmicos que foram adicionados com o método adicionaObstaculo.
  * \sa adicionaObstaculo(Obstaculo *novoObstaculo)
*/

Navegador::~Navegador()
{
    apagaObstaculos();
}

void Navegador::ativar()
{
    navegadorAtivo = true;
}

void Navegador::desativar()
{
    navegadorAtivo = false;
}

/**
 * @brief
 *  Recebe um seguimento definido por dois pontos (inicio, fim)
 * e calcula um novo seguimento que começa em inicio, tem a
 * direção inicio -> fim, mas possui um tamanho diferente,
 * definido por tamSeg.
 *  O ponto final do seguimento calculado é retornado por
 * referencia no parametro fimSegCalculado.
 *  Se inicio == fim, o seguimento é invalido, neste caso
 * é atribuida uma didreção V( 0 , 1) para o seguimento
 * e false é retornado pela função.
 *  Se tamSeg == 0.f , o ponto final calculado sera igual
 * ao inicio.
 * @param inicio - Inicio do seguimento
 * @param fim - Fim do seguimento.
 * @param tamSeg - Tamanho do novo seguimento que sera calculado
 * @param fimSegCalculado - Ponto final do seguimento calculado (retorno por referencia)
 * @return bool - true se inicio != fim, false caso contrario
 */
bool Navegador::limitaSegmento(const Ponto &inicio, Ponto &fim, float tamSeg, Ponto& fimSegCalculado)
{
    if(inicio == fim)
    {
        fimSegCalculado = Ponto(fim.x(), fim.y()+tamSeg);
        return false;
    }

    if(tamSeg == 0)
    {
        fimSegCalculado = inicio;
        return true;
    }

    float d =squared_distance(  inicio, fim);
    d = sqrt(d);

    Vetor VetSeg = fim - inicio;
    Vetor unitario(VetSeg.x() / d , VetSeg.y() / d);

    fimSegCalculado = inicio + tamSeg * unitario;

    return true;
}


/**
 * @brief
 * Retorna um poto aleatorio dentro do campo
 * @return Ponto
 */
Ponto Navegador::pontoAleatorio()
{
    float x = -Config::MEIO_COMPRIMENTO_CAMPO + rand()%int(Config::COMPRIMENTO_CAMPO);
    float y = -Config::MEIA_LARGURA_CAMPO + rand()%int(Config::LARGURA_CAMPO);

    return Ponto ( x , y);
}


/**
 * @brief Retorna um poto aleatorio dentro do campo que não esteja dentro de um obstaculo
 *
 * @return Ponto
 */
Ponto Navegador::pontoAleatorioSemColisao()
{
    Ponto P = pontoAleatorio();
    while(obstaculoContemPonto(P))
    {
        P = pontoAleatorio();
    }
    return P;
}


/**
 * @brief
 * Atribui o ID do robo que esta usando o navegador
 * @param Id
 */
void Navegador::setId(int Id)
{
    m_ID = Id;
}


/**
 * @brief
 *  Retorna o ultimo alvo calculado ou a origem
 * caso ainda não tenha sido calculado nenhum alvo.
 * @return Ponto
 */
Ponto Navegador::getUltimoAlvoCalculado()
{
    if(m_caminho.size() > 0)
        return m_caminho[0];
    else
        return m_origem;
}


/**
 * @brief
 *  Retorna os pontos do ultimo caminho
 * calculado pelo navegador
 * @return const vector<Ponto> - Pontos do ultimo caminho
 */
const vector<Ponto> &Navegador::getUltimosAlvosCalculado()
{
    return m_caminho;
}


/*! Faz a busca do caminho */
Ponto Navegador::RRT (Ponto origem, Ponto alvo)
{
    calculaCaminho(origem, alvo);
    Sistema::modeloMundo.getRoboEq(m_ID)->setPacotePathPlanning(criaPacotePathPlanning());
    deletaObstaculosExterno();

    if(m_caminho.size() > 0)
        return m_caminho[0];

    return alvo;
}


Ponto Navegador::RRT (Ponto alvo)
{
    if(navegadorAtivo){

        if(m_ID >= 0 && m_ID < NUM_MAX_ROBOS)
        {
            calculaCaminho(Sistema::modeloMundo.getRoboEq(m_ID)->getPosicao() , alvo);
            Sistema::modeloMundo.getRoboEq(m_ID)->setPacotePathPlanning(criaPacotePathPlanning());
            deletaObstaculosExterno();

            return m_caminho[0];
        }

        cout << "PathPlanning::Erro de ID,  MeuID = " << m_ID << endl;
    }

    return alvo;
}


/**
 * @brief
 *  Utiliza o metodo pontosRRT(Ponto origem, Ponto alvo)
 * passando a posição do robo como origem.
 * @param alvo
 * @return const vector<Ponto>
 */
vector<Ponto> Navegador::pontosRRT(Ponto alvo)
{
    if(navegadorAtivo){

        if(m_ID >= 0 && m_ID < NUM_MAX_ROBOS)
        {
            calculaCaminho(Sistema::modeloMundo.getRoboEq(m_ID)->getPosicao() , alvo);
            Sistema::modeloMundo.getRoboEq(m_ID)->setPacotePathPlanning(criaPacotePathPlanning());
            deletaObstaculosExterno();

            return m_caminho;
        }
        cout << "PathPlanning::Erro de ID,  MeuID = " << m_ID << endl;
    }

    return vector<Ponto>(1, alvo);
}


/**
 * @brief
 *  Retorna todos os pontos do caminho calculado
 * o caminho é formado pelos pontos do caminho
 * até o alvo final na ultima posicao do vetor,
 * a origem não é incluida no caminho, a primeira
 * posição do vetor é o primeiro ponto do caminho
 * calculado.
 * @param origem - Origem do caminho
 * @param alvo - Alvo (destino)
 * @return const vector<Ponto> - Pontos que levam
 * a origem ao alvo.
 */
vector<Ponto> Navegador::pontosRRT(Ponto origem, Ponto alvo)
{
    calculaCaminho(origem, alvo);
    Sistema::modeloMundo.getRoboEq(m_ID)->setPacotePathPlanning(criaPacotePathPlanning());
    deletaObstaculosExterno();
    return m_caminho;
}

/**
 * @brief
 *  Adiciona um obstaculo virtual no navegador
 * @param novoObstaculo - Obstaculo que sera adicionado.
 */
void Navegador::adicionaObstaculo(Poligono *novoObstaculo)
{
    m_obstaculosExtra.push_back(novoObstaculo);
}

/**
 * @brief
 *  Apaga todos os obstaculos virtuais do Navegador
 */
void Navegador::apagaObstaculos()
{
    list<Poligono*>::iterator i;
    for(i = m_obstaculosExtra.begin() ; i != m_obstaculosExtra.end() ; i++)
    {
        delete *i;
    }
    m_obstaculosExtra.clear();
}

void Navegador::ativaObstaculoRoboAdv(unsigned id)
{
    if(id < m_obstaculosRoboAdvAtivados.size())
        m_obstaculosRoboAdvAtivados[id] = true;
    else
        cout << "Navegador:: Erro ao ativar obstaculo robo adversario, id invalido" << endl;
}

void Navegador::ativaObstaculoRoboEq(unsigned id)
{
    if(id < m_obstaculosRoboEqAtivados.size())
        m_obstaculosRoboEqAtivados[id] = true;
    else
        cout << "Navegador:: Erro ao ativar obstaculo robo equipe, id invalido" << endl;
}

void Navegador::desativaObstaculoRoboAdv(unsigned id)
{
    if(id < m_obstaculosRoboAdvAtivados.size())
        m_obstaculosRoboAdvAtivados[id] = false;
    else
        cout << "Navegador:: Erro ao desativar obstaculo robo adversario, id invalido" << endl;
}

void Navegador::desativaObstaculoRoboEq(unsigned id)
{
    if(id < m_obstaculosRoboEqAtivados.size())
        m_obstaculosRoboEqAtivados[id] = false;
    else
        cout << "Navegador:: Erro ao desativar obstaculo robo equipe, id invalido" << endl;
}

void Navegador::ativaTodosObstaculosRobos()
{
    for(unsigned i = 0 ; i < m_obstaculosRoboEqAtivados.size(); i++)
        m_obstaculosRoboEqAtivados[i] = true;

    for(unsigned i = 0 ; i < m_obstaculosRoboAdvAtivados.size(); i++)
        m_obstaculosRoboAdvAtivados[i] = true;
}

void Navegador::ativaObstaculosRobosEq()
{
    for(unsigned i = 0 ; i < m_obstaculosRoboEqAtivados.size(); i++)
        m_obstaculosRoboEqAtivados[i] = true;
}


void Navegador::desativaObstaculosRobosEq()
{
    for(unsigned i = 0 ; i < m_obstaculosRoboEqAtivados.size(); i++)
        m_obstaculosRoboEqAtivados[i] = false;
}

void Navegador::ativaObstaculosRobosAdv()
{
    for(unsigned i = 0 ; i < m_obstaculosRoboAdvAtivados.size(); i++)
        m_obstaculosRoboAdvAtivados[i] = true;
}

void Navegador::desativaObstaculosRobosAdv()
{
    for(unsigned i = 0 ; i < m_obstaculosRoboAdvAtivados.size(); i++)
        m_obstaculosRoboAdvAtivados[i] = false;
}

PacotePathPlanning Navegador::criaPacotePathPlanning()
{
    PacotePathPlanning pacote;

    for(unsigned i = 0 ; i < m_caminho.size() ; i++)
    {
        //        cout << "Pontos " << m_caminho[i] << endl;
        pacote.add_x(m_caminho[i].x());
        pacote.add_y(m_caminho[i].y());
    }
    return pacote;
}


bool Navegador::estaoProximos(const Ponto &orig, const Ponto &alvo, float tolerancia)
{
    float dx = orig.x() - alvo.x();
    float dy = orig.y() - alvo.y();
    if(dx < 0) dx = -dx;
    if(dy < 0) dy = -dy;

    if(dx < tolerancia && dy < tolerancia)
    {
        //   cout << "Estão proximos true" << endl;
        return true;
    }
    //  cout << "Estão proximos false" << endl;
    return false;
}

