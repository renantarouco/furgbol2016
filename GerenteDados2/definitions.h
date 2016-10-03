#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <QDate>
#include <QMessageBox>
#include <QDateTime>
#include <QDir>
#include <QFileDialog>
#include <QListWidgetItem>
#include <QLabel>
#include <QGLWidget>
#include <QMenu>
#include <QMouseEvent>
#include <QTimer>
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QThread>
#include <QCheckBox>
#include <QTreeWidgetItem>
#include <QUdpSocket>
#include <QSettings>
#include <QMutex>

#include <opencv/cxcore.h>
#include <opencv/cv.h>

#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <string>
#include <iostream>
#include <QThread>

/// OPENGL
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "mensagem_gerente_dados.pb.h"

using namespace std;
using namespace cv;

/// estrutura criada para auxilizar na analise dos pacotes enviados pela SSL vision
struct RoboSSL{
    RoboSSL():achado(false){}
    float x, y, orientation, confidence;
    bool achado;
};

enum CorEquipe {
    Amarelo=0, Azul=1
};

enum LadoCampo{
    ESQUERDO=0, DIREITO=1
};

enum FonteDados{
    SSL_VISION=0, SIMULADOR=1
};

const int NUM_MAX_ROBOS = 12;
const int NUM_ROBOS_JOGANDO = 6;

/// ROBO
const int NUM_FRAMES_ACHADO = 10;
const int NUM_FRAMES_NAO_ACHADO = 10;

/// global functions
static float squaredDistance(const Mat_<float> &a,const  Mat_<float> &b){
    Mat_<float> aux;
    float sum;
    aux = a-b;
    sum = aux.dot(aux);
    return sum;
}

#endif // DEFINITIONS_H
