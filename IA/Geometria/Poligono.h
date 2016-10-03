#ifndef POLIGONO_H
#define POLIGONO_H

#include "Definitions.h"

/**
    Classe usada para termos vários tipo de Posicionamento da Defesa dos Robôs.
    Iremos usar essa classe como base para fazer o posicionamento dos robos na defesa,
    o posicionamento irá ser feito por um Poligono (Circulo, Area, Reta, Triangulo, ...), qualquer objeto
    que quisermos criar, basta apenas implementar as funções para que possa ser feito o posicionamento corretamente
*/
class Poligono
{
protected:
    float distCentroAreaDefesa; ///< Distância que o robô terá que ficar do centro do Poligono

public:

    Poligono();

    virtual ~Poligono();

    /**
        Função usada para construir o objeto com as informações reais dele dado o centro do objeto
        @param centroObjeto Centro do Objeto que iremos construir
        @param _distRoboCentroPoligono Distancia que o robo vai precisar ficar do objeto
    */
    virtual void construir(const Ponto& centroObjeto, float _distRoboCentro) = 0;

    /**
        Função que calcula o novo Ponto dado o ponto anterior e o valor de deslocamento calculado
        @param quantRobosPosicionar Quantidade de robos que irão se posicionar no Objeto
        @return Vetor com os pontos dos robos que irão se posicionar no objeto
    */
    virtual vector<Ponto> calcularAlvosPosicionarDefesa(int qtRobosPosicionar) = 0;

    /**
        Função que calcula os alvos finais de acordo com a quantidade de robos que irão se posicionar.
        Iremos calcular esses alvos usando circulos para acharmos as interseccoes e fazendo verificações
        para identificar se o alvo calculado é válido e retorna um vetor com os Alvos de cada robô
        @param alvoInicial Alvo inicial no qual o robô iria se posicionar
        @param quantRobosPosicionar Quantidade de robos que irão se posicionar
        @return Alvos acima do ponto e abaixo ou aos lados do ponto aonde os robôs irão se posicionar
    */
    virtual vector<Ponto> calcularAlvosFinaisDefesa(const Ponto& alvoInicial, int qtRobosPosicionar) = 0;

    /**
        Funão que retorna uma nova instancia da class
        @return Nova instancia da classe
    */
    virtual Poligono* getNovaInstancia() = 0;

    /**
        Recebe um ponto e verifica se ele esta dentro do poligono
        @return true se o ponto esta dentro do poligono, false se não estiver
    */
    virtual bool isPontoDentro(const Ponto &ponto) = 0;

    /**
        Nesse método iremos verificar se a reta faz interseccao com o Poligono
        @param reta Reta que iremos analisar se intercepta a nossa área.
        @return true se intersecciona, false caso contrário
    */
    virtual bool isInterseccaoReta(const Reta& reta)=0;

    /**
        Nesse método iremos verificar se a reta faz interseccao com o Poligono
        @param reta Reta que iremos analisar se intercepta a nossa área.
        @param pontos vector<Ponto> vetor de pontos que intersecciona os dois objetos
        @return true se intersecciona, false caso contrário
    */
    virtual bool isInterseccaoReta(const Reta& reta, vector<Ponto>& pontos)=0;

    /**
        Recebe dois ponto que definem um segmento, verifica se esse segmento faz
        intercessao com o circulo.
        @return true se o segmento faz intercessao, false se não faz intercessao
    */
    virtual bool isInterseccao(const Ponto &inicioSeg, const Ponto &fimSeg)=0;

    /**
        Retorna o centro do poligono
        @return ponto centro do poligono
    */
    virtual Ponto getCentro() = 0;
};

#endif // POLIGONO_H
