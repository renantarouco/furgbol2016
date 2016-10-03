#include "GerenteDeliberativoCentral.h"
#include <Sistema.h>

GerenteDC::GerenteDC(){
    estado = SELECAO;
    numRobosPresentesAnt=0;
    jogadaSelecionada = NULL;
}

GerenteDC::~GerenteDC(){
}

void GerenteDC::init(){
    cout << "INICIANDO GDC" << endl;

    /// fazendo o carregamento das jogadas
    carregarJogadas();
}

void GerenteDC::carregarJogadas(){

    /// verificando se estamos no modo de teste ou é jogo normal
    if(!carregador.pegarNomeArquivosJogadas(Config::PATH_PLAYBOOK)){
        cout << "Nao foi possivel pegar o nome dos arquivos das jogadas" << endl;
        return;
    }

    /// setando o nome das jogadas escolhidas
    carregador.setNomeJogadasEscolhidas(carregador.getNomeArquivosJogadas());

    /// carregando as jogadas que estão dentro da pasta PLAYBOOK
    carregador.carregarJogadasEscolhidas();

    /// Verificando se foi completada o carregamento das jogadas
    if(carregador.isCarregamentoSemErro()){
        cout << "JOGADAS CARREGADAS" << endl;

        /// pegando a referencia das jogadas e inserindo nas outra variáveis que irão manter a referência
        jogadas = carregador.getJogadas();
        seletor.setJogadas(jogadas);

    }else{
        jogadas = new vector<Jogada>;
        cout << "Nao foi possivel carregar os arquivos das jogadas. Jogadas com erro" << endl;
    }
}

string GerenteDC::getNomeJogadaAtual(){
    if(jogadaSelecionada != NULL)
        return jogadaSelecionada->getNome();

    return "";
}

unsigned short GerenteDC::getEstado(){
    return estado;
}

void GerenteDC::setEstado(GerenteDC::Estado _estado){
    estado = _estado;
}

void GerenteDC::setJogadas(vector<Jogada> *jogadas){
    this->jogadas = jogadas;
}

vector<Jogada>* GerenteDC::getJogadas(){
    return jogadas;
}

map<int, vector<Tatica*> >  GerenteDC::getVetorPapeis(){
    return papeis;
}

bool GerenteDC::selecaoOn(){
    if (estado == SELECAO) return true;
    return false;
}

bool GerenteDC::isExecucaoOn(){
    if (estado == EXECUCAO) return true;
    return false;
}

bool GerenteDC::trocarPapeisOn()
{
    return estado == TROCAR_PAPEIS;
}

void GerenteDC::mudarSinalPontosJogadas(){

    /// Verificando cada jogada
    foreach(Jogada jogada, *jogadas){

        /// Verificando as táticas de cada papel
        for(int i = 0; i < NUM_MAX_ROBOS_JOGANDO-1; i++){
            vector<Tatica*> taticas = jogada.getPapel(i);

            /// Analisando em cada tática se ela tem parâmetros do tipo ponto, se tiver então iremos alterar o sinal do ponto.
            foreach(Tatica *tatica, taticas){

                if(tatica == NULL){
                    cout << "Tatica vazia" << endl;
                    abort();
                }

                /// Verificando se a tática possue algum parametro do tipo ponto
                if(!tatica->getParamPonto().empty()){
                    vector<Ponto> pontos = tatica->getParamPonto();

                    /// Pegando todos os pontos da tática
                    for(unsigned int i = 0; i < pontos.size(); i++)
                        pontos[i] = Ponto(pontos[i].x()*-1, pontos[i].y()); /// Alterando o sinal do ponto

                    tatica->setParamPonto(pontos); /// Setando na tática os pontos novos.
                }
            }
        }
    }

    Sistema::modeloMundo.setMudarSinalPontosJogadas(false); /// Setando que não iremos mudar o sinal das jogadas
}

map<int, vector<Tatica*> > GerenteDC::atribuirPapeis(){
    cout << "atribuindo papeis" << endl;

    papeis = seletor.atribuirPapeis(); /// Atribuindo novamente os papeis aos robos
    return papeis;
}

