#include "Campo.h"
#include <Sistema.h>

Campo::Campo(){
}

Campo::~Campo(){
}

void Campo::construir(const Ponto& _centroAreaEq, const Ponto& _centroAreaAdv){
    cout << "CONSTRUINDO O CAMPO" << endl;

    /// criando a area da equipe
    areaEq.construir(_centroAreaEq);

    /// criando a area adversária
    areaAdv.construir(_centroAreaAdv);

    /// Criando o retângulo dos limites do campo.
    retanguloCampo = Retangulo(Ponto(-Config::MEIO_COMPRIMENTO_CAMPO, -Config::MEIA_LARGURA_CAMPO), Ponto(Config::MEIO_COMPRIMENTO_CAMPO, Config::MEIA_LARGURA_CAMPO));

    /// Criando as linhas que circudam o campo
    //    linhaHorizontalSup = Segmento(Ponto(-Config::MEIO_COMPRIMENTO_CAMPO, Config::MEIA_LARGURA_CAMPO), Ponto(Config::MEIO_COMPRIMENTO_CAMPO, Config::MEIA_LARGURA_CAMPO));
    //    linhaHorizontalInf = Segmento(Ponto(-Config::MEIO_COMPRIMENTO_CAMPO, -Config::MEIA_LARGURA_CAMPO),Ponto(Config::MEIO_COMPRIMENTO_CAMPO, -Config::MEIA_LARGURA_CAMPO));
    linhaFundoEsq = Segmento(Ponto(-Config::MEIO_COMPRIMENTO_CAMPO, Config::MEIA_LARGURA_CAMPO), Ponto(-Config::MEIO_COMPRIMENTO_CAMPO, -Config::MEIA_LARGURA_CAMPO));
    linhaFundoDir = Segmento(Ponto(Config::MEIO_COMPRIMENTO_CAMPO, Config::MEIA_LARGURA_CAMPO), Ponto(Config::MEIO_COMPRIMENTO_CAMPO, -Config::MEIA_LARGURA_CAMPO));

    /// Construindo os triangulos que serão usados para indicar a área que podemos chutar e que o adversário terá mais chance de chutar
    //    construirTriangulos(centroGolEq, centroGolAdv);
}

void Campo::trocarLado(){
    cout << "TROCANDO O LADO DA NOSSA EQUIPE" << endl;

    /// pegando os centros atuais
    Ponto centroAreaEq = areaEq.getCentro();
    Ponto centroAreaAdv = areaAdv.getCentro();

    /// invertendo o lado das goleiras
    centroAreaEq = Ponto(-centroAreaEq.x(), 0.0);
    centroAreaAdv = Ponto(-centroAreaAdv.x(), 0.0);

    /// construindo novamente o campo
    construir(centroAreaEq, centroAreaAdv);
}

