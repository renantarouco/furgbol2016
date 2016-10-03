#include "Executor.h"
#include<Sistema.h>

Executor::Executor(){
    cout << "INICIANDO EXECUTOR" << endl;
    ativo = true;
    jogadaSelecionada = NULL;
}

Executor::~Executor(){
}

void Executor::setJogada(Jogada* _jogadaEscolhida){
    jogadaSelecionada = _jogadaEscolhida;
}

Jogada* Executor::getJogadaEscolhida() {
    return jogadaSelecionada;
}

string Executor::getNomeJogada() {
    return jogadaSelecionada->getNome();
}

void Executor::setAtividade(bool _ativo){
    ativo=_ativo;
}

bool Executor::isAtivo(){
    return ativo;
}

bool Executor::isJogadaFinalizada(){

    if(jogadaSelecionada != NULL){

    /// Pegando as condições para a jogada ser finalizada
    vector<Finaliza> condsTermino = jogadaSelecionada->getCondFinaliza();
    map<string, bool>::iterator fatoJogada;
    map<string, bool>* fatos = Sistema::modeloMundo.getFatos();

    /// Analisando cada condição de término da jogada
    for(unsigned int i = 0; i < condsTermino.size();i++)
    {
        unsigned int qtFatosAplicaveis = 0; /// Indica quantos fatos do conjunto de condições estão sendo aplicáveis

        /// Analisando cada fato que a jogada precisa para ser finaliza, verificando os conjuntos de fatos separados
        for(map<string, bool>::iterator it = condsTermino[i].condicoes.begin(); it != condsTermino[i].condicoes.end(); it++)
        {

            /// Pegando a fato da jogada com o identificador correspodente
            fatoJogada = fatos->find((*it).first);

            if(fatoJogada == fatos->end())
            {
                cout << "O Fato que foi procurado nao existe no Modelo de Mundo. ATUALIZAR" << endl;

                /** Verificando se o fato da jogada possue o mesmo valor que o valor que está no modelo de mundo
                se possuir então iremos incrementar o valor da quantidade de fatos aplicaveis, se todos os
                fatos desse conjunto de condições forem aplicaveis, então a condição será finalizada */
            }else if(fatoJogada->second == (*it).second)
            {
                qtFatosAplicaveis++;
            }
        }

        /// Verificando se a quantidade de fatos aplicaveis é igual ao total de fatos do cojunto de fatos das condições
        /// se for então isso indica que a jogada possuem condições para ser finalizada
        if(qtFatosAplicaveis == condsTermino[i].condicoes.size())
        {
            return true;
        }
    }
    }

    return false;
}

bool Executor::isAlgumRoboTocouBola() {

    /// Verificando se algum robô tocou na bola
    if(Sistema::avaliador.roboAdvTocouBola()){
        return true; /// Setando que algum robo tocou na bola

    }else if(Sistema::avaliador.roboEqTocouBola()){
        int idRoboTocouBola = Sistema::avaliador.getIdDistRoboEqMaisPertoBola().first; /// Id do robô da equipe mais perto da bola
        int idRoboAtivo = Sistema::modeloMundo.getIdRoboAtivo(); /// Pegando o id do robô ativo

        /// Verificando se o id do robô que tocou na bola
        if(idRoboTocouBola != idRoboAtivo){
            return true;
        }
    }

    return false;
}

