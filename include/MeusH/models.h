#pragma once

#ifndef MODELS
#define MODELS

#include"shaders.h"
#include"textures.h"
#include "vertex.h"
#include "mesh.h"

class Models
{
private:
    std::vector<Mesh*> meshes;
    glm::vec3 position;
public:
    Models(glm::vec3 position, std::vector<Mesh*> meshes){
        this->position = position;
        for(auto*i : meshes)
        {
            this->meshes.push_back(new Mesh(*i));
        }
    }

    ~Models(){
        for(auto*&i : this->meshes)
        {
            delete i;
        }
    }

    //funcoes
    void update(){

    }

    void render(Shader* shader){

    }
};


#endif