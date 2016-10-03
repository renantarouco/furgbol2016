#ifndef DEFINITIONS_H
#define DEFINITIONS_H

/**
 * Arquivo para serem definidos todos os tipos externos a arquitetura.
 */
#include <vector>
#include <list>
#include <map>
#include <iostream>
#include <pthread.h>
#include <cstdlib>
#include <cstdio>
#include <ctype.h>
#include <sstream>
#include <utility>
#include <stdexcept>
#include <errno.h>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <boost/foreach.hpp>
#include <opencv/cv.h>
#include <fcntl.h>
#include <termios.h>
#include <limits>

/********QTLIBS*************/
#include <QString>
#include <QSettings>
#include <QHostAddress>
#include <QUdpSocket>

/********CGAL**********/
#include <CGAL/enum.h>
#include <CGAL/Cartesian.h>
#include <CGAL/intersections.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Circular_kernel_intersections.h>
#include <CGAL/Circular_kernel_2.h>
#include <CGAL/Algebraic_kernel_for_circles_2_2.h>
#include <CGAL/squared_distance_2.h>
#include <CGAL/Circular_arc_point_2.h>

using namespace std;

/************REDEFINIÇÕES DA CGAL *********/
typedef CGAL::Cartesian<float>                                                                  Cartesiano;
typedef CGAL::Circular_kernel_2<Cartesiano ,  CGAL::Algebraic_kernel_for_circles_2_2 <float> >  Circular_k;
typedef CGAL::Point_2<Circular_k>                                                               Ponto;
typedef CGAL::Vector_2<Circular_k>                                                              Vetor;
typedef CGAL::Segment_2<Circular_k>                                                             Segmento;
typedef CGAL::Circular_arc_2<Circular_k>                                                        Arco;
typedef CGAL::Line_2<Circular_k>                                                                Reta;
typedef CGAL::Iso_rectangle_2<Circular_k>                                                       Retangulo;
typedef CGAL::Triangle_2<Circular_k>                                                            Triangulo;
typedef CGAL::Circular_arc_point_2<Circular_k>                                                  ArcPonto;
typedef CGAL::Object                                                                            Objeto;
typedef CGAL::Exact_predicates_inexact_constructions_kernel                                     K;
//typedef CGAL::Circle_2<Circular_k>		Circulo;

typedef pair<int, Ponto> IntPonto; ///< pair que indica um valor inteiro (id do robo, score chute) e um ponto (alvo, posicao)
typedef pair<int, float> IdDistancia; ///< pair que indica uma distancia e provavelmente o id do robo

enum TipoRobos {
    REAL=0, SIMULADOR3D=1, SIMULADOR2D=2
};

enum Direcao{
    HORARIO =0, ANTI_HORARIO = 1
};

struct Address {
    string ip;
    int porta;
    QHostAddress host;

    Address(string _ip="127.0.0.1", int _porta=4444){
        ip = _ip;
        host = QHostAddress(ip.c_str());
        porta = _porta;
    }

    void setHost(string _ip, int _porta){
        ip = _ip;
        porta = _porta;
        host = QHostAddress(ip.c_str());
    }
};

/// DEFINIÇÕES GERAIS
const string PATH_CONFIG = "../IA/config/";
const int NUM_MAX_ROBOS = 12;
const int NUM_MAX_ROBOS_JOGANDO = 6;

#endif
