#pragma once

#ifndef MODELS
#define MODELS

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include"shaders.h"
#include"textures.h"
#include "vertex.h"
#include "mesh.h"

//parte de leitura de obj
struct vectorInds{
    int val1, val2, val3;  
};

struct Ret{
    std::string val;
    int barraPos;
};

Ret getNumero(std::string valor, int posI){
    Ret r;
    std::string p = "";
    int indice = posI;
    for(int i = posI; i < valor.size(); i++){
        indice = i;
        if(valor.substr(i,1) == "/"){
            break;
        }
        p += valor.substr(i,1);
    }
    r.val = p;
    r.barraPos = indice;
    return r;
}

vectorInds processarString(std::string valor){
    vectorInds vet;
    //vertice
    Ret rv = getNumero(valor,0);
    if(rv.val == ""){return vet;}
    vet.val1 = stoi(rv.val);
    //textura
    Ret rt = getNumero(valor, rv.barraPos+1);
    if(rt.val == ""){vet.val3 = 1;}else{vet.val3 = stoi(rt.val);}
    //normais
    Ret rn = getNumero(valor, rt.barraPos+1);
    if(rn.val == ""){vet.val2 = 1;}else{vet.val2 = stoi(rn.val);}
    return vet;
}

struct Vect3{
    float x, y, z;
};

struct Vect2{
    float u, v;
};

//so lê objetos triangularizados
static std::vector<Vertex> lerObj(std::string filename){
            std::vector<Vertex> vertex;
            std::vector<Vect3> vertices;
            std::vector<Vect3> normais;
            std::vector<Vect2> texturas; 
            std::vector<vectorInds> faces;
            //tenta abrir o arquivo
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cerr << "Failed to open file: " << filename << std::endl;
                return vertex;
            }
            //pega uma linha
            std::string line;
            while (std::getline(file, line)) 
            {
                //armazena o conteudo da linha em um buffer
                std::istringstream iss(line);
                std::string prefix;
                //pego o conteudo da linha ate o primeiro tab
                iss >> prefix;
                //verifico o prefixo da linha
                if (prefix == "v") { //vertice
                    Vect3 ver;
                    iss >> ver.x >> ver.y >> ver.z;
                   vertices.push_back(ver);
                } else if (prefix == "vt") { //textura
                    Vect2 tex;
                    iss >> tex.u >> tex.v;
                   texturas.push_back(tex);
                } else if (prefix == "vn") { //normal
                    Vect3 normal;
                    iss >> normal.x >> normal.y >> normal.z;
                   normais.push_back(normal);
                } else if (prefix == "f") { // face
                    std::string valor;
                    std::string Lastvalor = "";
                    //montar uma face
                    iss >> valor;
                    while(Lastvalor != valor){
                        vectorInds ind = processarString(valor);
                        Lastvalor = valor;
                        iss >> valor;
                        faces.push_back(ind);
                    }
                    
                }
            }
            //criar o vertex array final
             vertex.resize(faces.size(), Vertex());
            //carrega todos os indices
            for (int i = 0; i < vertex.size(); i++)
            {
                    vertex[i].px = vertices[faces[i].val1 - 1].x;
                    vertex[i].py = vertices[faces[i].val1 - 1].y;
                    vertex[i].pz = vertices[faces[i].val1 - 1].z;
                    vertex[i].nx = normais[faces[i].val2 - 1].x;
                    vertex[i].ny = normais[faces[i].val2 - 1].y;
                    vertex[i].nz = normais[faces[i].val2 - 1].z;
                    vertex[i].tx = texturas[faces[i].val3 - 1].u;
                    vertex[i].ty = texturas[faces[i].val3 - 1].v;
            }
            return vertex;
}



class Model
{
private:
    Texture *texture;
    std::vector<Mesh*> meshes;
    glm::vec3 position;
public:
    Model(glm::vec3 position, Texture* texture, std::vector<Mesh*> meshes){
        this->texture = texture;
        this->position = position;

        for(auto*i: meshes){
            this->meshes.push_back(new Mesh(*i)); 
        }
        for(auto& i: this->meshes){
            auto mover = createTranslation(i->getTransf(), position.x, position.y, position.z);
            i->updateTransform(mover);
        }
    }

    Model(glm::vec3 position, Texture* texture, std::string filepath){
        std::vector<Vertex> pontos = lerObj(filepath);
        if(pontos.empty()){ //nao leu nada
            return;
        }
        this->texture = texture;
        this->position = position;
        this->meshes.push_back(new Mesh(pontos.data(), pontos.size(), NULL, 0)); 
        for(auto& i: this->meshes){
            auto mover = createTranslation(i->getTransf(), position.x, position.y, position.z);
            i->updateTransform(mover);
        }
    }

    void Mover(float x, float y, float z){
        for(auto& i: this->meshes){
            auto mover = createTranslation(i->getTransf(), x, y, z);
            i->updateTransform(mover);
        }
    }

    void Scale(float fatorScale){
        for(auto& i: this->meshes){
            auto scale = createScale(i->getTransf(), fatorScale);
            i->updateTransform(scale);
        }
    }

    void ScaleVar(float fx, float fy, float fz){
        for(auto& i: this->meshes){
            auto scale = createScaleVar(i->getTransf(), fx,  fy,  fz);
            i->updateTransform(scale);
        }
    }

    void ScaleXZ(float fatorScale){
        for(auto& i: this->meshes){
            auto scale = createScaleXZ(i->getTransf(), fatorScale);
            i->updateTransform(scale);
        }
    }

    void Rotate(float angle, float x, float y, float z){
        for(auto& i: this->meshes){
            auto rotate = createRotation(i->getTransf(), angle, x, y, z);
            i->updateTransform(rotate);
        }
    }

    void render(Shader *shader){
        this->texture->bind(0, GL_TEXTURE_2D);
        shader->use();

        for(auto&i: this->meshes){
            i->Render(shader, 0);
        }
        this->texture->unbind(GL_TEXTURE_2D);
    }

    void render(Shader *shader, glm::mat4 transform){
        this->texture->bind(0, GL_TEXTURE_2D);
        shader->use();
        
        for(auto&i: this->meshes){
            i->Render(shader, 0, transform);
        }
        this->texture->unbind(GL_TEXTURE_2D);
    }
    ~Model(){
        for(auto*&i: this->meshes){
             delete i;
        }
    }
};

#endif