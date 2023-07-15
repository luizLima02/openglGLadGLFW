#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <MeusH/matrix_my.h>
#include<vector>

//definir as possiveis opcoes de movimento de camera
enum CAMERA_MOV{
    FRENTE,
    TRAS,
    ESQUERDA,
    DIREITA
};

//valores default da camera
const float YAW             = -92.1f;
const float PITCH           = -29.2f;
const float SPEED           = 1.f;
const float SENSIBILIDADE   = 0.1f;
const float ZOOM            = 45.0f;

class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 FixedFront;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // euler Angles
    float Yaw;
    float Pitch;
    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSIBILIDADE), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        FixedFront = Front;
        updateCameraVector();
    }

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3 ffront = glm::vec3(0.0f, 0.0f, -1.0f) ,float yaw = YAW, float pitch = PITCH) : Front(glm::vec3(0.00793451f, -0.416281f, -0.909202f)), MovementSpeed(SPEED), MouseSensitivity(SENSIBILIDADE), Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Up = up;
        Yaw = yaw;
        Pitch = pitch;
        FixedFront = ffront;
        updateCameraVector();
    }

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MouseSensitivity(SENSIBILIDADE), Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        FixedFront = Front;
        updateCameraVector();
    }
     glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, Position + Front, Up);
    }

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(CAMERA_MOV direction, float deltaTime)
    {
        float velocity = MovementSpeed /* deltaTime*/;
        if (direction == FRENTE)
            Position += FixedFront * velocity;
        if (direction == TRAS)
            Position -= FixedFront * velocity;
        if (direction == ESQUERDA)
            Position -= Right * velocity;
        if (direction == DIREITA)
            Position += Right * velocity;
    }

    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true)
    {
        /*
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   += xoffset;
        Pitch += yoffset;
        std::cout << "Yaw " << Yaw << "\n";
        std::cout << "Pitch " << Pitch << "\n";

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
*/
        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVector();
    }
    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        /*
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
        */    
    }
   
private:
    void updateCameraVector()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        front.y = sin(glm::radians(Pitch));
        front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
        Front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        Up    = glm::normalize(glm::cross(Right, Front));
    }
};


#endif 