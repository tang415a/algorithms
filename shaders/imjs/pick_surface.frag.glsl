#version 300 es

//! F! Surface: Opaque; pick

#define TEXTURE texture
#define TEXTURE_CUBE texture
precision highp float;
precision highp int;

uniform vec3 u_frustum;
const float kFrustumType_Ortho2d = 0.0;
const float kFrustumType_Ortho3d = 1.0;
const float kFrustumType_Perspective = 2.0;
in vec3 v_eyeSpace;
const uint kShaderBit_Monochrome = 1u;
const uint kShaderBit_NonUniformColor = 2u;
const uint kShaderBit_OITFlatAlphaWeight = 4u;
const uint kShaderBit_OITScaleOutput = 8u;
const uint kShaderBit_IgnoreNonLocatable = 16u;
uniform float u_shaderFlags;
in float v_surfaceFlags;
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
in vec3 v_n;
uniform vec3 u_bgColor;
in vec2 v_texCoord;
uniform sampler2D s_texture;
uniform float u_applyGlyphTex;
in vec4 v_color;
uniform highp vec3 u_sunDir;
uniform float u_lightSettings[16];
uniform vec3 u_upVector;
uniform float u_reverseWhiteOnWhite;
uniform bool u_overrideClassifierColor;
uniform float u_renderPass;
const float kRenderPass_Background = 0.0;
const float kRenderPass_OpaqueLinear = 1.0;
const float kRenderPass_OpaquePlanar = 2.0;
const float kRenderPass_OpaqueGeneral = 3.0;
const float kRenderPass_Classification = 4.0;
const float kRenderPass_Translucent = 5.0;
const float kRenderPass_HiddenEdge = 6.0;
const float kRenderPass_Hilite = 7.0;
const float kRenderPass_WorldOverlay = 8.0;
const float kRenderPass_ViewOverlay = 9.0;
const float kRenderPass_PlanarClassification = 15.0;
vec4 g_surfaceTexel;
uniform vec4 u_monoRgb;
float mat_texture_weight;
vec2 mat_weights;
vec4 mat_specular;
in vec4 v_materialParams;
layout(location = 0) out vec4 FragColor0;
layout(location = 1) out vec4 FragColor1;
layout(location = 2) out vec4 FragColor2;

float extractNthBit(float flags, uint n) {
  return 0u != (uint(flags) & n) ? 1.0 : 0.0;
}

float extractShaderBit(uint flag) {
  return extractNthBit(floor(u_shaderFlags + 0.5), flag);
}

bool isShaderBitSet(uint flag) { return 0.0 != extractShaderBit(flag); }

float extractSurfaceBit(uint flag) {
  return extractNthBit(floor(v_surfaceFlags + 0.5), flag);
}

bool isSurfaceBitSet(uint flag) { return 0.0 != extractSurfaceBit(flag); }

vec4 sampleSurfaceTexture() { return TEXTURE(s_texture, v_texCoord); }

vec4 getSurfaceColor() { return v_color; }

void computeDirectionalLight(inout float diffuse, inout float specular,
                             vec3 normal, vec3 toEye, vec3 lightDir,
                             float lightIntensity, float specularExponent) {
  diffuse += lightIntensity * max(dot(normal, lightDir), 0.0);
  vec3 toReflectedLight = normalize(reflect(lightDir, normal));
  float specularDot = max(dot(toReflectedLight, toEye), 0.0001);
  // NB: If specularDot and specularExponent are both zero, 0^0 done below can
  // return NaN.  Must make sure specularDot is larger than zero (hence 0.0001
  // or greater, as ensured above).
  specular += lightIntensity * pow(specularDot, specularExponent);
}

float cel(float intensity) {
  float numCel = u_lightSettings[14];
  return numCel > 0.0 ? ceil(intensity * numCel) / numCel : intensity;
}
float decodeDepthRgb(vec3 rgb) {
  return dot(rgb, vec3(1.0, 1.0 / 255.0, 1.0 / 65025.0));
}

vec4 overrideColor(vec4 currentColor) {
  if (!u_overrideClassifierColor)
    return currentColor;

  if (0.0 == currentColor.a)
    return vec4(0.0, 0.0, 1.0, 0.5);

  return currentColor;
}

vec2 unpack2Bytes(float f) {
  f = floor(f + 0.5);
  vec2 v;
  v.y = floor(f / 256.0);
  v.x = floor(f - v.y * 256.0);
  return v;
}

vec2 unpackAndNormalize2Bytes(float f) { return unpack2Bytes(f) / 255.0; }

