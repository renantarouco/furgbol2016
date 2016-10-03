
#include <Sistema.h>

#include "PosicionaDefesa.h"

template <class Poligono>
PosicionaDefesa<Poligono>::PosicionaDefesa()
{
    posicaoDefesa = -1;
}

template <class Poligono>
PosicionaDefesa<Poligono>::PosicionaDefesa(Poligono* _poligono, Ponto _centro, float _distRoboCentro)
{
    poligono = _poligono;
    distRoboCentro = _distRoboCentro;
    centro = _centro;

    poligono->construir(centro, distRoboCentro);

    posicaoDefesa = -1;
}

template <class Poligono>
PosicionaDefesa<Poligono>::~PosicionaDefesa(){
    delete poligono;
}

template <class Poligono>
MaquinaSkills* PosicionaDefesa<Poligono>::executar(int id)
{
    Ponto alvo = calcularAlvoPosDefesa(id);

    /// Criando a máquina de skill só para nos posicionarmos em relação ao objeto analisado anteriormente.
    return new DefendePonto(alvo, id);
}

template <class Poligono>
bool PosicionaDefesa<Poligono>::verificarTermino(int id)
{
    id = 0;
    return id;
}

template <class Poligono>
Tatica* PosicionaDefesa<Poligono>::reconstruir()
{
    string poligono; /// Variável que irá armazenar a forma de posicionamento que a defesa irá fazer
    try{
        poligono = paramString.at(1);
    }catch(exception ex){
        cout << "WARNING: A tática não possui parâmetros setados." << endl;
    }

    /// Verificando a forma de posicionamento que os robôs irão fazer
    if(poligono == "circulo"){
        return new PosicionaDefesa<Circulo>(new Circulo, Ponto(0.0,0.0), 0.0);
    }else if(poligono == "area"){
        return new PosicionaDefesa<Area>(new Area, Ponto(0.0,0.0), 0.0);
    }
}

template <class Poligono>
float PosicionaDefesa<Poligono>::avaliacaoEscolhaRobo(int id)
{

    /// Calculando o alvo que o robô irá se posicionar
    Ponto alvo = calcularAlvoPosDefesa(id);

    /// Pegando a posição do robô que iremos analisar
    Ponto posRobo = Sistema::modeloMundo.getRoboEq(id)->getPosicao(); /// Pegando a posição do robô

    /// Calculando a distância do robô ao ponto central da região
    return squared_distance(posRobo, alvo);
}

template <class Poligono>
vector<Robo*> PosicionaDefesa<Poligono>::getRobosComTatica(int id)
{
    vector<Robo*> robosComTatica;

    BOOST_FOREACH(Robo* robo, Sistema::modeloMundo.getRobosEq()){

        /// Analisando se o robo esta presente e possui a tatica posiciona defesa,
        /// iremos pegar apenas as taticas que tiverem o mesmo centro de posicionamento que o dessa tatica atual
        Tatica* tatica = robo->getTaticaCorrente();
        if(robo->isPresente() && tatica != NULL && robo->getId() != id){

            if(tatica->getNome().find("PosicionaDefesa") != string::npos){

                string objeto1, objeto2; /// Variável que irá armazenar a forma de posicionamento que a defesa irá fazer
                //                string poligono1, poligono2;
                try{
                    objeto1 = paramString.at(0);
                    objeto2 = tatica->getParamString().at(0);

                    //                    poligono1 = paramString.at(1);
                    //                    poligono2 = tatica->getParamString().at(1);

                    /// Verificando se os objetos das duas posicionadefesa sao iguais
                    if(objeto1 == objeto2/* && poligono1 == poligono2*/)
                        robosComTatica.push_back(robo);

                }catch(exception ex){
                    cout << "WARNING: A tática não possui parâmetros setados." << endl;
                }
            }
        }
    }

    robosComTatica.push_back(Sistema::modeloMundo.getRoboEq(id));

    return robosComTatica;
}

