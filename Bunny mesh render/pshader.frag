#version 330

//phong
uniform vec4 lightpos;
uniform vec3 attenuation;
uniform float Kd, Ka, Ks;
uniform vec3 light_color, La;
uniform float alpha;

uniform vec3 mat_a;
uniform vec3 mat_d;
uniform vec3 mat_s;

in vec3 normal;
in vec3 p;
in float dist;

void main()
{
    vec3 n = normalize(normal);
    vec3 l;
    if (lightpos.w == 0.0){
        l = normalize(lightpos.xyz);
    } else {
        l = normalize(lightpos.xyz - p);
    }

    vec3 v = normalize(-p);
    vec3 r = normalize(reflect(-l, n));

    vec3 ambient = Ka* mat_a * La;
    vec3 diffuse = max(dot(n, l), 0.0)*Kd*mat_d*light_color;
    float intensity = pow(max(dot(r, v), 0.0), alpha) * step(0.001, max(dot(n, l), 0.0));
    vec3 specular = Ks* mat_s * light_color * intensity;

    float att = 1.0/(attenuation.x + attenuation.y*dist + attenuation.z*dist*dist);
    vec3 frag =  ambient+ att*( diffuse +specular);
    gl_FragColor = vec4(frag, 1.0);

}