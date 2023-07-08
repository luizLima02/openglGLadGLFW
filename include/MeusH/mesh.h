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
    float r;
    float g;
    float b;
    float a;
    //glm::vec2 textCoord;
    float tx;
    float ty;
};

class Mesh
{
    private:
        //std::vector<Vertex> vertices;
        unsigned verticesQnt;
        //std::vector<int> indices;
        unsigned indicesQnt;
        //buffers
        unsigned int VBO;
        unsigned int EAB; 

        void initBuffers(Vertex* vertices, const unsigned & qntVertices, unsigned int* indices, const unsigned& qntIndices){
            this->verticesQnt = qntVertices;
            this->indicesQnt = qntIndices;
            //crio os buffers e mando os dados
            //Vertex buffer
            glGenBuffers(1, &this->VBO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->verticesQnt * sizeof(Vertex), vertices, GL_STATIC_DRAW);

            //Indices buffer
            glGenBuffers(1, &this->EAB);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EAB);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesQnt * sizeof(unsigned int), indices, GL_STATIC_DRAW);
            //envio os dados para a placa
            //posicoes
            glVertexAttribPointer(0, 
                                  3,
                                  GL_FLOAT,
                                  false, 
                                  9*sizeof(float), 
                                  (void*)0);
            glEnableVertexAttribArray(0);
            //cores
            glVertexAttribPointer(1, 
                                  4,
                                  GL_FLOAT,
                                  false, 
                                  9*sizeof(float), 
                                  (void*)3);
            glEnableVertexAttribArray(1);
            //coordenadas de textura
            glVertexAttribPointer(2, 
                                  2,
                                  GL_FLOAT,
                                  false, 
                                  9*sizeof(float), 
                                  (void*)(7*sizeof(float)));
            glEnableVertexAttribArray(2);

        }   
    public:

    Mesh(Vertex* vertices, const unsigned & qntVertices, unsigned int* indices, const unsigned& qntIndices){
        this->initBuffers(vertices, qntVertices, indices, qntIndices);
    }

    ~Mesh(){
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EAB);
    }

    void Render(Shader *shader, unsigned int textI){
        
        //ativa shader
        shader->use();

        shader->setInt("texture_1", textI);
        shader->setFloat("uPixelSize", 5.0f);
        shader->set2dVec("uTextureSize", (float)256, (float)256);
        //renderiza
        glDrawElements(GL_TRIANGLES, this->indicesQnt, GL_UNSIGNED_INT, 0);
    }
};



#endif
