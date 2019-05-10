#ifndef SHOT_H_INCLUDED
#define SHOT_H_INCLUDED

#include <GL/glut.h>
#include <glm/glm.hpp>
#include <vector>
#include "Util.h"
#include "Object.h"

using namespace std;

class Shot{
private:
    glm::vec3 translate;
    Object* object;
public:
    Shot(glm::vec3, Object*);
    void move(float, float, float);
    void draw();
    glm::vec3 getTranslate();
    Hitbox getHitbox();
};

#endif
