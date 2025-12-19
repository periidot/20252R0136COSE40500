#version 330

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec3 normal[];
out vec3 flat_normal; 

in vec3 p[];     
out vec3 flat_p;

in float dist[];  
out float flat_dist; 


void main() 
{
    vec3 v0 = p[0];
    vec3 v1 = p[1];
    vec3 v2 = p[2];
    
    vec3 edge1 = v1 - v0;
    vec3 edge2 = v2 - v0;
    vec3 N_face = normalize(cross(edge1, edge2));

    for(int i = 0; i < gl_in.length(); i++) 
    {
        gl_Position = gl_in[i].gl_Position;
        

        flat_normal = N_face; 
       
        flat_p = p[i];        
        flat_dist = dist[i];
        
        EmitVertex();
    }
    EndPrimitive();
}