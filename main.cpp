#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <sstream>
#include <fstream>
#include <time.h>
#include <mmsystem.h>
#include "Util.h"
#include "Ship.h"
#include "Light.h"
#include "Material.h"
#include "Input.h"
#include "Asteroid.h"
#include "LifeBonus.h"
#include "ScoreBonus.h"
#include "Timer.h"
#include "Sound.h"

using namespace std;

Object* molde_obj_asteroid = new Object("C:\\Space3D\\Objetos\\icosahedron.obj", 18);
bool FULL_SCREEN = false;
bool pause = true, play_again = false;
GLfloat angle, fAspect;
GLfloat rotX, rotY, rotX_ini, rotY_ini;
GLfloat obsX, obsY, obsZ, obsX_ini, obsY_ini, obsZ_ini;
int x_ini,y_ini,bot;
Ship* ship = new Ship(glm::vec3(0, 0, 0));
Object* earth = new Object("C:\\Space3D\\Objetos\\earth.obj", 250);
LifeBonus* coracao = new LifeBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
ScoreBonus* estrela = new ScoreBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
int score = 0, life = 100;
int QNTD_ASTEROIDS = (int)(score/1000)+12;
Sound* tiro = new Sound("C:\\Space3D\\Sounds\\fire.wav");
Sound* explosao = new Sound("C:\\Space3D\\Sounds\\explosion.wav");
Sound* gameover = new Sound("C:\\Space3D\\Sounds\\gameover.wav");
Sound* bonus = new Sound("C:\\Space3D\\Sounds\\levelup.wav");
Sound* background = new Sound("C:\\Space3D\\Sounds\\background.wav");
Sound* music = new Sound("C:\\Space3D\\Sounds\\ss.ogg");

vector<Asteroid*> asteroids;

Light* farol_nave = new Light(
    0,
    glm::vec4(.5, .5, .5, 1),
    glm::vec4(0.5, 0.5, 0.5, 1),
    glm::vec4(1, 1, 1, 1),
    glm::vec4(ship->getTranslate(), 0)+glm::vec4(0, 5, -40, 1),
    glm::vec3(0, 0, -1)
);

Light* point_light = new Light(
    1,
    glm::vec4(.2, .2, .2, 1),
    glm::vec4(0.10, 0.10, 0.10, .5),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0, 0, 0, 1),
    glm::vec3(0, 0, 0)
);


Light* ilum_nave = new Light(
    2,
    glm::vec4(.5, .5, .5, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(0.3, 0.3, 0.3, 1),
    glm::vec4(ship->getTranslate(), 0)+glm::vec4(0, 250, 0, 1),
    glm::vec3(0, -1, 0)
);


Material* mat = new Material(
    glm::vec4(0.2, 0.2, 0.2, 0.2),
    20
);

float rot_terra = 0;

vector<glm::vec4> stars;

/**
Gera estrelas em posições aleatórias
**/
void generate_stars(){
    for(int i=0; i<1000; i++){
        int sinal = rand()%2;
        if(sinal==0)
            sinal=-1;
        int x = (rand()%1000)*sinal;
        sinal = rand()%2;
        if(sinal==0)
            sinal=-1;
        int y = (rand()%1000)*sinal;
        sinal = rand()%2;
        if(sinal==0)
            sinal=-1;
        int z = (rand()%1000)*sinal;
        stars.push_back(glm::vec4(x, y, z, rand()%4));
    }
}

/**
Gerencia a câmera
**/
void camera_manager(void)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-obsX,-obsY,-obsZ);
    glRotatef(rotX,1,0,0);
    glRotatef(rotY,0,1,0);
}

/**
Especifica parâmetros da visualização
**/
void view_manager(void)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, fAspect, 0.1, 1500);
    camera_manager();
}

/**
Correção de aspecto
**/
void resize(GLsizei w, GLsizei h)
{
    if(h==0)
        h=1;
    glViewport(0, 0, w, h);
    fAspect = (GLfloat)w/(GLfloat)h;
    view_manager();
}

/**
Mostra textos na tela, numa posição (x, y) e com uma fonte(font)
**/
void show_text(int x, int y, float r, float g, float b, void* font, string str)
{
    glColor3f(r, g, b);
    glRasterPos2i(x, y);
    for(int i=0; i<str.size(); i++){
        glutBitmapCharacter(font, str[i]);
    }
}

