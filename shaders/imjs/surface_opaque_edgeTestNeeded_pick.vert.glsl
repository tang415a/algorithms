#version 300 es

//! V! Surface: Opaque; edgeTestNeeded; pick

#define TEXTURE texture
#define TEXTURE_CUBE texture
#define MAT_NORM g_nmx
#define MAT_MV u_mv
#define MAT_MVP u_mvp
#define MAT_MODEL u_modelMatrix
precision highp float;
precision highp int;

uniform vec3 u_qScale;
uniform vec3 u_qOrigin;
float g_vertexLUTIndex;
vec2 g_vertexBaseCoords;
vec2 g_vertexData2;
uniform sampler2D u_vertLUT;
uniform vec4 u_vertParams;
float g_vert_stepX;
vec2 g_vert_center;
uniform mat4 u_proj;
uniform mat4 u_mv;
uniform vec3 u_frustum;
const float kFrustumType_Ortho2d = 0.0;
const float kFrustumType_Ortho3d = 1.0;
const float kFrustumType_Perspective = 2.0;
uniform float u_renderOrder;
const float kRenderOrder_BlankingRegion = 2.0;
const float kRenderOrder_Linear = 4.0;
const float kRenderOrder_Silhouette = 6.0;
const float kRenderOrder_LitSurface = 3.0;
const float kRenderOrder_PlanarUnlitSurface = 10.0;
const float kRenderOrder_PlanarLitSurface = 11.0;
const float kRenderOrder_PlanarBit = 8.0;
out vec3 v_eyeSpace;
const uint kShaderBit_Monochrome = 1u;
const uint kShaderBit_NonUniformColor = 2u;
const uint kShaderBit_OITFlatAlphaWeight = 4u;
const uint kShaderBit_OITScaleOutput = 8u;
const uint kShaderBit_IgnoreNonLocatable = 16u;
uniform float u_shaderFlags;
vec3 g_featureIndex;
vec4 g_featureAndMaterialIndex;
out float v_surfaceFlags;
const uint kSurfaceBit_HasTexture = 1u;
const uint kSurfaceBit_ApplyLighting = 2u;
const uint kSurfaceBit_HasNormals = 4u;
const uint kSurfaceBit_IgnoreMaterial = 8u;
const uint kSurfaceBit_TransparencyThreshold = 16u;
const uint kSurfaceBit_BackgroundFill = 32u;
const uint kSurfaceBit_HasColorAndNormal = 64u;
const uint kSurfaceBit_OverrideAlpha = 128u;
const uint kSurfaceBit_OverrideRgb = 256u;
const uint kSurfaceBit_NoFaceFront = 512u;
const uint kSurfaceBit_MultiplyAlpha = 1024u;
const float kSurfaceMask_None = 0.0;
const float kSurfaceMask_HasTexture = 1.0;
const float kSurfaceMask_ApplyLighting = 2.0;
const float kSurfaceMask_HasNormals = 4.0;
const float kSurfaceMask_IgnoreMaterial = 8.0;
const float kSurfaceMask_TransparencyThreshold = 16.0;
const float kSurfaceMask_BackgroundFill = 32.0;
const float kSurfaceMask_HasColorAndNormal = 64.0;
const float kSurfaceMask_OverrideAlpha = 128.0;
const float kSurfaceMask_OverrideRgb = 256.0;
const float kSurfaceMask_NoFaceFront = 512.0;
const float kSurfaceMask_MultiplyAlpha = 1024.0;
uniform float u_surfaceFlags;
uniform float u_transparencyThreshold;
uniform float u_lineWeight;
float g_lineWeight;
out float v_lineWeight;
uniform highp vec4 u_batch_id;
out vec4 v_feature_id;
mat3 g_nmx;
out vec3 v_n;
out vec2 v_texCoord;
uniform vec4 u_qTexCoordParams;
uniform vec4 u_color;
out vec4 v_color;
vec4 mat_rgb;
vec2 mat_alpha;
bool use_material;
uniform vec4 u_materialColor;
uniform vec4 u_materialParams;
out vec4 v_materialParams;
in vec3 a_pos;

vec4 unquantizePosition(vec3 pos, vec3 origin, vec3 scale) {
  return vec4(origin + scale * pos, 1.0);
}

