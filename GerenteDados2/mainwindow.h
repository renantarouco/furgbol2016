#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "definitions.h"
#include "gerenteVisao.h"
#include "gerenteEstado.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void errorReferee(QAbstractSocket::SocketError error);
    void errorVision(QAbstractSocket::SocketError error);

    void on_pbStartStop_clicked();

    void readRefereeData();
    void readVisionData();

    void send_packet_ia();

    void on_rbRightColor_clicked(bool checked);
    void on_rbLeftColor_clicked(bool checked);
    void on_rbBlueColor_clicked(bool checked);
    void on_rbYellowColor_clicked(bool checked);
    void on_sbIDGoleiro_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    Config config;

    bool receivingVisionPacket;
    GerenteVisao* gerenteVisao;
    QUdpSocket* multicast_vision;

    bool receivingRefereePacket;
    GerenteEstado* gerenteEstado;
    QUdpSocket* multicast_referee;

    QUdpSocket* socket_ia;
    SSL_Referee pacoteReferee;
};

#endif // MAINWINDOW_H