/**
Reinicia a câmera na posição inicial
**/
static void restart_camera(){
    angle = 60;
    rotX = 15;
    rotY = 0;
    obsX = 0;
    obsY = 100;
    obsZ = 300;
}


void resetGame(){
    ship = new Ship(glm::vec3(0, 0, 0));
    farol_nave = new Light(
        0,
        glm::vec4(.5, .5, .5, 1),
        glm::vec4(0.5, 0.5, 0.5, 1),
        glm::vec4(1, 1, 1, 1),
        glm::vec4(ship->getTranslate(), 0)+glm::vec4(0, 5, -40, 1),
        glm::vec3(0, 0, -1)
    );

    point_light = new Light(
        1,
        glm::vec4(.2, .2, .2, 1),
        glm::vec4(0.10, 0.10, 0.10, .5),
        glm::vec4(0.3, 0.3, 0.3, 1),
        glm::vec4(0, 0, 0, 1),
        glm::vec3(0, 0, 0)
    );


    ilum_nave = new Light(
        2,
        glm::vec4(.5, .5, .5, 1),
        glm::vec4(0.3, 0.3, 0.3, 1),
        glm::vec4(0.3, 0.3, 0.3, 1),
        glm::vec4(ship->getTranslate(), 0)+glm::vec4(0, 250, 0, 1),
        glm::vec3(0, -1, 0)
    );

    coracao = new LifeBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
    estrela = new ScoreBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
    score = 0;
    life = 100;
    pause=true;
    play_again=false;
    restart_camera();
    asteroids.clear();
    QNTD_ASTEROIDS = (int)(score/1000)+12;
}

static void SPECIAL_KEY_DOWN(int KEY, int x, int y){
    switch(KEY){

        break;
    }
}

static void SPECIAL_KEY_UP(int KEY, int x, int y){
    switch(KEY){

    }
}

static void NORMAL_KEY_DOWN(unsigned char KEY, int x, int y){
    switch(tolower(KEY)){
    case 27:
        exit(0);
    case GLUT_KEY_SPACE:
        KEY_SPACE = true;
        break;
    case 'a':
        KEY_A = true;
        break;
    case 'd':
        KEY_D = true;
        break;
    case 'w':
        KEY_W = true;
        break;
    case 's':
        KEY_S = true;
        break;
    case 'r':
        /**
        Reiniciar a câmera na posicao inicial
        **/
        //restart_camera();
        break;
    case 'p':
        pause = !pause;
        if(pause){
            background->stop();
            music->playLoop(75);
        }
        else{
            music->stop();
            background->playLoop(20);
        }
        break;
    case 'y':
        resetGame();
        break;
    }
}

static void NORMAL_KEY_UP(unsigned char KEY, int x, int y){
    switch(tolower(KEY)){
    case GLUT_KEY_SPACE:
        KEY_SPACE = false;
        break;
    case 'a':
        KEY_A = false;
        break;
    case 'd':
        KEY_D = false;
        break;
    case 'w':
        KEY_W = false;
        break;
    case 's':
        KEY_S = false;
        break;
    }
}

static void EXEC_KEY_FUNCTIONS(){
    if(KEY_SPACE){
        /**
        Quando a tecla espaço é pressionada, a nave atira
        **/
        if(ship->fire()){
            tiro->play(25);
        }
    }
    /**
    Quando as teclas A, D, W, S são pressionadas, a nave e a luz se movimentam
    **/
    if(KEY_A && ship->getTranslate()[0]>-175){
        ship->move(-4, 0, 0);
        farol_nave->move(-4, 0, 0);
        ilum_nave->move(-4, 0, 0);
        obsX-=4;
    }
    if(KEY_D && ship->getTranslate()[0]<175){
        ship->move( 4, 0, 0);
        farol_nave->move( 4, 0, 0);
        ilum_nave->move( 4, 0, 0);
        obsX+=4;
    }
    if(KEY_W && ship->getTranslate()[2]>-175){
        ship->move( 0, 0,-4);
        farol_nave->move( 0, 0,-4);
        ilum_nave->move( 0, 0,-4);
    }
    if(KEY_S && ship->getTranslate()[2]<50){
        ship->move( 0, 0, 4);
        farol_nave->move( 0, 0, 4);
        ilum_nave->move( 0, 0, 4);
    }
}

