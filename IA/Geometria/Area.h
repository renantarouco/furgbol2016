#ifndef AREA_H
#define AREA_H

#include "Circulo.h"

/**
    Classe usada para guardar informações das Areas dos Goleiros e também usada para fazer
    o Posicionamento de uma defesa caso queiramos
*/
class Area : public Poligono
{
private:
    Arco semiCirculoSup; ///< SemiCirculo superior
    Arco semiCirculoInf; ///< SemiCirculo inferior
    Segmento segmentoFrenteArea;    ///< Segmento que fica na frente da área.
    Retangulo retanguloArea;  ///< Retângulo que fica dentro da área.
    Segmento segmentoGol;
    Ponto centro;
    Circulo circuloPosicionarDefesa; ///< @todo por enquanto a area está sendo representanda como um circulo, posteriormente alterar isso

public:
    Area();
    Area(const Ponto& _centro);

    ~Area();

    Arco getSemiCirculoSup();
    Arco getSemiCirculoInf();
    Segmento getSegmentoGol();
    Segmento getSegmentoArea();
    Retangulo getRetanguloArea();

    void construir(const Ponto &_centro);

    /**
        Função usada para construir o objeto com as informações reais dele dado o centro do objeto
        @param centroObjeto Centro do Objeto que iremos construir
        @param _distRoboCentroPoligono Distancia que o robo vai precisar ficar do objeto
    */
    void construir(const Ponto& _centro, float _distRoboCentro);

    /**
        Função que calcula o novo Ponto dado o ponto anterior e o valor de deslocamento calculado
        @param quantRobosPosicionar Quantidade de robos que irão se posicionar no Objeto
        @return Vetor com os pontos dos robos que irão se posicionar no objeto
        @todo implementar a função de calcularAlvoPosicionar Area
    */
    vector<Ponto> calcularAlvosPosicionarDefesaFrente(int qtRobosPosicionar);
    vector<Ponto> calcularAlvosPosicionarDefesa(int qtRobosPosicionar);

    /**
        Função que calcula um novo alvo dado o alvo inicial e o valor de afastamento que o novo alvo
        terá que ficar para não colidir com o alvo anterior
        @param alvoInicial Alvo inicial no qual o robô iria se posicionar
        @param valorAfast Valor de Afastamento que o novo alvo terá que ficar para não colidir com o alvo inicial
        @return Alvos acima do ponto e abaixo ou aos lados do ponto aonde os robôs irão se posicionar
        @todo implementar a função de calcularAlvoFinalDadosAfastAlvoInicial Area
    */
    vector<Ponto> calcularAlvosFinaisDefesa(const Ponto& alvoInicial, int qtRobosPosicionar);

    /**
        Funão que retorna uma nova instancia da class
        @return Nova instancia da classe
    */
    Poligono* getNovaInstancia();

    /**
        Nesse método iremos verificar se o ponto passado como parâmetro está dentro dessa área
        @param Ponto ponto Ponto que queremos verificar se está dentro da área da equipe.
        @return bool Valor que indica se o ponto está dentro da área ou não.
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
        Retorna o centro do retangulo da area
        @return ponto centro do retangulo da area
        @todo implementar
    */
    Ponto getCentro();
};

#endif // AREA_H
