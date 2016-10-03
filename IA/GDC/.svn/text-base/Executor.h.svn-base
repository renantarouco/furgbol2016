#ifndef EXECUTOR_H
#define EXECUTOR_H

#include<Jogada.h>

/**
 * Este modulo acompanha as condições de termino das jogadas.
 * Ele deve ser responsavel por sincronizar as taticas em grupo.
 * Caso uma tatica em grupo demore o robo deve calcular uma tatica alternativa.
 */
class Executor
{
private:
    Jogada* jogadaSelecionada; ///< Jogada que foi escolhida para ser executada
    double tempoDecorrido; ///< Tempo que a jogada levou para ser executada
    bool ativo; ///< Indica se o Executor está ativo (sendo executado)
    int roboAtivo; ///< Indica o id do Robô ativo que possue a Tática Ativ

public:
    Executor();
    ~Executor();

    /**
        Função que seta a Jogada que foi escolhida para ser executada
        @param _jogadaEscolhida Jogada escolhida para ser executada
    */
    void setJogada(Jogada* _jogadaEscolhida);

    /**
        Função que retorna a Jogada que foi escolhida para ser executada
        @return Jogada que foi escolhida para ser executada
    */
    Jogada* getJogadaEscolhida();

    /**
        Função que retorna o Nome da Jogada que está sendo executada
        @return Nome da Jogada que está sendo executada
    */
    string getNomeJogada();

    /**
        Função que seta se o Executor está ativado ou não
        @param _ativo Indica se o Executor está ativo ou não
    */
    void setAtividade(bool _ativo);

    /**
        Função que retorna se o Executor está ativo ou não
        @return True se o Executor estiver ativo, false senão estiver
    */
    bool isAtivo();

    /**
        Função chamada para verificar se a joga já acabou,
        Está função deve ser chamada na parte sequencial pela furgbolMain.
        @return True se a jogada tiver sido finalizada, false senão tiver
    */
    bool isJogadaFinalizada();

    /**
        Nesse método iremos verificar se algum robo tocou na bola.
        @return True se tiver tocado, false senão tiver tocado
    */
    bool isAlgumRoboTocouBola();

    /**
        Função que executa as pós condições da Jogada após ela ter sido finalizada
    */
    void executarPosCondDaJogada();

    /**
        Dados dois vetores de taticas verifica se existe alguma diferenca entre eles.
        Se existir analisa qual o grau de mudança entre as taticas se for significativo preenche
        o vetor de papeis com as posicoes alteradas.
        Restricão , no momento apenas a tatica ativa pode ser trocada.
        @todo Refazer essa função de verificar os papeis, analisar como será a comparação dos melhores robôs para cada tática
    */
//    bool verificarPapeis(vector< vector<Tatica*> >& papeis,vector<int>& posicoesFila, const  vector<Tatica*>& taticasCorrentes, const vector<Tatica*>& melhoresTaticas,const vector<int>& idsAgentes);

//    int getPosicaoDaTatica(vector<Tatica*> melhoresTaticas, Tatica* taticaCorrente);

//    int analisarDiffEntreTaticas(int idMelhorRobo,int idRoboAtual, Tatica* taticaCorrente);
};
#endif