/**
Desenha os objetos na tela
**/
static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    /**
    Gerencia a visão
    **/
    glPushMatrix();
        glTranslatef(ship->getTranslate().x, 0, 0);
        glPushMatrix();
            glColor3f(1, 0, 0);
            glTranslatef(0, -50, -4);
            glScalef(life, 1, 1);
            glutSolidCube(5);
        glPopMatrix();
        /**
        Escreve o placar e vida da nave
        **/
        show_text(-192, 200, 1, 1, 0, GLUT_BITMAP_HELVETICA_18, "SCORE = " + parseString(score));
        glPushMatrix();
            glTranslatef(0, -50, 25);
            show_text(-20, 0, 1, 1, 1, GLUT_BITMAP_HELVETICA_18, "LIFE = " + parseString(life) + "%");
        glPopMatrix();
        if(play_again){
            show_text(-20, 120, 1, 1, 0, GLUT_BITMAP_HELVETICA_18, "PLAY AGAIN?");
            show_text(-20, 110, 0, 0, 1, GLUT_BITMAP_HELVETICA_18, "Y - YES");
            show_text(-20, 100, 1, 0, 0, GLUT_BITMAP_HELVETICA_18, "ESC - NO");
        }
        else if(pause){
            show_text(-56, 150, 1, 0.3, 0.2, GLUT_BITMAP_HELVETICA_18, "CONTROLS");
            show_text(-56.5, 140, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "A - Left");
            show_text(-57, 130, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "D - Right");
            show_text(-57.5, 120, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "W - Forward");
            show_text(-58, 110, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "S - Backward");
            show_text(-58.5, 100, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "SPACE BAR - Fire");
            show_text(-59, 90, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "MOUSE - Moves the camera");
            show_text(-59.5, 80, 0.078411, 0.303421, 0.473760, GLUT_BITMAP_HELVETICA_18, "R - Resets the camera position");
            show_text(-60, 60, 1, 0, 0, GLUT_BITMAP_HELVETICA_18, "ESC - Exit");
            show_text(-61, 50, 0, 1, 0, GLUT_BITMAP_HELVETICA_18, "P - Pause/Play");
        }
    glPopMatrix();
    view_manager();
    glEnable(GL_LIGHTING);
    /**
    Ambiente global
    **/
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, glm::value_ptr(glm::vec4(.5, .5, .5, 1)));
    farol_nave->defineSpot(40, 10);
    mat->define();
    ilum_nave->defineSpot(40, 10);
    glDisable(GL_LIGHT1);
    for(int i=0; i<(int)ship->getShots().size(); i++){
        glEnable(GL_LIGHT1);
        point_light->setPosicao(glm::vec4(ship->getShots()[i]->getTranslate()[0], ship->getShots()[i]->getTranslate()[1], ship->getShots()[i]->getTranslate()[2], 0));
        point_light->definePoint();
        glPushMatrix();
            /**
            Translada, rotaciona e desenha os tiros
            **/
            glTranslatef(ship->getShots()[i]->getTranslate()[0], ship->getShots()[i]->getTranslate()[1], ship->getShots()[i]->getTranslate()[2]);
            glRotatef(180, 0, 1, 0);
            ship->getShots()[i]->draw();
        glPopMatrix();
    }
    glPushMatrix();
        glColor3f(1, 1, 1);
        /**
        Desenha as estrelas
        **/
        for(int i=0; i<(int)stars.size(); i++){
            glPointSize(stars[i][3]);
            glBegin(GL_POINTS);
                glVertex3f(stars[i][0], stars[i][1], stars[i][2]);
            glEnd();
        }
    glPopMatrix();
    glPushMatrix();
        /**
        Desenha e translada o farol da nave
        **/
        glColor3f(1, 1, 1);
        glTranslatef(farol_nave->getPosicao().x, farol_nave->getPosicao().y, farol_nave->getPosicao().z);
        glutSolidSphere(5, 20, 20);
    glPopMatrix();
    /**
    Define a luz e material
    **/
    glPushMatrix();
        /**
        Translada e desenha a nave
        **/
        glTranslatef(ship->getTranslate().x, ship->getTranslate().y, ship->getTranslate().z);
        ship->draw();
    glPopMatrix();
    for(int i=0; i<(int)asteroids.size(); i++){
        glPushMatrix();
            /**
            Translada, rotaciona e desenha os asteroids
            **/
            glTranslatef(asteroids[i]->getTranslate()[0], asteroids[i]->getTranslate()[1], asteroids[i]->getTranslate()[2]);
            glRotatef(50, 1, 0, 0);
            glRotatef(-asteroids[i]->getRotate(), 0, 0, 1);
            asteroids[i]->draw();
        glPopMatrix();
    }
    glPushMatrix();
        /**
        Translada, rotaciona e desenha o LifeBonus
        **/
        glTranslatef(coracao->getTranslate().x, coracao->getTranslate().y, coracao->getTranslate().z);
        glRotatef(coracao->getRotate(), 0, 1, 0);
        coracao->draw();
    glPopMatrix();
    glPushMatrix();
        /**
        Translada, rotaciona e desenha o ScoreBonus
        **/
        glTranslatef(estrela->getTranslate().x, estrela->getTranslate().y, estrela->getTranslate().z);
        glRotatef(estrela->getRotate(), 0, 1, 0);
        estrela->draw();
    glPopMatrix();
    glPushMatrix();
        /**
        Translada, rotaciona e desenha a terra
        **/
        glTranslatef(550, 300,-900);
        glRotatef(rot_terra, 0, 1, 0);
        earth->draw();
    glPopMatrix();
    /**
    glPushMatrix();
        glColor3f(0.1, 0.1, 0.1);
        glBegin(GL_QUADS);
            glVertex3f(-5000, 0, -5000);
            glVertex3f( 5000, 0, -5000);
            glVertex3f( 5000, 0, 5000);
            glVertex3f(-5000, 0, 5000);
        glEnd();
    glPopMatrix();
    **/
    rot_terra+=0.05;
    glutSwapBuffers();
}

