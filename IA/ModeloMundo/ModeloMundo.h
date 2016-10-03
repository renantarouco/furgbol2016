    #ifndef MODELO_MUNDO_H
#define MODELO_MUNDO_H

#include "Definitions.h"
#include "Robo.h"
#include "Bola.h"
#include "Jogada.h"
#include "mensagem_gerente_dados.pb.h"
#include "Geometria.h"
#include "Config.h"
#include "Campo.h"
#include "Relogio.h"

#include "grSim_Packet.pb.h"
/**
 * Este é o modelo global onde todos os modulos tem acesso, nele são guardados principalmente, os fatos globais sobre o jogo que serao utilizados para escolher plays entre outras coisas.
 *
 * Também é nele que está o pacote que será enviado ao monitorador.
 */
class ModeloMundo
{
private:
    vector<Robo> robosEq; ///< Vetor com os robos da nossa equipe
    vector<int> idRobosEqMenosGoleiro; ///< Vetor com o id de todos os robos presentes da nossa equipe menos do goleiro
    vector<Robo> robosAdv; ///< Vetor com os robos da equipe adv
    int qtRobosEqPresentes, qtRobosAdvPresentes; ///< números que indicam as quantidades de robos de cada equipe que estão no campo
    int idGoleiroEq, idGoleiroAdv;
    Robo* roboAdvMaisProxBola, *roboEqMaisProxBola; ///< ids que indica qual o robô que está mais proximo da bola de cada time

    Bola bola; /// Objeto que representa a bola do jogo
    Campo campo; ///< Objeto que representa o campo e seus dados

    map<string, bool> fatos; ///< map que contém os fatos do mundo e se são verdadeiros ou não, usados para escolher a melhor jogada

    PacoteControle::LadoCampo ladoCampo; ///< dado que indica o lado da equipe no campo
    PacoteControle::CorEquipe corEquipe; ///< dado que indica qual a cor do time

    /// dados de log dos pacotes enviados pelo gerentes de dados
    int numeroUltimoFrameRecebido;
    double delayGerenteDados;
    double delayAteEnvio;
    double tempoPartida;

    bool mudarSinal; ///< Variável que iremos usar para verificar quando precisaremos mudar o sinal dos pontos das jogadas

    string estadoAtual, estadoAnt;
    Ponto posBolaNormalStart;

    Relogio relogio;
    float tempoIteracao;

public:
    ModeloMundo();
    ~ModeloMundo();

    void init();

    void coletaDados(const PacoteDados& pacoteEntrada);
    void coletaDados(const PacoteIASimulador2D& pacoteEntrada);
    void coletaDadosVisao(const PacoteVisao& pacoteVisao);
    void coletaDadosEstados(const SSL_Referee& pacoteEstados);
    void coletaDadosControle(const PacoteControle& pacoteControle);
    void coletaDadosBola(const PacoteBola& pacoteBola);

    void preencheFatos();
    void atualizarFatos();
    void resetaFatos();

    /// analisa qual das duas equipes tem o robo mais proximo da bola e também pega os robos que estão mais proximos da bola
    bool verificarRoboMaisProxBola();

    /// @todo implementar essa função para que seja usada nas faltas
    int getIdRoboNaoPodeTocarBola();

    vector<Robo*> getOutrosRobosComTatica(int _id, string _tatica);

    int getIdRoboAtivo();

    vector<int> getIdRobosComChute();

    /// Funçoes get
    Campo* getCampo();
    vector<Robo>* getRobosEq();
    vector<Robo>* getRobosAdv();
    PacoteControle::CorEquipe getCorEquipe();
    int getIdGoleiro();
    bool isLadoCampoEsquerdo();
    int getIdGoleiroAdv();
    map<string, bool>* getFatos();
    Robo* getRoboEq(int _id);
    Robo* getRoboAdv(int _id);
    Bola* getBola();
    PacoteControle::LadoCampo getLadoCampo();
    vector<int>* getIdRobosMenosGoleiro();
    int getQtRobosEqPresentes();
    int getQtRobosAdvPresentes();
    bool isEqAmarelo();
    bool isMudarSinalPontosJogadas();
    void PontoDentroAreaAdv(Ponto& alvo);
    bool isBolaDentroAreaAdv();

    /// sets
    void setRobosTemChute(map<int, bool>& idRobosSem); /// < cria um modelo de mundo novo
    void setIdGoleiro(int id);
    void setMudarSinalPontosJogadas(bool _mudarSinal);

};
#endif
