#ifndef JOGADA_H
#define JOGADA_H

#include <Tatica.h>

struct Finaliza{
    string modo;                 ///< Modo que as jogadas irão ser finalizadas.
    map<string, bool> condicoes; ///< Condições para a jogada ser finalizada.
};
/**
 * As jogadas estão associadas aos comandos de alto nivel para as atividades em conjunto realizadas pelos robos
 * A jogada em equipe possui 4 partes.
 *
 * Condições de inicio
 * Condições de termino - Cada posição do vetor terá condições para a jogada ser finalizada.
                          Para a jogada ser finalizada uma ou todas as posições do vetor terão que ser verdadeiras.
 * Papeis a serem dados para cada robo.
 * Condições especiais.
 *
 * no Futuro as jogadas deverão avaliar os oponentes considerados.
 */
class Jogada{

private:
        int id;                             ///< Id da jogada.
        string nome;                        ///< Nome da jogada a ser executada.
        map<string, bool> condAplicavel;    ///< Condições para a jogada ser aplicável.
        vector<Finaliza> condFinaliza;      ///< Condições para a jogada ser finalizada.
        double timeOut;                     ///< Tempo limite para a Jogada terminar.
        vector<string> condRoboAdv;         ///< Condições para selecionar o robô adversário da partida.
        map<string,bool> posCondicoes;      ///< Vetor contendo as condições para serem executadas quanod terminar a jogada
        float peso;                         ///< peso esta associado a probabilidade da jogada ser escolhida em um determinado instante.
        Tatica* taticaGoleiro;              ///< Tática que o goleiro irá executar nessa jogada

        /// Cada Papel será dado para apenas 1 robô, a ordem de execução é na ordem abaixo.
        vector<vector<Tatica*> > papeis;

 public:
        Jogada();

        /**
            Retorna o id da jogada.
            @return unsigned int ID da jogada;
        */
        unsigned int getId();

        /**
            Nesse método iremos setar o id da jogada.
            @param unsigned int id ID da jogada.
        */
        void setId(unsigned int id);

        /**
            Retorna o nome da jogada.
            @return string Nome da jogada.
        */
        string getNome();

        /**
            Setar o nome da Jogada.
            @param string nome Nome da Jogada.
        */
        void setNome(string nome);

        /**
            Retorna as condições para que a jogada seja aplicável.
            @return map<string, bool> Condições para a jogada ser aplicável.
        */
        map<string, bool> getCondAplicavel();

        /**
            Adiciona uma condição para a jogada ser aplicável.
            Para o jogada ser aplicável precisamos que todas as condições sejem verdadeiras.
            @param string condicao É o nome da condição que iremos pegar no arquivo.
            @param bool valor Valor da condição (true ou false).
        */
        void addCondAplicavel(string condicao, bool valor);

        /**
            Retorna as condições para que a jogada seja finalizada.
            @return map<string, map<string, bool> > Condições para a jogada ser finalizada.
        */
        vector<Finaliza> getCondFinaliza();

        /**
            Adiciona as condições para a jogada ser finalizada.
            Cada posicao do vetor terá condições diferentes. A posição do vetor só irá ser verdadeira
            se todas as condições desta posição tiverem valores iguais ao modelo de mundo.
            Se uma ou todas as posições do vetor forem verdadeiras então a jogada será finalizada.
            @param string modo Modo como a jogada será finalizada.
            @param map<string, bool> condicoes Condições para a jogada ser finalizada.
        */
        void addCondFinaliza(string modo, map<string, bool> condicoes);

        /**
            Retorna o tempo limite para a jogada ser finalizada.
            @return double Tempo limite da jogada.
        */
        double getTimeOut();

        /**
            Setar o tempo limite que a jogada deverá ser feita.
            @param double timeOut Tempo limite da Jogada.
        */
        void setTimeOut(double timeOut);

        /** Funcao que retorna o condicao para o robo adversario */
        string getCondRobosAdv(int posRoboAdv);

        /**
            Retorna as condições para selecionar os robôs adversários.
            @return vector<string> Condições dos robôs adversários.
        */
        vector<string> getCondRobosAdv();

        /**
            Adiciona robôs adversários.
            Usamos ele quando queremos usar uma tática em algum robô adversário e temos que saber
            algumas condições para podermos identificar qual robô iremos usar.
            @param int posVetor Posição que iremos inserir a condição no vetor.
            @param string condicao Indica a condição que iremos usar para pegar o robô adversário.
        */
        void addCondRoboAdversario(int posVetor, string condicao);

        /**
            Retorna as táticas do papel da jogada.
            @param int numPapel Indica o papel que queremos pegar.
            @return vector<Tatica*> Táticas do papel.
        */
        vector<Tatica*> getPapel(int numPapel);

        /**
            Adicionar uma tática à um determinado papel (1, 2, 3 ou 4).
            @param int num Indica em qual papel será inserida a tática.
            @param Tatica *tatica Tática é uma ação que o robô irá fazer.
        */
        void addTaticaPapel(int numPapel, Tatica *tatica);

        /**
            Função que retorna as Pós condições que a jogada deseja que sejam executadas
            @return Pós condições para serem executadas
        */
        map<string,bool> getPosCond();

        /**
            Função que seta as Pós condições que a jogada deseja que sejam executadas
            @param posCond Descricao da Condição para ser executada
            @param valor Valor da Condição indicando se deve ser executada ou não
        */
        void addPosCond(string posCond, bool valor);

        /**
            Função que seta a tática que o goleiro irá executar na jogada
            @param _taticaGoleiro Tática que o goleiro irá executar
        */
        void setTaticaGoleiro(Tatica* _taticaGoleiro);

        /**
            Funçao que retorna a tática que o goleiro irá executar na jogada
            @return Tatica que o goleiro irá executar
        */
        Tatica* getTaticaGoleiro();
};
#endif