float decodeUInt24(vec3 v) {
  v = v * vec3(1.0, 256.0, 256.0 * 256.0); // v.y <<= 8; v.z <<= 16
  return dot(v, vec3(1.0));                // v.x+v.y+v.z => v.x | v.y | v.z
}

float decodeUInt16(vec2 v) {
  v = v * vec2(1.0, 256.0); // v.y <<= 8
  return dot(v, vec2(1.0)); // v.x+v.y => v.x | v.y
}

vec4 unquantizeVertexPosition(vec3 encodedIndex, vec3 origin, vec3 scale) {
  vec2 tc = g_vertexBaseCoords;
  vec4 enc1 = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  tc.x += g_vert_stepX;
  vec4 enc2 = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  vec3 qpos =
      vec3(decodeUInt16(enc1.xy), decodeUInt16(enc1.zw), decodeUInt16(enc2.xy));
  g_vertexData2 = enc2.zw;
  return unquantizePosition(qpos, origin, scale);
}

vec2 computeLUTCoords(float index, vec2 dimensions, vec2 center, float mult) {
  float baseIndex = index * mult;

  // Fix precision issues wherein mod(x,y) => y instead of 0 when x is multiple
  // of y...
  float epsilon = 0.5 / dimensions.x;
  float yId = floor(baseIndex / dimensions.x + epsilon);
  float xId = baseIndex - dimensions.x * yId; // replaces mod()...

  return center + vec2(xId / dimensions.x, yId / dimensions.y);
}

vec2 compute_vert_coords(float index) {
  return computeLUTCoords(index, u_vertParams.xy, g_vert_center,
                          u_vertParams.z);
}

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractShaderBit(uint flag) {
  return extractNthBit(floor(u_shaderFlags + 0.5), flag);
}

bool isShaderBitSet(uint flag) { return 0.0 != extractShaderBit(flag); }

float getFeatureIndex() {
  g_featureIndex = g_featureAndMaterialIndex.xyz;
  ;
  return decodeUInt24(g_featureIndex);
}
float computeSurfaceFlags() { return u_surfaceFlags; }

float extractSurfaceBit(uint flag) {
  return extractNthBit(floor(v_surfaceFlags + 0.5), flag);
}

bool isSurfaceBitSet(uint flag) { return 0.0 != extractSurfaceBit(flag); }

float computeLineWeight() { return g_lineWeight; }

vec4 addUInt32s(vec4 a, vec4 b) {
  vec4 c = a + b;
  if (c.x > 255.0) {
    c.x -= 256.0;
    c.y += 1.0;
  }
  if (c.y > 255.0) {
    c.y -= 256.0;
    c.z += 1.0;
  }
  if (c.z > 255.0) {
    c.z -= 256.0;
    c.w += 1.0;
  }
  return c;
}

vec3 octDecodeNormal(vec2 e) {
  e = e / 255.0 * 2.0 - 1.0;
  vec3 n = vec3(e.x, e.y, 1.0 - abs(e.x) - abs(e.y));
  if (n.z < 0.0) {
    vec2 signNotZero = vec2(n.x >= 0.0 ? 1.0 : -1.0, n.y >= 0.0 ? 1.0 : -1.0);
    n.xy = (1.0 - abs(n.yx)) * signNotZero;
  }

  return normalize(n);
}

vec3 computeLightingNormal() {
  vec2 tc = g_vertexBaseCoords;
  tc.x += 3.0 * g_vert_stepX;
  vec4 enc = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  vec2 normal = mix(g_vertexData2, enc.xy,
                    extractSurfaceBit(kSurfaceBit_HasColorAndNormal));
  return mix(vec3(0.0), normalize(MAT_NORM * octDecodeNormal(normal)),
             extractSurfaceBit(kSurfaceBit_HasNormals));
}

// params.xy = origin. params.zw = scale.
vec2 unquantize2d(vec2 qpos, vec4 params) {
  return params.xy + params.zw * qpos;
}

