#version 440


in vec3  position;
in vec3  normal;

out vec3 vLighting;
out vec3 vNormal;


uniform mat4 modelview_mat;
uniform mat4 projection_mat;
uniform mat4 modelviewprojection_mat;
uniform mat4 normal_mat;

void main() {
    vec3 ambientLight = vec3(0.6, 0.6, 0.6);
    vec3 directionalLightColor = vec3(0.5, 0.5, 0.75);
    vec3 directionalVector = vec3(0.85, 0.8, 0.75);

    vec4 transformedNormal = normal_mat * vec4(normal, 1.0);

    float directional = max(dot(transformedNormal.xyz, directionalVector), 0.0);


    vLighting = ambientLight + (directionalLightColor * directional);
    vNormal = normal;

    gl_Position = modelviewprojection_mat * vec4(position, 1.0);

}
