#ifndef CARREGADOR_H
#define CARREGADOR_H

#include <Jogada.h>

/**
    Essa classe é responsável por fazer o carregamento dos arquivos .adj (Jogadas) e também por carregar constantes setadas na interface.
    Nela iremos carregar os arquivos, analisar quais arquivos estão com erro (se houver), identificar aonde está o erro, etc.
*/

class Carregador
{
private:
    vector<Jogada>* jogadas;    ///< Jogadas que iremos carregar.
    vector<Tatica*> taticas;    ///< Variável que irá armazenar todas as táticas que podemos usar.
    string logJogadasComErros;  ///< Vetor que irá armazenar as jogadas e os erros que tiverem quando forem ser carregadas.
    string nomeJogada;          ///< Nome da jogada que está sendo carregada em um instante.
    vector<string> nomeArquivosJogadas; ///< Vetor com o nome dos arquivos que contém as jogadas que serão carregadas
    vector<string> nomeJogadasEscolhidas; ///< Vetor com o nome das jogadas que o Usuário selecionou para serem usadas
    string nomeUltArqConstantesUsado; ///< Nome do último arquivo de constantes que foi usado
    string pathPastaJogadas;

    /**
        Nesse método iremos ler o arquivo da jogada, pegar as informação e setar as informações na jogada.
        Depois iremos retornar o ponteiro da jogada.
        @param Jogada &jogada Atributo que guardará as informações da jogada.
        @param string pathArquivo PathArquivo é o caminho do arquivo (pathPasta + nomeArquivo).
        @param unsigned int idJogada Id da jogada que queremos carregar.
        @return bool Retorna true se deu certo carregar a jogada, e retorna false senão deu certo carregar.
    */
    bool carregarJogada(Jogada &jogada, string pathArquivo, unsigned int idJogada);

    /**
        Nesse método iremos ler a condições para a jogada ser 'APLICAVEL'.
        Iremos pegar cada valor do arquivo e iremos verificar seus valores, se o primeiro caractere da condicao
        for '!' então o valor da condição será false, se não tiver o sinal então será true.
        @param fstream &arq Arquivo que iremos ler as condições para a jogada ser aplicavel.
        @param Jogada &jogada Atributo que irá guardar as informações da jogada lida do arquivo.
        @return bool Retorna true se deu certo carregar as condições, e retorna false quando não der certo.
    */
    bool lerCondAplicavel(fstream &arq, Jogada &jogada);

    /**
        Nesse método iremos ler a condições para a jogada ser 'FINALIZADA'.
        Iremos pegar cada valor do arquivo e iremos verificar seus valores, se o primeiro caractere da condicao
        for '!' então o valor da condição será false, se não tiver o sinal então será true.
        Iremos identificar o caractere '||', indica que temos que colocar essas condições na posição adiante do vetor de condFinaliza
        @param fstream &arq Arquivo que iremos ler as condições para a jogada ser aplicavel.
        @param Jogada &jogada Atributo que irá guardar as informações da jogada lida do arquivo.
        @return bool Retorna true se deu certo carregar as condições, e retorna false quando não der certo.
    */
    bool lerCondFinaliza(fstream &arq, Jogada &jogada);

    /**
        Nesse método iremos pegar alguma informação se existir a respeito de algum robô adversário, para usarmos na jogada.
        @param fstream &arq Arquivo que contém as informações da jogada.
        @param Jogada &jogada Váriavel que armazena as informações da jogada.
        @return bool Retorna true se deu certo carregar as informações dos robôs adversários, e retorna false quando não der certo.
    */
    bool lerRobosAdv(fstream &arq, Jogada &jogada);

    /**
        Função que faz a leitura no arquivo da jogada da tática que o goleiro irá executar
        @param &arq Arquivo que iremos pegar a tática
        @param &jogada Jogada aonde iremos setar a tática do goleiro
        @return True se ocorreu tudo certo, false caso não tenha ocorrido
    */
    bool lerTaticaGoleiro(fstream &arq, Jogada &jogada);

    /**
        Nesse método iremos pegar a tática correspondente a algum dos papeis da jogada, e depois inserir no papel.
        @param fstream &arq Arquivo que contém a tática que iremos pegar.
        @param Jogada &jogada Atributo que armazena as informações da jogada.
        @param int numPapel Armazena o número do papel que estamos usando.
        @return bool Retorna true se deu certo carregar os papeis da jogada, e retorna false quando não der certo.
    */
    bool lerTaticas(fstream &arq, Jogada &jogada, int numPapel);

    /**
        Nesse método iremos tratar as informações do arquivo a respeito de pontos.
        Quando acharmos um '(', então teremos a seguir uma estrutura do tipo Ponto,
        iremos então criar a variável, inserir as informações e retornar.
        @param string param Valor lido do arquivo da jogada.
        @param fstream &arq Arquivo que iremos ler para pegar os pontos.
        @param Tatica *tatica Variável que armazena os valores da tática.
    */
    void tratarPonto(string param, fstream &arq, Tatica* tatica);

    void imprimirInfoJogadas(Jogada jogada);

public:
    Carregador();

    ~Carregador();

    bool isTemJogadas();

    /**
        Nesse método iremos retornar as jogadas carregadas.
        @return vector<Jogada>* vetor com as jogadas carregadas.
    */
    vector<Jogada>* getJogadas();

    /**
        Funçao que retorna a lista com o nome dos arquivos das jogadas que poderão ser carregadas.
        @return Lista dos Nomes dos Arquivos das Jogadas
    */
    vector<string> getNomeArquivosJogadas();

    void setPathPastaJogadas(string _pathPastaJogadas);

    /**
        Função que seta a lista de nomes das jogadas que foram selecionadas para serem carregadas
        @param nomeJogadasSelecionadas Nome das jogadas que foram selecionadas para serem carregadas
    */
    void setNomeJogadasEscolhidas(const vector<string>& _nomeJogadasSelecionadas);

    /**
        Nesse método iremos retornar um string formatado contendo as jogadas e os seus respectivos erros.
        @return string Log de erro das jogadas que tentaram ser carregadas.
    */
    string getLogJogadasComErros();

    /**
        Nesse método iremos adicionar ao log de erro algum erro que aconteceu no carregamento das jogadas
        @param string erro Erro que ocorreu no carregamento.
    */
    void addLogJogadasComErros(string erro);

    /**
        Nesse método iremos indicar se poderemos iniciar o sistema ou não,
        isso irá depender se todas as jogadas que foram selecionadas foram carregadas corretamente.
        @return bool se for true poderemos iniciar o sistema, se for false não poderemos iniciar o sistema.
    */
    bool isCarregamentoSemErro();

    /**
        Nesse método iremos pegar o nome das Jogadas que estão em um determinada pasta.
        @return bool iremos retornar se deu certo ou não pegar o nome das jogadas.
    */
    bool pegarNomeArquivosJogadas(string _pathPastaJogadas);

    /**
        Nesse método iremos carregar as jogadas.
        Se o parâmetro for true indica que nós deveremos carregar todas as jogadas,
        se for false então iremos carregar somente as jogadas selecionadas na tabela.
        @param string pathPasta Caminho relativo da pasta onde estão as jogadas.
    */
    void carregarJogadasEscolhidas();
};

#endif // CARREGADOR_H
