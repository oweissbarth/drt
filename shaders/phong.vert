#version 440

const vec3 lightPos = vec3 (-277, 288, 547);

uniform mat4x4 modelview_mat;           // ModellView-Matrix
uniform mat4x4 modelviewprojection_mat;          // ModellViewProjection-Matrix
uniform mat4x4 normal_mat;         // Inverse transponierte ModellView-Matrix
uniform mat4x4 view_mat;

layout(location=0) in vec3  position;
layout(location=1) in vec3  normal;
layout(location=2) in vec3  vertexColor;

// Ausgabe für den Fragment-Shader
out vec3 normalInterp;
out vec3 vertPos;
out vec3 color;
out vec3 light_view;

void main()
{
	vec4 vertPos4 = modelview_mat * vec4(position, 1.0);

	vertPos = vec3(vertPos4) / vertPos4.w;
	light_view = vec3(view_mat *vec4(lightPos, 1.0));

	normalInterp = vec3(normal_mat * vec4(normal, 0.0));
	color = vertexColor;
	
	gl_Position = modelviewprojection_mat * vec4(position, 1.0);
}