void decodeMaterialParams(vec4 params) {
  mat_weights = unpackAndNormalize2Bytes(params.x);

  vec2 texAndSpecR = unpackAndNormalize2Bytes(params.y);
  mat_texture_weight = texAndSpecR.x;

  vec2 specGB = unpackAndNormalize2Bytes(params.z);
  mat_specular = vec4(texAndSpecR.y, specGB, params.w);
}
vec4 computeBaseColor() {
  g_surfaceTexel = sampleSurfaceTexture();
  vec4 surfaceColor = getSurfaceColor();

  // Compute color for raster glyph.
  vec4 glyphColor = surfaceColor;
  const vec3 white = vec3(1.0);
  const vec3 epsilon = vec3(0.0001);
  vec3 color = glyphColor.rgb;
  vec3 delta = (color + epsilon) - white;

  // set to black if almost white
  glyphColor.rgb *= float(u_reverseWhiteOnWhite <= 0.5 || delta.x <= 0.0 ||
                          delta.y <= 0.0 || delta.z <= 0.0);
  glyphColor = vec4(glyphColor.rgb * g_surfaceTexel.rgb, g_surfaceTexel.a);

  // Choose glyph color or unmodified texture sample
  vec4 texColor = mix(g_surfaceTexel, glyphColor, u_applyGlyphTex);

  // If untextured, or textureWeight < 1.0, choose surface color.
  return mix(surfaceColor, texColor,
             extractSurfaceBit(kSurfaceBit_HasTexture) *
                 floor(mat_texture_weight));
}

vec4 applyMaterialOverrides(vec4 baseColor) {
  float textureWeight = mat_texture_weight *
                        extractSurfaceBit(kSurfaceBit_HasTexture) *
                        (1.0 - u_applyGlyphTex);
  vec4 rgba = mix(baseColor, g_surfaceTexel, textureWeight);
  rgba.rgb =
      mix(rgba.rgb, v_color.rgb, extractSurfaceBit(kSurfaceBit_OverrideRgb));
  rgba.a = mix(rgba.a, v_color.a, extractSurfaceBit(kSurfaceBit_OverrideAlpha));
  rgba.a = mix(rgba.a, v_color.a * rgba.a,
               extractSurfaceBit(kSurfaceBit_MultiplyAlpha));
  return rgba;
}

vec4 finalizeBaseColor(vec4 baseColor) {
  return mix(baseColor, vec4(u_bgColor.rgb, 1.0),
             extractSurfaceBit(kSurfaceBit_BackgroundFill));
}

bool discardByAlpha(float alpha) {
  return isSurfaceBitSet(kSurfaceBit_HasTexture) && alpha < (1.0 / 255.0);
}

