#ifndef MOVE_BOLA_H
#define MOVE_BOLA_H

#include "MaquinaSkills.h"
#include <VaiParaBola.h>
#include <Chuta.h>
#include <ChutaAlto.h>
#include <GiraAntiHorario.h>
#include <GiraHorario.h>
#include <CarregaBola.h>
#include <ViraParaBola.h>
#include <VaiParaAlvo.h>
#include <Agente.h>
#include <EmpurraBola.h>
#include <MantemPosicao.h>
#include "GiraHorarioDrible.h"
#include "DominaBola.h"

/**
    Máquina utilizada para qualquer manipulação de bola.
*/
class MoveBola : public MaquinaSkills
{
private:
    float anguloChute; ///< Angulo que o robô que irá executar a maquina tem para poder chutar no alvo especificado
    Ponto alvoAprox; /// < Alvo que o robo vai utilizar para se aproximar da bola.
    Ponto alvoChute;
    bool chuteBaixo, chuteAlto;

public:
    MoveBola();
    ~MoveBola();

    void perceber();
    void transitar();

    void setDados(const Ponto& _alvoAprox, const Ponto& _alvoChute, vector<Parametro> _parametros=vector<Parametro>(0));
    void setDados(const Ponto& _alvoAprox, const Ponto& _alvoChute, float _anguloChute, const vector<Parametro>& _parametros=vector<Parametro>(0));

    void executar(Agente* agente);
};
#endif
