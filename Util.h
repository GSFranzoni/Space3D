#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <iostream>
#include <vector>
#include <fstream>
#include <glm/glm.hpp>

using namespace std;

struct Hitbox{
    float min_x, min_y, min_z, max_z, max_x, max_y;
    Hitbox(){
    }
    float getHitboxSize(){
        return max(max(abs(min_x)+abs(max_x), abs(min_y)+abs(max_y)), abs(min_z)+abs(max_z));
    }
};
float parseFloat(string);
int parseInt(string);
string parseString(int);
vector<string> split(string, char);

#endif
