#ifndef SERIAL_H
#define SERIAL_H

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>

#include <ProtocoloSerial.h>
/**
 * Classe que se comunica com o robo via porta serial
 */

class Serial
{
public:
    Serial();
    ~Serial();
    void setDispositivo(std::string _dispositivo);
    bool open();
    void close();
    bool write(const vector <unsigned char> & pacote);
    bool write(const ProtocoloSerial & pacote);

private:
    bool configurar();

    boost::asio::io_service io;
    boost::asio::serial_port serial;

    std::string dispositivo;
    vector<unsigned char> buf;

    int baud_rate;
};
#endif //SERIAL_H

