#ifndef AVALIADOR_H
#define AVALIADOR_H

#include "Config.h"
#include "Relogio.h"
#include "Definitions.h"

/**
 * O objetivo do avaliador é receber acões a serem realizadas e ele deve retornar o alvo ideal para uma defesa, o alvo ideal para chute, bons alvos para receber passe e coisas do tipo.
 * Também é avaliado na parte de percepção das skills.
 */

// WARNING , usando operador de atribuição default !
class Avaliador{
private:
    /// variáveis auxiliares
    Relogio relogio;

protected:
    Reta retaCirculo; ///< Reta perpendicular a área onde a defesa irá se posicionar
    double tempoDaPosse; ///< Atributo que indica o tempo que ocorreu a ultima posse
    bool posseBola; ///< Atributo que determina se a posse da bola está com a equipe.
    bool bolaNossaAnt; ///< Atributo que guarda a ulima verificacao de quem esta mais proximo da bola.

public:
    Avaliador();

    Reta getRetaCirculo();
    void setRetaCirculo(const Reta& _retaCirculo);

    /**
          Nesse método iremos pegar os robos da nossa equipe que estão entre o robo e o alvo.
          @param vector<int> idsRobosEq Ids dos robos da nossa equipe que iremos desconsiderar a distancia
          @param vector<int> idsRobosAdv Ids dos robos adv que iremos desconsiderar a distância.
          @param Segmento segPontoInicialAlvo Segmento que iremos analisar os robôs que estão a uma certa distância dele.
          @param float distSegPontoInicialAlvo Distância dos robos entre o segmento do ponto inicial ao alvo.
          @return vector<Ponto> Vetor das posições dos robos que estão entre o robo e o alvo.
          /// @todo ajeitar essa funcao
        */
    vector<Ponto> getRobosEntrePontos(const vector<int>& idRobosEqIgnorar, const vector<int>& idRobosAdvIgnorar,
                                      const Segmento& segPontoInicialAlvo, float distSegmento);

    /**
        @brief Esta função verifica se a posse de bola é nossa.
        Isso acontece quando os nossos robos estão mais perto da bola por mais de um segundo
    */
    bool verificarPosseBola();

    /**
        Nesse método iremos calcular o ângulo que indica a rotação que teremos que fazer para ficar de frente para a bola.
        @return Angulo calculado para o robô ficar de frente para a bola.
    */
    void calculaAnguloChuteGol();
    /**
        calcula angulo de abertura com o gol baseado na distancia do robo com o mesmo
        @return novo angulo de abertura
    */

    float calcularOrientacaoAlvoBola(const Ponto& alvo);

    /**
     * @brief
     *  Aqui sera calculado a orientacao que o robo deve ter para virar
     * para um determinada psoicao alvo.
     * @param alvo - Posicao pra onde o robo vai girar
     * @return float - Orientacao
     */
    float calcularOrientacaoPosicaoParaAlvo(const Ponto& posicao ,const Ponto& alvo);

    /** Funcao que pega o id do robo que nao pode tocar na bola */
    int getIdRoboNaoPodeTocarBola();

    /**
        Nesse método iremos pegar o robô da nossa equipe que está mais perto da bola.
        @return IdDistancia Um pair que indica o id do nosso robô que está mais perto da bola e a distância que ele está dela.
    */
    IdDistancia getIdDistRoboEqMaisPertoBola();

    /**
        Função que retorna a posicao do robo mais proximo da bola
        @return Ponto posicao do robo adv mais proximo da bola
    */
    Ponto getPosAdvMaisPertoBola();

    /**
        Nesse método iremos pegar o robô adv que está mais perto da bola.
        @return IdDistancia Um pair que indica o id do robô adv que está mais perto da bola e a distância que ele está dela.
    */
    IdDistancia getIdDistAdvMaisPertoBola();

    /**
        @brief retorna o numero de robos adversários que estao a NO MAXIMO a distancia passada
        em relacao ao ponto passado.
    */
    int getNumAdvPertoPonto(const Ponto& ponto, float distancia);

