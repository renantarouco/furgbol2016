#include "visualizacao.h"

Visualizacao::Visualizacao(QWidget *parent) : QGLWidget(QGLFormat(QGL::DoubleBuffer), parent)
{
    /// toda vez que o timer gerar um evento timeout iremos atualizar a janela de visualização
    connect(&timer, SIGNAL(timeout()), this, SLOT(update()));
}

Visualizacao::~Visualizacao(){
}

void Visualizacao::compileFieldShapeGL(double width, double height){
    // single size - standard
    double LENGTH_FIELD= 4.05;
    double WIDTH_FIELD= 6.05;
    double RAIO_AREA= 0.8;
    double RAIO_CIRCULO_CENTRAL= 0.5;
    double LINHA_AREA= 0.35;
    double WIDTH_TRAVE= 0.7;
    double LENGTH_TRAVE= 0.25;


    /********************* COMPILANDO OS SHAPES DO CAMPO ***************/
    glNewList(SCAMPO, GL_COMPILE);

    /// criando o retangulo com a cor verde do campo
    glEnable(GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(0.0f, 0.4f, 0.0f, 0.7f); /// verde escuro

    /// desenhando o retangulo do campo
    glBegin(GL_TRIANGLE_FAN);

    /// quatro cantos do campo
    glVertex2f(-width, height);
    glVertex2f(width, height);
    glVertex2f(width, -height);
    glVertex2f(-width, -height);

    glEnd();
    glDisable(GL_BLEND); /// finalizando o desenho do retangulo do campo

    /// criando as linhas de marcacao das areas do campo
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINE_LOOP);

    /// laterais do campo
    glVertex2f(-WIDTH_FIELD/2.0, LENGTH_FIELD/2.0);
    glVertex2f(WIDTH_FIELD/2.0, LENGTH_FIELD/2.0);
    glVertex2f(WIDTH_FIELD/2.0, -LENGTH_FIELD/2.0);
    glVertex2f(-WIDTH_FIELD/2.0, -LENGTH_FIELD/2.0);

    glEnd(); /// finalizando o desenho das laterais

    /// desenhando a linha central
    glBegin(GL_LINES);
    glVertex2f(0.0, -LENGTH_FIELD/2.0);
    glVertex2f(0.0, LENGTH_FIELD/2.0);
    glEnd();

    /// desenhando circulo central
    glBegin(GL_LINE_LOOP);
    double angle;
    for (int i = 0;i < 360.0; i++)
    {
        angle = 2*M_PI*i/360.0;
        glVertex2f(RAIO_CIRCULO_CENTRAL*cos(angle),RAIO_CIRCULO_CENTRAL*sin(angle));
    }
    glEnd();
    /// fim do circulo central

    /// trave esquerda
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-WIDTH_FIELD/2.0, WIDTH_TRAVE/2.0);
    glVertex2f(-LENGTH_TRAVE-WIDTH_FIELD/2.0, WIDTH_TRAVE/2.0);
    glVertex2f(-LENGTH_TRAVE-WIDTH_FIELD/2.0, -WIDTH_TRAVE/2.0);
    glVertex2f(-WIDTH_FIELD/2.0, -WIDTH_TRAVE/2.0);
    glEnd();
    /// fim da trave esquerda

    /// trave direita
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(WIDTH_FIELD/2.0, WIDTH_TRAVE/2.0);
    glVertex2f(LENGTH_TRAVE+WIDTH_FIELD/2.0, WIDTH_TRAVE/2.0);
    glVertex2f(LENGTH_TRAVE+WIDTH_FIELD/2.0, -WIDTH_TRAVE/2.0);
    glVertex2f(WIDTH_FIELD/2.0, -WIDTH_TRAVE/2.0);
    glEnd();
    /// fim da trave direita

    /// area esquerda
    /// linha da frente da area
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(RAIO_AREA - WIDTH_FIELD/2.0, LINHA_AREA/2.0);
    glVertex2f(RAIO_AREA - WIDTH_FIELD/2.0, -LINHA_AREA/2.0);
    glEnd();

    /// semicirculo inferior
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 90;i++)
    {
        angle = -2*M_PI*i/360;
        glVertex2f(RAIO_AREA*cos(angle)-WIDTH_FIELD/2.0, RAIO_AREA*sin(angle)-LINHA_AREA/2.0);
    }
    glEnd();

    /// semicirculo superior
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 90;i++)
    {
        angle = 2*M_PI*i/360;
        glVertex2f(RAIO_AREA*cos(angle)-WIDTH_FIELD/2.0, RAIO_AREA*sin(angle)+LINHA_AREA/2.0);
    }
    glEnd();
    /// fim da area esquerda

    /// area direita
    /// linha da frente da area
    glColor4f(1.0f,1.0f,1.0f,1.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-RAIO_AREA + WIDTH_FIELD/2.0, LINHA_AREA/2.0);
    glVertex2f(-RAIO_AREA + WIDTH_FIELD/2.0, -LINHA_AREA/2.0);
    glEnd();

    /// semicirculo inferior
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 90;i++)
    {
        angle = -2*M_PI*i/360;
        glVertex2f(-RAIO_AREA*cos(angle)+WIDTH_FIELD/2.0, RAIO_AREA*sin(angle)-LINHA_AREA/2.0);
    }
    glEnd();

    /// semicirculo superior
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < 90;i++)
    {
        angle = 2*M_PI*i/360;
        glVertex2f(-RAIO_AREA*cos(angle)+WIDTH_FIELD/2.0, RAIO_AREA*sin(angle)+LINHA_AREA/2.0);
    }
    glEnd();
    /// fim da area direita

    glEndList();
    /********************* FIM DA COMPILACAO DO CAMPO ***************/}

