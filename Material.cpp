#include "Material.h"
#include <glm/gtc/type_ptr.hpp>
#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>

Material::Material(glm::vec4 especularidade, GLfloat espec){
    this->especularidade = especularidade;
    this->espec = espec;
}

void Material::setEspecularidade(glm::vec4 especularidade){
    this->especularidade = especularidade;
}

void Material::setEspec(GLfloat espec){
    this->espec = espec;
}

glm::vec4 Material::getEspecularidade(){
    return this->especularidade;
}

GLfloat Material::getEspec(){
    return this->espec;
}

void Material::define(){
    glMaterialfv(GL_FRONT, GL_SPECULAR, glm::value_ptr(especularidade));
	glMateriali(GL_FRONT,GL_SHININESS, espec);
}