#define SENS_ROT	20.0
#define SENS_OBS	30.0
#define SENS_TRANSL	60.0
/**
Função de callback de movimento do mouse
**/
void MOUSE_MOVE(int x, int y)
{
    if(bot==GLUT_LEFT_BUTTON)
    {
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        rotY = rotY_ini - deltax/SENS_ROT;
        rotX = rotX_ini - deltay/SENS_ROT;
    }
    else if(bot==GLUT_RIGHT_BUTTON)
    {
        int deltaz = y_ini - y;
        obsZ = obsZ_ini + deltaz/SENS_OBS;
    }
    else if(bot==GLUT_MIDDLE_BUTTON)
    {
        int deltax = x_ini - x;
        int deltay = y_ini - y;
        obsX = obsX_ini + deltax/SENS_TRANSL;
        obsY = obsY_ini - deltay/SENS_TRANSL;
        if(obsY<1)
            obsY=1;
    }
    camera_manager();
}

/**
Função de callback de click do mouse
**/
void MOUSE_CLICK(int button, int state, int x, int y)
{
    if(state==GLUT_DOWN)
    {
        x_ini = x;
        y_ini = y;
        obsX_ini = obsX;
        obsY_ini = obsY;
        obsZ_ini = obsZ;
        rotX_ini = rotX;
        rotY_ini = rotY;
        bot = button;
    }
    else bot = -1;
}

/**
Função de inicialização
**/
void init()
{
    restart_camera();
    glutFullScreen();
    glEnable(GL_DEPTH_TEST);
    generate_stars();
    srand(time(0));
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
}

/**
Verifica a colisão entre o hitbox de objetos
**/
bool collision(Hitbox hit_a, glm::vec3 translate_a, Hitbox hit_b, glm::vec3 translate_b){
    return (hit_a.min_x+translate_a.x <= hit_b.max_x+translate_b.x && hit_a.max_x+translate_a.x >= hit_b.min_x+translate_b.x) &&
           (hit_a.min_y+translate_a.y <= hit_b.max_y+translate_b.y && hit_a.max_y+translate_a.y >= hit_b.min_y+translate_b.y) &&
           (hit_a.min_z+translate_a.z <= hit_b.max_z+translate_b.z && hit_a.max_z+translate_a.z >= hit_b.min_z+translate_b.z);
}

