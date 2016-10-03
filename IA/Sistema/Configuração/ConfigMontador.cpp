#include "ConfigMontador.h"

float ConfigMontador::MAX_VEL_RODAS;
float ConfigMontador::SPEED_UP;
float ConfigMontador::SPEED_DOWN;
float ConfigMontador::MAX_MUDANCA_VEL_ANGULAR;
float ConfigMontador::P_GIRO;
float ConfigMontador::D_GIRO;
float ConfigMontador::ACELERACAO;
float ConfigMontador::DESACELERACAO;
map<string, ConfigSkill> ConfigMontador::CONFIG_SKILLS;

ConfigMontador::ConfigMontador()
{

}

void ConfigMontador::load(string pathConfig)
{
    QSettings settings(QString(pathConfig.c_str()), QSettings::IniFormat);

    MAX_VEL_RODAS = settings.value("max_vel_rodas").toDouble();
    SPEED_UP = settings.value("speed_up").toDouble();
    SPEED_DOWN = settings.value("speed_down").toDouble();
    MAX_MUDANCA_VEL_ANGULAR = settings.value("max_mudanca_vel_angular").toDouble();
    P_GIRO = settings.value("p_giro").toInt();
    D_GIRO = settings.value("d_giro").toInt();
    ACELERACAO = settings.value("aceleracao").toDouble();
    DESACELERACAO = settings.value("desaceleracao").toDouble();

    ConfigSkill constsSkill; /// Constantes que cada skill possui para controlarmos melhor o robo

    settings.beginGroup("CARREGA_BOLA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["CARREGA_BOLA"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("CHUTA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["CHUTA"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("CHUTA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["CHUTA_ALTO"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("EMPURRA_BOLA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["EMPURRA_BOLA"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("GIRA_ANTI_HORARIO");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["GIRA_ANTI_HORARIO"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("GIRA_EIXO");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["GIRA_EIXO"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("GIRA_HORARIO");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["GIRA_HORARIO"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("MANTE_POSICAO");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["MANTE_POSICAO"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("VAI_PARA_ALVO");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["VAI_PARA_ALVO"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("VAI_PARA_BOLA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["VAI_PARA_BOLA"] = constsSkill;
    settings.endGroup();

    settings.beginGroup("VIRA_PARA_BOLA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["VIRA_PARA_BOLA"] = constsSkill;
    settings.endGroup();


    settings.beginGroup("GIRA_HORARIO_DRIBLE");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["GIRA_HORARIO_DRIBLE"] = constsSkill;
    settings.endGroup();


    settings.beginGroup("DOMINA_BOLA");
    constsSkill.max_vel_aprox = settings.value("max_vel_aprox").toDouble();
    constsSkill.max_vel_linear = settings.value("max_vel_linear").toDouble();
    constsSkill.min_vel_linear= settings.value("min_vel_linear").toDouble();
    constsSkill.max_vel_angular = settings.value("max_vel_angular").toDouble();
    constsSkill.min_vel_angular = settings.value("min_vel_angular").toDouble();
    CONFIG_SKILLS["DOMINA_BOLA"] = constsSkill;
    settings.endGroup();
}
