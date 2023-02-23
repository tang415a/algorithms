// #extension GL_OES_standard_derivatives : enable

precision highp float;

uniform float time;
uniform vec2 mouse;
uniform vec2 resolution;

// shadertoy emulation
#define iTime time
#define iResolution vec3(resolution, 0.1)

const int MAX_ITERS = 64;
const float EPSILON = 1e-2;

#define SPHERE1_CTR                                                            \
  vec4(0.75 * sin(0.5 * iTime), -1.5 * sin(0.5 * iTime), 5.0, 1.0)
#define SPHERE2_CTR                                                            \
  vec4(-0.69 * cos(0.5 * iTime), 1.5 * sin(0.5 * iTime), 5.0, 1.0)
#define SPHERE3_CTR                                                            \
  vec4(0.83 * cos(0.5 * iTime), -1.0 * cos(0.5 * iTime), 5.0, 1.0)
#define SPHERE4_CTR                                                            \
  vec4(1.7 * cos(0.6 * iTime), 1.7 * cos(0.7 * iTime), 5.0, 1.0)
const vec4 SPHERE1_COLOR = vec4(0.0, 0.2, 0.9, 1.0);
const vec4 SPHERE2_COLOR = vec4(0.9, 0.1, 0.9, 1.0);
const vec4 SPHERE3_COLOR = vec4(0.9, 0.1, 0.2, 1.0);
const vec4 SPHERE4_COLOR = vec4(0.9, 0.1, 0.05, 1.0);
const float SPHERE1_RAD = 0.5;
const float SPHERE2_RAD = 0.5;
const float SPHERE3_RAD = 0.5;
const float SPHERE4_RAD = 0.5;

const vec4 LIGHT1_POS = vec4(10.0, -10.0, -10.0, 1.0);
const vec4 LIGHT2_POS = vec4(0.0, 0.0, -10.0, 1.0);
const vec4 LIGHT3_POS = vec4(-10.0, 10.0, -10.0, 1.0);
const vec4 LIGHT_COLOR = vec4(0.5, 0.5, 0.5, 1.0);
const float SHINE = 499.0;
const vec4 AMBIENT = vec4(0.0); // vec4(0.06, 0.05, 0.05, 1.0);

// vec4 GROUND_COLOR = vec4(0.5* (0.5 + cos(0.05*iTime)), 0.65, 0.7 * (0.5 +
// sin(0.5*iTime)), 1.0);
vec4 GROUND_COLOR = vec4(0.5, 0.5, 0.7, 1.0);

// float saturate(float x) { return clamp(x, 0.0, 1.0); }

float sphereImplicit(in vec4 pt, in float radius, in vec4 position) {
  return length(pt - position) - radius;
}

float smin(float a, float b, float blendRadius) {
  float c = saturate(0.5 + (b - a) * (0.5 / blendRadius));
  return mix(b, a, c) - blendRadius * c * (1.0 - c);
}

void _mainImage(out vec4 fragColor, in vec2 fragCoord) {
  fragColor = vec4(0.0);

  vec4 rayDir = vec4(fragCoord.xy / iResolution.xy - vec2(0.5, 0.5), 1.0, 0.0);
  vec4 iterPos = vec4(rayDir.xyz, 1.0);
  rayDir = rayDir / length(rayDir);

  float specular = 0.0;

  vec4 color = GROUND_COLOR;
  vec3 normal = vec3(0.0, 1.0, 0.0);

  for (int i = 0; i < MAX_ITERS; i++) {
    float d =
        smin(smin(smin(sphereImplicit(iterPos, SPHERE1_RAD, SPHERE1_CTR),
                       sphereImplicit(iterPos, SPHERE2_RAD, SPHERE2_CTR), 1.3),
                  sphereImplicit(iterPos, SPHERE3_RAD, SPHERE3_CTR), 1.2),
             sphereImplicit(iterPos, SPHERE4_RAD, SPHERE4_CTR), 1.25);
    if (d < EPSILON) {
      specular = (8.0 * SHINE) / (8.0 * 3.14159265);
      float d1 =
          abs(1.0 / (EPSILON + sphereImplicit(iterPos, 0.5, SPHERE1_CTR)));
      float d2 =
          abs(1.0 / (EPSILON + sphereImplicit(iterPos, 0.5, SPHERE2_CTR)));
      float d3 =
          abs(1.0 / (EPSILON + sphereImplicit(iterPos, 0.5, SPHERE3_CTR)));
      float d4 =
          abs(1.0 / (EPSILON + sphereImplicit(iterPos, 0.5, SPHERE4_CTR)));

      float i1 = d1 / (d1 + d2 + d3 + d4);
      float i2 = d2 / (d1 + d2 + d3 + d4);
      float i3 = d3 / (d1 + d2 + d3 + d4);
      float i4 = d4 / (d1 + d2 + d3 + d4);

      vec3 normal1 = normalize(vec3(iterPos - SPHERE1_CTR));
      vec3 normal2 = normalize(vec3(iterPos - SPHERE2_CTR));
      vec3 normal3 = normalize(vec3(iterPos - SPHERE3_CTR));
      vec3 normal4 = normalize(vec3(iterPos - SPHERE4_CTR));

      normal =
          normalize(i1 * normal1 + i2 * normal2 + i3 * normal3 + i4 * normal4);
      color = (i1 * SPHERE1_COLOR + i2 * SPHERE2_COLOR + i3 * SPHERE3_COLOR +
               i4 * SPHERE4_COLOR);
      break;
    } else {
      iterPos += d * rayDir;
    }
  }

  vec3 light1dir = normalize(vec3(LIGHT1_POS - iterPos));
  vec3 light2dir = normalize(vec3(LIGHT2_POS - iterPos));
  vec3 light3dir = normalize(vec3(LIGHT3_POS - iterPos));

  vec3 r1 = -normalize(reflect(light1dir, vec3(normal)));
  vec3 r2 = -normalize(reflect(light2dir, vec3(normal)));
  vec3 r3 = -normalize(reflect(light3dir, vec3(normal)));

  vec3 v = -normalize(vec3(iterPos));
  vec3 h1 = normalize(light1dir + v);
  vec3 h2 = normalize(light2dir + v);
  vec3 h3 = normalize(light3dir + v);

  fragColor =
      LIGHT_COLOR *
      (dot(normal, light1dir) + specular * pow(max(dot(r1, h1), 0.0), SHINE) +
       dot(normal, light2dir) + specular * pow(max(dot(r2, h2), 0.0), SHINE) +
       dot(normal, light3dir) + specular * pow(max(dot(r3, h3), 0.0), SHINE));
  fragColor *= color;
  fragColor += AMBIENT;
}
void main(void) { _mainImage(gl_FragColor, gl_FragCoord.xy); }