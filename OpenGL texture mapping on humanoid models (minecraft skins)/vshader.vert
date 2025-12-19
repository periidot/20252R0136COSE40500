#version 330
#extension GL_ARB_compatibility: enable 

layout(location = 0) in vec4 vpos; 
layout(location = 1) in vec2 vtex; 

out vec2 texcoord;
uniform mat4 modelview;
uniform mat4 projection;

void main() 
{
    gl_Position = projection * modelview * vpos;
    texcoord = vtex; 
}

