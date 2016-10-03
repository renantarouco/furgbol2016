#include "Chute.h"
#include <Sistema.h>

Chute::Chute(){
}

Chute::~Chute(){
}

void Chute::executar(Agente* agente){

    int id = agente->getId();
    avaliadorRobo.setId(id);

    agente->ativarObstaculosEq(); /// ativando path planning
    agente->addBolaComoObstaculo(); /// adicionando a Bola como obstaculos para que ele faça a volta na bola caso ele esteja do lado contrário ao gol adv
    agente->addAreaEqObstaculo();
    agente->addAreaAdvObstaculo();
    agente->ativarObstaculosAdv();
    //agente->addAreaAdvObstaculo();

    /// variáveis auxiliares
    Ponto centroGolAdv = Sistema::modeloMundo.getCampo()->getAreaAdv()->getCentro();

    /// setando os parametros que a maquina usara para fazer as transicoes
    vector<MaquinaSkills::Parametro> parametros;
    //verificar proximidade para implementação do chute alto
    Ponto posicaoadv = Sistema::avaliador.getPosAdvMaisPertoBola();
    Ponto posicaobola = Sistema::modeloMundo.getBola()->getPosicao();

    float angulo = Sistema::avaliador.calcularOrientacaoAlvoBola(posicaoadv);



    float distancia = sqrt(pow((posicaoadv.x() - posicaobola.x()),2)+pow((posicaoadv.y() - posicaobola.y()),2));
    cout << ">DISTANCIA ROBO ADV MAIS PROXIMO DA BOLA: " << distancia << endl;

    //if(distancia > 1000 && (angulo > 45 || angulo <-45)){
        parametros.push_back(Sistema::modeloMundo.getRoboEq(id)->isTemChute() ? MaquinaSkills::CHUTE_BAIXO : MaquinaSkills::SEM_CHUTE);
    //}
    //else{
        //parametros.push_back(Sistema::modeloMundo.getRoboEq(id)->isTemChute() ? MaquinaSkills::CHUTE_ALTO : MaquinaSkills::SEM_CHUTE);
    //}

    /// Calculando o alvo de aproximacao que o robo ira se posicionar para ir para o alvo corretamente
    Ponto alvoAprox = avaliadorRobo.calcularAlvoAproximacao(centroGolAdv);
    //Sistema::modeloMundo.PontoDentroAreaAdv(alvoAprox);

    /// Verificando se iremos chutar em algum outro lugar senao o gol adversario
    float anguloChute = Sistema::avaliador.calcularAnguloAberturaGol();

    /// setando os dados na maquina para pode executar corretamente
    maqMoveBola.setDados(alvoAprox, centroGolAdv, anguloChute, parametros);

    /// executando a máquina
    maqMoveBola.executar(agente);

    //    avaliadorRobo.calcularAlvoParaChutarGol();

    //    /// calcula um alvo para chutar a gol , por equanto o alvo é sempre no centro do gol
    //    /// desta forma não vão vamos precisar de histeressis no momento.
    //    ///  fazer score para outras posicoes do gol
    //    PontoInt alvoScore = avaliadorRobo.calcularAlvoParaChutarGol();

    //    cout << "Alvo de score " << alvoScore.second << endl;

    //    /// Verificando se o robo tem um score bom pra chutar, caso nao tenha ira ser calculado um alvo pra levar a bola
    //    if(alvoScore.second < PONTUACAO_LIMITE_CHUTE){

    //        /// Verificando se o robo pode ou nao chutar a bola
    //        parametros.push_back(Sistema::modeloMundo.getRoboEq(id)->isTemChute() ? MaquinaSkills::TEM_CHUTE : MaquinaSkills::SEM_CHUTE);

    //        /// Calculando o alvo de aproximacao que o robo ira se posicionar para ir para o alvo corretamente
    //        alvoAprox = calcAlvoAproximacao(id, alvoScore.first);

    //        /// Verificando se iremos chutar em algum outro lugar senao o gol adversario
    //        anguloChute = Sistema::avaliador.calcularAnguloAberturaGol(alvoScore.first, Config::COMPRIMENTO_GOL-100);

    //        return new MoveBola(alvoAprox, alvoScore.first, id, parametros, anguloChute);
    //    }

    //    cout << "Robo ira carregar bola" << endl;

    //    parametros[1] = MaquinaSkills::SEM_CHUTE;

    //    /// Calculando o alvo para o robo carregar a bola pra se livrar da marcacao e achar um espaco pra chutar
    //    Ponto alvoCarregar = avaliadorRobo.calcularAlvoCarregarBola(alvoScore.first);
    //    alvoAprox = calcAlvoAproximacao(id, alvoCarregar);
    //    anguloChute = Sistema::avaliador.calcularAnguloAberturaGol(alvoCarregar, 4*RAIO_ROBO);

    //    return new MoveBola(alvoAprox, alvoCarregar, id, parametros, anguloChute);
}

