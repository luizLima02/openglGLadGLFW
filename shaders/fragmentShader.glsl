#version 430 compatibility

out vec4 frag_color;
uniform sampler2D texture_1;
uniform float uPixelSize;
uniform vec2  uTextureSize;


varying vec4 v_color;
varying vec2 v_texCoord;

void main() {
  vec2 coord = v_texCoord * uTextureSize;
  vec2 pixelCoord = floor(coord / uPixelSize) * uPixelSize;
  vec2 textureCoord = (pixelCoord + 0.3 * uPixelSize) / uTextureSize;
  
  frag_color = texture(texture_1, textureCoord); //* v_color;//v_color;
};