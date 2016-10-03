#ifndef AVALIADORROBO_H
#define AVALIADORROBO_H

#include "Definitions.h"

/*!
  *  Função local de avaliação do robo, aqui são feitas as avaliações que dizem
  *  respeito a apenas um robo e guardam valores que podem ser usados pelo mesmo
  *  robo em outras avaliações
  */

class AvaliadorRobo{
    int id;                     ///< Id do robô que irá executar os métodos.
    Reta retaSemiCirculo;       ///< Essa variável pode ser usada caso o ponto de intersecção do alvo de defesa for no semicirculo
    Ponto alvoDefesaBaixo;
    Ponto alvoDefesaCima;

public:
    AvaliadorRobo();
    AvaliadorRobo(int _id);
    AvaliadorRobo(const AvaliadorRobo & _avaliador);

    void setId(int _id);

    /**
        Calcula um alvo onde o robo deve se aproximar da bola para cumprir seu objetivo
        @param o alvo objetivo final
        @param raioRegiao Raio da regiao de aproximacao aonde o robo ira comecar a girar ate chegar no alvo de aproximacao (O raio tem que ser ao quadrado )
        @return alvo aproximacao
    */
    Ponto calcularAlvoAproximacao(const Ponto & alvo);

    /**
       Verifica um score para cada alvo e retorna o melhor alvo junto com o seu score.
       No momento este método só avalia para o centro do gol, com mais testes vai ser possivel determinar
       outros alvos para chute dentro do gol.
       @return Um pair que retorna o ponto escolhido pra chute e o score desse ponto.
       /// @todo ajeitar essa funcao
    */
    IntPonto calcularAlvoParaChutarGol();

    /**
        Nesse método iremos calcular o melhor alvo para irmos para que possamos ter uma abertura para o gol adversário.
        Iremos analisar os pontos acima e abaixo do robô que irá carregar a bola.
        Existem tres 4 areas os triangulos que não são area de chute o meio do campo (600 pra cima e pra baixo),
        a parte de baixo do campo e a parte de cima
        @param ponto Ponto onde a carrega bola deve querer chegar no final
        @return Ponto que o robô deve ir.
    */
    Ponto calcularAlvoCarregarBola(const Ponto &ponto);

    /**
        Nesse método iremos calcular um ponto bom para chutarmos na sua direção
        @return Melhor ponto para chutarmos.
    */
    Ponto calcularAlvoChuteLongaDist();

    /**
        Nesse método iremos calcular um ponto para nos posicionarmos ou para chutar nele.
        @param pontoFixo Ponto onde iremos ter como referência.
        @param alvoPosicionarOuChutar É o ponto que iremos calcular para nos posicionarmos ou chutarmos no ponto fixo
                                            apartir de uma posicao inicial.
        @param deslocamento Se o ponto do destinoInicial não for bom então iremos fazer uma iteração
               para identificar se o ponto do destinoInicial + deslocamento fica bom, até encontrarmos um ponto bom.
        @param deslocMaximo Será o valor máximo que ele poderá analisar do destino Inicial (em y).
        @todo POSSIBILIDADE DE COLOCAR EM RELAÇÂO A UM PONTO PASSADO PARA SE CALCULAR A REDUÇÂO.
        /// @todo ajeitar essa funcao
    */
        IntPonto calcularMelhorAlvoPosicionarOuChutar(const Ponto &pontoFixo, const Ponto & alvoPosicionarOuChutar, float deslocamento, float deslocMaximo,int scoreCorte);

    /**
        Nesse método iremos calcular um ponto dentro da reta que faz interseção com o ponto fixo passado.
        @param pontoFixo Ponto onde iremos ter como referência.
        @param alvoPosicionarOuChutar É o ponto que iremos calcular para nos posicionarmos ou chutarmos no ponto fixo
                                            apartir de uma posicao inicial.
        @param retaDeDeslocamento Reta que iremos usar como referência para nos posicionarmos
        @param deslocamento Se o ponto do destinoInicial não for bom então iremos fazer uma iteração
               para identificar se o ponto do destinoInicial + deslocamento fica bom, até encontrarmos um ponto bom.
        @param deslocMaximo Será o valor máximo que ele poderá analisar do destino Inicial (em y).
        POSSIBILIDADE DE COLOCAR EM RELAÇÂO A UM PONTO PASSADO PARA SE CALCULAR A REDUÇÂO.
        /// @todo ajeitar essa funcao
    */
        IntPonto calcularMelhorAlvoPosicionarOuChutar(const Ponto &pontoFixo, const Ponto &alvoPosicionarOuChutar, const Reta& retaDeDeslocamento, float deslocamento, float deslocMaximo,int scoreCorte);

    /**
        Idem aos de cima porem so desloca para cima ou para baixo.
    */
    /// @todo ajeitar essa funcao
        IntPonto calculaMelhorAlvoPosicionarOuChutarInferior(const Ponto &pontoFixo, const Ponto &alvoPosicionarOuChutar, float deslocamento, float deslocMaximo,int scoreCorte);
    /// @todo ajeitar essa funcao
        IntPonto calculaMelhorAlvoPosicionarOuChutarSuperior(const Ponto &pontoFixo, const Ponto &alvoPosicionarOuChutar, float deslocamento, float deslocMaximo,int scoreCorte);

    /**
        Calcula o alvo para o robô se posicionar caso o outro robô do nosso time perda a bola.
        O robô terá que ficar do lado oposto ao robô que está com a bola.
        @param distLateral Distância da lateral do campo.
        @param distLinhaFundo Distância do linha de fundo que o robo tera que ficar.
        @return Alvo que será gerado com base nas posições dos robôs e na distância da lateral.
    */
    Ponto calcularAlvoPosPerdaBola(int distLateral, int distLinhaFundo);

    /**
        Calcula um alvo em um segmento onde teremos que fazer uma intersecção com a bola ou não.
        Essa função só serve quando o segmento é vertical, não pode ser horizontal ou inclinado. (Por enquanto)
        @param condicao Variável que irá indicar se iremos ou não interceptar o robô que está com a bola.
        @param segmento Segmento que temos que pegar o ponto.
        @return Alvo que iremos calcular pro robô.
    */
    Ponto calcularAlvoNoSegmento(string condicao,const Segmento & segmento);

    /**
      Nesse método iremos calcular um ponto dentro da região que faça interseção com o gol adversário.
      @param Ponto central da região.
      @param Raio da região.
      @return Alvo da região em que o robô irá se posicionar.
    */
    Ponto calculaAlvoRegiaoInterceptaGolAdv(const Ponto &ponto, const float& raio);

    /**
        Nesse método iremos calcular a quantidade de robôs que estão na região passada como parâmetro.
        @param centro Ponto central da região.
        @param raio Raio da região.
        @return Quantidade de robôs nessa região.
    */
    int getQtRobosRegiao(const Ponto& centro, const float& raio);

    /**
        Função que atualiza o valor da distância que a bola foi carregado pelo robô
    */
    void atualizarDistBolaCarregada();
};


#endif // AVALIADORROBO_H
