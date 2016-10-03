#ifndef ROBO_H
#define ROBO_H

#include "Comando.h"
#include "Tatica.h"
#include "mensagem_ia_simulador2D.pb.h"

const int RAIO_ROBO=90; /// raio maximo do robo.

/**
 * A classe robo é a definição física e situacianal do robo.
 * Contém informações como a tatica corrente , as velocidades, o caminho que o robo deve seguir.
 * Nesta classe existem apenas métodos de atribuição e acesso
 */
class Robo
{
private:
    int id;
    bool present;
    Ponto posicao;
    Ponto posicaoAnt;
    float orientacao;
    Vetor vetOrientacao; /// < Vetor de orietacao do robo;
    Vetor velocidade;
    float velAngular;
    string skill; /// < Nome da skill sendo usada pelo robo.
    bool alvoMudou; /// Flag que sinaliza se o alvo mudou consideravelmente
    float distCarregouBola;
    Ponto alvoAprox;
    bool temChute;
    bool temDrible;
    bool sendoMarcado; ///< indica se o robo está sendo ou não marcado por outro robô

    PacotePathPlanning planning;
    string papel;
    Tatica *taticaCorrente;

    Comando comando; /// COmando corrente gerado para este robo.
    bool tocarBola; ///< Variável que irá indicar se o robô poderá pegar na bola

public:
    Robo();

    void init(int _id=0, bool _temChute=true);
    void setDados(const Ponto& _pos, float _orientacao);

    void setPresent();
    void dontPresent();

    /// Funções set
    void setTemChute(bool _temChute);
    void setTemDrible(bool _temDrible);
    void setPacotePathPlanning(const PacotePathPlanning & _planning);
    void setSendoMarcado(bool _sendoMarcado);
    void setId(int _id);
    void setPresenca(bool _presente);
    void setPosicao(const Ponto &_posicao);
    void setPosicaoAnt(const Ponto &_posicaoAnt);
    void setVelocidade(const Vetor & _vel);
    void setVelAngular(float _velAngular);
    void setNomeTaticaCorrente(const string& _nomeTaticaCorrente);
    void setOrientacao(float _orientacao);
    void setAlvo(const Ponto& _alvo);
    void setAlvoFinal(const Ponto&  _alvoFinal);
    void setRoboTemChute(bool _roboTemChute);
    void setAlvoAprox(const Ponto& _alvoAprox);
    void setNomeSkill(const string& _skill);
    void setTaticaCorrente(Tatica* _tatica);
    void setComando(const Comando & _comando);
    void setAlvoMudou(bool _alvoMudou);
    void setDistCarregouBola(float _distCarregouBola);
    void setAlvoChute(const Ponto& _alvoChute);
    void setAlvoOrientacao(const Ponto& _alvoOrientacao);
    void setTocarBola(bool _tocarBola);

    /// Funções get
    bool isTemChute();
    bool isTemDrible();
    bool isSendoMarcado();
    bool isPresente();
    bool isRoboTemChute();
    bool isTocarBola();
    bool isAlvoMudou();
    PacotePathPlanning getPacotePathPlanning() const;
    Ponto getAlvoFinal();
    Ponto getAlvoOrientacao();
    int getId();
    Ponto getPosicao();
    Ponto getPosicaoAnt();
    Vetor getVelocidade();
    float getVelAngular();
    Vetor getVetorOrientacao();
    float getOrientacao();
    string getPapel();
    string getNomeTaticaCorrente();
    float getDistCarregouBola();
    Tatica* getTaticaCorrente();
    string getSkill();
    Comando getComando();
    Ponto getAlvoAprox();
};
#endif
