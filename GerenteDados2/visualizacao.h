#ifndef VISUALIZACAO_H
#define VISUALIZACAO_H

#include "definitions.h"
#include "bola.h"
#include "robo.h"
#include "config.h"

/// valores usados para compilar os shapes no opengl
#define SNUM0 1
#define SNUM1 2
#define SNUM2 3
#define SNUM3 4
#define SNUM4 5
#define SNUM5 6
#define SNUM6 7
#define SNUM7 8
#define SNUM8 9
#define SNUM9 10
#define SNUM10 11
#define SNUM11 12
#define SCAMPO 20
#define SBOLA 30
#define SROBO 40
#define SOFF 50
#define SCHUTE 60
#define SCONTORNO 70

class Visualizacao : public QGLWidget
{
    Q_OBJECT
public:
    /// variaveis auxiliares
    double zoomx, zoomy;
    double ballx, bally;
    QTimer timer;

    Bola* bola;
    vector<Robo>* robosEq; //Robos da Equipe
    vector<Robo>* robosAdv; //Robos Adversários

    Config* config;

    explicit Visualizacao(QWidget *parent = 0);
    ~Visualizacao();

    void renderBallGL();
    void renderSingleRobotGL(int id, Robo& r, bool equipeAzul);
    void renderAllRobotsGL();
    void renderFieldGL();

    void compileFieldShapeGL(double width, double height);
    void compileBallShapeGL();
    void compileNumbersGL();
    void compileRobotShapeGL();

    void initializeGL();//inicializa painel opengl
    void resizeGL(int w, int h);//é chamada para redimencionar painel opengl
    void paintGL();//redesenha os robo, a bola e o texto ao lado
};

#endif // VISUALIZACAO_H
