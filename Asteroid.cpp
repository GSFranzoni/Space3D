#include <windows.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Asteroid.h"

Asteroid::Asteroid(glm::vec3 translate, float v, Object* molde_obj_asteroid){
    this->translate = translate;
    this->velocity = v;
    this->rotation = 0;
    this->object = molde_obj_asteroid;
}

void Asteroid::move(){
    this->translate+=glm::vec3(0, 0, velocity);
}

void Asteroid::draw(){
    this->object->draw();
}

glm::vec3 Asteroid::getTranslate(){
    return this->translate;
}

void Asteroid::rotate(float r){
    this->rotation+=r;
    if(this->rotation>360)
        this->rotation=0;
}

Object* Asteroid::getObject(){
    return this->object;
}

float Asteroid::getRotate(){
    return this->rotation;
}

Hitbox Asteroid::getHitbox(){
    return this->object->getHitbox();
}
