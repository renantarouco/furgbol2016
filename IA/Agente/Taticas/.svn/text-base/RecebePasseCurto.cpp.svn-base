#include "RecebePasseCurto.h"
#include <Sistema.h>

RecebePasseCurto::RecebePasseCurto(){
}

RecebePasseCurto::~RecebePasseCurto(){
}

void RecebePasseCurto::executar(Agente* agente){
//        agente->ativarNavegador();

//    /// Calculand o alvo para o robô se posicionar para receber o passe curto
//    Ponto alvo = calcularAlvoReceberPasseCurto(id);

//    /// Criando a maquina para posicionar o robô para receber o passe curto do outro robô.
//    return new DefendePonto(alvo, id);
}

bool RecebePasseCurto::verificarTermino(int id){
    id = 0;
    return id;
}

float RecebePasseCurto::avaliacaoEscolhaRobo(int id){

    /// Calculando o alvo aonde o robô irá se posicionar para receber o passe
    Ponto alvo = calcularAlvoReceberPasseCurto(id);

    /// Criando a região que iremos pegar o robô mais próximo dela.
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();

    /// Calculando a distância do robô ao ponto central da regiao
    return squared_distance(posRobo, alvo);
}

int RecebePasseCurto::getIdMelhorRobo(vector<int>& _ids){

    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE RECEBE PASSE CURTO" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1 ){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática, é o robô que está mais perto de uma região para receber um passe curto. ****/

    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i< _ids.size(); i++){

        /// Calculando a distância do robô à região.
        float distRoboRegiao = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
        if(menorDistRoboRegiao > distRoboRegiao){
            idRoboMaisPerto = _ids[i];                  /// Pegando o id do robô mais perto da região.
            posVetorRobo = i;                           /// Pegando o indice do vetor para removermos depois o id do robo
            menorDistRoboRegiao = distRoboRegiao; /// Setando a nova distância
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " RECEBE_PASSE_CURTO: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }

    _ids.erase(_ids.begin() + posVetorRobo); /// Apagando o id do robô que selecionamos para essa tática.

    return idRoboMaisPerto;
}

Ponto RecebePasseCurto::calcularAlvoReceberPasseCurto(int id){

    Ponto alvo; ///< Alvo aonde o robô irá se posicionar para receber o passe

    /// Pegando a posicao do robo e da bola para saber
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao();
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();

    /// Se o robô já estiver na região certa então não irá se mexer só irá esperar o passe
    if(squared_distance(posRobo, posBola) <= ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE*ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE){
        alvo = posRobo;

    }else{

        /// Criando a região minima que o robô terá que ficar para receber o passe
        Circulo circuloRegiao(posBola, ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE*ConfigAvaliador::RAIO_REGIAO_RECEBER_PASSE);
        Reta retaCortaRegiaoPasse(posBola, Ponto(posBola.x(), posBola.y()+1));

        vector<Ponto> pontosInterseccao;
        circuloRegiao.isInterseccaoReta(retaCortaRegiaoPasse, pontosInterseccao);

        /// O cara que dara o passe ficara com a posicao com y maior o que recebera ficara com a posicao com menor y
        alvo = pontosInterseccao[0].y() < pontosInterseccao[1].y() ? pontosInterseccao[0] : pontosInterseccao[1];
    }

    return alvo;
}

bool RecebePasseCurto::isAtiva(){
    return false;
}

Tatica * RecebePasseCurto::getNovaInstancia(){
    return new RecebePasseCurto;
}

string RecebePasseCurto::getNome(){
    return "RoubaPasseCurto";
}


void RecebePasseCurto::imprimirNome(){
    cout << "RecebePasseCurto" << endl;
}

float RecebePasseCurto::getLimiarAvaliacao()
{
    return 0.0;
}

