#version 330 core

in vec2 pixelPosition;
out vec4 FragColor;
uniform vec3 eye;
uniform vec3 forward;
uniform vec3 right;
uniform vec3 up;

uniform vec3 objectMin;
uniform vec3 objectMax;
uniform sampler3D tex;

uniform mat4 inv;
uniform float isoValue;
uniform float aspect;

const float fov = radians(45.0);
const float dt = 0.005;

void main()
{

    vec2 ndc = pixelPosition * 2.0 - 1.0;
    float tanHalfFov = tan(fov * 0.5);

    vec3 rayDir = normalize(forward + ndc.x * aspect * tanHalfFov * right + ndc.y * tanHalfFov * up);

    vec3 rayPos = eye;

    vec3 t0s = (vec3(0.0) - rayPos) * (1.0 / rayDir);
    vec3 t1s = (vec3(1.0) - rayPos) * (1.0 / rayDir);
    vec3 tsmaller = min(t0s, t1s);
    vec3 tbigger  = max(t0s, t1s);
    float tEnter = max(max(tsmaller.x, tsmaller.y), tsmaller.z);
    float tExit  = min(min(tbigger.x, tbigger.y), tbigger.z);
    if (tEnter > tExit) discard;

    float t = max(0.0, tEnter);
    vec3 prevPos = rayPos + rayDir * t;
    float prevVal = texture(tex, prevPos).r;

    t += dt;

    for (; t < tExit; t += dt)
    {
        vec3 currPos = rayPos + rayDir * t;
        float currVal = texture(tex, currPos).r;

        if ((prevVal - isoValue) * (currVal - isoValue) < 0.0)
        {
            vec3 startPos = prevPos;
            vec3 endPos = currPos;
            vec3 hitPos = startPos;
           
            for(int i = 0; i < 6; i++) {
                vec3 midPos = mix(startPos, endPos, 0.5);
                float midVal = texture(tex, midPos).r;
                
                if((prevVal - isoValue) * (midVal - isoValue) < 0.0) {
                    endPos = midPos;
                } else {
                    startPos = midPos;
                    prevVal = midVal;
                }
                hitPos = midPos;
            }

            float eps = 0.005;
            vec3 grad;
            grad.x = texture(tex, hitPos + vec3(eps,0,0)).r - texture(tex, hitPos - vec3(eps,0,0)).r;
            grad.y = texture(tex, hitPos + vec3(0,eps,0)).r - texture(tex, hitPos - vec3(0,eps,0)).r;
            grad.z = texture(tex, hitPos + vec3(0,0,eps)).r - texture(tex, hitPos - vec3(0,0,eps)).r;
            
            vec3 normal = normalize(-grad);
            if (length(grad) < 0.0001) normal = vec3(0,0,0);

            vec3 lightDir = normalize(vec3(1.0,1.0,1.0));
            vec3 viewDir  = normalize(eye - hitPos);

            float diff  = max(dot(normal, lightDir), 0.0);

            vec3 reflectDir = reflect(-lightDir, normal);
            float spec  = pow(max(dot(viewDir, reflectDir), 0.0), 30.0);

            vec3 ambient = vec3(0.1, 0.1, 0.1);
            vec3 diffuseColor = vec3(0.3, 0.3, 0.8);

            vec3 color = ambient + diffuseColor * diff + vec3(1.0) * spec;

            FragColor = vec4(color, 1.0);
            return;
        }

        prevVal = currVal;
        prevPos = currPos;
    }

    FragColor = vec4(0.0);
}