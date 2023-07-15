#version 430 compatibility

out vec4 frag_color;
uniform sampler2D texture_1;
uniform float uPixelSize;
uniform vec2  uTextureSize;

varying vec2 v_texCoord;

varying vec3 v_normal;
uniform vec3 lightDirection;
uniform vec3 lightColor;

uniform bool chegada;

varying vec3 pointToLight;
varying vec3 pointToCam;

void main() {
  vec3 pToLight = normalize(pointToLight);
  vec3 pToCam = normalize(pointToCam);
  vec3 halfVec = normalize(pToCam + pToLight);
  //ligh dir
  vec3 v_normal_n = normalize(v_normal);
  vec3 lightDirection_n = normalize(-lightDirection);

  float lightd = dot(v_normal_n, lightDirection_n);
  float lightp = dot(v_normal_n, pToLight);
  float lighte = dot(v_normal_n, halfVec);

  if(lightd < 0.0) lightd = 0.0;
  if(lightp < 0.0) lightp = 0.0;
  if(lighte < 0.0) lighte = 0.0;


  //pixelando
  vec2 coord = v_texCoord * uTextureSize;
  vec2 pixelCoord = floor(coord / uPixelSize) * uPixelSize;
  vec2 textureCoord = (pixelCoord + 0.3 * uPixelSize) / uTextureSize;
  
  if(chegada){
    vec4 vcolor = vec4(1.0, 1.0, 0.0, 1.0);
    frag_color.rgb = 0.2*lightColor*vcolor.rgb;
    frag_color.rgb += 0.2*lightColor*lightd*vcolor.rgb;    
    frag_color.rgb += 0.5*lightColor*lightp*vcolor.rgb;
    frag_color.rgb += lightColor*pow(lighte, 500.0)*vcolor.rgb;  
    frag_color.a = vcolor.a;
  }else{
    vec3 texColor = texture2D(texture_1, v_texCoord).rgb;
    //saida
    frag_color.rgb = 0.2*lightColor*texColor;
    frag_color.rgb += 0.2*lightColor*lightd*texColor;    
    frag_color.rgb += 0.5*lightColor*lightp*texColor;
    frag_color.rgb += lightColor*pow(lighte, 500.0)*texColor;  
    frag_color.a = texture(texture_1, v_texCoord).a;
  }
};