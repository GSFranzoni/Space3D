#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <ctype.h>
#include "Shot.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

Shot::Shot(glm::vec3 translate, Object* obj){
    this->object = obj;
    this->translate = translate;
}

void Shot::move(float tx, float ty , float tz){
    this->translate+=glm::vec3(tx, ty, tz);
}

void Shot::draw(){
    this->object->draw();
}

glm::vec3 Shot::getTranslate(){
    return this->translate;
}

Hitbox Shot::getHitbox(){
    return this->object->getHitbox();
}
