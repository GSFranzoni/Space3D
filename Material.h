#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include <glm/glm.hpp>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

class Material{
private:
    glm::vec4 especularidade;
    GLfloat espec;
public:
    Material(glm::vec4, GLfloat);
    void setEspecularidade(glm::vec4);
    void setEspec(GLfloat);
    glm::vec4 getEspecularidade();
    GLfloat getEspec();
    void define();
};

#endif
