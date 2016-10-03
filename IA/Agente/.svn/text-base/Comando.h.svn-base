#ifndef COMANDO_H
#define COMANDO_H

#include "Definitions.h"

/// Cada skill tera uma velocidade de aproximacao para chegar no alvo e uma velocidade de deslocamente
struct VelSkill{
    float velAproximacao; /// metros por segundo
    float velDeslocamento; /// metros por segundo
    float velAngular; /// radianos por segundo
};

/**
 * Estrutura geral criada pela estratégia, a partir desta estrutura só resta converter para um formato legivel pelo robo.
 *
 */
class Comando
{
public:
    enum TipoChute{
        CHUTE_BAIXO =0,
        CHUTE_ALTO =1,
        SEM_CHUTE =2
    };

private:
    vector<Ponto> alvo;
    Ponto alvoFinal;
    Ponto alvoOrientacao;
    Ponto alvoChute;
    float orientacao;
    Vetor vetOrientacao;
    //    Vetor vetDirecaoAlvo;
    //	bool chute;
    bool drible;
    Direcao m_direcaoDriblador;
    unsigned int nivelChute; /// Nivel do Chute é especificado pelo montador a partir do alvo de chute ou distancia do chute.   NIVEL PERCENTUAL
    TipoChute tipoChute;

public:
    Comando();
    Comando(float _direcao,bool _drible, TipoChute _tipoChute);
    Comando(const Comando& comando);

    //        bool temChute();
    void setAlvoFinal(const Ponto & _alvo);
    Ponto getAlvoFinal();
    void setAlvo(const Ponto& ponto);
    void setAlvo(const vector<Ponto> &pontos);

    void setAlvoChute(const Ponto& _alvoChute);
    void setAlvoOrientacao(const Ponto& _alvoOrientacao);
    void setOrientacao(float _orientacao);
    void setVetorOrientacao(const Vetor& _vetOrientacao);
    //        void setChute(bool _chute);
    void setDrible(bool _drible);
    void setDirecaoDriblador(Direcao direcao);
    void setNivelChute(unsigned int _nivelPercentual);
    void setTipoChute(TipoChute _tipoChute);

    Ponto getAlvo() const;
    const vector<Ponto> & getAlvos();
    Ponto getAlvoChute();
    Ponto getAlvoOrientacao();
    bool isUsaDrible();
    Direcao getDirecaoDrible();

    TipoChute getTipoChute();
    float getOrientacao();
    Vetor getVetOrientacaoFinal();
    //    Vetor getVetDirecaoAlvo();
    unsigned int getNivelChute();

    friend ostream& operator<<(ostream& os, const Comando& a);
};
#endif