void Visualizacao::compileBallShapeGL()
{
    double cx=0.0,cy=0.0;
    double theta=0.0;
    double BALL_RADIUS = 0.0215;
    double K_INCREMENT = 2.0f * M_PI / 360.0;

    // compilando shape da bola
    glNewList(SBOLA, GL_COMPILE);
    glColor4f(1.0f, 0.2f, 0.0f, 1.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360.0; ++i){
        double vx =cx + BALL_RADIUS*cosf(theta);
        double vy =cy + BALL_RADIUS*sinf(theta);

        glVertex2f(vx, vy);
        theta += K_INCREMENT;
    }
    glEnd();
    glEndList();
    // fim da compilação da bola
}

void Visualizacao::compileNumbersGL()
{
    double const tamSeg=0.03;

    //COMECO NUMEROO
    glNewList(SNUM0,GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0,tamSeg);
    glVertex2f(-tamSeg,tamSeg);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(-tamSeg,-tamSeg);
    glVertex2f(0.0,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO0

    //COMECO NUMERO1
    glNewList(SNUM1,GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0,tamSeg);
    glVertex2f(0.0,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO1

    //COMECO NUMERO2
    glNewList(SNUM2,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,tamSeg);
    glVertex2f(0.0,tamSeg);
    glVertex2f(0.0,0.0);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(-tamSeg,-tamSeg);
    glVertex2f(0.0,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO2

    //COMECO NUMERO3
    glNewList(SNUM3,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,tamSeg);
    glVertex2f(0.0,tamSeg);
    glVertex2f(0.0,0.0);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,-tamSeg);
    glVertex2f(-tamSeg,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO3

    //COMECO NUMERO4A
    glNewList(SNUM4,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,tamSeg);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(0.0,0.0);
    glVertex2f(0.0,tamSeg);
    glVertex2f(0.0,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO4

    //COMECO NUMERO5
    glNewList(SNUM5,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,-tamSeg);
    glVertex2f(0.0,-tamSeg);
    glVertex2f(0.0,0.0);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(-tamSeg,tamSeg);
    glVertex2f(0.0,tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO5

    //COMECO NUMERO6
    glNewList(SNUM6,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,-tamSeg);
    glVertex2f(0.0,-tamSeg);
    glVertex2f(0.0,0.0);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(-tamSeg,tamSeg);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,-tamSeg);
    glVertex2f(-tamSeg,0.0);
    glEnd();
    glEndList();
    //FIM NUMERO6

    //COMECO NUMERO7
    glNewList(SNUM7,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg,tamSeg);

    glVertex2f(0.0,tamSeg);
    glVertex2f(0.0,-tamSeg);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(-tamSeg/2.0,-tamSeg/5.0);
    glVertex2f(tamSeg/2.0,-tamSeg/5.0);
    glEnd();
    glEndList();
    //FIM NUMERO7

    //COMECO NUMERO8
    glNewList(SNUM8,GL_COMPILE);
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.0,tamSeg);
    glVertex2f(-tamSeg,tamSeg);
    glVertex2f(-tamSeg,0.0);
    glVertex2f(-tamSeg,-tamSeg);
    glVertex2f(0.0,-tamSeg);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glVertex2f(-tamSeg,0.0);

    glVertex2f(0.0,0.0);
    glEnd();
    glEndList();
    //FIM NUMERO8

    //COMECO NUMERO9
    glNewList(SNUM9,GL_COMPILE);
    glBegin(GL_LINE_STRIP);
    glVertex2f(tamSeg,tamSeg);
    glVertex2f(0.0,tamSeg);
    glVertex2f(0.0,0.0);
    glVertex2f(tamSeg,0.0);
    glVertex2f(tamSeg,-tamSeg);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex2f(tamSeg,tamSeg);
    glVertex2f(tamSeg,0.0);
    glEnd();
    glEndList();
    //FIM NUMERO9

    //COMECO NUMERO10
    glNewList(SNUM10,GL_COMPILE);
    /// parte do 1
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.025,0.0);
    glVertex2f(-0.025,+tamSeg);
    glVertex2f(-0.025,-tamSeg);
    glEnd();
    /// parte do zero
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.025,0.0);
    glVertex2f(0.025,tamSeg);
    glVertex2f(0.025-tamSeg,tamSeg);
    glVertex2f(0.025-tamSeg,0.0);
    glVertex2f(0.025-tamSeg,-tamSeg);
    glVertex2f(0.025,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO10

    //COMECO NUMERO11
    glNewList(SNUM11,GL_COMPILE);
    /// parte do 1
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.02,0.0);
    glVertex2f(-0.02,+tamSeg);
    glVertex2f(-0.02,-tamSeg);
    glEnd();
    /// parte do 1
    glBegin(GL_LINE_LOOP);
    glVertex2f(0.02,0.0);
    glVertex2f(0.02,+tamSeg);
    glVertex2f(0.02,-tamSeg);
    glEnd();
    glEndList();
    //FIM NUMERO11
}

void Visualizacao::compileRobotShapeGL(){
    double RAIO_ROBO = 0.09;

    //COMECO ROBO
    glNewList(SROBO,GL_COMPILE);
    glBegin(GL_POLYGON);
    double temp = M_PI/360.0;
    double ini = 53.0*M_PI/180.0; /// calculando o angulo inicial em radianos
    double max = 2.0*M_PI-ini; /// calculando o angulo final
    for (double i = ini; i < max; i += temp){
        glVertex2f(RAIO_ROBO*cos(i),RAIO_ROBO*sin(i));
    }
    glEnd();
    glEndList();
    //FIM ROBO

    //COMECO CONTORNO DO ROBO
    glNewList(SCONTORNO, GL_COMPILE);
    glBegin(GL_LINES);
    temp = M_PI/360.0;
    ini = 53*M_PI/180.0; /// calculando o angulo inicial em radianos
    max = 2*M_PI-ini; /// calculando o angulo final
    for (double i = ini; i < max; i += temp){
        glVertex2f(RAIO_ROBO*cos(i),RAIO_ROBO*sin(i));
    }
    glVertex2f(RAIO_ROBO*cos(ini),RAIO_ROBO*sin(ini));
    glVertex2f(RAIO_ROBO*cos(max),RAIO_ROBO*sin(max));
    glEnd();
    glEndList();
    //FIM ROBO
}

void Visualizacao::initializeGL()
{
    /// compilando o shape do campo
    compileFieldShapeGL(this->width(), this->height());

    /// compilando o shape da bola
    compileBallShapeGL();

    /// compilando os numeros dos robos
    compileNumbersGL();

    /// compilando os shapes do robo e dos numeros dos ids dos robos
    compileRobotShapeGL();

    /// iniciando timer de atualização dos desenho
    timer.start();
}

void Visualizacao::resizeGL(int width, int height)
{
    /// calculando a taxa da largura em relacao a altura para identificar qual vai se o redimensionamento
    double ratio = double(this->width()) / double(this->height());

    /// pegando os valores minimos e maximos da nova janela
    zoomx = ratio * 2.25f;
    zoomy = 2.25f;

    /// pegando a parte da janela que interessa para poder redimensionar os shapes de acordo com o viewZoom setado
    glViewport(0.0, 0.0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    /// aplicando a transformacao nos elementos da janela
    gluOrtho2D(-zoomx, zoomx, -zoomy, zoomy);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Visualizacao::paintGL()
{
    /// limpando os shapes
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    /// renderizando o campo
    renderFieldGL();

    /// renderizando a bola
    renderBallGL();

    /// renderizando os robos
    renderAllRobotsGL();
}

void Visualizacao::renderFieldGL(){
    glCallList(SCAMPO);
}

void Visualizacao::renderSingleRobotGL(int id, Robo& r, bool equipeAzul){
    GLfloat posx = r.getPosicao()[0][0]/1000.0;
    GLfloat posy = r.getPosicao()[1][0]/1000.0;
    GLfloat angle = r.getPosicao()[2][0];
    GLfloat red, green, blue;
    if(equipeAzul){
        red=green=0.0;
        blue=255.0;
    }else{
        blue=0.0;
        red=125.0;
        green=125.0;
    }

    /// setando a posicao e o angulo do robo
    glPushMatrix();

    glColor3f(red, green, blue); /// setando a cor
    glTranslated(posx, posy, 0);
    glRotated((angle*180.0)/M_PI,0,0,1);
    glCallList(SROBO);

    glPopMatrix();
    /// finalizando o desenho do robo

    /// setando a posicao do numero do robo
    glPushMatrix();
    glColor3f(0.0f,0.0f,0.0f);
    glTranslated(posx, posy, 0);

    /// verificando qual é o id do robo
    switch(id){
    case 0:
        glCallList(SNUM0);
        break;
    case 1:
        glCallList(SNUM1);
        break;
    case 2:
        glCallList(SNUM2);
        break;
    case 3:
        glCallList(SNUM3);
        break;
    case 4:
        glCallList(SNUM4);
        break;
    case 5:
        glCallList(SNUM5);
        break;
    case 6:
        glCallList(SNUM6);
        break;
    case 7:
        glCallList(SNUM7);
        break;
    case 8:
        glCallList(SNUM8);
        break;
    case 9:
        glCallList(SNUM9);
        break;
    case 10:
        glCallList(SNUM10);
        break;
    case 11:
        glCallList(SNUM11);
        break;
    }
    glPopMatrix();
    /// fim do desenho do numero
}

void Visualizacao::renderAllRobotsGL(){

    /// renderizando os robos da equipe
    for(int id=0;id<robosEq->size();id++){
        if(robosEq->at(id).foiAchado()){
            renderSingleRobotGL(id, robosEq->at(id), config->corEquipe==Azul);
        }
    }

    /// renderizando os robos adversários
    for(int id=0;id<robosAdv->size();id++){
        if(robosAdv->at(id).foiAchado()){
            renderSingleRobotGL(id, robosAdv->at(id), config->corEquipe!=Azul);
        }
    }
}

void Visualizacao::renderBallGL(){
    cv::Mat_<float> pos = bola->getPosicao();

    /// setando a posicao da bola
    glPushMatrix();
    glTranslated(pos[0][0]/1000.0, pos[1][0]/1000.0, 0);
    glCallList(SBOLA);
    glPopMatrix();
}
