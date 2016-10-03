#ifndef DEFENDEPONTO_H
#define DEFENDEPONTO_H

#include <MaquinaSkills.h>
#include <ViraParaBola.h>
#include <VaiParaAlvo.h>
#include <MantemPosicao.h>
#include <GiraEixo.h>

/**
    Maquina usada para se manter em uma posição escolhida por uma tatica, podendo ser virado para bola ou não
    Está máquina não envolve manipulação de bola.
 */
class DefendePonto : public MaquinaSkills
{
private:
    Ponto alvo;
    bool ficarParado;

public:
    DefendePonto();
    ~DefendePonto();

    void perceber();
    void transitar();

    void setDados(const Ponto& _alvo, const vector<Parametro>& _parametros=vector<Parametro>(0));
    void executar(Agente* agente);
};

#endif // DEFENDEPONTO_H
