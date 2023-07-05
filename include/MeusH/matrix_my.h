#ifndef MATRIX_MY
#define MATRIX_MY
#include<cmath>
//glm funcoes de transformacoes
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define PI 3.14159265

glm::mat4 createRotation(glm::mat4 matriz, float angle, float v1, float v2, float v3){
    glm::mat4 rotacion = glm::rotate(matriz, angle, glm::vec3(v1, v2, v3));

    return rotacion;
}

glm::mat4 createTranslation(glm::mat4 matriz, float tansX, float tansY, float tansZ){
    glm::mat4 tansla = glm::translate(matriz, glm::vec3(tansX, tansY, tansZ));

    return tansla;
}

glm::mat4 createScale(glm::mat4 matriz, float factor){
    glm::mat4 scale = glm::scale(matriz, glm::vec3(factor, factor, factor));
    return scale;
}

glm::mat4 createPerspective(float fovy, float aspect, float near, float far){
    glm::mat4 perspect = glm::perspective(glm::radians(fovy), aspect, near, far);
    return perspect;
}

glm::mat4 createCamera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp){
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}



#endif