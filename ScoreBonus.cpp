#include <windows.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "ScoreBonus.h"

ScoreBonus::ScoreBonus(glm::vec3 translate, float v){
    this->translate = translate;
    this->velocity = v;
    this->rotation = 0;
    this->object = new Object(URL_SCOREBONUS, 5);
}

void ScoreBonus::move(){
    this->translate+=glm::vec3(0, 0, velocity);
}

void ScoreBonus::rotate(float r){
    this->rotation+=r;
    if(this->rotation>360)
        this->rotation=0;
}

void ScoreBonus::draw(){
    this->object->draw();
}

glm::vec3 ScoreBonus::getTranslate(){
    return this->translate;
}

float ScoreBonus::getRotate(){
    return this->rotation;
}

Object* ScoreBonus::getObject(){
    return this->object;
}

Hitbox ScoreBonus::getHitbox(){
    return this->object->getHitbox();
}
