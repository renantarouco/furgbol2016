#ifndef CIRCULO_H
#define CIRCULO_H

#include "Poligono.h"

/**
    Classe usada para guardar informações de um Circulo qualquer e também para fazer o Posicionamento
    da Defesa em forma de Circulo caso queiramos
*/
class Circulo : public CGAL::Circle_2<Circular_k>, public Poligono
{
public:
    Circulo();
    Circulo(const Ponto& centro, float raio_quadrado);
    Circulo(const Ponto& p1, const Ponto& p2, const Ponto& p3);

    /**
        Função usada para construir o objeto com as informações reais dele dado o centro do objeto
        @param centroObjeto Centro do Objeto que iremos construir
        @param _distRoboCentroPoligono Distancia que o robo vai precisar ficar do objeto
    */
    void construir(const Ponto& centroObjeto, float _distRoboCentro);

    /**
        Função que calcula o novo Ponto dado o ponto anterior e o valor de deslocamento calculado
        @param pontos Vetor com os pontos que os robos irao se posicionar
        @param quantRobosPosicionar Quantidade de robos que irão se posicionar no Objeto
        @return Vetor com os pontos dos robos que irão se posicionar no objeto
    */
    vector<Ponto> calcularAlvosPosicionarDefesa(int qtRobosPosicionar);

    /**
        Função que calcula os alvos finais de acordo com a quantidade de robos que irão se posicionar.
        Iremos calcular esses alvos usando circulos para acharmos as interseccoes e fazendo verificações
        para identificar se o alvo calculado é válido e retorna um vetor com os Alvos de cada robô
        @param alvoInicial Alvo inicial no qual o robô iria se posicionar
        @param quantRobosPosicionar Quantidade de robos que irão se posicionar
        @return Alvos acima do ponto e abaixo ou aos lados do ponto aonde os robôs irão se posicionar
    */
    vector<Ponto> calcularAlvosFinaisDefesa(const Ponto& alvoInicial, int qtRobosPosicionar);

    /**
        Funão que retorna uma nova instancia da class
        @return Nova instancia da classe
    */
    Poligono* getNovaInstancia();

    /**
        Recebe um ponto e verifica se ele esta dentro do circulo
        @return true se o ponto esta dentro do circulo, false se não estiver
    */
    bool isPontoDentro(const Ponto &ponto);

    /**
        Nesse método iremos verificar se a reta faz interseccao com o Poligono
        @param reta Reta que iremos analisar se intercepta a nossa área.
        @return true se intersecciona, false caso contrário
    */
    bool isInterseccaoReta(const Reta& reta);

    /**
        Nesse método iremos verificar se a reta faz interseccao com o Poligono
        @param reta Reta que iremos analisar se intercepta a nossa área.
        @param pontos vector<Ponto> vetor de pontos que intersecciona os dois objetos
        @return true se intersecciona, false caso contrário
    */
    bool isInterseccaoReta(const Reta& reta, vector<Ponto>& pontos);

    /**
        Recebe dois ponto que definem um segmento, verifica se esse segmento faz
        intercessao com o circulo.
        @return true se o segmento faz intercessao, false se não faz intercessao
    */
    bool isInterseccao(const Ponto &inicioSeg, const Ponto &fimSeg);

    /**
        Retorna o centro do Circulo
        @return Ponto centro do circulo
    */
    Ponto getCentro();
};

#endif // CIRCULO_H
