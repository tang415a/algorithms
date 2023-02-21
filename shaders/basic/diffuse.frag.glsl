#version 410

in vec3 LightIntensity;

layout(location = 0) out vec4 FragColor;

// FragColor: the output color of the fragment
void main() { FragColor = vec4(LightIntensity, 1.0); }