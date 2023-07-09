#version 430 compatibility

layout (location = 0) in vec4 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

varying vec3 v_normal;
varying vec2 v_texCoord;

//light
uniform vec3 lightpos;
varying vec3 pointToLight;

uniform vec3 campos;
varying vec3 pointToCam;

uniform mat4 transform;
uniform mat4 move;
uniform mat4 projection;
uniform mat4 view;


void main()
{
    
    
    pointToLight = lightpos - position.xyz;
    pointToCam = campos - position.xyz;

    v_normal = (transform*vec4(normal, 1.0)).xyz;

    v_texCoord = texCoord;
    v_normal = normal;
    gl_Position = projection* view * transform * position;
}