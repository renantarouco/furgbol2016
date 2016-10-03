#include "ConfigComunicacao.h"

TipoRobos ConfigComunicacao::TIPO_ROBOS;
string ConfigComunicacao::DISPOSITIVO_SERIAL;
bool ConfigComunicacao::USAR_REFEREE;
bool ConfigComunicacao::ENVIA_MONITORADOR;
int ConfigComunicacao::NUM_PACOTES_SERIAL;
int ConfigComunicacao::NUM_PACOTES_SIMULADOR;
int ConfigComunicacao::NUM_PACOTES_MONITORADOR;
int ConfigComunicacao::REP_PACOTES_SERIAL;
int ConfigComunicacao::REP_PACOTES_MONITORADOR;
Address ConfigComunicacao::ADDRESS_SIMULADOR;
Address ConfigComunicacao::ADDRESS_MONITORADOR;
int ConfigComunicacao::PORTA_RECEBE_GD;
int ConfigComunicacao::PORTA_RECEBER;

ConfigComunicacao::ConfigComunicacao(){
}

void ConfigComunicacao::load(string pathConfig){
    QString path(pathConfig.c_str());
    path.append("config.ini");

    QSettings settings(path, QSettings::IniFormat);
    settings.beginGroup("COMUNICACAO");

    USAR_REFEREE = settings.value("usar_juiz").toBool();
    TIPO_ROBOS = (TipoRobos)settings.value("tipo_robos").toInt();
    ENVIA_MONITORADOR = settings.value("envia_monitorador").toBool();

    /// Pacotes por segundo
    NUM_PACOTES_SERIAL = settings.value("num_pacotes_serial").toInt();
    NUM_PACOTES_SIMULADOR = settings.value("num_pacotes_simulador").toInt();
    NUM_PACOTES_MONITORADOR = settings.value("num_pacotes_monitorador").toInt();

    /// Numero de vezes que os pacotes de envio irão ser repetidos
    REP_PACOTES_SERIAL = settings.value("rep_pacotes_serial").toInt();
    REP_PACOTES_MONITORADOR = settings.value("rep_pacotes_monitorador").toInt();

    DISPOSITIVO_SERIAL = settings.value("dispositivo_serial").toString().toStdString();

    ADDRESS_SIMULADOR.setHost(settings.value("ip_simulador").toString().toStdString(), settings.value("porta_simulador").toInt());

    ADDRESS_MONITORADOR.setHost(settings.value("ip_monitorador").toString().toStdString(), settings.value("porta_monitorador").toInt());

    PORTA_RECEBER = settings.value("porta_receber").toInt();

    settings.endGroup();
}
