#include "DefesaArea.h"

#include "Sistema.h"

DefesaArea::DefesaArea()
{
    temPosicao = false;
}

DefesaArea::~DefesaArea()
{
}

void DefesaArea::executar(Agente *agente)
{
    int id = agente->getId();
    agente->desativarObstaculosEq();
    agente->addAreaEqObstaculo();

    /// calculando o alvo da tática
    Ponto alvo = calcularAlvoPosDefesa(id);

    /// setando dados na maquina para pode executar
    maqDefendePonto.setDados(alvo);

    /// executando maquina
    maqDefendePonto.executar(agente);
}

bool DefesaArea::verificarTermino(int id)
{
    return false;
}

float DefesaArea::avaliacaoEscolhaRobo(int id)
{
    /// Calculando o alvo que o robô irá se posicionar
    Ponto alvo = calcularAlvoPosDefesa(id);

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao(); /// Pegando a posição do robô

    /// Calculando a distância do robô ao ponto central da região
    return squared_distance(posRobo, alvo);
}

int DefesaArea::getIdMelhorRobo(vector<int> &_ids)
{
    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0) {
        cout << "SEM ROBOS PARA ESCOLHER NA TATICA DE POSICIONA DEFESA" << endl;
        return -1;
    }

    /// Se tiver apenas um ID o melhor papel é o unico que sobrou.
    if(_ids.size() == 1){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin()); /// Removendo o robô que sobrou
        return idRestante;
    }

    /** O melhor robô para essa tática é o robô que está mais perto da região que queremos posicionar ele*/
    int idRoboMaisPerto = -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posVetorRobo = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDistRoboRegiao = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.
    for(unsigned int i = 0; i < _ids.size(); i++){

        /// Calculando a distância do robô à região.
        float distRoboPonto = avaliacaoEscolhaRobo(_ids[i]);

        /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
        if(menorDistRoboRegiao > distRoboPonto){
            idRoboMaisPerto = _ids[i];           /// Pegando o id do robô mais perto da região.
            posVetorRobo = i;                    /// Pegando o indice do vetor para removermos depois o id do robo
            menorDistRoboRegiao = distRoboPonto; /// Setando a nova distância
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

bool DefesaArea::isAtiva()
{
    return false;
}

Tatica *DefesaArea::getNovaInstancia()
{
    return new DefesaArea();
}

void DefesaArea::imprimirNome()
{
    cout << "DefesaArea" << endl;
}

string DefesaArea::getNome(){
    return "DefesaArea";
}

float DefesaArea::getLimiarAvaliacao()
{
    return 0.0;
}

/** Funcao que calcula o alvo aonde o robo ira se posicionar na defesa */
Ponto DefesaArea::calcularAlvoPosDefesa(int id){

    /// pegando a area da equipe que usaremos para nos posicionar
    areaEq = Sistema::modeloMundo.getCampo()->getAreaEq();

    /// pegando os robos com a mesma tática DefesaCirculo e que se posicionam no mesmo objeto
    vector<Robo*> robosComTatica = Sistema::modeloMundo.getOutrosRobosComTatica(id, "DefesaArea");
    robosComTatica.push_back(Sistema::modeloMundo.getRoboEq(id));

    /// Calculando o alvo aonde o robô irá se posicionar no poligono
    vector<Ponto> alvos = areaEq->calcularAlvosPosicionarDefesa(robosComTatica.size());
    //    cout << "qt alvos: " << alvos.size() << endl;

    //    if(!temPosicao){

    if(!alvos.empty()){

        /// enquanto tiver alvos ou até encontrarmos o alvo ideial para o robo da tática iremos continuar executando
        while(alvos.size() > 0){
            /// pegando o primeiro e alvo
            Ponto alvo = alvos[0];

            /// analisando quais dos robos é o mais proximo do alvo
            int posMelhorRobo = 0;
            double menorDist = squared_distance(robosComTatica[0]->getPosicao(), alvo);
            for(int j=1; j < robosComTatica.size(); j++){

                /// calculando a dist do robo j até o alvo
                double dist = squared_distance(robosComTatica[j]->getPosicao(), alvo);
                if(dist < menorDist){
                    posMelhorRobo = j;
                    menorDist = dist;
                }
            }

            /// verificando se o robo que foi escolhido é o robo da tática local, caso contrário iremos continuar a execução
            if(robosComTatica[posMelhorRobo]->getId() == id){
                return alvo;
            }

            /// apango o primeiro alvo e o melhor robo para este alvo, removemos para não ser analisado novamente
            robosComTatica.erase(robosComTatica.begin() + posMelhorRobo);
            alvos.erase(alvos.begin());
        }
    }

    /// Caso não tenha pontos para o robo se posicionar iremos deixar ele parado
    cout << "Robo " << id << " não tem posição na defesa" << endl;
    temPosicao = false;
    posDefesa = Sistema::modeloMundo.getRoboEq(id)->getPosicao();
    //    }

    return posDefesa;
}