vec2 computeTexCoord() {
  vec2 tc = g_vertexBaseCoords;
  tc.x += 3.0 * g_vert_stepX;
  vec4 rgba = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);
  vec2 qcoords = vec2(decodeUInt16(rgba.xy), decodeUInt16(rgba.zw));
  return mix(vec2(0.0), unquantize2d(qcoords, u_qTexCoordParams),
             extractSurfaceBit(kSurfaceBit_HasTexture));
}

void decodeMaterialColor(vec4 rgba) {
  mat_rgb = vec4(rgba.rgb, float(rgba.r >= 0.0));
  mat_alpha = vec2(rgba.a, float(rgba.a >= 0.0));
}
vec4 getMaterialParams() { return u_materialParams; }
vec4 computeMaterialParams() {
  const vec4 defaults = vec4(26265.0, 65535.0, 65535.0, 13.5);
  return use_material ? getMaterialParams() : defaults;
}

vec4 computePosition(vec4 rawPos) {
  vec4 pos = MAT_MV * rawPos;

  v_eyeSpace = pos.xyz;
  const float blankingRegionOffset = 2.0 / 65536.0;
  if (kRenderOrder_BlankingRegion == u_renderOrder)
    v_eyeSpace.z -= blankingRegionOffset * (u_frustum.y - u_frustum.x);

  return u_proj * pos;
}

void computeFeatureOverrides() {
  g_featureIndex = g_featureAndMaterialIndex.xyz;
}

void computeMaterial() { decodeMaterialColor(u_materialColor); }

vec4 computeBaseColor() {
  float colorTableStart =
      u_vertParams.z * u_vertParams.w; // num rgba per-vertex times num vertices
  float colorIndex = decodeUInt16(g_vertexData2);
  vec2 tc = computeLUTCoords(colorTableStart + colorIndex, u_vertParams.xy,
                             g_vert_center, 1.0);
  vec4 lutColor = TEXTURE(u_vertLUT, tc);
  lutColor.rgb /= max(0.0001, lutColor.a);

  vec4 color =
      mix(u_color, lutColor, extractShaderBit(kShaderBit_NonUniformColor));
  return color;
}

vec4 applyMaterialColor(vec4 baseColor) {
  float useMatColor = float(use_material);
  vec3 rgb = mix(baseColor.rgb, mat_rgb.rgb, useMatColor * mat_rgb.a);
  float a = mix(baseColor.a, mat_alpha.x, useMatColor * mat_alpha.y);
  return vec4(rgb, a);
}

bool checkForLateDiscard() {
  return v_color.a < u_transparencyThreshold &&
         isSurfaceBitSet(kSurfaceBit_TransparencyThreshold);
}

void main() {
  g_vert_stepX = 1.0 / u_vertParams.x;
  float vert_stepY = 1.0 / u_vertParams.y;
  g_vert_center = vec2(0.5 * g_vert_stepX, 0.5 * vert_stepY);

  g_vertexLUTIndex = decodeUInt24(a_pos);
  g_vertexBaseCoords = compute_vert_coords(g_vertexLUTIndex);

  vec2 tc = g_vertexBaseCoords;
  tc.x += g_vert_stepX * 2.0;
  g_featureAndMaterialIndex = floor(TEXTURE(u_vertLUT, tc) * 255.0 + 0.5);

  g_lineWeight = u_lineWeight;

  g_nmx = mat3(MAT_MV);

  use_material = 0.0 == extractNthBit(floor(u_surfaceFlags + 0.5),
                                      kSurfaceBit_IgnoreMaterial);

  vec4 rawPosition = unquantizeVertexPosition(a_pos, u_qOrigin, u_qScale);
  computeFeatureOverrides();
  computeMaterial();
  vec4 baseColor = computeBaseColor();
  baseColor = applyMaterialColor(baseColor);
  v_color = baseColor;
  gl_Position = computePosition(rawPosition);
  v_surfaceFlags = computeSurfaceFlags();
  v_lineWeight = computeLineWeight();
  v_feature_id = addUInt32s(u_batch_id, vec4(g_featureIndex, 0.0)) / 255.0;
  v_n = computeLightingNormal();
  v_texCoord = computeTexCoord();
  v_materialParams = computeMaterialParams();
  if (checkForLateDiscard()) {
    gl_Position = vec4(2.0, 2.0, 2.0, 1.0);
    return;
  }
}
