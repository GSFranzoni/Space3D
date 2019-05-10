#include "Light.h"
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

Light::Light(GLint id, glm::vec4 ambiente, glm::vec4 difusa, glm::vec4 especular, glm::vec4 posicao, glm::vec3 direcao){
    this->id = id;
    this->ambiente = ambiente;
    this->difusa = difusa;
    this->especular = especular;
    this->posicao = posicao;
    this->direcao = direcao;
}
void Light::defineSpot(float cutoff, float exp){
    this->define();
    glLightfv(GL_LIGHT0+id, GL_SPOT_DIRECTION, glm::value_ptr(direcao));
    glLightf(GL_LIGHT0+id, GL_SPOT_CUTOFF, cutoff);
    glLightf(GL_LIGHT0+id, GL_SPOT_EXPONENT, exp);
}
void Light::define(){
    glLightfv(GL_LIGHT0+id, GL_AMBIENT, glm::value_ptr(ambiente));
    glLightfv(GL_LIGHT0+id, GL_DIFFUSE, glm::value_ptr(difusa));
    glLightfv(GL_LIGHT0+id, GL_SPECULAR, glm::value_ptr(especular));
    glLightfv(GL_LIGHT0+id, GL_POSITION, glm::value_ptr(posicao));
    glEnable(GL_LIGHT0+id);
}
void Light::definePoint(){
    glLightfv(GL_LIGHT0+id, GL_DIFFUSE, glm::value_ptr(difusa));
    glLightfv(GL_LIGHT0+id, GL_SPECULAR, glm::value_ptr(especular));
    glLightfv(GL_LIGHT0+id, GL_POSITION, glm::value_ptr(posicao));
    glEnable(GL_LIGHT0+id);
}
void Light::move(GLfloat tx, GLfloat ty, GLfloat tz){
    this->posicao+=glm::vec4(tx, ty, tz, 0);
}
void Light::setDifusa(glm::vec4 difusa){
    this->difusa = difusa;
}
void Light::setEspecular(glm::vec4 especular){
    this->especular = especular;
}
void Light::setPosicao(glm::vec4 posicao){
    this->posicao = posicao;
}
void Light::setAmbiente(glm::vec4 ambiente){
    this->ambiente = ambiente;
}
void Light::setDirecao(glm::vec3 direcao){
    this->direcao = direcao;
}
glm::vec3 Light::getDirecao(){
    return this->direcao;
}
glm::vec4 Light::getDifusa(){
    return this->difusa;
}
glm::vec4 Light::getEspecular(){
    return this->especular;
}
glm::vec4 Light::getPosicao(){
    return this->posicao;
}
glm::vec4 Light::getAmbiente(){
    return this->ambiente;
}
