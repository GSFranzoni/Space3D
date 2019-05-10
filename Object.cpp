#include <windows.h>
#include "Object.h"
#include "Util.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glut.h>
#include <fstream>

Object::Object(string filename, float s)
{
    this->scale = s;
    this->loadOBJ(filename);
}

void Object::loadOBJ(string filename)
{
    ifstream file;
    file.open(filename.c_str());
    string line;
    vector<float>corAux(3);
    while(file.good())
    {
        getline(file, line);
        if(line.substr(0,3)=="Kd "){
            vector<string> s = split(line, ' ');
            corAux[0]=(parseFloat(s[1]));
            corAux[1]=(parseFloat(s[2]));
            corAux[2]=(parseFloat(s[3]));
        }
        if(line.substr(0,2)=="v ")
        {
            vector<string> s = split(line, ' ');
            this->vertices.push_back(VERT(parseFloat(s[1])*this->scale, parseFloat(s[2])*this->scale, parseFloat(s[3])*this->scale));
            if(this->vertices.empty()){
                this->hitbox.max_x = parseFloat(s[1])*this->scale;
                this->hitbox.min_x = parseFloat(s[1])*this->scale;
                this->hitbox.max_y = parseFloat(s[2])*this->scale;
                this->hitbox.min_y = parseFloat(s[2])*this->scale;
                this->hitbox.max_z = parseFloat(s[3])*this->scale;
                this->hitbox.min_z = parseFloat(s[3])*this->scale;
            }
            else{
                if(parseFloat(s[1])*this->scale<this->hitbox.min_x){
                    this->hitbox.min_x = parseFloat(s[1])*this->scale;
                }
                else if(parseFloat(s[1])*this->scale>this->hitbox.max_x){
                    this->hitbox.max_x =  parseFloat(s[1])*this->scale;
                }
                if(parseFloat(s[2])*this->scale<this->hitbox.min_y){
                    this->hitbox.min_y = parseFloat(s[2])*this->scale;
                }
                else if(parseFloat(s[2])*this->scale>this->hitbox.max_y){
                    this->hitbox.max_y = parseFloat(s[2])*this->scale;
                }
                if(parseFloat(s[3])*this->scale<this->hitbox.min_z){
                    this->hitbox.min_z = parseFloat(s[3])*this->scale;
                }
                else if(parseFloat(s[3])*this->scale>this->hitbox.max_z){
                    this->hitbox.max_z = parseFloat(s[3])*this->scale;
                }
            }
        }
        if(line.substr(0,2)=="f ")
        {
            vector<string> s = split(line, ' ');
            vector<int> inds;
            for(int i=1; i<s.size(); i++)
            {
                inds.push_back(parseInt(s[i])-1);
            }
            this->faces.push_back(FACE(inds));
            this->faces.back().cor=corAux;
        }
    }
}

Hitbox Object::getHitbox(){
    return this->hitbox;
}

void Object::draw(){
    for(int f=0; f < (int)this->faces.size(); f++)
	{
	    glColor3f(this->faces[f].cor[0],this->faces[f].cor[1],this->faces[f].cor[2]);
		glBegin(GL_POLYGON);
		for(int v=0; v < (int)this->faces[f].ind.size(); v++)
        {
			glVertex3f
			(
                this->vertices[this->faces[f].ind[v]].x,
                this->vertices[this->faces[f].ind[v]].y,
                this->vertices[this->faces[f].ind[v]].z
            );
		}
		glEnd();
	}
}

