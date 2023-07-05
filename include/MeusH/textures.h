#ifndef TEXTURE_H
#define TEXTURE_H

#include "shaders.h"
#include "stb_image.h"

class Texture
{
private:
    unsigned int id;
    int width;
    int height;
    int nrChannels;
public:
    Texture(const char* filePath, GLenum tipo){ 
    unsigned char *data = stbi_load(filePath, &this->width, &this->height, &this->nrChannels, 0);

    glGenTextures(1, &this->id);
    glBindTexture(tipo, this->id);

    glTexParameteri(tipo, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(tipo, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, this->width, this->height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(tipo);
    }else{
        std::cout << "ERROR::CARREGAMENTO DE TEXTURA FALHOU\n";
    }
    
    glActiveTexture(0);
    glBindTexture(tipo, 0);
    stbi_image_free(data);
    }

    ~Texture(){
        glDeleteTextures(11, &this->id);
    }

    unsigned int getId() const{ return this->id; }

    void bind(GLint texture_unit, GLenum tipo){
        glActiveTexture(GL_TEXTURE0 + texture_unit);
        glBindTexture(tipo, this->id);
    }

    void unbind(GLenum tipo){
        glActiveTexture(0);
        glBindTexture(tipo, 0);
    }
    
};

#endif