bool Chute::verificarTermino(int id){

    //    if(Sistema::modeloMundo.getRobo(id)->getComando().temChute()){
    //        chutou = true;
    //    }

    //    if(chutou && Sistema::modeloMundo.getBola()->foiChutada()){
    //        return true;
    //    }

    id = 0;
    return id;
}

float Chute::avaliacaoEscolhaRobo(int id){

    //    /// Verificando se o robô com esse id pode tocar na bola, caso não posso a avaliação dele será muito ruim, para que não seje escolhido
    //    if(!Sistema::modeloMundo.getRoboEq(id)->isTocarBola()){
    //        return numeric_limits<float>::infinity(); /// retornando um valor muito grande
    //    }

    /// Caso o robô possa tocar na bola iremos fazer os calculos normais de avaliação
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao(); /// Pegando a posição da bola
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao(); /// Pegando a posição do robô

    return squared_distance(posBola, posRobo); /// Calculando a distância da robô a bola
}

int Chute::getIdMelhorRobo(vector<int>& _ids)
{
    /// Se não tiver ids é porque deu erro.
    if(_ids.size() == 0 ) {
        cout << "SEM ROBOS PARA ESCOLHER MELHOR NA TATICA DE CHUTE" << endl;
        return -1;
    }

    /// Se não tiver ids é porque deu erro se tiver apenas um ID o melhor papel é o unico que sobrou
    if(_ids.size() == 1){
        int idRestante = _ids[0];
        _ids.erase(_ids.begin());
        return idRestante;
    }

    /** O melhor robô para essa tática é o robô que está mais perto da região que queremos posicionar ele*/
    int idMelhorRobo= -1;        /// Variável que iremos armazenar o valor do id do robô selecionado.
    int posicao = -1;           /// Variável que iremos usar para armazenar a posição do vetor que iremos remover.
    float menorDist = numeric_limits<float>::infinity();  /// Variável que iremos usar para armazenar a distância entre os robôs.

    for(unsigned int i = 0; i < _ids.size(); i++){
        Robo* roboEq = Sistema::modeloMundo.getRoboEq(_ids[i]);

        /// Verificando se o robô pode tocar na bola
        if(roboEq->isTocarBola() && roboEq->isTemChute())
        {
            /// Calculando a distância do robo a bola.
            float distRoboBola = avaliacaoEscolhaRobo(_ids[i]);

            /// Verificando se a distância que encontramos é menor que a anterior.
            if(distRoboBola < menorDist){
                menorDist = distRoboBola;     /// Setando a nova menor distância encontrada
                idMelhorRobo = _ids[i]; /// Pegando o id do robô que tem a menor distancia
                posicao=i;                /// Pegando a posição do vetor para removermos o robô do vetor
            }
        }
    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idMelhorRobo == -1)
    {
        cout << " CHUTE: AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }
    _ids.erase(_ids.begin() + posicao);

    return idMelhorRobo;
}

bool Chute::isAtiva(){
    return true;
}

Tatica* Chute::getNovaInstancia(){
    return new Chute;
}

void Chute::imprimirNome(){
    cout << "Chute" << endl;
}

float Chute::getLimiarAvaliacao()
{
    return 0.0;
}

string Chute::getNome()
{
    return "Chute";
}
