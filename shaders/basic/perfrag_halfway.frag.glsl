#version 410

in vec3 Position;
in vec3 Normal;

uniform struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 La;       // Ambient light intesity
  vec3 L;        // Diffuse and specular light intensity
} Light;

uniform struct MaterialInfo {
  vec3 Ka;         // Ambient reflectivity
  vec3 Kd;         // Diffuse reflectivity
  vec3 Ks;         // Specular reflectivity
  float Shininess; // Specular shininess factor
} Material;

layout(location = 0) out vec4 FragColor;

// Computing h requires fewer operations than it takes to compute r, so we
// should expect some efficiency gain by using the halfway vector. The angle
// between the halfway vector and the normal vector is proportional to the angle
// between the vector of pure reflection (r) and the vector towards the viewer
// (v) when all vectors are coplanar. Therefore, we expect that the visual
// results will be similar, although not exactly the same.
vec3 phongModel(vec3 position, vec3 n) {
  vec3 ambient = Light.La * Material.Ka;
  vec3 s = normalize(Light.Position.xyz - position);
  float sDotN = max(dot(s, n), 0.0);
  vec3 diffuse = Material.Kd * sDotN;
  vec3 spec = vec3(0.0);
  if (sDotN > 0.0) {
    vec3 v = normalize(-position.xyz);
    vec3 h = normalize(s + v);
    spec = Material.Ks * pow(max(dot(h, n), 0.0), Material.Shininess);
  }
  return ambient + Light.L * (diffuse + spec);
}

void main() { FragColor = vec4(phongModel(Position, normalize(Normal)), 1.0); }
