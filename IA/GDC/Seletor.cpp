#include "Seletor.h"
#include <Sistema.h>
#include <DefendeGol.h>

Seletor::Seletor(){
    cout << "INICIANDO SELETOR" << endl;
    jogadaSelecionada = NULL;
    ehteste=false;
}

void Seletor::setJogadas(vector<Jogada>* _jogadas){
    jogadas = _jogadas;
}

map<int, vector<Tatica*> > Seletor::atribuirPapeis(){

    /// map que irá conter o id do robo como chave e o vetor de táticas que o robo irá executar
    map<int, vector<Tatica*> > papeisRobos;

    /// setando o vetor de táticas do goleiro
    int idGoleiro = Sistema::modeloMundo.getIdGoleiro();
    papeisRobos[idGoleiro] = vector<Tatica*>(1, jogadaSelecionada->getTaticaGoleiro());

    /// Pegando os ids dos robôs presentes sem o goleiro
    vector<int>* idRobosMenosGoleiro = Sistema::modeloMundo.getIdRobosMenosGoleiro();

    /// removendo o goleiro da analise pegando os 5 robos restantes
    for(int i = 0; i < NUM_MAX_ROBOS_JOGANDO-1; i++)
    {
        /// Pegando o papel a ser atribuido a algum robô
        vector<Tatica*> papel = jogadaSelecionada->getPapel(i);

        /// Pegando o id do melhor robô para a primeira tática do papel.
        int idRobo = papel[0]->getIdMelhorRobo(*idRobosMenosGoleiro);

        //        cout << idRobo << " " << papel[0]->getNome() << endl;

        //        cout << "Tatica " << papel[0]->getNome() << " - robo id: " << idRobo << endl;

        //        cout << "Nome da tatica " << papel[0]->getNome() << endl;

        //        /// Verificando se a tática do papel for a ativa e se o robô não pode tocar na bola,
        //        /// iremos escolher um outro robo e pular a vez desse robo
        //        if(papel[0]->isAtiva() && !Sistema::modeloMundo.getRoboEq(idRobo)->isTocarBola() && jogoNormal){

        //            idRobosPresentes.erase(idRobosPresentes.begin() + idRobo); /// Removendo o robo do vetor de ids
        //            int idRoboAnt = idRobo; /// Setando em um variavel auxiliar para não perder o valor do id do robo

        //            /// Escolhendo outro id do vetor para o papel correspondente
        //            idRobo = papel[0]->getIdMelhorRobo(idRobosPresentes);

        //            /// Setando o id novamente no vetor para ser usado posteriormente
        //            idRobosPresentes.push_back(idRoboAnt);
        //        }

        /// Atribuindo ao robôs o papel correspondente.
        papeisRobos[idRobo] = papel;
    }

    //    int idRoboAtivo = Sistema::modeloMundo.getIdRoboAtivo(); /// Pegando o id do robo ativo

    //    /// Setando que os outros robos que não possuem a tática ativa não poderão tocar na bola
    //    for(int i = 1; i < quantIdsRobosPresentes; i++){

    //        /// Verificando se o id do robô ativo é diferente do robô atual
    //        if(idRoboAtivo != i)
    //            Sistema::modeloMundo.getRoboEq(i)->setTocarBola(false);
    //    }

    return papeisRobos;
}


Jogada* Seletor::selecionar(string nomeJogada){

    /// Procurando a jogada que possue esse nome
    for(int i=0;i<jogadas->size();i++){
        Jogada* jogada = &jogadas->at(i);

        /// verificando se os nomes são iguais
        if(jogada->getNome() == nomeJogada){
            jogadaSelecionada = jogada;
            return jogadaSelecionada;
        }
    }

    cout << "Não existe jogada com este nome: "<< nomeJogada << endl;
    jogadaSelecionada = NULL;
    return NULL;
}

Jogada* Seletor::selecionar(){

    vector<Jogada*> jogadasSelecionadas; /// Variável que iremos guardar a jogada selecionada.

    /// Pegando o map com os fatos do modelo de mundo para analisarmos com as condições da jogada.
    map<string, bool>* fatos = Sistema::modeloMundo.getFatos();

    /// **** Filtrando as jogadas que podem ser aplicáveis com base apenas nos fatos do modelo de mundo. ****
    for(int i=0;i<jogadas->size();i++){
        Jogada* jogada = &jogadas->at(i);

        map<string, bool> condAplicavel = jogada->getCondAplicavel(); /// Pegando as condições para a jogada ser aplicável
        map<string, bool>::iterator it;                              /// Iterator para percorrer o map das condições
        bool aplicavel = true;                                       /// Variável que irá guardar o valor se a jogada pode ser aplicavel ou não.

        /// Percorrendo o map das condições.
        /// Para a jogada ser aplicável todas as condições precisam ter valores iguais ao modelo de mundo.
        for(it = condAplicavel.begin(); it != condAplicavel.end(); it++){

            bool valor = fatos->at((*it).first); /// Pegando o primeiro valor do it que indica o fato do modelo de mundo que temos que comparar os valores.

            /// Quando o valor do modelo de mundo não for igual ao valor da condição para a jogada ser aplicável, então a jogada não pode ser usada nessa situação.
            if((*it).second != valor){
                aplicavel = false;
                break;
            }
        }

        /// Se a variável aplicavel for true, é porque a jogada pode ser aplicável a essa situação, senão não poderá ser usada nessa situação.
        if(aplicavel)
            jogadasSelecionadas.push_back(jogada);
    }

    /// Se o número de jogadas escolhidas for maior que 1, iremos selecionar a jogada aleatoriamente, caso contrário iremos pegar a única jogada
    if(jogadasSelecionadas.size() > 1){
        jogadaSelecionada = jogadasSelecionadas[rand() % jogadasSelecionadas.size()];

    }else if(jogadasSelecionadas.size() == 1){
        jogadaSelecionada = jogadasSelecionadas[0];

    }else{

        cout << "ATENÇÃO: NÃO TEMOS JOGADAS PARA ESSES TIPOS DE FATOS ABAIXO." << endl << endl;
        map<string, bool>::iterator it;

        /// Imprimindo os fatos do modelo de mundo para poder identificar que tipo de jogada temos que construir para concertar esse problema.
        for(it = fatos->begin(); it != fatos->end(); it++){
            cout << "Fato: "<< (*it).first << " = " << (*it).second << endl;
        }

        cout << "Selecionando a jogada de STOP padrão para ser executada, para que os robos não fiquem parados no campo quando não tiver jogada selecionavel" << endl;
        for(int i = 0;i<jogadas->size();i++){
            Jogada* jogada = &jogadas->at(i);

            if(jogada->getNome() == "Stop"){
                jogadaSelecionada = jogada;
            }
        }
    }

    return jogadaSelecionada;
} 

Jogada* Seletor::getJogadaTeste(string nomeJogada){

    /// Procurando a jogada que possue esse nome
    BOOST_FOREACH(Jogada jogada, *jogadas){
        if(jogada.getNome().find(nomeJogada) != string::npos){
            jogadaSelecionada = &jogada;
            break;
        }
    }

    return jogadaSelecionada;
}

Jogada* Seletor::getJogadaTeste(){
    jogadaSelecionada = &jogadas->at(0);
    return jogadaSelecionada;
}
