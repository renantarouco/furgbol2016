#include <QCoreApplication>
#include "Sistema.h"
#include "Comunicador.h"
#include "Carregador.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    /// carregando as constantes
//    Config config;
//    config.load();

    ConfigComunicacao::load();
    Config::load();

    /// variáveis utilizadas na IA
    QMutex mBUS; ///< Mutex para controlar o acesso ao objeto communcation bus
    CommunicationBUS bus; /// barramento utilizado na comunicação entre a thread principal e a de comunicacao;

    /// iniciando a thread do Sistema
    Sistema sistema;
    sistema.init(&mBUS, &bus);
    sistema.start();

    /// iniciando a thread do comunicador que é aonde iremos enviar os pacotes para os robos ou simuladores
    Comunicador comunicador;
    comunicador.init(&mBUS, &bus);
    comunicador.start();

    /// loop da thread do main
    a.exec();

    /// parando as threads
    sistema.stop();
    comunicador.stop();

    return 0;
}
