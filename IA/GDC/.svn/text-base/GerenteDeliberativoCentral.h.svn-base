#ifndef GERENTE_DELIBERATIVO_CENTRAL_H
#define GERENTE_DELIBERATIVO_CENTRAL_H

#include "Carregador.h"
#include "Executor.h"
#include "Seletor.h"

/**
 * Módulo princiapal da IA , é ele que controla em alto nivel o desenvolvimento da partida.
 * Dependendo da situação do jogo ele transita entre 3 estados.
 *
 * Dividido em 3 estados: Carregador, Seletor , e Executor(THREAD)
 */
class GerenteDC{
public:
    enum Estado{
        SELECAO = 0,
        EXECUCAO = 1,
        TROCAR_PAPEIS =2
    };

private:
    vector<Jogada>* jogadas; ///< Vetor com as jogadas que foram carregadas
    map<int, vector<Tatica*> > papeis; ///< Vetor com os papeis de cada agente
    Estado estado; ///< Estado que está sendo executado no momento (SELETOR, EXECUTOR)
    Seletor seletor; ///< Seletor usada para selecionar a melhor jogada no momento e atribuir os papeis a cada robo
    Executor executor; ///< Executor usado para executar as condições da jogada e acompanhar a execução da jogada
    Carregador carregador; ///< objeto que faz o carregamento das jogadas a partir dos arquivos .adj

//    pthread_t threadExecutor; ///< Thread usada para executar o Executor
    int numRobosPresentesAnt;

    Jogada* jogadaSelecionada; ///< jogada que foi selecionada para ser executada

public:
    GerenteDC();
    ~GerenteDC();

    void init();

    void carregarJogadas();

    /**
        Função que retorna o nome da Jogada que está sendo executada
        @return Nome da Jogada que está sendo executada
    */
    string getNomeJogadaAtual();

    /**
        Função que seta o estado que o GDC irá executar
        @param _estado Estado que o GDC irá executar
    */
    void setEstado(GerenteDC::Estado _estado);

    /**
        Função que retorna o id do Estado que está executando no momento no GDC
        @return Estado que está executando o GDC
    */
    unsigned short getEstado();

    /**
        Nesse método iremos setar as jogadas que iremos usar na partida.
        @param vector<Jogada>* jogadas Jogadas que iremos usar na partida.
    */
    void setJogadas(vector<Jogada>* jogadas);

    /**
        Nesse método iremos retornar o vetor que contém as jogadas carregadas.
        @return vector<Jogada>* Vetor que contém as jogadas carregadas.
    */
    vector<Jogada>* getJogadas();

    /**
        Função que retorna um vetor dos papeis que da jogada
        @return Vetor de agentes com seus papeis respectivos
    */
    map<int, vector<Tatica*> > getVetorPapeis();

    /**
        Funçao que retorna se o estado de Seleção está sendo executado ou não
        @return True se estiver sendo executado, false senão estiver
    */
    bool selecaoOn();

    /**
        Funçao que retorna se o estado de Execução está sendo executado ou não
        @return True se estiver sendo executado, false senão estiver
    */
    bool isExecucaoOn();

    bool trocarPapeisOn();

    /**
        Nesse método iremos alterar o sinal dos pontos em algumas jogadas, mas só iremos mudar o sinal quando mudar o lado do campo.
    */
    void mudarSinalPontosJogadas();


    map<int, vector<Tatica*> > atribuirPapeis();

    /**
        Função que seleciona a melhor jogada para o momento se utilizando dos fatos e das condições
        para a jogada ser executada.
        @return Vetor de agentes com seus papeis respectivos
    */
    map<int, vector<Tatica*> > selecionarJogada();

    /**
        Função que monitora toda a execução da jogada, analisa se foi finaliza e se os papeis estão distribuidos corretamente
    */
    void analisarJogada();
};
#endif
