#pragma once

#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <vector>
#include "shaders.h"
#include "textures.h"

struct Vertex
{
    //glm::vec3 position;
    float px;
    float py;
    float pz;
    //glm::vec3 color;
    //float r;
    //float g;
    //float b;
    //float a;
    //glm::vec2 textCoord;
    float tx;
    float ty;
};

class Mesh
{
    private:
        std::vector<Vertex> vertices;
        std::vector<int> indices;

        unsigned int VBO;
        unsigned int EAB; 

        void initBuffers(){

        }
    public:

    Mesh(){

    }

    ~Mesh(){
        
    }
};



#endif
