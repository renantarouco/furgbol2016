#include "Bola.h"

#include "Sistema.h"

Bola::Bola(){
    posicao = CGAL::ORIGIN;
    vetorVelocidade = CGAL::NULL_VECTOR;
}

const Ponto &Bola::getPosicao(){
    return posicao;
}

const Ponto &Bola::getPosicaoAnterior()
{
    return posicaoAnt;
}

void Bola::setPosicao(const Ponto &_posicao){

    /// verificando se são pontos diferentes (uma forma de tratar ruidos pequenoss da visão)
    float dist = squared_distance(posicao, _posicao);
    if(dist > ConfigAvaliador::TOL_MESMO_ALVO){
        posicaoAnt = posicao;
        posicao = _posicao;
    }
}

void Bola::setPosicao(const Ponto &_posicao, float tempoIteracao)
{
    /// verificando se são pontos diferentes (uma forma de tratar ruidos pequenoss da visão)
    float dist = squared_distance(posicao, _posicao);
    if(dist > ConfigAvaliador::TOL_MESMO_ALVO*ConfigAvaliador::TOL_MESMO_ALVO){

        /// Calcular o vetor direcao unitario
        vetorVelocidade = Vetor((_posicao-posicaoAnt)/tempoIteracao);
        velLinear = sqrt(vetorVelocidade.squared_length());

        /// setando as novas posicao
        posicaoAnt = posicao;
        posicao = _posicao;
    }else{

        /// caso o alvo seja o mesmo a velocidade será zero
        vetorVelocidade = Vetor(0.0, 0.0);
        velLinear = 0.0;
    }
}

Vetor Bola::getVetorVelocidade(){
    return vetorVelocidade;
}

void Bola::setVetorVelocidade(const Vetor &_velocidade){
    vetorVelocidade = _velocidade;
}

void Bola::setAltura(float _altura){
    altura = _altura;
}

bool Bola::foiChutada(){
    return false;
}

Ponto Bola::getPosChutada()
{
    return posicaoChutada;
}

void Bola::setPosChutada(Ponto _posicaoChutado)
{
    posicaoChutada = _posicaoChutado;
}

bool Bola::isPertoAreaEq()
{
    /// variáveis auxiliares
    Ponto centroGolEq = Sistema::modeloMundo.getCampo()->getAreaEq()->getCentro();

    double distBola = squared_distance(posicao, centroGolEq);
    if(distBola < ConfigAvaliador::HIST_BOLA_PERTO_AREA_EQ * ConfigAvaliador::HIST_BOLA_PERTO_AREA_EQ){
        return true;
    }
    return false;
}

bool Bola::isPertoLinhaFundoEq(){

    if(Sistema::modeloMundo.isLadoCampoEsquerdo()){
        if(posicao.x() <= -ConfigAvaliador::HIST_BOLA_PERTO_LINHA_FUNDO_EQ){
            return true;
        }
    }else{
        if(posicao.x() >= ConfigAvaliador::HIST_BOLA_PERTO_LINHA_FUNDO_EQ){
            return true;
        }
    }

    return false;
}
