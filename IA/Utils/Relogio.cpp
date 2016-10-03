#include "Relogio.h"

#include <sys/time.h>

Relogio::Relogio()
{
    tempoInicial = getTempoDoDia();
}

Relogio::~Relogio()
{
}

double Relogio::getTempoPassado()
{
    return getTempoDoDia() - tempoInicial;
}

double Relogio::getTempoDoDia()
{
    struct timeval tv;
    gettimeofday(&tv,0);

    return (double)tv.tv_sec + (double)tv.tv_usec*0.000001;
}

void Relogio::setTempoInicial(double t)
{
    tempoInicial = t;
}

