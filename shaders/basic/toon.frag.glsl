#version 410

// The basic effect is to have large areas of constant color with sharp
// transitions between them. This simulates the way that an artist might shade
// an object using strokes of a pen or brush.

in vec3 Position;
in vec3 Normal;

uniform struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 La;       // Ambient light intesity
  vec3 L;        // Diffuse and specular light intensity
} Light;

uniform struct MaterialInfo {
  vec3 Ka; // Ambient reflectivity
  vec3 Kd; // Diffuse reflectivity
} Material;

/*
Four Levels (use three levels in this case)
Cosine of the Angle between s and n   Value used
Between 1 and 0.75                    0.75
Between 0.75 and 0.5                  0.5
Between 0.5 and 0.25                  0.25
Between 0.25 and 0.0                  0.0
*/
const int levels = 3;
const float scaleFactor = 1.0 / levels;

layout(location = 0) out vec4 FragColor;

vec3 toonShade() {
  vec3 n = normalize(Normal);
  vec3 s = normalize(Light.Position.xyz - Position);
  vec3 ambient = Light.La * Material.Ka;
  float sDotN = max(dot(s, n), 0.0);
  vec3 diffuse = Material.Kd * floor(sDotN * levels) * scaleFactor;

  return ambient + Light.L * diffuse;
}

void main() { FragColor = vec4(toonShade(), 1.0); }
