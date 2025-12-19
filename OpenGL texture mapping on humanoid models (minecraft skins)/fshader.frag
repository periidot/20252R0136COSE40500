#version 330
#extension GL_ARB_compatibility: enable 

in vec2 texcoord;
out vec4 fColor;

uniform sampler2D texmap;

void main() 
{ 
    fColor = texture(texmap, texcoord);
}