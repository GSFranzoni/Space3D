#ifndef SCOREBONUS_H_INCLUDED
#define SCOREBONUS_H_INCLUDED

#include <glm/glm.hpp>
#include "Object.h"
#include "Shot.h"
#include "Light.h"
#include <vector>

#define URL_SCOREBONUS "C:\\Space3D\\Objetos\\estrela.obj"

class ScoreBonus{
private:
    Object* object;
    glm::vec3 translate;
    float velocity;
    float rotation;
public:
    ScoreBonus(glm::vec3, float);
    void move();
    void draw();
    void rotate(float);
    glm::vec3 getTranslate();
    float getRotate();
    Object* getObject();
    Hitbox getHitbox();
};


#endif
