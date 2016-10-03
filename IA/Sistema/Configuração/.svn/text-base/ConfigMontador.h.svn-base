#ifndef CONFIGMONTADOR_H
#define CONFIGMONTADOR_H

#include "Definitions.h"

/// Cada skill tera uma velocidade de aproximacao para chegar no alvo e uma velocidade de deslocamente
struct ConfigSkill{
    float max_vel_aprox; /// m/s
    float max_vel_linear, min_vel_linear; /// m/s
    float max_vel_angular, min_vel_angular; /// rad/s
};

/**
    Classe de configuracao que sera usada para determinar
    as velocidades para cada skill enviar pro robo
*/
class ConfigMontador
{
public:
    ConfigMontador();

    static float MAX_VEL_RODAS; /// rad/s
    static float SPEED_UP, SPEED_DOWN; /// m/s
    static float MAX_MUDANCA_VEL_ANGULAR; /// rad/s
    static float P_GIRO, D_GIRO; /// Constantes usada para fazer o robo girar mais rapido ou mais suavemente
    static float ACELERACAO, DESACELERACAO; /// m/s²
    static map<string, ConfigSkill> CONFIG_SKILLS;

    static void load(string pathConfig);
};

#endif // CONFIGMONTADOR_H
