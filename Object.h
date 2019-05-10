#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include "Util.h"
#include <iostream>
#include <vector>
#include <glm/glm.hpp>

using namespace std;

struct VERT{
	float x,y,z;
	VERT(float a, float b, float c){
        this->x = a;
        this->y = b;
        this->z = c;
    }
};

struct FACE{
	vector<int> ind;
	FACE(vector<int> inds){
        for(int i=0; i<(int)inds.size(); i++){
            ind.push_back(inds[i]);
        }
	}
	vector<float>cor;
};

class Object{
private:
    vector<VERT> vertices;
    vector<FACE> faces;
    Hitbox hitbox;
    float scale;
public:
    void loadOBJ(string);
    Object(string, float);
    vector<VERT> getVertices();
    vector<FACE> getFaces();
    void setVertices(vector<VERT>);
    void setFaces(vector<FACE>);
    void draw();
    Hitbox getHitbox();
};

#endif
