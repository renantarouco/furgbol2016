#include "Serial.h"

using namespace boost::asio;

//! passar para as configurações da interface
const int NUM_REPETICOES = 2;       //se possivel eliminar essa variavel

Serial::Serial() : io() , serial(io) , buf(8)
{
    dispositivo = "/dev/ttyUSB0";
    baud_rate = 115200;
    //baud_rate=115000;

}

void Serial::setDispositivo(std::string _dispositivo){
    dispositivo = _dispositivo;
}

Serial::~Serial()
{
    close();
}

bool Serial::open()
{
    close();

    try{
        //! Abre a porta serial
        serial.open(dispositivo);

        cout << dispositivo << endl;

        /// Configurando a porta serial caso de certo abrir
        return configurar();

    }catch(boost::system::system_error error){
        cout << "Erro ao abrir o dispositivo serial. " << error.what() << endl;
    }

    return false;
}

bool Serial::configurar(){

    try{
        /**
           Configura o baud rate
        */
        serial.set_option(serial_port_base::baud_rate(baud_rate));

        /**
           Configura a paridade
           none -- sem paridade
           odd  -- paridade impar
           even -- paridade par
        */
        //serial.set_option(serial_port_base::parity(serial_port_base::parity::type::none));

        /**
           Configura o numero de stop bits
           one -- um stop bit
           onepointfive -- 1.5 stop bits
           two -- dois stop bits
        */
        //serial.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::type::one));

        /**
           Configura o tamanho do caractere
        */
        unsigned int tam = 8;
        serial.set_option(serial_port_base::character_size(tam));

        return true;

    }catch(boost::system::system_error error){
        cout << "Erro ao configurar o dispositivo serial. " << error.what() << endl;
    }

    return false;
}

void Serial::close()
{
    /// Se a serial estiver aberta iremos fecha-la
    if(serial.is_open()){
        serial.close();
    }
}

//!
bool Serial::write(const ProtocoloSerial & pacote)
{
    vector <unsigned char> buf(8,0);

//    cout << pacote << endl;

    //a funcao serializa da classe ProtocoloSerial deve ser reescrita para receber um vector<unsigned char> & buffer
    pacote.serializa(buf);

//    cout << "Enviou Dados: ";
//    for(unsigned int i=0;i<buf.size();i++){
//        cout << (int)buf[i] << " ";
//    }
//    cout << endl;

    for(int i=0;i<NUM_REPETICOES;i++){
        //analizar se essa funcao ja e suficiente ou se e necessario ser sincrono, usando a funcao write
        serial.write_some(buffer(buf, buf.size()));
    }

    return true;

}

bool Serial::write(const vector <unsigned char> &buf){

    //analizar se essa funcao ja e suficiente ou se e necessario ser sincrono, usando a funcao write
    serial.write_some(buffer(buf, buf.size()));

    return true;

}
