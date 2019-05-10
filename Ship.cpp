#include <windows.h>
#include <GL/glut.h>
#include <GL/glut.h>
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Ship.h"

Ship::Ship(glm::vec3 translate){
    this->translate = translate;
    this->object = new Object(URL_SHIP, 5);
    this->fire_timer = new Timer(300);
}

void Ship::move(float tx, float ty, float tz){
    this->translate+=glm::vec3(tx, ty, tz);
}

void Ship::draw(){
    this->fire_timer->update();
    this->object->draw();
}

bool Ship::fire(){
    if(this->fire_timer->valid()){
        this->shots.push_back(new Shot(this->translate+glm::vec3(-25, 0, -15), molde_obj_tiro));
        this->shots.push_back(new Shot(this->translate+glm::vec3( 25, 0, -15), molde_obj_tiro));
        return true;
    }
    return false;
}

glm::vec3 Ship::getTranslate(){
    return this->translate;
}

Object* Ship::getObject(){
    return this->object;
}

vector<Shot*>& Ship::getShots(){
    return this->shots;
}

Hitbox Ship::getHitbox(){
    return this->object->getHitbox();
}
