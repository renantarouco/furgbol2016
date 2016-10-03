#include "gerenteEstado.h"

GerenteEstado::GerenteEstado(Config* _config){
    estadoAtual="halt";
    estadoAnt="";

    config = _config;
}