    /**
        Nesse método iremos pegar o robô adv que está mais perto da nosso área e que está sem bola.
        @param robosForaAlcanceBola Indica se o robo a ser marcado tera que ficar a uma distancia maior que a DISTANCIA_JOGO_PARADO
        @return int Id do robô mais proximo do nosso gol sem bola.
    */
    int getIdAdvMaisProxGolSemBola(bool robosForaAlcanceBola);

    /**
        Nesse método iremos pegar o robô adv que está mais perto da nosso área e que está sem bola.
        @param vector<int> idsRobosAdvMarcados Ids dos robos adversários que iremos desconsiderar pois já estão sendo marcados.
        @param bool robosForaAlcanceBola Irá indicar se iremos considerar os robôs que estão a menos de 500 mm da bola.
        @return int Id do robô mais proximo do nosso gol sem bola.
        @todo Sera usada posteriormente quando tiver varias taticas de marcar ou marcar saida de bola em uma mesma jogada
    */
    int getIdAdvMaisProxGolSemBola(vector<int> idsRobosAdvMarcados, bool robosForaAlcanceBola);

    /**
            Nesse método iremos calcula a quantidade de robôs da nossa equipe e da equipe adversária em uma área do campo.
            @param int id Id do robô que não iremos analisar a posição.
            @param int ladoCampo Indica o lado do campo que você quer calcular.
            @param int posCampo Indica a posição (em cima ou embaixo) do lado do campo que você quer calcular. (1 - em cima; 0 - embaixo).
            @return int Retorna a quantidade de robôs daquela área do campo.
        */
    int getQtRobosAreaCampoFrenteRoboComBola(int idDesconsiderar, int posCampo);

    /**
      @brief calcula a distancia entre todos os outros robos e uma reta
      @param id do robo em questão ( o qual não vai ser calculada a distancia)
      @param o segmento a ser calculado a distancia;
    */
    vector<float> getDistEntreRobosSegmento(const vector<Ponto>& posicoes,const Segmento& segmento);
    vector<float> getDistEntreAlvoeOutrosRobos(const vector<Ponto>& posicoes, const Ponto &alvo);

    /**
        @brief retorna um float de 0.1 a 1 que diz a redução do score que a avalição vai sofrer dependendo da distancia
        do robo com o gol em y( verificar se nao vale a pena deixar como outro tipo de distancia)
        Passa um parametro que onde a distancia dele sera considerada a redução.
    */
    float reduzirDistGolAdv();

    /**
      @brief Função empirica que tenta avaliar um score relativo a uma distancia de um robo a reta e
      a distancia de um robo ao robo que vai usar a reta de alguma forma.
      A ideia desta função é que para distancias pequenas da reta ela deve retornar valores
      altos enquanto que para distancias um pouco maiores o valor deve já tender a 0.
      @param const float& distSegmento Distância do robô à reta
      @param const float& distRobo Distância do robô ao outro robô.
      @return float Score desse robô que foi calculado apartir das distâncias passadas.
    */
    float analisarAlvo(const float& distSegmento, const float& distRobo);

    /**
        Nessa função iremos analisar se apartir da posição inicial para o alvo que queremos chutar se é bom pra chutar ou não.
        Aqui nós iremos pegar os scores de todos os robôs e somar se o score < 300 ele chuta se score > 300 não chuta.
        @param Ponto pontoInicial Alvo que iremos pegar e analisar se é bom pra chutar ou passar para o alvo.
        @param Ponto alvo Alvo que queremos chutar ou passar a bola.
        @param vector<Ponto> posRobos Posição dos robos que iremos analisar
        @param bool reducaoScore Indica se queremos que a função use o fator de redução da área do campo para analisar o score.
        @return float Retorna o score para poder chutar.
    */
    float analisarScoreAlvo(const Ponto& pontoInicial, const Ponto& alvo, vector<Ponto> posRobos, bool reducaoScore);

    /**
        Nesse método iremos verificar se algum robo adv tocou na bola
        @return bool Retorna true se tocaram na bola e false senão tiverem tocada na bola
    */
    bool roboAdvTocouBola();

    /**
        Nesse método iremos verificar se o robo tocou na bola.
        @return bool Retorna true se tocou na bola e false se não tocou na bola
    */
    bool roboEqTocouBola();

