#ifndef CONFIGAVALIADOR_H
#define CONFIGAVALIADOR_H

#include <Robo.h>

/**
  Guarda as configurações de interface referente a ao avaliador , ou seja as tolerancias e outros parametros utilizados na avaliação.

 */
class ConfigAvaliador{   

public:
    ConfigAvaliador();

    static float MIN_DIST_GOL;

    /// Gerais
    static float TOL_ORIENTACAO;
    static float K_ANALISE;
    static float Q_ANALISE;

    /// Ativas
    static float RAIO_CIRCULO_GIRAR;
    static float RAIO_REGIAO_RECEBER_PASSE;
    static int SCORE_MAX;

    /// Posiciona Defesa
    static float DIST_ROBOS_DEFESA;
    static float DIST_ROBOS_BOLA_JOGO_PARADO;

    /// marcar
    static float SCORE_MUDAR_MARCACAO;
    static float DIST_MARCAR_SAIDA_BOLA;
    static float DIST_MARCAR_ROBO;
    static float RAIO_APROX_MARCACAO;

    static float TEMPO_ANALISAR_POSSE_BOLA; /// segundo

    static float DIST_ANGULO_LIMPAR;
    static float DIST_ANGULO_CHUTAR;
    static float DIST_ANGULO_CARREGAR_BOLA;

    static float TOL_MESMO_ALVO;
    static float TOL_TOQUE;
    static float TOL_PERTENCE_ALVO;
    static float RAIO_APROX;

    static float HIST_BOLA_PERTO_AREA_EQ;
    static float HIST_BOLA_PERTO_LINHA_FUNDO_EQ;

    static void load(string pathConfig=PATH_CONFIG);
};

#endif // CONFIGAVALIADOR_H
