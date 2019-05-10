#include <windows.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "LifeBonus.h"

LifeBonus::LifeBonus(glm::vec3 translate, float v){
    this->translate = translate;
    this->velocity = v;
    this->rotation = 0;
    this->object = new Object(URL_LIFEBONUS, 3);
}

void LifeBonus::move(){
    this->translate+=glm::vec3(0, 0, velocity);
}

void LifeBonus::rotate(float r){
    this->rotation+=r;
    if(this->rotation>360)
        this->rotation=0;
}

void LifeBonus::draw(){
    this->object->draw();
}

glm::vec3 LifeBonus::getTranslate(){
    return this->translate;
}

Object* LifeBonus::getObject(){
    return this->object;
}

float LifeBonus::getRotate(){
    return this->rotation;
}

Hitbox LifeBonus::getHitbox(){
    return this->object->getHitbox();
}