void Campo::construirTriangulos(const Ponto& centroGolEq, const Ponto& centroGolAdv){

    //    /// Cria os triangulos encontrados nos cantos da goleira adversária.
    //    linhaHorizontalSup = Segmento(Ponto(-Config::MEIO_Config::COMPRIMENTO_CAMPO, 2700),Ponto(Config::MEIO_Config::COMPRIMENTO_CAMPO, 2700));
    //    linhaHorizontalInf = Segmento(Ponto(-Config::MEIO_Config::COMPRIMENTO_CAMPO, -2700),Ponto(Config::MEIO_Config::COMPRIMENTO_CAMPO, -2700));
    //    linhaVerticalEsq = Segmento(Ponto(-Config::MEIO_Config::COMPRIMENTO_CAMPO, 2700), Ponto(-Config::MEIO_Config::COMPRIMENTO_CAMPO, -2700));
    //    linhaVerticalDir = Segmento(Ponto(Config::MEIO_Config::COMPRIMENTO_CAMPO, 2700), Ponto(Config::MEIO_Config::COMPRIMENTO_CAMPO, -2700));

    //    /// Variáveis utilizadas para criar os triângulos que indica a área de chute da nossa equipe
    //    Ponto cantoFundoInfGoleiraAdv;
    //    Ponto cantoFundoSupGoleiraAdv;
    //    Ponto cantoFrenteInfGoleiraAdv;
    //    Ponto cantoFrenteSupGoleiraAdv;

    //    /// Variáveis utilizadas para criar os triângulos que indica a área de chute da equipe adversária
    //    Ponto cantoFundoInfGoleiraEq;
    //    Ponto cantoFundoSupGoleiraEq;
    //    Ponto cantoFrenteInfGoleiraEq;
    //    Ponto cantoFrenteSupGoleiraEq;

    //    /// Dependendo do lado iremos colocar coordenadas diferentes para ambos os triângulos
    //    if(Sistema::modeloMundo.isLadoCampoEsquerdo()){

    //        /// Adicionando as coordenadas do gol adversário para criar os triângulos da área de chute da nossa equipe
    //        cantoFundoInfGoleiraAdv = Ponto(centroGolAdv.x()+180, centroGolAdv.y()-350);
    //        cantoFundoSupGoleiraAdv=Ponto(centroGolAdv.x()+180, centroGolAdv.y()+350);
    //        cantoFrenteInfGoleiraAdv=Ponto(centroGolAdv.x(), centroGolAdv.y()-350);
    //        cantoFrenteSupGoleiraAdv=Ponto(centroGolAdv.x(), centroGolAdv.y()+350);

    //        /// Adicionando as coordenadas do gol da nossa equipe para criar os triângulos da área de chute da equipe adv
    //        cantoFundoInfGoleiraEq=Ponto(centroGolAdv.x()-180, centroGolAdv.y()-350);
    //        cantoFundoSupGoleiraEq=Ponto(centroGolAdv.x()-180, centroGolAdv.y()+350);
    //        cantoFrenteInfGoleiraEq=Ponto(centroGolAdv.x(), centroGolAdv.y()-350);
    //        cantoFrenteSupGoleiraEq=Ponto(centroGolAdv.x(), centroGolAdv.y()+350);

    //    }else{
    //        /// Adicionando as coordenadas do gol adversário para criar os triângulos da área de chute da nossa equipe
    //        cantoFundoInfGoleiraAdv=Ponto(centroGolAdv.x()-180, centroGolAdv.y()-350);
    //        cantoFundoSupGoleiraAdv=Ponto(centroGolAdv.x()-180, centroGolAdv.y()+350);
    //        cantoFrenteInfGoleiraAdv=Ponto(centroGolAdv.x(), centroGolAdv.y()-350);
    //        cantoFrenteSupGoleiraAdv=Ponto(centroGolAdv.x(), centroGolAdv.y()+350);

    //        /// Adicionando as coordenadas do gol da nossa equipe para criar os triângulos da área de chute da equipe adv
    //        cantoFundoInfGoleiraEq=Ponto(centroGolAdv.x()+180, centroGolAdv.y()-350);
    //        cantoFundoSupGoleiraEq=Ponto(centroGolAdv.x()+180, centroGolAdv.y()+350);
    //        cantoFrenteInfGoleiraEq=Ponto(centroGolAdv.x(), centroGolAdv.y()-350);
    //        cantoFrenteSupGoleiraEq=Ponto(centroGolAdv.x(), centroGolAdv.y()+350);
    //    }

    //    /************ Criando os triangulos que indicam a área de chute da nossa equipe ********************/
    //    Reta retaSupAdv(cantoFrenteSupGoleiraAdv, cantoFundoInfGoleiraAdv);
    //    Reta retaInfAdv(cantoFrenteInfGoleiraAdv, cantoFundoSupGoleiraAdv);

    //    Ponto pontoLinhaSupAdv;
    //    Ponto pontoLinhaInfAdv;

    //    /// Warning esse ponteiro não deve ser NULL
    //    if(!isInterseccaoSegmentoReta(linhaHorizontalSup, retaSupAdv, pontoLinhaSupAdv))
    //        cout << "Modelo Mundo cria triangulos adversários ponteiro NULL na intersecção de segmento" << endl;

    //    /// Warning esse ponteiro não deve ser NULL
    //    if(!isInterseccaoSegmentoReta(linhaHorizontalInf, retaInfAdv, pontoLinhaInfAdv))
    //        cout << "Modelo Mundo cria triangulos adversários ponteiro NULL na intersecção de segmento" << endl;

    //    /// Calculando os triângulos que correspondem a área que os nosso robôs terão para chutar ao gol adversário.
    //    trianguloSupCampoAdv = Triangulo(Ponto(centroGolAdv.x(),Config::MEIA_Config::LARGURA_CAMPO), pontoLinhaSupAdv, cantoFrenteSupGoleiraAdv);
    //    trianguloInfCampoAdv = Triangulo(Ponto(centroGolAdv.x(),-Config::MEIA_Config::LARGURA_CAMPO), pontoLinhaInfAdv, cantoFrenteInfGoleiraAdv);

    //    /************ Criando os triangulos que indicam a área de chute da equipe adversária ********************/
    //    Reta retaSupEq(cantoFrenteSupGoleiraEq, cantoFundoInfGoleiraEq);
    //    Reta retaInfEq(cantoFrenteInfGoleiraEq, cantoFundoSupGoleiraEq);

    //    Ponto pontoLinhaSupEq;
    //    Ponto pontoLinhaInfEq;

    //    /// Warning  esse ponteiro não deve ser NULL
    //    if(!isInterseccaoSegmentoReta(linhaHorizontalSup, retaSupEq, pontoLinhaSupEq))
    //        cout << "Modelo Mundo cria triangulos da equipe ponteiro NULL na intersecção de segmento" << endl;

    //    /// Warning  esse ponteiro não deve ser NULL
    //    if(!isInterseccaoSegmentoReta(linhaHorizontalInf, retaInfEq, pontoLinhaInfEq))
    //        cout << "Modelo Mundo cria triangulos da equipe ponteiro NULL na intersecção de segmento" << endl;

    //    /// Calculando os triângulos que correspondem a área que os nosso robôs terão para chutar ao gol adversário.
    //    trianguloSupCampoEq = Triangulo(Ponto(centroGolEq.x(), Config::MEIA_Config::LARGURA_CAMPO), pontoLinhaSupEq, cantoFrenteSupGoleiraEq);
    //    trianguloInfCampoEq = Triangulo(Ponto(centroGolEq.x(), -Config::MEIA_Config::LARGURA_CAMPO), pontoLinhaInfEq, cantoFrenteInfGoleiraEq);
}