template <class Poligono>
Ponto PosicionaDefesa<Poligono>::calcularAlvoPosDefesa(int id)
{
    construirPoligono();

    /// Pegando todos os robôs que estão fazendo a Defesa Area também
    vector<Robo*> robosPosicionaDefesa = getRobosComTatica(id);

    /// Calculando o alvo aonde o robô irá se posicionar no poligono
    vector<Ponto> pontosPosicionarRobos = poligono->calcularAlvoPosicionar(robosPosicionaDefesa.size());
    if(!pontosPosicionarRobos.empty()){

        /// Ordenando os dois vetores em ordem decrescente com o valor do y do ponto e posicao do robo
        sort(pontosPosicionarRobos.begin(), pontosPosicionarRobos.end(), compararPos);
        sort(robosPosicionaDefesa.begin(), robosPosicionaDefesa.end(), compararPosRobo);

        /// Analisando qual e a posicao do robo no vetor e associando a posicao do ponto do outro vetor no robo
        for(unsigned int i = 0; i < robosPosicionaDefesa.size(); i++){
            if(robosPosicionaDefesa[i]->getId() == (unsigned) id){
                return pontosPosicionarRobos[i];
            }
        }

        /// Verificando se temos apenas 1 robô usando essa tática
        //        if(pontosPosicionarRobos.size() == 1){
        //            posicaoDefesa = 0;
        //            return pontosPosicionarRobos[0];
        //        }

        //        cout << "Id do robo " << id << endl;
        //        cout << "Ponto para posicionar defesa " << pontosPosicionarRobos.size() << endl;

        //        if(posicaoDefesa != -1){

        //            if(posicaoDefesa < pontosPosicionarRobos.size()){
        //                return pontosPosicionarRobos[posicaoDefesa];
        //            }else{
        //                cout << "Nao existe um ponto nesse posicao do vetor de posicoes da defesa" << endl;
        //            }
        //        }

        //        BOOST_FOREACH(Ponto ponto, pontosPosicionarRobos){

        //            /// Verificando se o alvo final do robo que esta setado e o mesmo que um dos pontos que foi calculado pra ele se posicionar na defesa
        //            /// Isso sera feito para nao precisar calcular tudo novamente
        //            Ponto alvoFinal = Sistema::modeloMundo.getRoboEq(id)->getAlvoFinal();
        //            if(alvoFinal != CGAL::ORIGIN){
        //                if(squared_distance(alvoFinal, ponto) <= Avaliador::TOL_MESMO_ALVO*Avaliador::TOL_MESMO_ALVO){
        //                    return ponto;
        //                }
        //            }
        //        }

        //        sort(pontosPosicionarRobos.begin(), pontosPosicionarRobos.end(), compararPonto);
        //        for(int i = 0; i < pontosPosicionarRobos.size(); i++){
        //            cout << pontosPosicionarRobos[i] << endl << endl;
        //        }
        //        exit(0);

        //        /// Variável que irá armazenar o valor do alvo do robô que está executando esta tática no momento
        //        Ponto alvo;

        //        int idRoboMaisPerto; /// Id do robo que está mais perto da bola
        //        float menorDist; /// Menor distancia encontrada
        //        int posRoboVetor; /// Posição do robo no vetor dos robos, iremos usar para remover o robo que já foi setado o novo alvo
        //        float distRoboAlvo; /// Distancia do robo ao ponto de posicionamento
        //        Ponto pontoPosRobo; /// Ponto aonde o robô irá se posicionar

        //        /// Analisando cada ponto e verificando o robô que está mais perto dele
        //        int qtRobosPos = robosPosicionaDefesa.size();
        //        for(int i = 0; i < qtRobosPos; i++){

        //            /// Pegando o ponto que será analisado
        //            pontoPosRobo = pontosPosicionarRobos[i];

        //            /// Setando nas variaveis os valores do primeiro robo do vetor
        //            idRoboMaisPerto = robosPosicionaDefesa[0]->getId();
        //            menorDist = squared_distance(robosPosicionaDefesa[0]->getPosicao(), pontoPosRobo);
        //            posRoboVetor = 0;

        //            /// Distribuindo os pontos de acordo com a distância que os robôs estão de cada ponto
        //            for(unsigned int j = 1; j < robosPosicionaDefesa.size(); j++){

        //                /// Calculando a distancia do robo ao alvo
        //                distRoboAlvo = squared_distance(robosPosicionaDefesa[j]->getPosicao(), pontoPosRobo);

        //                /// Verificando se a distância desse robô ao ponto é menor que a menor distancia encontrada
        //                if(distRoboAlvo < menorDist){
        //                    idRoboMaisPerto = robosPosicionaDefesa[j]->getId();
        //                    menorDist = distRoboAlvo;
        //                    posRoboVetor = j;
        //                }
        //            }

        //            /// Removendo o robô do vetor para não ser usado mais
        //            robosPosicionaDefesa.erase(robosPosicionaDefesa.begin() + posRoboVetor);

        //            /// Verificando se o robô que foi selecionado é o mesmo que está executando essa tática no momento,
        //            /// se for iremos pegar o ponto que foi selecionado
        //            if(id == idRoboMaisPerto){
        //                alvo = pontoPosRobo;
        //                posicaoDefesa = i;
        //            }/*else{
        //                Sistema::modeloMundo.getRoboEq(idRoboMaisPerto)->setAlvoFinal(pontoPosRobo);
        //            }*/
        //        }

        //        return alvo;
    }

    return Sistema::modeloMundo.getRoboEq(id)->getPosicao();
}

