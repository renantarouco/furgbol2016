#include "DadosSensoriais.h"

DadosSensoriais::DadosSensoriais()
{
}
ostream & operator <<(ostream &os, const DadosSensoriais &d)
{
    os << "Dados Sensoriais:" << endl;
    if(d.bolaPertoParaChute){
        os << "bolaPertoParaChute" <<endl;
    }
    if(d.dentroRaioAprox){
        os << "dentroRaioAprox" <<endl;
    }
    if(d.deFrenteParaBola){
        os << "deFrenteParaBola" <<endl;
    }
    if(d.comAnguloDeChute){
        os << "comAnguloDeChute" <<endl;
    }
    if(d.alvoMudou){
        os << "alvoMudou" << endl;
    }

    if(d.carregarBola){
        os << "limiteCarregarBola" <<endl;
    }
    if(d.noAlvoMarcado){
        os << "noAlvoAproxMarcado" <<endl;
    }
//    if(d.girarAntiHorario){
//        os << "alvoPertoAntiHorario" << endl;
//    }
    if(d.girarHorario){
        os << "alvoPertoHorario" << endl;
    }

    return os;
}
