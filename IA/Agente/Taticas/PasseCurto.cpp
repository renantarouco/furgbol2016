#include "PasseCurto.h"
#include <Sistema.h>

PasseCurto::PasseCurto(){
}

PasseCurto::~PasseCurto(){
}

void PasseCurto::executar(Agente* agente){
//        agente->ativarNavegador();

//    /// Pegando a posiçao do robô que irá receber o passe, que é justamente o alvo que o robô terá
//    vector<Robo*> robosReceberPasseCurto = Sistema::modeloMundo.getOutrosRobosComTatica(id, "RecebePasseCurto");

//    /// Enquanto nao encontrar um robo para receber passe curto o robo ira ficar parado
//    if(robosReceberPasseCurto.empty()){
//        return new DefendePonto(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), id, vector<MaquinaSkills::Parametro>(1, MaquinaSkills::FICAR_PARADO));
//    }

//    /// Pegando a posição da bola
//    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

//    /// Pegando a posição do robô que receberá o passe curto
//    Ponto posRoboReceberaPasseCurto(robosReceberPasseCurto[0]->getPosicao());

//    /// Criando a região em volta do robô que irá fazer o passe.
//    Circulo circuloRegiao(posBola,ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE*ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE);

//    /// Verificando se o robô que receberá o passe está no alvo esperando o passe
//    if(circuloRegiao.has_on_bounded_side(Sistema::modeloMundo.getRoboEq(id)->getPosicao()) && circuloRegiao.has_on_bounded_side(posRoboReceberaPasseCurto)){

//        /// Vetor com os parâmetros necessários para fazer o passe curto
//        vector<MaquinaSkills::Parametro> parametros(1);
//        parametros.push_back(MaquinaSkills::SEM_CHUTE);

//        /// Criando a máquina para o robô mover a bola para a direção do outro robô
//        Ponto alvoAprox = Sistema::avaliador.calcularAlvoAproximacao(Sistema::modeloMundo.getBola()->getPosicao(), ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE*ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE);
//        return new MoveBola(alvoAprox, posRoboReceberaPasseCurto, id, parametros);
//    }

//    /// Criando a região minima que o robô terá que ficar para receber o passe
//    Reta retaCortaRegiaoPasse(posBola, Ponto(posBola.x(), posBola.y()+1));
//    vector<Ponto> pontosInterseccao = interseccaoRetaCirculo(retaCortaRegiaoPasse, circuloRegiao);

//    /// O cara que dara o passe ficara com a posicao com y maior o que recebera ficara com a posicao com menor y
//    Ponto alvo = pontosInterseccao[0].y() > pontosInterseccao[1].y() ? pontosInterseccao[0] : pontosInterseccao[1];

//    /// Gerando um máquina para o robô ficar na mesma posição que está
//    return new DefendePonto(alvo, id);
}

bool PasseCurto::verificarTermino(int id){

    /// Pegando a distância do robô a bola
    float distRoboBola = squared_distance(Sistema::modeloMundo.getRoboEq(id)->getPosicao(), Sistema::modeloMundo.getBola()->getPosicao());

    /// Se a distância do robô a bola for menor que 5 mm então o tocou na bola
    if(distRoboBola <= ConfigAvaliador::TOL_TOQUE * ConfigAvaliador::TOL_TOQUE)
        return true;

    return false;
}

float PasseCurto::avaliacaoEscolhaRobo(int id){

    /// Pegando a posição da bola para compararmos com as posiçoes dos outros robôs
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância entre os dois pontos
    return squared_distance(posBola, posRobo);
}

int PasseCurto::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE PASSE CURTO" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô que está mais perto da bola. ****/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Verificando se o robô que iremos analisar pode tocar na bola
        if(Sistema::modeloMundo.getRoboEq(_ids[i])->isTocarBola()){

            /// Calculando a distância do robô à região.
            float distRoboBola = avaliacaoEscolhaRobo(_ids[i]);

            /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
            if(menorDistRoboRegiao > distRoboBola){
                idRoboMaisPerto = _ids[i];                  /// Pegando o id do robô mais perto da região.
                posVetorRobo = i;                           /// Pegando o indice do vetor para removermos depois o id do robo
                menorDistRoboRegiao = distRoboBola; /// Setando a nova distância
            }
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " PASSE_CURTO: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    /// Apagando o id do robô que selecionamos para essa tática.
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

bool PasseCurto::isAtiva(){
    return true;
}

Tatica * PasseCurto::getNovaInstancia(){
    return new PasseCurto;
}

void PasseCurto::imprimirNome(){
    cout << "PasseCurto" << endl;
}

string PasseCurto::getNome()
{
    return "PasseCurto";
}

float PasseCurto::getLimiarAvaliacao()
{
    return 0.0;
}
