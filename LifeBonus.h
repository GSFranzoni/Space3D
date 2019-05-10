#ifndef LIFEBONUS_H_INCLUDED
#define LIFEBONUS_H_INCLUDED

#include <glm/glm.hpp>
#include "Object.h"
#include "Shot.h"
#include "Light.h"
#include "Util.h"
#include <vector>

#define URL_LIFEBONUS "C:\\Space3D\\Objetos\\coracao.obj"

class LifeBonus{
private:
    Object* object;
    glm::vec3 translate;
    float velocity;
    float rotation;
public:
    LifeBonus(glm::vec3, float);
    void move();
    void draw();
    void rotate(float);
    bool collision();
    glm::vec3 getTranslate();
    float getRotate();
    Object* getObject();
    Hitbox getHitbox();
};

#endif
