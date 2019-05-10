#ifndef ASTEROID_H_INCLUDED
#define ASTEROID_H_INCLUDED

#include <glm/glm.hpp>
#include "Object.h"
#include "Shot.h"
#include <vector>
#include <windows.h>
#include <GL/glut.h>

using namespace std;


class Asteroid{
private:
    Object* object;
    glm::vec3 translate;
    float velocity, rotation;
public:
    Asteroid(glm::vec3, float, Object*);
    void move();
    void rotate(float);
    void draw();
    glm::vec3 getTranslate();
    float getRotate();
    Object* getObject();
    Hitbox getHitbox();
};

#endif
