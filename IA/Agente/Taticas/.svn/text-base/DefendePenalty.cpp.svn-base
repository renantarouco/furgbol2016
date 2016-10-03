#include "DefendePenalty.h"
#include <Sistema.h>

DefendePenalty::DefendePenalty(){
}

DefendePenalty::~DefendePenalty(){
}

void DefendePenalty::executar(Agente* agente){

    /// pegando os dados que iremos precisar para executar a tática da DefendeGol
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();
    Area* areaEq = Sistema::modeloMundo.getCampo()->getAreaEq();
    Ponto centroGolEq = areaEq->getCentro();
    Segmento segmentoGolEq = areaEq->getSegmentoGol();
    float fator = centroGolEq.x() > 0.0 ? -1 : 1;
    float deslocar_x = fator*(RAIO_ROBO + ConfigAvaliador::TOL_PERTENCE_ALVO);

    /// posicao x e y do alvo que o goleiro irá se posicionar
    float posAlvo_x = deslocar_x + centroGolEq.x();
    float posAlvo_y = centroGolEq.y();

    /// Reta que é criada com base na direcao da bola
    Reta retaDirecaoBola = Sistema::avaliador.calcularRetaDirecaoBola();

    /// Verificando se tem pontos em que a reta passa pelo gol da nossa equipe, o robo irá se posicionar nesse ponto
    Ponto pontoInterseccao;
    if(Geometria::isInterseccaoSegmentoReta(segmentoGolEq, retaDirecaoBola, pontoInterseccao)){

        /// Deslocando o goleiro um pouco pra fora do gol
        posAlvo_x = deslocar_x + pontoInterseccao.x();
        posAlvo_y = pontoInterseccao.y();

    }else{

        /// verificando se tem o robo adv mais proximo da bola está mirando para chutar
        Ponto posAdvMaisProxBola = Sistema::avaliador.getPosAdvMaisPertoBola();
        Reta retaRoboAdvBola(posAdvMaisProxBola, posBola);

        /// verificando se a reta robo bola intercepta o gol
        if(Geometria::isInterseccaoSegmentoReta(segmentoGolEq, retaRoboAdvBola, pontoInterseccao)){

            /// Deslocando o goleiro um pouco pra fora do gol
            posAlvo_x = deslocar_x + pontoInterseccao.x();
            posAlvo_y = pontoInterseccao.y();
        }
    }

    /// setando os dados na maquina
    maqDefendePonto.setDados(Ponto(posAlvo_x, posAlvo_y));

    /// executando a maquina
    maqDefendePonto.executar(agente);
}

bool DefendePenalty::verificarTermino(int id){
    id = 0;
    return id;
}

float DefendePenalty::avaliacaoEscolhaRobo(int id){
    id = 0;
    return id;
}

int DefendePenalty::getIdMelhorRobo(vector<int>& _ids){
    return 0; /// O id do robô goleiro é sempre zero
}

bool DefendePenalty::isAtiva(){
    return true;
}

Tatica* DefendePenalty::getNovaInstancia(){
    return new DefendePenalty;
}

string DefendePenalty::getNome()
{
    return "DefendePenalty";
}

void DefendePenalty::imprimirNome(){
    cout << " DefendePenalty " << endl;
}

float DefendePenalty::getLimiarAvaliacao()
{
    return 0.0;
}
