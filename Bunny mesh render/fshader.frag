#version 330

//flat
in vec3 flat_normal;
in vec3 flat_p;
in float flat_dist;

uniform vec4 lightpos;
uniform vec3 attenuation;
uniform float Kd, Ka, Ks;
uniform vec3 light_color, La;
uniform float alpha;
uniform vec3 mat_a;
uniform vec3 mat_d;
uniform vec3 mat_s;


void main()
{
    vec3 n = normalize(flat_normal); 
    vec3 l;
    
    if (lightpos.w == 0.0){
        l = normalize(lightpos.xyz);
    } else {
        l = normalize(lightpos.xyz - flat_p); //point light
    }
    
    vec3 v = normalize(-flat_p);
    vec3 r = normalize(reflect(-l, n));

    vec3 ambient = Ka * mat_a * La;
    float att = 1.0/(attenuation.x + attenuation.y * flat_dist + attenuation.z * flat_dist * flat_dist);
    vec3 diffuse = max(dot(n, l), 0.0) * Kd * mat_d * light_color;
    float intensity = pow(max(dot(r, v), 0.0), alpha) * step(0.001, max(dot(n, l), 0.0));
    vec3 specular = Ks * mat_s * light_color * intensity;

    vec3 frag = ambient + att * (diffuse + specular);
    gl_FragColor = vec4(frag, 1.0);
}
