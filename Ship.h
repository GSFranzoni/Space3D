#ifndef SHIP_H_INCLUDED
#define SHIP_H_INCLUDED

#include <glm/glm.hpp>
#include "Object.h"
#include "Shot.h"
#include "Light.h"
#include "Util.h"
#include "Timer.h"
#include <vector>

#define URL_SHIP "C:\\Space3D\\Objetos\\ship.obj"

static Object* molde_obj_tiro = new Object("C:\\Space3D\\Objetos\\ammo_rocket.obj", 500);

class Ship{
private:
    Object* object;
    glm::vec3 translate;
    vector<Shot*> shots;
    Timer* fire_timer;
public:
    Ship(glm::vec3);
    void move(float, float, float);
    void draw();
    bool fire();
    vector<Shot*>& getShots();
    Object* getObject();
    glm::vec3 getTranslate();
    Hitbox getHitbox();
};

#endif