Area* Campo::getAreaEq(){
    return &areaEq;
}

Area* Campo::getAreaAdv(){
    return &areaAdv;
}

Segmento Campo::getLinhaFundoEsq()
{
    return linhaFundoEsq;
}

Segmento Campo::getLinhaFundoDir()
{
    return linhaFundoDir;
}

bool Campo::isPontoDentro(const Ponto &ponto){
    return retanguloCampo.has_on_bounded_side(ponto); /// Verificando se o ponto está dentro dos limites do campo
}

bool Campo::isPontoDentroAreaEq(const Ponto &ponto)
{
    return areaEq.isPontoDentro(ponto);
}

bool Campo::isPontoDentroAreaAdv(const Ponto &ponto)
{
    return areaAdv.isPontoDentro(ponto);
}

bool Campo::isPontoDentroAreaChute(const Ponto& ponto, bool nossaEquipe){

    /// Triângulos que indicam a área de chute.
    Triangulo tSup;
    Triangulo tInf;

    /// Verificando se iremos analisar o robô da nossa equipe ou o robô adversário e
    /// Pegando o triangulo superior e inferior para analisarmos se o robô que quer chutar está dentro desses triângulos
    if(nossaEquipe){
        tSup = trianguloSupCampoAdv;
        tInf = trianguloInfCampoAdv;
    }else{
        tSup = trianguloSupCampoEq;
        tInf = trianguloInfCampoEq;
    }

    return tSup.has_on_bounded_side(ponto) || tInf.has_on_bounded_side(ponto);

    return true;
}