map<int, vector<Tatica*> > GerenteDC::selecionarJogada(){

    /// Verificando se estamos em modo de teste, caso estejamos iremos pegar a única jogada que foi carregada
    if(Config::MODO_TESTE){

        cout << "selecionando jogada teste...." << endl;
        jogadaSelecionada = seletor.selecionar(Config::JOGADA_TESTE); /// Selecionando a melhor jogada a ser aplicável.
    }else{

        cout << "selecionando jogada...." << endl;
        jogadaSelecionada = seletor.selecionar(); /// Selecionando a melhor jogada a ser aplicável.
    }

    cout << "Nova Jogada escolhida: " << jogadaSelecionada->getNome() << endl;

    executor.setJogada(jogadaSelecionada); /// Setando a jogada que foi escolhida

    papeis = seletor.atribuirPapeis(); /// Pegando os papeis dos agentes

    cout << "papeis atribuidos....." << endl;

    estado = EXECUCAO; /// Setando o estado do GDC como de execução

    return papeis;
}

void GerenteDC::analisarJogada(){

    /** Verificando se a jogada foi finalizada */
    if(executor.isJogadaFinalizada())
    {
        //        executor->executarPosCondDaJogada(); /// Executando as pos condições das jogadas
        estado = SELECAO;

        //        /** Verificando se algum robô tocou na bola para podermos setar que o robô ativo pode tocar na bola */
        //    }else if(executor->isAlgumRoboTocouBola()){

        //        /// Caso o robo nao pudesse tocar na bola agora ele pode
        //        int idRoboAtivo = Sistema::modeloMundo.getIdRoboAtivo();
        //        Robo* robo = Sistema::modeloMundo.getRoboEq(idRoboAtivo);
        //        if(!robo->isTocarBola()){
        //            robo->setTocarBola(true);
        //        }

        /** Verificando se iremos analisar os papeis da jogada */
    }else{

        /// Verificando se a quantidade de robos esta alterado, se estiver teremos que reposicionar os papeis
        int numRobosPresentesAtual = Sistema::modeloMundo.getQtRobosEqPresentes();
        if(numRobosPresentesAnt != numRobosPresentesAtual){
            numRobosPresentesAnt = numRobosPresentesAtual;
            estado = SELECAO;
        }

    }

    /// @todo implementar função para verificar se precisar trocar as táticas entre os robos
    /*else if(analisarPapeis)
    {*/
    //        papeis = seletor->atribuirPapeis();

    //        /** Analisando se os papeis de cada robô realmente são os ideais para os robos atuais */
    //        vector<Tatica*> taticasCorrentes; /// Vetor com as táticas correntes de cada papel
    //        vector<int> idsRobosPresentes; /// Vetor com os ids dos robôs que estão presentes no campo;
    //        BOOST_FOREACH(Robo* robo, Sistema::modeloMundo.getRobosEq())
    //        {

    //            /// Verificando se o robô do agente está presente
    //            if(robo->isPresente())
    //            {
    //                taticasCorrentes.push_back(robo->getTaticaCorrente());
    //                posAgentesPapeis.push_back(agentes->at(robo->getId()).getPosicao());
    //                idsRobosPresentes.push_back(robo->getId());
    //            }
    //        }

    //        /// Verificando qual a melhor tática para cada robô atualmente
    //        vector<Tatica*> melhoresTaticas(taticasCorrentes.size());
    //        for(unsigned int i = 0; i < taticasCorrentes.size(); i++)
    //        {
    //            melhoresTaticas[i] = papeis[idsRobosPresentes[i]][0];
    //        }

    //        /// caso tenha que ser mudados vai ser colocados nos papeis
    //        if(executor->verificarPapeis(papeis, posAgentesPapeis, taticasCorrentes, melhoresTaticas, idsRobosPresentes))
    //        {
    //            estado = TROCAR_PAPEIS;
    //        }
    //    }
}
