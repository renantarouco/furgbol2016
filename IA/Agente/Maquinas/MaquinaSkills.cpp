#include "MaquinaSkills.h"

MaquinaSkills::MaquinaSkills()
{
}

MaquinaSkills::~MaquinaSkills(){
}

bool MaquinaSkills::parametroExiste(Parametro p)
{
    for(unsigned int i = 0; i < parametros.size(); i++){
        if(p == parametros[i])
            return true;
    }

   return false;
}
