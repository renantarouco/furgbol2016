#include "Config.h"

bool Config::MODO_TESTE;
string Config::JOGADA_TESTE;
map<int, bool> Config::ROBOS_TEM_CHUTE;
string Config::PATH_PLAYBOOK;
string Config::PATH_PLAYBOOK_TESTE;

/// DEFINIÇÕES DO CAMPO
float Config::MEIO_COMPRIMENTO_CAMPO;
float Config::MEIA_LARGURA_CAMPO;
float Config::COMPRIMENTO_CAMPO;
float Config::LARGURA_CAMPO;
float Config::COMPRIMENTO_GOL;
float Config::MEIO_COMPRIMENTO_GOL;
float Config::RAIO_SEMI_CIRCULO_AREA;
float Config::MEIA_LARGURA_SEGMENTO_AREA;

Config::Config()
{
}

void Config::load(string pathConfig){

    /// DEFINIÇÕES DO CAMPO
    COMPRIMENTO_CAMPO = 6550.0;   //  COMPRIMENTO_CAMPO = 6050.0;
    LARGURA_CAMPO = 4550.0;     // LARGURA_CAMPO = 4050.0;
    MEIO_COMPRIMENTO_CAMPO = COMPRIMENTO_CAMPO/2.0;
    MEIA_LARGURA_CAMPO = LARGURA_CAMPO/2.0;
    COMPRIMENTO_GOL = 700.0;
    MEIO_COMPRIMENTO_GOL = 350.0;
    RAIO_SEMI_CIRCULO_AREA = 800.0;
    MEIA_LARGURA_SEGMENTO_AREA = 175.0;

    QString path(pathConfig.c_str());
    path.append("config.ini");

    QSettings settings(path, QSettings::IniFormat);

    MODO_TESTE = settings.value("modo_teste").toBool();
    JOGADA_TESTE = settings.value("jogada_teste").toString().toStdString();
    PATH_PLAYBOOK = settings.value("path_playbook").toString().toStdString();
    PATH_PLAYBOOK_TESTE = settings.value("path_playbook_testes").toString().toStdString();

    settings.beginGroup("ROBO_0");
    ROBOS_TEM_CHUTE[0] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_1");
    ROBOS_TEM_CHUTE[1] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_2");
    ROBOS_TEM_CHUTE[2] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_3");
    ROBOS_TEM_CHUTE[3] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_4");
    ROBOS_TEM_CHUTE[4] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_5");
    ROBOS_TEM_CHUTE[5] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_6");
    ROBOS_TEM_CHUTE[6] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_7");
    ROBOS_TEM_CHUTE[7] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_8");
    ROBOS_TEM_CHUTE[8] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_9");
    ROBOS_TEM_CHUTE[9] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_10");
    ROBOS_TEM_CHUTE[10] = settings.value("tem_chute").toBool();
    settings.endGroup();

    settings.beginGroup("ROBO_11");
    ROBOS_TEM_CHUTE[11] = settings.value("tem_chute").toBool();
    settings.endGroup();

    /// carregando as constantes do avaliador de acordo com o tipo de simulacao
    QString pathAvaliador(PATH_CONFIG.c_str()), pathMontador(PATH_CONFIG.c_str());

    /// Verificando quais serão as constantes
    /// que iremos usar se é para os robos reais ou para os do simulador
    if(ConfigComunicacao::TIPO_ROBOS == REAL){

        /// setando o path do avaliador
        pathAvaliador.append("avaliador.ini");
        ConfigAvaliador::load(pathAvaliador.toStdString());

        /// setando o path do montador
        pathMontador.append("montador.ini");
        ConfigMontador::load(pathMontador.toStdString());

    }else if(ConfigComunicacao::TIPO_ROBOS == SIMULADOR3D){

        /// setando o path do avaliador
        pathAvaliador.append("avaliador_simulador3d.ini");
        ConfigAvaliador::load(pathAvaliador.toStdString());

        /// setando o path do montador
        pathMontador.append("montador_simulador3d.ini");
        ConfigMontador::load(pathMontador.toStdString());

    }else if(ConfigComunicacao::TIPO_ROBOS == SIMULADOR2D){
        /// setando o path do avaliador
        pathAvaliador.append("avaliador_simulador2d.ini");
        ConfigAvaliador::load(pathAvaliador.toStdString());

        /// setando o path do montador
        pathMontador.append("montador_simulador2d.ini");
        ConfigMontador::load(pathMontador.toStdString());
    }
}

Config::~Config()
{
}
