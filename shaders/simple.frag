#version 440

in vec3 vLighting;
in vec3 vNormal;
out vec4 pixel;
uniform vec3 color;

void main()
{
    //pixel = vPosition;
    pixel = vec4(color * vLighting, 1.0);
}
