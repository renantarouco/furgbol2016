#include "Comando.h"

Comando::Comando()
{
    alvoChute = CGAL::ORIGIN;
    alvoFinal = CGAL::ORIGIN;
    m_direcaoDriblador = ANTI_HORARIO;

}

Comando::Comando(float _direcao, bool _drible ,TipoChute _tipoChute)
{


    orientacao = _direcao;
    //    chute = _chute;
    drible = _drible;
    tipoChute = _tipoChute;
    alvoChute = CGAL::ORIGIN;
    alvoFinal = CGAL::ORIGIN;
    m_direcaoDriblador = ANTI_HORARIO;
    //    moduloVelDeslocamento = Montador::VEL_MAX;
    //    moduloVelAproximacao = Montador::VEL_MINIMA_DESLOCAMENTO;

}

Comando::Comando(const Comando &comando)
{
    alvo = comando.alvo;
    alvoChute = comando.alvoChute;
    alvoFinal = comando.alvoFinal;
    orientacao = comando.orientacao;
    tipoChute = comando.tipoChute;
    drible = comando.drible;
    vetOrientacao = comando.vetOrientacao;
    nivelChute = comando.nivelChute;
    m_direcaoDriblador = comando.m_direcaoDriblador;
}

void Comando::setAlvoFinal(const Ponto &_alvo)
{
    alvoFinal =_alvo;
}

//bool Comando::temChute()
//{
//    return chute;
//}

Ponto Comando::getAlvoFinal(){
    return alvoFinal;
}

void Comando::setAlvo(const Ponto& ponto)
{
    alvo.clear();
    alvo.push_back(ponto);
}

void Comando::setAlvo(const vector<Ponto> &pontos)
{
    alvo = pontos;
}

void Comando::setAlvoChute(const Ponto& _alvoChute)
{
    alvoChute = _alvoChute;
}

void Comando::setAlvoOrientacao(const Ponto &_alvoOrientacao)
{
    alvoOrientacao = _alvoOrientacao;
}
//void Comando::setChute(bool _chute)
//{
//    chute =_chute;
//}

void Comando::setOrientacao(float _orientacao)
{
    orientacao = _orientacao;
    vetOrientacao = Vetor (cos(_orientacao),sin(_orientacao));
}

void Comando::setVetorOrientacao(const Vetor &_vetOrientacao)
{
    vetOrientacao = _vetOrientacao;
}
void Comando::setDrible(bool _drible)
{
    drible = _drible;
}

void Comando::setDirecaoDriblador(Direcao direcao)
{
    m_direcaoDriblador = direcao;
}

bool Comando::isUsaDrible()
{
    return drible;
}

Direcao Comando::getDirecaoDrible()
{
    return m_direcaoDriblador;
}

void Comando::setNivelChute(unsigned int _nivelChute)
{
    nivelChute = _nivelChute;
}
void Comando::setTipoChute(TipoChute _tipoChute)
{
    tipoChute =_tipoChute;
}

Ponto Comando::getAlvo() const
{
    if(alvo.size() > 0)
        return alvo[0];
    else
        return Ponto();
}

const vector<Ponto> &Comando::getAlvos()
{
    return alvo;
}

Ponto Comando::getAlvoChute()
{
    return alvoChute;
}

Ponto Comando::getAlvoOrientacao()
{
    return alvoOrientacao;
}

unsigned int Comando::getNivelChute(){
    return nivelChute;
}

Comando::TipoChute Comando::getTipoChute(){
    return tipoChute;
}

float Comando::getOrientacao(){
    return orientacao;
}

Vetor Comando::getVetOrientacaoFinal()
{
    return vetOrientacao;
}

//Vetor Comando::getVetDirecaoAlvo()
//{
//    return vetDirecaoAlvo;
//}

ostream & operator <<(ostream &os, const Comando &c)
{
    os << "Alvo " << c.getAlvo() << endl;
    os << "Direcao " << c.orientacao  << endl;
    return os;
}
