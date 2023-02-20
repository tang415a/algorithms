#version 410

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition; // Light position in eye coords.
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main() {
  // Convert normal and position to eye coords
  // normal matrix is the inverse matrix of the tranpose matrix of model view
  // matrix
  // I = Ld * Kd * cos(theta) where cos(theta) = (n.dot(l)) / (|n||l|)
  vec3 tnorm = normalize(NormalMatrix * VertexNormal);
  vec4 eyeCoords = ModelViewMatrix * vec4(VertexPosition, 1.0);
  vec3 s = normalize(vec3(LightPosition - eyeCoords));

  LightIntensity = Ld * Kd * max(dot(s, tnorm), 0.0);
  // finally store the vertex clip coordinate in the built-in output variable
  // `gl_position`
  gl_Position = MVP * vec4(VertexPosition, 1.0);
}