template <class Poligono>
void PosicionaDefesa<Poligono>::construirPoligono()
{

    distRoboCentro = 0.0; /// Distancia que o robo vai ficar ao centro do Poligono
    centro = Ponto(0.0, 0.0); /// Posicao do centro do Poligono

    try{
        objetoRef = paramString.at(0);
        distRoboCentro = paramFloat.at(0);

        /// Verificando qual é o objeto que iremos ter como referencia para pegar o centro
        if(objetoRef == "b"){
            centro = Sistema::modeloMundo.getBola()->getPosicao();
        }else if(objetoRef == "ge"){
            centro = Sistema::modeloMundo.getCentroGolEq();
        }

    }catch(exception ex){
        cout << "WARNING: Erro ao pegar os parametros da posiciona defesa para construir o poligono." << endl;
    }

    poligono->construir(centro, distRoboCentro);
}

template <class Poligono>
int PosicionaDefesa<Poligono>::getIdMelhorRobo(vector<int>& _ids)
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

    string objetoRef="";
    try{
        objetoRef = paramString.at(0);
        //        cout << "objeto de ref: " << objetoRef << endl;
    }catch(exception ex){
        cout << "WARNING: Erro ao pegar os parametros da posiciona defesa para construir o poligono." << endl;
    }

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

    //    if(objetoRef != "b"){

    //        for(unsigned int i = 0; i < _ids.size(); i++){

    //            /// Calculando a distância do robô à região.
    //            float distRoboPonto = avaliacaoEscolhaRobo(_ids[i]);

    //            /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
    //            if(menorDistRoboRegiao > distRoboPonto){
    //                idRoboMaisPerto = _ids[i];           /// Pegando o id do robô mais perto da região.
    //                posVetorRobo = i;                    /// Pegando o indice do vetor para removermos depois o id do robo
    //                menorDistRoboRegiao = distRoboPonto; /// Setando a nova distância
    //            }
    //        }

    //        /// Se tiver robo com chute iremos analisar quais dos robos que possuem chute mais proximos da bola
    //    }else{

    //        //        cout << "analisando os robos com chute" << endl;

    //        /// Se nao tiver robos com chute iremos analisar o mais proximo da bola
    //        vector<int> idRobosComChute = Sistema::modeloMundo.getIdRobosComChute();

    //        vector<Robo*> robos = Sistema::modeloMundo.getRobosEq();

    //        for(unsigned int i = 0; i < idRobosComChute.size(); i++){

    //            if(robos[idRobosComChute[i]]->isPresente()){

    //                /// Calculando a distância do robô à região.
    //                float distRoboPonto = avaliacaoEscolhaRobo(idRobosComChute[i]);

    //                /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
    //                if(distRoboPonto < menorDistRoboRegiao){
    //                    idRoboMaisPerto = idRobosComChute[i];           /// Pegando o id do robô mais perto da região.
    //                    menorDistRoboRegiao = distRoboPonto; /// Setando a nova distância
    //                }
    //            }
    //        }

    //        //        cout << "Id do melhor robo " << idRoboMaisPerto << endl;

    //        /// Se o id for diferente de -1 e porque escolheu um robo valido pra posicionar, caso contrario e porque nao tem robo com chute no campo entao iremos pegar os outros robos
    //        if(idRoboMaisPerto == -1) {
    //            //            cout << "Nao tem robos com chute no campo" << endl;

    //            for(unsigned int i = 0; i < _ids.size(); i++){

    //                /// Calculando a distância do robô à região.
    //                float distRoboPonto = avaliacaoEscolhaRobo(_ids[i]);

    //                /// Verificando se a distância calculada é menor que a distância calculada anteriormente.
    //                if(menorDistRoboRegiao > distRoboPonto){
    //                    idRoboMaisPerto = _ids[i];           /// Pegando o id do robô mais perto da região.
    //                    posVetorRobo = i;                    /// Pegando o indice do vetor para removermos depois o id do robo
    //                    menorDistRoboRegiao = distRoboPonto; /// Setando a nova distância
    //                }
    //            }

    //        }else{

    //            /// vendo aonde está o id do robo com chute no veto de _ids dos robos
    //            for(int i=0;i<_ids.size();i++){
    //                if(_ids[i] == idRoboMaisPerto){
    //                    posVetorRobo=i;
    //                    break;
    //                }
    //            }
    //        }
    //    }

    /// Não encontrou o robo mais perto do robô que está com a bola, ou seja , problemas.
    if(idRoboMaisPerto == -1) {
        cout << " AVISO ROBO MAIS PERTO É -1" << endl;
        return -1;
    }
    _ids.erase(_ids.begin() + posVetorRobo);

    return idRoboMaisPerto;
}

template <class Poligono>
Ponto PosicionaDefesa<Poligono>::getAlvoPosDefesa()
{
    return alvoPosDefesa;
}

template <class Poligono>
bool PosicionaDefesa<Poligono>::isAtiva()
{
    return false;
}

template <class Poligono>
Tatica * PosicionaDefesa<Poligono>::getNovaInstancia()
{
    return new PosicionaDefesa;
}

template <class Poligono>
void PosicionaDefesa<Poligono>::imprimirNome()
{
    cout << "PosicionaDefesa" << endl;
}

template <class Poligono>
float PosicionaDefesa<Poligono>::getLimiarAvaliacao()
{
    return 0.0;
}
