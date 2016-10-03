#ifndef CONFIG_H
#define CONFIG_H

#include "ConfigAvaliador.h"
#include "ConfigComunicacao.h"
#include "ConfigMontador.h"

/**
  *Classe que guarda todas as configurações setadas pesla interface e passa por valor para o sistema
  *ao clicar no botão iniciar sistema.
  */
class Config
{
public:
    Config();
    ~Config();

    static bool MODO_TESTE;
    static string JOGADA_TESTE;
    static map<int, bool> ROBOS_TEM_CHUTE;
    static string PATH_PLAYBOOK;
    static string PATH_PLAYBOOK_TESTE;

    /// DEFINIÇÕES DO CAMPO
    static float MEIO_COMPRIMENTO_CAMPO;
    static float MEIA_LARGURA_CAMPO;
    static float COMPRIMENTO_CAMPO;
    static float LARGURA_CAMPO;
    static float COMPRIMENTO_GOL;
    static float MEIO_COMPRIMENTO_GOL;
    static float RAIO_SEMI_CIRCULO_AREA;
    static float MEIA_LARGURA_SEGMENTO_AREA;

    static void load(string pathConfig=PATH_CONFIG);
};

#endif // CONFIG_H
