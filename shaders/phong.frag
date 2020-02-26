#version 440

const vec3 diffuseColor = vec3(0.5, 0.0, 0.0);
const vec3 specColor = vec3(1.0, 1.0, 1.0);
const vec3 ambient = vec3(0.3, 0.3, 0.3);



in vec3 normalInterp;
in vec3 vertPos;
in vec3 color;
in vec3 light_view;

void main()
{
  vec3 normal = normalize(normalInterp); 
  vec3 lightDir = normalize(light_view - vertPos);

  float lambertian = max(dot(lightDir,normal), 0.0);
  float specular = 0.0;

  if(lambertian > 0.0) {

    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 viewDir = normalize(-vertPos);

    float specAngle = max(dot(reflectDir, viewDir), 0.0);
    specular = pow(specAngle, 4.0);
    specular *= lambertian;

  }


  gl_FragColor = vec4( lambertian*color+specColor*specular*0.5+ambient, 1.0);
}
