#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED

#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <glm/glm.hpp>

class Light{
private:
    GLint id;
    glm::vec4 ambiente, difusa, especular, posicao;
    glm::vec3 direcao;
public:
    Light(GLint, glm::vec4, glm::vec4, glm::vec4, glm::vec4, glm::vec3);
    void setAmbiente(glm::vec4);
    void setDifusa(glm::vec4);
    void setEspecular(glm::vec4);
    void setPosicao(glm::vec4);
    void setDirecao(glm::vec3);
    glm::vec3 getDirecao();
    glm::vec4 getAmbiente();
    glm::vec4 getDifusa();
    glm::vec4 getEspecular();
    glm::vec4 getPosicao();
    void defineSpot(float, float);
    void definePoint();
    void define();
    void move(GLfloat, GLfloat, GLfloat);
};

#endif
