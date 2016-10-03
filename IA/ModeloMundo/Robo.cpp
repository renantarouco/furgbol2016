#include "Robo.h"

Robo::Robo(){
    id = 0;
    present = false; // Avaliar a implicação destas inicialização no inicio do jogo
    posicao = CGAL::ORIGIN;
    orientacao = 0;
    velocidade = CGAL::NULL_VECTOR;
    velAngular = 0.0;
    papel = "none";
    skill = "none";
    taticaCorrente = NULL;
    tocarBola = true;
    temChute = true;
    temDrible = true;
}

void Robo::init(int _id, bool _temChute){
    id = _id;
    present = false; // Avaliar a implicação destas inicialização no inicio do jogo
    posicao = CGAL::ORIGIN;
    orientacao = 0;
    velocidade = CGAL::NULL_VECTOR;
    velAngular = 0.0;
    papel = "none";
    skill = "none";
    taticaCorrente = NULL;
    tocarBola = true;
    temChute = _temChute;
    temDrible = true;
}

void Robo::setTemChute(bool _temChute)
{
    temChute = _temChute;
}

bool Robo::isTemChute()
{
    return temChute;
}

void Robo::setTemDrible(bool _temDrible)
{
    temDrible = _temDrible;
}

bool Robo::isTemDrible()
{
    return temDrible;
}

Tatica* Robo::getTaticaCorrente(){
    return taticaCorrente;
}

string Robo::getSkill(){
    return skill;
}

void Robo::setAlvoAprox(const Ponto& _alvoAprox){
    alvoAprox = _alvoAprox;
}

void Robo::setTaticaCorrente(Tatica* _tatica){
    taticaCorrente = _tatica;

}

void Robo::setPacotePathPlanning(const PacotePathPlanning & _planning){
    planning.CopyFrom(_planning);
}

PacotePathPlanning Robo::getPacotePathPlanning() const{
    return planning;
}

void Robo::setDados(const Ponto &_pos, float _orientacao)
{
    present = true;

    /// setando a posicao
    posicaoAnt = posicao;
    posicao = _pos;

    /// setando orientacao
    vetOrientacao = Vetor(cos(_orientacao),sin(_orientacao));
    orientacao =_orientacao;
    comando.setOrientacao(orientacao);
}

void Robo::setPresent()
{
    present = true;
}

void Robo::dontPresent()
{
    present = false;
}

void Robo::setSendoMarcado(bool _sendoMarcado)
{
    sendoMarcado = _sendoMarcado;
}

bool Robo::isSendoMarcado()
{
    return sendoMarcado;
}

void Robo::setId(int _id){
    id=_id;
}

bool Robo::isPresente(){
    return present;
}

void Robo::setPresenca(bool _presente){
    present= _presente;
}

void Robo::setPosicao(const Ponto &_posicao){
    posicaoAnt = posicao; /// setando a posicao atual na anterior
    posicao=_posicao; /// setando a nova posicao
}

void Robo::setPosicaoAnt(const Ponto &_posicaoAnt){
    posicaoAnt = _posicaoAnt;
}

void Robo::setOrientacao(float _orientacao)
{
    vetOrientacao = Vetor(cos(_orientacao),sin(_orientacao));
    orientacao =_orientacao;
    comando.setOrientacao(orientacao);
}

void Robo::setAlvo(const Ponto& _alvo)
{
    comando.setAlvo(_alvo);
}
void Robo::setAlvoFinal(const Ponto &_alvoFinal)
{
    comando.setAlvoFinal(_alvoFinal);
}

Ponto Robo::getAlvoFinal(){
    return comando.getAlvoFinal();
}

void Robo::setAlvoChute(const Ponto& _alvoChute)
{
    comando.setAlvoChute(_alvoChute);
}

void Robo::setAlvoOrientacao(const Ponto &_alvoOrientacao)
{
    comando.setAlvoOrientacao(_alvoOrientacao);
}

Ponto Robo::getAlvoOrientacao()
{
    return comando.getAlvoOrientacao();
}

void Robo::setNomeSkill(const string &_skill)
{
    skill = _skill;
}

int Robo::getId()
{
    return id;

}

Ponto Robo::getAlvoAprox()
{

    return alvoAprox;
}

Comando Robo::getComando()
{
    return comando;
}
void Robo::setComando(const Comando &_comando)
{
    comando=_comando;
}
void Robo::setAlvoMudou(bool _alvoMudou)
{
    alvoMudou =_alvoMudou;
}

void Robo::setDistCarregouBola(float _distCarregouBola){
    distCarregouBola = _distCarregouBola;
}

void Robo::setVelocidade(const Vetor & _vel){
    velocidade = _vel;
}

void Robo::setVelAngular(float _velAngular){
    velAngular = _velAngular;
}


Ponto Robo::getPosicao()
{
    return posicao;
}

Ponto Robo::getPosicaoAnt()
{
    return posicaoAnt;
}

Vetor Robo::getVelocidade(){
    return velocidade;
}

float Robo::getVelAngular(){
    return velAngular;
}

Vetor Robo::getVetorOrientacao()
{
    return vetOrientacao;
}

float Robo::getOrientacao(){
    return orientacao;
}

string Robo::getNomeTaticaCorrente(){
    return taticaCorrente != NULL ? taticaCorrente->getNome() : "";
}

string Robo::getPapel(){
    return papel;
}

bool Robo::isTocarBola(){
    return tocarBola;
}
bool Robo::isAlvoMudou()
{
    return alvoMudou;
}

float Robo::getDistCarregouBola(){
    return distCarregouBola;
}

void Robo::setTocarBola(bool _tocarBola){
    this->tocarBola = _tocarBola;
}