void update(){
    /**
    Colisão da nave com o LifeBonus
    **/
    if(collision(ship->getHitbox(), ship->getTranslate(), coracao->getHitbox(), coracao->getTranslate())){
        coracao = new LifeBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
        life+=20;
        if(life>100)
            life=100;
        bonus->play(80);
    }
    /**
    Colisão da nave com o ScoreBonus
    **/
    if(collision(ship->getHitbox(), ship->getTranslate(), estrela->getHitbox(), estrela->getTranslate())){
        estrela = new ScoreBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
        score+=100;
        bonus->play(80);
    }
    /**
    Colisão da nave com os asteroids
    **/
    for(int i=0; i<(int)asteroids.size(); i++){
        if(collision(asteroids[i]->getHitbox(), asteroids[i]->getTranslate(), ship->getHitbox(), ship->getTranslate())){
            asteroids.erase(asteroids.begin()+i);
            i--;
            life-=10;
            explosao->play(90);
        }
    }
    /**
    Colisão dos tiros com os asteroids
    **/
    for(int j=0; j<ship->getShots().size(); j++){
        bool hit = false;
        for(int i=0; i<(int)asteroids.size(); i++){
            if(collision(asteroids[i]->getHitbox(), asteroids[i]->getTranslate(), ship->getShots()[j]->getHitbox(), ship->getShots()[j]->getTranslate())){
                asteroids.erase(asteroids.begin()+i);
                ship->getShots().erase(ship->getShots().begin()+j);
                hit = true;
                score+=20;
                explosao->play(90);
                break;
            }
        }
        if(hit)
            j--;
    }
    /**
    Verifica se o LifeBonus saiu da área de jogo
    **/
    if(coracao->getTranslate().z>75){
        coracao = new LifeBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
    }
    /**
    Verifica se o ScoreBonus saiu da área de jogo
    **/
    if(estrela->getTranslate().z>75){
        estrela = new ScoreBonus(glm::vec3(rand()%200, 0, -2500), (rand()%5)+1);
    }
    /**
    Verifica se os asteroids saíram da área de jogo, e remove os que saíram
    **/
    for(int i=0; i<(int)asteroids.size(); i++){
        if(asteroids[i]->getTranslate()[2]>75){
            asteroids.erase(asteroids.begin()+i);
            i--;
            life-=5;
        }
    }
    /**
    Gera novos asteroids, enquanto tiverem menos que a quantidade pré definida.
    **/
    while((int)asteroids.size()<QNTD_ASTEROIDS){
        int positivo = rand()%2;
        if(positivo==0)
            asteroids.push_back(new Asteroid(glm::vec3(rand()%200, 0, -1500), (rand()%5)+1, molde_obj_asteroid));
        else
            asteroids.push_back(new Asteroid(glm::vec3(-rand()%200, 0, -1500), (rand()%5)+1, molde_obj_asteroid));
    }
    /**
    Move e rotaciona os asteroids
    **/
    for(int i=0; i<(int)asteroids.size(); i++){
        asteroids[i]->move();
        asteroids[i]->rotate(3);
    }
    /**
    Move e rotaciona o LifeBonus
    **/
    coracao->move();
    coracao->rotate(3);
    /**
    Move e rotaciona o ScoreBonus
    **/
    estrela->move();
    estrela->rotate(3);
    /**
    Executa as funções de teclado
    **/
    EXEC_KEY_FUNCTIONS();
    /**
    Retira os tiros que saíram da área de jogo
    **/
    for(int i=0; i<(int)ship->getShots().size(); i++){
        ship->getShots()[i]->move(0, 0, -12);
        if(ship->getShots()[i]->getTranslate()[2]<-1200){
            ship->getShots().erase(ship->getShots().begin()+i);
            i--;
        }
    }
    QNTD_ASTEROIDS = (int)(score/1000)+12;
    if(life<=0){
        gameover->play(80);
        PlaySound(TEXT("C:\\Space3D\\Sounds\\background.wav"), NULL, SND_FILENAME | SND_ASYNC| SND_LOOP);
        life=0;
        play_again=true;
    }
}

void run(int t){
    if(!pause && !play_again){
        update();
    }
    glutPostRedisplay();
    glutTimerFunc(5, run, 1);
}

int main()
{
    FreeConsole();
    music->playLoop(75);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Space 3D");
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    init();
    glutKeyboardFunc(NORMAL_KEY_DOWN);
    glutKeyboardUpFunc(NORMAL_KEY_UP);
    glutSpecialFunc(SPECIAL_KEY_DOWN);
    glutSpecialUpFunc(SPECIAL_KEY_UP);
    //glutMotionFunc(MOUSE_MOVE);
    //glutMouseFunc(MOUSE_CLICK);
    glutTimerFunc(5, run, 1);
    glutMainLoop();
    return EXIT_SUCCESS;
}
