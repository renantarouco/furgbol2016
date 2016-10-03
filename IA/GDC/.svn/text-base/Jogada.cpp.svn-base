#include "Jogada.h"

Jogada::Jogada(){
    papeis.resize(NUM_MAX_ROBOS_JOGANDO-1); /// diminuindo 1 por causa do goleiro
}

unsigned int Jogada::getId(){
    return id;
}

void Jogada::setId(unsigned int id){
    this->id = id;
}

string Jogada::getNome(){
    return nome;
}

void Jogada::setNome(string nome){
    this->nome = nome;
}

map<string, bool> Jogada::getCondAplicavel(){
    return condAplicavel;
}

void Jogada::addCondAplicavel(string chave, bool result){
    this->condAplicavel[chave] = result;
}

vector<Finaliza> Jogada::getCondFinaliza(){
    return condFinaliza;
}

void Jogada::addCondFinaliza(string modo, map<string, bool> condicoes){
    Finaliza finaliza;
    finaliza.modo = modo;
    finaliza.condicoes = condicoes;
    this->condFinaliza.push_back(finaliza);
}

double Jogada::getTimeOut(){
    return timeOut;
}

void Jogada::setTimeOut(double timeOut){
    this->timeOut = timeOut;
}

string Jogada::getCondRobosAdv(int posRoboAdv){

    /// Verificando se a posicao do robo e valida
    if(posRoboAdv != -1 && (uint) posRoboAdv < condRoboAdv.size())
        return condRoboAdv.at(posRoboAdv);
    else
        cout << "Posicao do robo adv no vetor de condicoes e invalido" << endl;

    return "";
}

vector<string> Jogada::getCondRobosAdv(){
    return condRoboAdv;
}

void Jogada::addCondRoboAdversario(int posVetor, string condicao){
    condRoboAdv.resize(posVetor+1);
    condRoboAdv[posVetor] = condicao;
}

vector<Tatica*> Jogada::getPapel(int numPapel){
    return papeis.at(numPapel);
}

void Jogada::addTaticaPapel(int numPapel, Tatica *tatica){

    /// adicionando a tatica no papel
    papeis.at(numPapel).push_back(tatica);
}

map<string,bool> Jogada::getPosCond(){
    return posCondicoes;
}

void Jogada::addPosCond(string posCond, bool valor){
    posCondicoes[posCond] = valor;
}

void Jogada::setTaticaGoleiro(Tatica* _taticaGoleiro){
    taticaGoleiro = _taticaGoleiro;
}

Tatica* Jogada::getTaticaGoleiro(){
    return taticaGoleiro;
}
