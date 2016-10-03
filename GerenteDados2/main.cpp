#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //    GerenteDados gerenteDados;
    //    gerenteDados.load();

    //    /// iniciando a gerenciamento dos dados da visao e do estado do jogo
    //    gerenteDados.start();
    //    gerenteDados.wait();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
