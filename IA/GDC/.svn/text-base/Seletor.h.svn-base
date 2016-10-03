#ifndef SELETOR_H
#define SELETOR_H

#include <Jogada.h>
#include <ConfigTeste.h>

/**
 * Avalia qual jogada vai ser aplicada em um dado momento.
 * Este módulo também guarda como foram completadas as jogadas no passado para escolher a mais adequada para o momento.
 */
class Seletor{

private:
        bool ehteste;
        Jogada* jogadaSelecionada; ///< Atributo que armazena a posição do vetor jogadas que indica a jogada escolhida.
        vector<Jogada>* jogadas;        ///< Vetor que armazena as jogadas que iremos usar na partida.

        /// Os vetores abaixo indicam quantas vezes a jogada teve uma dessas consequencias.
        vector<int> sucedida;
        vector<int> completada;
        vector<int> fracassada; ///< @todo ISSO VAI SAIR
        vector<int> abortada;
 
public:
        Seletor();

        void setJogadas(vector<Jogada>* _jogadas);

        /** este metodo de acesso retorna a primeira jogada do vetor
            ele é usado no modo teste retornando a unica jogada escolhida evitando calculos.
        */
        Jogada* getJogadaTeste(string nomeJogada);

        /** este metodo de acesso retorna a primeira jogada do vetor
            ele é usado no modo teste retornando a unica jogada escolhida evitando calculos.
        */
        Jogada* getJogadaTeste();
        /**
            Aqui são atualizados os pesos de cada jogada
            @todo especificar a formula do artigo aqui.
        */
        void atualizarPesos();

        /**
            Nesse método iremos selecionar a melhor jogada de acordo com as condições para a jogada ser aplicavel.
            @return Jogada que foi selecionada.
        */
        Jogada* selecionar(string nomeJogada);

        /**
            Nesse método iremos selecionar a melhor jogada de acordo com as condições para a jogada ser aplicavel.
            @return Jogada que foi selecionada.
        */
        Jogada* selecionar();

        /**
            Nesse método pegaremos os papéis da jogada selecionada e atribuir aos robôs.
            @vector<vector<Tatica*> > cada posição do vetor indica o robô que contém as táticas associadas a ele.
        */
        map<int, vector<Tatica*> > atribuirPapeis();
};
#endif
