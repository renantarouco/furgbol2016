#include "Agente.h"
#include<DefendeGol.h>
#include<Sistema.h>

Agente::Agente()
{
    id =0;
    posFila=0;
    iteracoes=0;
}

Agente::~Agente(){
}

void Agente::init(int _id, QMutex *_mBUS, CommunicationBUS *_bus)
{
    id = _id;

    montador.setId(id);
    navegador.setId(id);
    navegador.ativar();

    mBUS = _mBUS;
    bus = _bus;
}

void Agente::limparFilaTaticas(){
    filaTaticasPen.clear();
}

void Agente::ativarObstaculosEq(){
    navegador.ativaObstaculosRobosEq();
}

void Agente::ativarObstaculosAdv(){
    navegador.ativaObstaculosRobosEq();
}

void Agente::desativarObstaculosEq(){
    navegador.desativaObstaculosRobosEq();
}

void Agente::desativarObstaculosAdv(){
    navegador.desativaObstaculosRobosAdv();
}

void Agente::addAreaEqObstaculo(){
    navegador.adicionaObstaculo(new Area(*Sistema::modeloMundo.getCampo()->getAreaEq()));
}

void Agente::addAreaAdvObstaculo(){
    navegador.adicionaObstaculo(new Area(*Sistema::modeloMundo.getCampo()->getAreaAdv()));
}

void Agente::addBolaComoObstaculo(float dist)
{
    float squaredDist = dist*dist;
    Ponto posBola = Sistema::modeloMundo.getBola()->getPosicao();
    navegador.adicionaObstaculo(new Circulo(posBola, squaredDist));
}

unsigned int Agente::getId()
{
    return id;
}

void Agente::executarTatica(){

    if(Sistema::modeloMundo.getRoboEq(id)->isPresente()){

        /// verificando se ainda tem Tática na fila para executar
        if(!filaTaticasPen.empty()){

            /// verificando se iremos usar o navegador nessa iteração
            navegadorPronto = iteracoes++ % 10 ? true : false;

            /// pegando a tática que será executada
            Tatica* tatica = filaTaticasPen[posFila];

            /// setando a tática atual no robo que corresponde ao agente
            Sistema::modeloMundo.getRoboEq(id)->setTaticaCorrente(tatica);

            /// executando tática
            tatica->executar(this);

            cout << id << " executando tática " << tatica->getNome() << endl;

            /// setando o pacote do agente no barramento de comunicação
            addPacoteBUS();
        }else{
            cout << "id_agente: " << id << " tem fila de táticas vazia" << endl;
        }
    }
}

bool Agente::atualizarTatica(){

    /// Verificando se a jogada terminou
    if(filaTaticasPen[posFila]->verificarTermino(id))
    {
        /// Senao existir mais taticas e a tatica for a tatica ativa iremos selecionar uma nova jogada, caso contrario iremos continuar executando a tatica
        if(posFila == filaTaticasPen.size()-1){
            if(filaTaticasPen[posFila]->isAtiva())
            {
                return true;
            }
        }else{
            posFila++;
            Sistema::modeloMundo.getRoboEq(id)->setTaticaCorrente(filaTaticasPen[posFila]);
        }
    }

    return false;
}

void Agente::setPapel(vector<Tatica *>& _taticasPen){
    filaTaticasPen = _taticasPen;

    posFila=0;
    if(filaTaticasPen.size() == 0)
    {
        cout << "Atencao nenhuma tatica se aplica a esta situacao " << endl;
        return;
    }
    Sistema::modeloMundo.getRoboEq(id)->setTaticaCorrente(filaTaticasPen[posFila]);
}

bool Agente::isFilaTaticasVazia()
{
    return filaTaticasPen.empty();
}

void Agente::setPosicao(int pos)
{
    posFila =pos;

}

int Agente::getPosicao()
{

    return posFila;
}

Tatica* Agente::getTaticaCorrente()
{
    return filaTaticasPen[posFila];
}

Ponto Agente::calcAlvoFromPathPlanning(const Ponto &destino)
{
    return navegador.RRT(destino);
}

vector<Ponto> Agente::calcAlvosFromPathPlanning(const Ponto &destino)
{
    return navegador.pontosRRT(destino);
}

bool Agente::isPresente()
{
    return Sistema::modeloMundo.getRoboEq(id)->isPresente();
}

void Agente::addPacoteBUS()
{

    /// Analisando para aonde iremos enviar os pacotes do robo
    switch(ConfigComunicacao::TIPO_ROBOS){
    case REAL:
        mBUS->lock();
        bus->setPacoteRobo(id, montador.criaPacoteSerial());
        mBUS->unlock();
        break;

    case SIMULADOR3D:
        mBUS->lock();
        bus->setPacoteRobo(id, montador.criaPacoteGrSim());
        mBUS->unlock();
        break;

    case SIMULADOR2D:
        montador.calculaVelLinear(); /// calculando a velocidade que o robo tera que ter
        break;
    }
}

void Agente::limparPacote(){

    /// deletando o pacote do agente atual para que não seja enviado
    mBUS->lock();
    bus->limparPacoteRobo(id);
    mBUS->unlock();
}

void Agente::setNavegador(Navegador _navegador){
    navegador = _navegador;
}

Navegador* Agente::getNavegador(){
    return &navegador;
}

void Agente::operator=(const Agente& a){
    id = a.id;
}

ostream& operator<<(ostream& os, const Agente& a){
    //    os <<"agente "<< a.getId() <<endl;
    return os;
}

