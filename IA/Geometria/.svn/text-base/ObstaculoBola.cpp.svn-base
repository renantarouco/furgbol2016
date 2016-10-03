#include "ObstaculoBola.h"
#include "Sistema.h"

const float ObstaculoBola::TAMANHO_EXTRA = 10;

ObstaculoBola::ObstaculoBola()
{
}

ObstaculoBola::~ObstaculoBola()
{
}

void ObstaculoBola::construir(const Ponto &centroObjeto, float _distRoboCentro)
{
    cout << "Erro ao contruir Poligono Obstaculo bola, ele nao pode ser construido" << endl;
}

vector<Ponto> ObstaculoBola::calcularAlvoPosicionar(int qtRobosPosicionar)
{
    cout << "Erro ao calcularAlvoPosicionar do Poligono ObstaculoBola, metodo ainda nao implementado" << endl;
}

vector<Ponto> ObstaculoBola::calcularAlvosFinais(const Ponto &alvoInicial, int qtRobosPosicionar)
{
    cout << "Erro ao calcularAlvosFinais do Poligono ObstaculoBola, metodo ainda nao implementado" << endl;
}

Poligono *ObstaculoBola::getNovaInstancia()
{
    cout << "Erro ao dar getNovaInstancia do Poligono ObstaculoBola, metodo ainda nao implementado" << endl;
    return 0x0; // Esse poligono deveria ser um singleton, porque so existe uma bola, logo deveria existir apenas uma instancia
}

bool ObstaculoBola::isPontoDentro(const Ponto &ponto)
{
    float raioObstaculo = Bola::RAIO_MAX+TAMANHO_EXTRA;
    return squared_distance(Sistema::modeloMundo.getBola()->getPosicao(), ponto) <= raioObstaculo*raioObstaculo;
}

bool ObstaculoBola::isInterseccao(const Ponto &inicioSeg, const Ponto &fimSeg)
{
    cout << "Erro ao calcular interseccao com a bola do Poligono ObstaculoBola, metodo ainda nao implementado" << endl;
    return false;
}

Ponto ObstaculoBola::getCentro()
{
    return Sistema::modeloMundo.getBola()->getPosicao();
}
