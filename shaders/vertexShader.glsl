#version 430 compatibility

attribute vec4 position;
attribute vec4 color;
attribute vec2 texCoord;

varying vec4 v_color;
varying vec2 v_texCoord;

//uniform mat4 transform;
uniform mat4 move;
uniform mat4 projection;
uniform mat4 view;

/*
mat4 view = mat4(1, 0, 0,  0,
	            0, 1, 0,  0,
	            0, 0, 1, -1,
	            0, 0, 0, 1);
*/
void main()
{
    
    mat4 transform = mat4(1, 0, 0,  0,
                          0, 1, 0,  0,
                          0, 0, 1, 0,
                          0, 0, 0,  1);
    
    v_texCoord = texCoord;
    v_color = color;
    gl_Position = projection* view * transform * position;
}