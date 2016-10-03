#ifndef TATICA_H
#define TATICA_H

#include <MaquinaSkills.h>
#include <AvaliadorRobo.h>

/**
 * Táticas são comandos em alto nível a serem dados para cada robo.
 * A tatica retorna uma máquina de estados com parâmetros
 * associados para executar seu objetivo. É interessante notar a existencia da flexibilidade ao utilizar táticas.
 * Cada tática pode ter de 0 a n parametros, ela deve especificar o que vai ser feito e não como.
 * A tática pode exigir sincronização para isso, se a próxima tótica for uma do tipo sincronizada,
 * o robô só transita para a próxima se a anterior terminar.
 *
 *
 * Táticas são classes abstratas redefinidas para cada tipo de tática diferente.
 * Toda tática redefinida possui flags que são testadas para verificar seu termino
 *
 * Os vetores que guardam os parâmetros da tática serão preenchidos na sequência em que o arquivo da jogada for lido,
 * se o retorno for int (vetor paramInt), se for float (vetor paramFloat), se for string (vetor paramString).
 *
 */
class Tatica{

protected:
    int posParam;                ///< Essa váriavel irá indicar qual será a posição do vetor dos parametros que iremos ler
    vector<int> paramInt;        ///< Parâmetros inteiros da tática.
    vector<float> paramFloat;    ///< Parâmetros floats da tática.
    vector<string> paramString;  ///< Parâmetros string da tática.
    vector<bool> paramBool;      ///< Parâmetros booleanos da tática.
    vector<Ponto> paramPonto;    ///< Parâmetros pontos da tática.
    AvaliadorRobo avaliadorRobo; ///< Avaliador de aspectos relacionados ao próprio robô

public:
    Tatica();

    virtual ~Tatica() = 0;

    static const int PONTUACAO_LIMITE_CHUTE = 130; /// Pontuação mínima para a tática chute ser executada.

    /**
            Função que retorna o nome da Tática
            @return Nome da Tatica
        */
    virtual string getNome()=0;

    /**
            Nesse método iremos setar o vetor com os pontos da tática.
            @param vector<Ponto> paramPonto Pontos que foram passados como parâmetros do arquivo das jogadas.
        */
    void setParamPonto(const vector<Ponto>& paramPonto);

    /**
            Nesse método iremos retornar os parâmetros do tipo 'Ponto' que foram carregados do arquivo das jogadas.
            @return vector<Ponto> pontos que foram carregados do arquivo.
        */
    vector<Ponto> getParamPonto();

    /**
            Adiciona o valor do parâmetro no vetor dos parâmetros Ponto.
            @param Ponto ponto Atributo que irá guardar as informações de um ponto.
        */
    void addParamPonto(Ponto ponto);

    /**
            Função que seta os parâmetros strings da tática
            @param _paramString Vetor com os parametros do tipo string
        */
    void setParamString(vector<string> _paramString);

    /**
            Nesse método iremos retornar os parâmetros do tipo 'String' que foram carregados do arquivo de jogadas.
            @return vector<string> Vetor com os parâmetros do tipo 'string'
        */
    vector<string> getParamString();

    /**
            Adiciona o valor do parâmetro no vetor dos parâmetros string's.
            @param string param Parâmetro da tática.
        */
    void addParamString(string param);

    /**
            Função que seta os parametros do tipo inteiros da tática
            @param _paramInt Parametros do tipo inteiro
        */
    void setParamInt(vector<int> _paramInt);

    /**
            Nesse método iremos retornar os parâmetros do tipo 'int' que foram carregados do arquivo de jogadas.
            @return vector<int> Vetor dos parâmetros inteiros
        */
    vector<int> getParamInt();

    /**
            Adiciona o valor do parâmetro no vetor dos parâmetros inteiros.
            @param int param Parâmetro da tática.
        */
    void addParamInt(int param);

    /**
            Função que seta os parametros do tipo float da tática
            @param _paramFloat Parametros do tipo float
        */
    void setParamFloat(vector<float> _paramFloat);

    /**
            Nesse método iremos retornar os parâmetros do tipo 'float' que foram carregados do arquivo de jogadas.
            @return vector<float> Vetor dos parâmetros floats
        */
    vector<float> getParamFloat();

    /**
            Adiciona o valor do parâmetro no vetor dos parâmetros floats.
            @param float param Parâmetro da tática.
        */
    void addParamFloat(float param);

    /**
            Nesse método iremos retornar os parâmetros do tipo 'bool' que foram carregados do arquivo de jogadas.
            @return vector<bool> Vetor dos parâmetros booleanos
        */
    vector<bool> getParamBool();

    void setParamBool(vector<bool> _paramBool);

    /**
            Adiciona o valor do parâmetro no vetor dos parâmetros booleanos.
            @param bool param Parâmetor booleano lido do arquivo.
        */
    void addParamBool(bool param);

    /**
            Método que executa a tática.
            @param int id É o identificador do robô a executar a tática.
            @param AvaliadorRobo* avaliadorRobo Iremos usar essa variável para analisar a situação do robô com o modelo de mundo.
            @return MaquinaSkills* Retorna a maquina de skills que irá ser usada para executar essa tática.
        */
    virtual void executar(Agente* agente) = 0;

    /**
            Verifica o término da tática, é feita juntamente com o módulo executor.
            @param int id É o identificador do robô a executar a tática.
            @return bool Retorna se foi terminada ou não.
        */
    virtual bool verificarTermino(int id) = 0;

    /**
            Funcao que retorna um score utilizado para avaliar o melhor robo para fazer
            esta jogada.
        */
    virtual float avaliacaoEscolhaRobo(int id) = 0;

    /**
            Nesse método iremos analisar qual o melhor robô que se aplica a essa tática, de acordo com o modelo de mundo.
            @param vector<int>& _ids Vetor com os ids dos robôs que estão sem táticas.
            @return int Id do melhor robô para a tática.
        */
    virtual int getIdMelhorRobo(vector<int>& _ids) = 0;

    /**
            Método que responde se a tática em questão está ativa.
            @return bool Retorna se a tática é ativa ou não.
        */
    virtual bool isAtiva() = 0;

    /**
            Nesse método iremos criar uma nova instancia da tática usada no momento.
            @return Tatica* retorna a nova instancia da tática.
        */
    virtual Tatica* getNovaInstancia() = 0;

    /**
            Função para debug que imprime o nome de cada tática.
        */
    virtual void imprimirNome() = 0;

    virtual float getLimiarAvaliacao() = 0;

    friend class Carregador;
};
#endif
