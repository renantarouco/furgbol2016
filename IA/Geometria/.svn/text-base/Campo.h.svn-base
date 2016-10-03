#ifndef CAMPO_H
#define CAMPO_H

#include "Config.h"
#include "Geometria.h"

class Campo
{
private:
    /// Linhas que limitam o campo de jogo
//    Segmento linhaHorizontalSup;    ///< Linha Horizontal Superior do Campo
//    Segmento linhaHorizontalInf;    ///< Linha Horizontal Inferior do Campo
    Segmento linhaFundoEsq;      ///< Linha Vertical da Esquerda do Campo
    Segmento linhaFundoDir;      ///< Linha Vertical da Direita do Campo

    /// Triangulos usados para determinar a área para o robô chutar.
    Triangulo trianguloSupCampoEq;  ///< Triangulo Superior que indica a área de chute da equipe adversária.
    Triangulo trianguloInfCampoEq;  ///< Triangulo Inferior que indica a área de chute da equipe adversária.
    Triangulo trianguloSupCampoAdv; ///< Triangulo Superior que indica a área de chute da nossa equipe.
    Triangulo trianguloInfCampoAdv; ///< Triangulo Inferior que indica a área de chute da nossa equipe.

    /// Area dos Goleiros das Equipes
    Area areaEq;  ///< Area da nossa equipe
    Area areaAdv; ///< Area equipe adversária

    Retangulo retanguloCampo; ///< Retângulo que representa o campo

    void construirTriangulos(const Ponto &centroGolEq, const Ponto &centroGolAdv);

public:
    Campo();
    ~Campo();

    Area* getAreaEq();
    Area* getAreaAdv();

    Segmento getLinhaFundoEsq();
    Segmento getLinhaFundoDir();

    /**
        Função usada para construir e setar os valores dos objetos do campo
    */
    void construir(const Ponto &_centroAreaEq=Ponto(-Config::MEIO_COMPRIMENTO_CAMPO,0.0), const Ponto &_centroAreaAdv=Ponto(Config::MEIO_COMPRIMENTO_CAMPO,0.0));

    void trocarLado();

    /**
        Nesse método iremos verificar se o ponto passado como parâmetro está dentro dos limites do campo.
        @param ponto Ponto que queremos verificar se está dentro dos limites.
        @return Valor que indica se o ponto está dentro dos limites do campo ou nao.
    */
    bool isPontoDentro(const Ponto &ponto);

    /**
        Nesse método iremos verificar se o ponto passado como parâmetro está dentro da área da nossa equipe.
        @param ponto Ponto que queremos verificar se está dentro dos limites.
        @return Valor que indica se o ponto está dentro da aérea ou não
    */
    bool isPontoDentroAreaEq(const Ponto& ponto);

    /**
        Nesse método iremos verificar se o ponto passado como parâmetro está dentro da área da equipe adversária
        @param ponto Ponto que queremos verificar se está dentro dos limites.
        @return Valor que indica se o ponto está dentro da aérea ou não
    */
    bool isPontoDentroAreaAdv(const Ponto& ponto);

    /**
        Nesse método iremos verificar se o robo está nos triangulos do canto da quadra, que são os lugares que poderemos chutar no gol aversário.
        @param ponto Ponto que iremos verificar se está dentro do campo
        @param nossaEquipe Valor que indica se iremos analisar se o robô da nossa equipe está na área de chute ou robô adv.
        @return Retorna true se estiver dentro da área de chute e false senão estiver dentro da área de chute.
    */
    bool isPontoDentroAreaChute(const Ponto& ponto, bool nossaEquipe);
};

#endif // CAMPO_H
