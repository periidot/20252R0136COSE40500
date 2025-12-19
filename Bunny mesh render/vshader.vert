#version 330

layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vNormal;

uniform mat4 modelviewm;
uniform mat4 projection;
uniform vec4 lightpos;

out vec3 normal;
out vec3 p;
out float dist;

void main()
{
    vec4 eyepos = modelviewm * vec4(vPosition, 1.0);
    p = eyepos.xyz;
    gl_Position = projection * eyepos;
    normal = normalize(mat3(transpose(inverse(modelviewm))) * vNormal);

    dist = length(lightpos.xyz - p);
}