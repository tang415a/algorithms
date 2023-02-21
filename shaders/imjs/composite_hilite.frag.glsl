#version 300 es

//! F! Composite-Hilite

#define TEXTURE texture
#define TEXTURE_CUBE texture
precision highp float;
precision highp int;

in vec2 v_texCoord;
uniform sampler2D u_opaque;
uniform mat3 u_hilite_settings;
uniform vec2 u_hilite_width;
uniform vec2 u_invScreenSize;
uniform sampler2D u_hilite;
out vec4 FragColor;

float computeAmbientOcclusion() { return 1.0; }

vec4 computeOpaqueColor() {
  vec4 opaque = TEXTURE(u_opaque, v_texCoord);
  opaque.rgb *= computeAmbientOcclusion();
  return opaque;
}

vec2 windowCoordsToTexCoords(vec2 wc) { return wc * u_invScreenSize; }

vec2 readEdgePixel(float xOffset, float yOffset) {
  vec2 t = windowCoordsToTexCoords(gl_FragCoord.xy + vec2(xOffset, yOffset));
  return TEXTURE(u_hilite, t).xy;
}

vec4 computeEdgeColor() {
  float hiliteWidth = u_hilite_width.x;
  float emphWidth = u_hilite_width.y;
  float maxWidth = max(hiliteWidth, emphWidth);
  if (0.0 == maxWidth)
    return vec4(0.0);

  vec2 nearest = vec2(0.0, 0.0);
  for (int x = -1; x <= 1; x++)
    for (int y = -1; y <= 1; y++)
      if (0 != x || 0 != y)
        nearest = nearest + readEdgePixel(float(x), float(y));

  nearest = nearest * vec2(float(hiliteWidth > 0.0), float(emphWidth > 0.0));
  float maxNearest = max(nearest.x, nearest.y);
  if (0.0 == maxNearest && maxWidth > 1.0) {
    for (int i = -2; i <= 2; i++) {
      float f = float(i);
      nearest = nearest + readEdgePixel(f, -2.0) + readEdgePixel(-2.0, f) +
                readEdgePixel(f, 2.0) + readEdgePixel(2.0, f);
    }

    nearest = nearest * vec2(float(hiliteWidth > 1.0), float(emphWidth > 1.0));
    maxNearest = max(nearest.x, nearest.y);
  }

  if (0.0 != maxNearest) {
    float emphasized = float(nearest.y > nearest.x);
    vec3 rgb = mix(u_hilite_settings[0], u_hilite_settings[1], emphasized);
    return vec4(rgb, 1);
  }

  return vec4(0.0);
}

vec4 computeColor() { return computeOpaqueColor(); }

vec4 computeBaseColor() {
  vec4 baseColor = computeColor();

  vec2 flags = floor(TEXTURE(u_hilite, v_texCoord).rg + vec2(0.5, 0.5));
  float isHilite = max(flags.x, flags.y);
  if (1.0 == isHilite) {
    float isEmphasize = flags.y * (1.0 - flags.x);
    vec3 rgb = mix(u_hilite_settings[0], u_hilite_settings[1], isEmphasize);
    float ratio =
        mix(u_hilite_settings[2][0], u_hilite_settings[2][1], isEmphasize) *
        isHilite;
    return vec4(mix(baseColor.rgb, rgb, ratio), 1.0);
  }

  vec4 outline = computeEdgeColor();
  return mix(baseColor, vec4(outline.rgb, 1.0), outline.a);
}

void assignFragData(vec4 baseColor) { FragColor = baseColor; }

void main() {
  vec4 baseColor = computeBaseColor();
  assignFragData(baseColor);
}