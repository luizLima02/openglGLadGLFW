#pragma once

#ifndef MESH_H
#define MESH_H
#include <glm/glm.hpp>
#include <vector>
#include "shaders.h"
#include "textures.h"
#include "vertex.h"
#include "primitivas.h"

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

        glm::mat4 transform;
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
                                  8*sizeof(float), 
                                  (void*)(0*sizeof(float)));
            glEnableVertexAttribArray(0);
            //normais
            glVertexAttribPointer(1, 
                                  3,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
            //coordenadas de textura
            glVertexAttribPointer(2, 
                                  2,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(6*sizeof(float)));
            glEnableVertexAttribArray(2);

        }   

        void initBuffers(Primitiva* primitiva){
            this->verticesQnt = primitiva->getVertivesQnt();
            this->indicesQnt = primitiva->getIndicesQnt();
            //crio os buffers e mando os dados
            //Vertex buffer
            glGenBuffers(1, &this->VBO);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferData(GL_ARRAY_BUFFER, this->verticesQnt * sizeof(Vertex), primitiva->getVertices(), GL_STATIC_DRAW);

            //Indices buffer
            glGenBuffers(1, &this->EAB);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EAB);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indicesQnt * sizeof(unsigned int), primitiva->getIndices(), GL_STATIC_DRAW);
            //envio os dados para a placa
            //posicoes
            glVertexAttribPointer(0, 
                                  3,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(0*sizeof(float)));
            glEnableVertexAttribArray(0);
            //cores
            glVertexAttribPointer(1, 
                                  3,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(3*sizeof(float)));
            glEnableVertexAttribArray(1);
            //coordenadas de textura
            glVertexAttribPointer(2, 
                                  2,
                                  GL_FLOAT,
                                  false, 
                                  8*sizeof(float), 
                                  (void*)(6*sizeof(float)));
            glEnableVertexAttribArray(2);

        }   

        void updateTransform(glm::mat4 transform){
            this->transform = transform;
        }
    public:

    Mesh(Vertex* vertices, const unsigned & qntVertices, unsigned int* indices, const unsigned& qntIndices){
        this->initBuffers(vertices, qntVertices, indices, qntIndices);
        glm::mat4 transform = glm::mat4(1, 0, 0,  0,
                          0, 1, 0,  0,
                          0, 0, 1, 0,
                          0, 0, 0,  1);
        this->transform = transform;
    }

    Mesh(Primitiva* primitiva){
        this->initBuffers(primitiva);
        glm::mat4 transform = glm::mat4(1, 0, 0,  0,
                                        0, 1, 0,  0,
                                        0, 0, 1, 0,
                                        0, 0, 0,  1);
        this->transform = transform;
    }

    ~Mesh(){
        glDeleteBuffers(1, &this->VBO);
        glDeleteBuffers(1, &this->EAB);
    }

    glm::mat4 getTransf(){return this->transform;}
    
    void Render(Shader *shader, unsigned int textI){
        //ativa shader
        shader->use();
        shader->setMat4("transform", this->transform);
        shader->setInt("texture_1", textI);
        shader->setFloat("uPixelSize", 5.0f);
        shader->set2dVec("uTextureSize", (float)256, (float)256);
        //renderiza
        glDrawElements(GL_TRIANGLES, this->indicesQnt, GL_UNSIGNED_INT, 0);
    }

    void Render(Shader *shader, unsigned int textI, glm::mat4 transformacao){
        //ativa shader
        this->updateTransform(transformacao);
        shader->use();
        shader->setMat4("transform", this->transform);
        shader->setInt("texture_1", textI);
        shader->setFloat("uPixelSize", 5.0f);
        shader->set2dVec("uTextureSize", (float)256, (float)256);
        //renderiza
        glDrawElements(GL_TRIANGLES, this->indicesQnt, GL_UNSIGNED_INT, 0);
    }
};

#endif
