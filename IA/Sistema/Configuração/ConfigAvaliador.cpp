#include "ConfigAvaliador.h"

#include "Config.h"

float ConfigAvaliador::TOL_MESMO_ALVO;
float ConfigAvaliador::TOL_TOQUE;
float ConfigAvaliador::TOL_PERTENCE_ALVO;
float ConfigAvaliador::RAIO_APROX;
float ConfigAvaliador::TOL_ORIENTACAO;
float ConfigAvaliador::K_ANALISE;
float ConfigAvaliador::Q_ANALISE;
float ConfigAvaliador::RAIO_CIRCULO_GIRAR;
float ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE;
int ConfigAvaliador::SCORE_MAX;
float ConfigAvaliador::DIST_ROBOS_DEFESA;
float ConfigAvaliador::DIST_ROBOS_BOLA_JOGO_PARADO;
float ConfigAvaliador::SCORE_MUDAR_MARCACAO;
float ConfigAvaliador::DIST_MARCAR_SAIDA_BOLA;
float ConfigAvaliador::DIST_MARCAR_ROBO;
float ConfigAvaliador::RAIO_APROX_MARCACAO;
float ConfigAvaliador::TEMPO_ANALISAR_POSSE_BOLA; /// segundo
float ConfigAvaliador::DIST_ANGULO_LIMPAR;
float ConfigAvaliador::DIST_ANGULO_CHUTAR;
float ConfigAvaliador::DIST_ANGULO_CARREGAR_BOLA;
float ConfigAvaliador::MIN_DIST_GOL;
float ConfigAvaliador::HIST_BOLA_PERTO_AREA_EQ;
float ConfigAvaliador::HIST_BOLA_PERTO_LINHA_FUNDO_EQ;

ConfigAvaliador::ConfigAvaliador(){
}

void ConfigAvaliador::load(string pathConfig){

    /// Verificando se iremos usar os valores de acordo com os robos reais ou se iremos usar os dados de acordo com o simulador
    QSettings settings(QString(pathConfig.c_str()), QSettings::IniFormat);

    /// Valores em cm
    TOL_TOQUE = settings.value("tol_toque").toFloat();
    TOL_ORIENTACAO = (settings.value("tol_orientacao").toFloat()* M_PI)/180.0;
    //     TOL_ORIENTACAO = settings.value("tol_orientacao").toFloat();
    TOL_PERTENCE_ALVO = settings.value("tol_alvo").toFloat();
    K_ANALISE = settings.value("k_analise").toFloat();
    Q_ANALISE = settings.value("q_analise").toFloat();
    TOL_MESMO_ALVO = settings.value("tol_mesmo_alvo").toFloat();
    RAIO_APROX = settings.value("raio_aprox").toFloat();
    RAIO_CIRCULO_GIRAR =settings.value("raio_circulo_girar").toFloat();
    SCORE_MAX = settings.value("score_max").toInt();

    /// marcacao
    SCORE_MUDAR_MARCACAO = settings.value("score_mudar_marcacao").toFloat();
    DIST_MARCAR_SAIDA_BOLA = settings.value("dist_marcar_saida_bola").toFloat();
    DIST_MARCAR_ROBO = settings.value("dist_marcar_robo").toFloat();

    /// segundo
    TEMPO_ANALISAR_POSSE_BOLA = settings.value("tempo_analisar_posse_bola").toFloat();

    HIST_BOLA_PERTO_AREA_EQ = settings.value("hist_bola_perto_area_eq").toFloat();
    HIST_BOLA_PERTO_LINHA_FUNDO_EQ = settings.value("hist_bola_perto_linha_fundo_eq").toFloat();

    RAIO_APROX_MARCACAO = settings.value("raio_aprox_marcacao").toFloat();
    RAIO_REGIAO_RECEBER_PASSE = 4 * RAIO_ROBO + TOL_PERTENCE_ALVO;

    /// Posiciona Defesa
    DIST_ROBOS_DEFESA = 2*RAIO_ROBO + TOL_PERTENCE_ALVO;
    DIST_ROBOS_BOLA_JOGO_PARADO = 500.0 + RAIO_ROBO + TOL_PERTENCE_ALVO;

    DIST_ANGULO_LIMPAR = Config::MEIO_COMPRIMENTO_CAMPO;
    DIST_ANGULO_CHUTAR = Config::MEIO_COMPRIMENTO_GOL;
    DIST_ANGULO_CARREGAR_BOLA = 2*RAIO_ROBO;
}
