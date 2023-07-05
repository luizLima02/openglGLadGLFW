#version 430 compatibility

out vec4 frag_color;
uniform sampler2D texture1;
varying vec4 v_color;
varying vec2 v_tex;

void main() {
  frag_color = texture(texture1, v_tex); //* v_color;//v_color;
};