    /**
        Nesse método iremos calcular um angulo de abertura com ponto de origem na bola e final no alvo.
        Dependendo da largura que irá ser passada como parametro o angulo pode ser maior ou menor.
        @param Ponto alvo Alvo para onde iremos analisar
        @param float largura É a largura que o alvo tem
    */
    float calcularAnguloAbertura(Ponto alvo, float largura);

    float calcularAnguloAberturaGol();

    /**
        Nesse método iremos calcular um angulo de abertura com ponto de origem na bola e final no alvo.
        Dependendo da largura que irá ser passada como parametro o angulo pode ser maior ou menor.
        @param Ponto alvo Alvo para onde iremos analisar
        @param float largura É a largura que o alvo tem
    */
    float calcularAnguloAberturaGol(Ponto alvo, float largura);


    /**
        Nesse método iremos calcular uma reta que vai do robô adv que está com a bola até o centro do nosso gol.
        @return Reta Reta incidente que vai do robo adv que está com a bola até nosso gol.
    */
    Reta calcularRetaRoboAdvBola();

    Reta calcularRetaDirecaoBola();


    /**
        Dado um ponto do interseccao calcula um alvo deslocado em uma reta com
        a distancia de afastamento passada.
        @param Ponto um ponto de interseccao de onde será calculada a distancia
        @param float a distancia de afastamento
    */
    Ponto calcularAlvoComAfastamentoRetaIncidente(const Ponto& pontoInterseccao, float distAfastamento);

    /**
        Nesse método iremos calcular um alvo para o robô se posicionar a uma certa
        distância da bola para receber um passe curto.
        @param string tipoPosicao Indica se o robô irá dar ou receber o passe.
        @return Ponto Ponto mais perto do robô, calculado para o robô se posicionar.
    */
    Ponto calcularAlvoPosicionarPasseCurto(string tipoPosicao);

    /**
        Nesse método iremos calcular um ponto para o robô ficar que faz intersecao com a posicao do objeto passado e que
        fique a uma certa distância do mesmo.
        @param Ponto pontoObjeto ponto do objeto que iremos ter como referência para nos posicionarmos.
        @param float distDoObjeto Distância que temos que ficar do objeto.
        @return Ponto ponto que faz interseção com o objeto e está a uma certa distância do mesmo.
    */
    Ponto calcularAlvoDistPonto(const Ponto &pontoObjeto, float distDoObjeto);

    /**
        Calcula um ponto que fique atrás do robô a uma distância constante.
        @return Ponto alvo que iremos calcular
    */
    Ponto calcularAlvoAtrasRobo();

    /**
        Nesse método iremos verificar se o ponto passado como parâmetro está dentro do campo da equipe
        podendo o ponto estar fora da area do campo também
        @param Ponto ponto Ponto que queremos verificar se está dentro do campo equipe
        @return bool Valor que indica se o ponto está dentro do campo equipe ou não.
    */
    bool isPontoLadoEq(const Ponto& ponto);

    /**
        Nesse método iremos verificar se o ponto passado como parâmetro está dentro do campo adversario
        podendo o ponto estar fora da area do campo também
        @param Ponto ponto Ponto que queremos verificar se está dentro do campo adversário
        @return bool Valor que indica se o ponto está dentro do campo Adversário ou não.
    */
    bool isPontoLadoAdv(const Ponto& ponto);

    /**
      Nesse método iremos analisar se a bola é nossa, ou não.
      @return bool Retorna true se a bola for nossa e false senão for nossa.
    */
    bool isBolaNossa();

    /**
        Nesse método iremos analisar se a bola é nossa, ou não.
        @param int& idRoboAdvMaisPertoBola id do robô adv mais perto da bola, se a bola não for nossa então iremos pegar o id
                                           do robô adv mais perto dela.
        @return bool Retorna true se a bola é nossa e false senão for nossa.
    */
    bool isBolaNossa(int& idAdvMaisPertoBola);

    /**
      @brief funcao para calcular o ponto de giro em relacao a outro ponto
      @param Ponto que o robo vai girar em torno
      @param bool sentido horario ou anti horario de giro
            TRUE -> SENTIDO HORARIO
            FALSE -> SENTIDO ANTI-HORARIO
      @todo Revisar essa função
      */
    Ponto calcularAlvoGirar(const Ponto& pontoParaGirar, bool horario, int idRobo);
};
#endif