vec4 applyLighting(vec4 baseColor) {
  if (baseColor.a <= 0.0 || !isSurfaceBitSet(kSurfaceBit_ApplyLighting))
    return baseColor;
  vec3 normal;
  if (dot(v_n.xyz, v_n.xyz) == 0.0) {
    // try flat normal
    normal = normalize(cross(dFdx(v_eyeSpace.xyz), dFdy(v_eyeSpace.xyz)));
    if (dot(normal.xyz, normal.xyz) == 0.0)
      return baseColor;
  } else
    normal = normalize(v_n.xyz);

  // Extract surface properties
  vec3 rgb = baseColor.rgb;

  // Check if it is front face; otherwise reverse the normal
  normal *= 2.0 * float(gl_FrontFacing) - 1.0;
  vec3 toEye = kFrustumType_Perspective == u_frustum.z
                   ? normalize(v_eyeSpace.xyz)
                   : vec3(0.0, 0.0, -1.0);

  // Extract material properties
  float diffuseWeight = mat_weights.x;
  float specularWeight = mat_weights.y * u_lightSettings[13];
  float specularExponent = mat_specular.a;
  vec3 specularColor =
      mat_specular.rgb *
      u_lightSettings[15]; // u_lightSettings[15] - specular component
  const float ambientWeight =
      1.0; // Ignore MicroStation's ambient weights - usually bogus.

  // Compute directional lights
  const vec3 portraitDir = vec3(-0.7071, 0.0, 0.7071);
  float portraitIntensity = u_lightSettings[12];
  float sunIntensity = u_lightSettings[0];

  float directionalDiffuseIntensity = 0.0;
  float directionalSpecularIntensity = 0.0;
  computeDirectionalLight(directionalDiffuseIntensity,
                          directionalSpecularIntensity, normal, toEye, u_sunDir,
                          sunIntensity, specularExponent);
  computeDirectionalLight(directionalDiffuseIntensity,
                          directionalSpecularIntensity, normal, toEye,
                          portraitDir, portraitIntensity, specularExponent);

  const float directionalFudge =
      0.92; // leftover from old lighting implementation
  vec3 diffuseAccum = cel(directionalDiffuseIntensity) * diffuseWeight * rgb *
                      directionalFudge; // directional light is white.
  vec3 specularAccum =
      directionalSpecularIntensity * specularWeight * specularColor;

  // Compute ambient light
  float ambientIntensity = u_lightSettings[4];
  vec3 ambientColor =
      vec3(u_lightSettings[1], u_lightSettings[2], u_lightSettings[3]);
  if (ambientColor.r + ambientColor.g + ambientColor.b == 0.0)
    ambientColor = rgb;

  diffuseAccum += ambientIntensity * ambientWeight * ambientColor;

  // Compute hemisphere lights
  vec3 ground =
      vec3(u_lightSettings[5], u_lightSettings[6], u_lightSettings[7]);
  vec3 sky = vec3(u_lightSettings[8], u_lightSettings[9], u_lightSettings[10]);
  float hemiIntensity = u_lightSettings[11];

  //  diffuse
  float hemiDot = dot(normal, u_upVector);
  float hemiDiffuseWeight = cel(0.5 * hemiDot + 0.5);
  vec3 hemiColor = mix(ground, sky, hemiDiffuseWeight);
  diffuseAccum += hemiIntensity * hemiColor * rgb;

  //  sky specular
  vec3 reflectSky = normalize(reflect(u_upVector, normal));
  float skyDot = max(dot(reflectSky, toEye), 0.0001);
  float hemiSpecWeight = hemiIntensity * pow(skyDot, specularExponent);

  //  ground specular
  vec3 reflectGround = normalize(reflect(-u_upVector, normal));
  float groundDot = max(dot(reflectGround, toEye), 0.0001);
  hemiSpecWeight += hemiIntensity * pow(groundDot, specularExponent);

  specularAccum += hemiSpecWeight * specularColor * hemiColor;

  // Clamp while preserving hue.
  vec3 litColor = diffuseAccum + specularAccum;
  float maxIntensity = max(litColor.r, max(litColor.g, litColor.b));
  baseColor.rgb = litColor / max(1.0, maxIntensity);

  return baseColor;
}

vec4 applyMonochrome(vec4 baseColor) {
  // Compute lit monochrome color
  vec3 litRgb = baseColor.rgb;
  litRgb = vec3(dot(litRgb, vec3(.222, .707, .071)));
  litRgb *= u_monoRgb.rgb;

  // Select lit or unlit based on u_monoColor.a
  vec4 monoColor = vec4(mix(u_monoRgb.rgb, litRgb, u_monoRgb.a), baseColor.a);

  // Select monochrome or element color based on shader flag
  return mix(baseColor, monoColor, extractShaderBit(kShaderBit_Monochrome));
}

vec4 reverseWhiteOnWhite(vec4 baseColor) {
  const vec3 white = vec3(1.0);
  const vec3 epsilon = vec3(0.0001);
  vec3 color = baseColor.rgb;
  vec3 delta = (color + epsilon) - white;
  vec4 wowColor =
      vec4(baseColor.rgb *
               vec3(float(delta.x <= 0.0 || delta.y <= 0.0 || delta.z <= 0.0)),
           baseColor.a); // set to black if almost white
  return mix(baseColor, wowColor, floor(u_reverseWhiteOnWhite + 0.5));
}

void assignFragData(vec4 baseColor) {
  if (u_renderPass >= kRenderPass_OpaqueLinear &&
      u_renderPass <= kRenderPass_OpaqueGeneral)
    baseColor.a = 1.0;
  else
    baseColor = vec4(baseColor.rgb * baseColor.a, baseColor.a);

  vec4 output0 = baseColor;
  vec4 output1 = vec4(0.0);
  vec4 output2 = vec4(0.0);
  output0 = overrideColor(output0);

  FragColor0 = output0;
  FragColor1 = output1;
  FragColor2 = output2;
}

void main() {
  decodeMaterialParams(v_materialParams);

  vec4 baseColor = computeBaseColor();
  baseColor = applyMaterialOverrides(baseColor);
  baseColor = finalizeBaseColor(baseColor);
  if (discardByAlpha(baseColor.a)) {
    discard;
    return;
  }
  baseColor = applyLighting(baseColor);
  baseColor = applyMonochrome(baseColor);
  baseColor = reverseWhiteOnWhite(baseColor);
  assignFragData(baseColor);
}