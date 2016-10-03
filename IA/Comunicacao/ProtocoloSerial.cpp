#include "ProtocoloSerial.h"
#include "Sistema.h"

ProtocoloSerial::ProtocoloSerial(): velocidadePercentualRodas(4,0) , direcaoRodas(4,HORARIO)
{
    enableChute = 0;
    nivelChute = 0;
    tipoChute = Comando::SEM_CHUTE;
    velocidadePercentualDriblador = 0;
    direcaoDriblador = ANTI_HORARIO;
    id = 128;

    enableDrible = false;

}

/**
\brief Seta o id do robo

 */
void ProtocoloSerial::setId(unsigned char _id){
    switch(_id){
    case 0:
        id = 128;
        break;
    case    1:
        id = 129;
        break;
    case 2:
        id = 130;
        break;
    case 3:
        id = 131;
        break;
    case 4:
        id = 132;
        break;
    }

    /// TODO Colocar os outros ids
}

void ProtocoloSerial::limpaPacote(){

    fill(velocidadePercentualRodas.begin(),velocidadePercentualRodas.end(),0);

    velocidadePercentualDriblador = 0;

    tipoChute = Comando::SEM_CHUTE;

    nivelChute = 0;
}

/**
\brief Seta a velocidade percentual das rodas do robô

\param numRoda: numero da roda a ser setada a velocidade
\param vel: velocidade requerida.

A velocidade varia de 0 a 100
 */
void ProtocoloSerial::setVelocidadePercentualRodas(int numRoda, unsigned char _vel){
    velocidadePercentualRodas[numRoda] = _vel;
}

/**
\brief Seta as velocidades percentuais das rodas do robô

\param vel: vetor com todas as velocidades percentuais


A velocidades variam de 0 a 100
 */
void ProtocoloSerial::setVelocidadePercentualRodas(vector <unsigned char> _vel){
    velocidadePercentualRodas = _vel;
}

/**
\brief Seta as direção de cada roda do robô.

\param numRoda: numero da roda a ser setada a direção
\param _dir: direção: HORARIO ou ANTI_HORARIO

 */
void ProtocoloSerial::setDirecaoRodas(int numRoda, Direcao _dir){
    direcaoRodas[numRoda] = _dir;
}


/**
\brief Seta as direções das rodas do robô

\param _dir: vetor com todas as direções

Valores possíveis para a direção: HORARIO ou ANTI_HORARIO
*/

void ProtocoloSerial::setDirecaoRodas(vector<Direcao> _dir){
    direcaoRodas = _dir;
}

/**
\brief Seta a velocidade percentual do driblador

\param _vel: velocidade percentual do driblador

A velocidades variam de 0 a 100
*/
void ProtocoloSerial::setVelocidadePercentualDriblador(unsigned char _vel){
    velocidadePercentualDriblador = _vel;
}

/**
\brief Seta as direção de rotação do driblador.

\param _dir: direção: HORARIO ou ANTI_HORARIO

 */
void ProtocoloSerial::setDirecaoDriblador(Direcao _dir){
    direcaoDriblador = _dir;
}

/**
\brief Seta qual o tipo do chute

\param _tipoChute: tipo do chute: CHUTE_ALTO, CHUTE_BAIXO ou SEM_CHUTE

*/

void ProtocoloSerial::setTipoChute(Comando::TipoChute _tipoChute){
    tipoChute = _tipoChute;
}

/**
\brief Seta o nível percentual do chute

\param _nivelPercentual: nivel do chute, varia de 0 a 100

*/
void ProtocoloSerial::setNivelChute(unsigned char _nivelPercentual){

    //nivel com 4 bits, possibilitando 16 níveis de chute;

    //! VERIFICAR ESSA CONTA
    nivelChute = (unsigned char)(_nivelPercentual*15/100);

}

void ProtocoloSerial::setEnableDrible(bool _enable)
{
    enableDrible = _enable;
}

void ProtocoloSerial::setEnableChute(bool _enable){
    if(_enable){
        enableChute = 1;
    }
    else{
        enableChute = 0;
    }
}


/**
\brief Função para serializar os dados para envio serial

1 | ID
0 | Velocidade Motor 1
0 | Velocidade Motor 2
0 | Velocidade Motor 3
0 | Velocidade Motor 4
0 | Velocidade Driblador
0 | X | X | DirDR | Dir4 | Dir3 | Dir2 | Dir1
0 | X | Enable | Modo | Força

\return dados serializados.
*/
void  ProtocoloSerial::serializa(vector <unsigned char> &buffer) const{

    fill(buffer.begin(), buffer.end(), 0);

    buffer[0] = id;

    for(int i=1;i<=4;i++)
    {
        buffer[i] = velocidadePercentualRodas[i-1];
        //        if(buffer[i]==10)
        //            buffer[i] = 9;
    }

    // O robo nao pode chutar com o driblador ligado!! Risco de queimar o drible
    if(enableDrible && !enableChute)
    {
        buffer[5] = 70;
    }
    else
    {
        buffer[5] = 0;
    }


    //    bitsChute = 0;
    //    Direcao dir;
    //    // Adaptado temporariamente
    //    if(tipoChute==Comando::SEM_CHUTE){
    //        buffer[5] = 0;
    //    }else if(tipoChute==Comando::CHUTE_BAIXO){
    //        buffer[5] = 50;
    //        dir = HORARIO;
    //    }else if(tipoChute==Comando::CHUTE_ALTO){
    //        buffer[5] = 50;
    //        dir = HORARIO;
    //    }

    //    cout << "Drible = "<< direcaoDriblador << " e " << enableDrible << " chute " << (unsigned)enableChute <<  endl;

    //! O byte de direção tera a seguinte configuração =|_ |_ |_ |dirDri |dir3 |dir2 |dir1 |dir0|
    buffer[6] = 0;
    //    buffer[6] = dir << 4 | direcaoRodas[3] << 3 | direcaoRodas[2] << 2 | direcaoRodas[1] << 1 | direcaoRodas[0];
    buffer[6] = direcaoDriblador << 4 | direcaoRodas[3] << 3 | direcaoRodas[2] << 2 | direcaoRodas[1] << 1 | direcaoRodas[0];

    unsigned char bitsChute;
    if(tipoChute==Comando::SEM_CHUTE){
        bitsChute = 0;
    }else if(tipoChute==Comando::CHUTE_BAIXO){
        bitsChute =  2;
    }else if(tipoChute==Comando::CHUTE_ALTO){
        bitsChute = 3;
    }

    bitsChute = bitsChute | enableChute << 2 ;

    //   buffer[7] = 0b01100000 | nivelChute;
    buffer[7] = bitsChute << 4 | nivelChute;


}
ostream & operator <<(std::ostream &out, ProtocoloSerial pct)
{
    out << "Id = " << static_cast<int>(pct.id) << endl;
    out << "Velocidades = ";
    for(unsigned int i=0;i< pct.velocidadePercentualRodas.size();i++){
        out << " " << static_cast<int>(pct.velocidadePercentualRodas[i]);
    }
    out << endl;
    out << "Drible = " << pct.enableDrible << endl;

    return out;

}