void Executor::executarPosCondDaJogada(){

    /// Pegando as pos condições da jogada que foi executada para adicionarmos agora
    map<string, bool> posCondJogada = jogadaSelecionada->getPosCond();

    /// Pegando as pos condições
    for(map<string, bool>::iterator it = posCondJogada.begin(); it != posCondJogada.end(); it++){

        /// Verificando se iremos setar o robô ativo para não tocar na bolas
        if((*it).first == "robo_ativo_nao_tocar_bola"){

            /// Pegando o id do robo ativo
            int idRoboAtivo = Sistema::modeloMundo.getIdRoboAtivo();

            /// Verificando se o id não é o id do goleiro e se é diferente de -1
            if(idRoboAtivo > 0){
                Sistema::modeloMundo.getRoboEq(idRoboAtivo)->setTocarBola(false); /// Setando que o robô ativo não irá tocar na bola
            }else{
                cout << "Robô ativo possui ID inválido" << endl;
            }

            /// Pegando a quantidade de robos que estão presentes na partida
            int quantRobosPresentesEq = Sistema::modeloMundo.getQtRobosEqPresentes();

            /// Setando que os outros robos da equipe podem tocar na bola
            for(int i = 0; i < quantRobosPresentesEq; i++){

                /// Analisando se o id do robo ativo é diferente do id atual do robo
                if(idRoboAtivo != i)
                    Sistema::modeloMundo.getRoboEq(i)->setTocarBola(true);
            }

            break;
        }
    }
}

//bool Executor::verificarPapeis(vector<vector<Tatica*> >& papeis, vector<int>& posicoesFila, const vector<Tatica*>& taticasCorrentes,
//                               const vector<Tatica*>& melhoresTaticas, const vector<int>& idRobosPresentes){
////    bool trocouPapel = false;

//    /// Analisando as táticas que estão sendo executadas no momento
//    for(unsigned int i = 0; i < taticasCorrentes.size(); i++){

//        Tatica* tatica = taticasCorrentes[i];

//        /// se a tatica corrente foi atribuida a um robo diferente
//        /// Por enquanto apenas se a tatica for ativa.
//        if(tatica->isAtiva()){

//            if(tatica->getNome().find(melhoresTaticas[i]->getNome()) != string::npos){

//                cout << "Nome da tatica ativa " << tatica->getNome() << endl;

//                /// analisa a diferenca entre o robo ideal e o com a tatica
//                int idMelhorRobo = getPosicaoDaTatica(melhoresTaticas, tatica);
//                cout << "Id do melhor robo: " << idMelhorRobo << endl;

//                if(Sistema::modeloMundo.getRoboEq(idMelhorRobo)->isPresente()){

//                    cout << "Id do robo atual: " << idRobosPresentes[i] << endl;

//                    Tatica* tatica = taticasCorrentes[i];
//                    float limiar = tatica->getLimiarAvaliacao();
//                    float valorMelhorRobo = tatica->avaliacaoEscolhaRobo(idMelhorRobo);
//                    float valorRoboAtual = tatica->avaliacaoEscolhaRobo(idRobosPresentes[i]);
//                    float diff = valorMelhorRobo - valorRoboAtual;

//                    cout << "Diferenca " << diff << endl;
//                    cout << "Limiar " << limiar << endl;

//                    //cout << "*********** diferença entre os robos *************" << endl << diferenca << endl;
//                    if(diff > limiar){

//                        int auxPosicao = posicoesFila[idMelhorRobo];
//                        vector<Tatica*> aux = papeis[idMelhorRobo];

//                        /// Trocando o papel do melhor robo com o robo atual da tatica
//                        posicoesFila[idMelhorRobo] = posicoesFila[idRobosPresentes[i]];
//                        papeis[idMelhorRobo] = papeis[idRobosPresentes[i]];

//                        /// Atualizando a tatica ativa para o melhor robo
//                        posicoesFila[idRobosPresentes[i]] = auxPosicao;
//                        papeis[idRobosPresentes[i]] = aux;

//                        return true;
//                    }
//                }
//            }
//        }
//    }

//    return false;
//}

//int Executor::getPosicaoDaTatica(vector<Tatica*> melhoresTaticas, Tatica* taticaCorrente){

//    for(unsigned int i = 0; i < melhoresTaticas.size(); i++){
//        if(taticaCorrente->getNome().find(melhoresTaticas[i]->getNome()) != string::npos)
//            return i;
//    }

//    return -1;
//}

//int Executor::analisarDiffEntreTaticas(int idMelhorRobo, int idRoboAtual, Tatica *taticaCorrente){
//    /// Este numero nunca deve ser negativo
//    return taticaCorrente->avaliacaoEscolhaRobo(idMelhorRobo) - taticaCorrente->avaliacaoEscolhaRobo(idRoboAtual);
//}
