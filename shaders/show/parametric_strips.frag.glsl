/**
 * Example Fragment Shader
 * Sets the color and alpha of the pixel by setting gl_FragColor
 */

// Set the precision for data types used in this shader
precision highp float;
precision highp int;

// Default THREE.js uniforms available to both fragment and vertex shader
uniform mat4 modelMatrix;
uniform mat4 modelViewMatrix;
uniform mat4 projectionMatrix;
// uniform mat4 viewMatrix;
uniform mat3 normalMatrix;

// Default uniforms provided by ShaderFrog.
// uniform vec3 cameraPosition;
uniform float time;

// A uniform unique to this shader. You can modify it to the using the form
// below the shader preview. Any uniform you add is automatically given a form
uniform vec3 lineColor;
uniform vec3 ambientColor;
uniform float lineWidth;

// Example varyings passed from the vertex shader
varying vec3 vPosition;
varying vec3 vNormal;
varying vec2 vUv;
varying vec2 vUv2;

void main() {
  vec3 lightPosition = vec3(1.1, 2.2, 2.9);
  // Calculate the real position of this pixel in 3d space, taking into account
  // the rotation and scale of the model. It's a useful formula for some
  // effects. This could also be done in the vertex shader
  vec3 worldPosition = (modelMatrix * vec4(vPosition, 1.0)).xyz;

  // Calculate the normal including the model rotation and scale
  vec3 worldNormal = normalize(vec3(modelMatrix * vec4(vNormal, 0.0)));

  vec3 lightVector = normalize(lightPosition - worldPosition);

  // An example simple lighting effect, taking the dot product of the normal
  // (which way this pixel is pointing) and a user generated light position
  float brightness = dot(worldNormal, lightVector);

  float tiling = 10.0;
  float xPos = tiling * (vUv.x);
  float yPos = tiling * (vUv.y);
  float pos = fract(fract(xPos) + fract(yPos));
  float val = step(pos, lineWidth);

  vec3 col = vec3(val);
  if (col.x > 0.0) {
    col = lineColor;
  } else {
    col = vec3(1.0);
  }

  float ambientStrength = 2.0;
  vec3 ambient = ambientColor * ambientStrength;

  // Fragment shaders set the gl_FragColor, which is a vector4 of
  // ( red, green, blue, alpha ).
  gl_FragColor = vec4(col * (brightness + ambient), 1.0);

  // Uncomment lines below to see various ways of setting color

  // gl_FragColor = vec4( lineColor*(brightness+ambient), 1.0 ); // Standard
  // "Lambert" lighting gl_FragColor = vec4( vec3(brightness), 1.0 ); //Only
  // Brightness gl_FragColor = vec4( vUv.x, 0.0, 0.0, 1.0 ); //UV "U" coord as
  // red gl_FragColor = vec4( 0.0, vUv.y, 0.0, 1.0 ); //UV "V" coord as green
  // gl_FragColor = vec4( vUv.xy, 0.0, 1.0 ); //UV coord ("debug")

  // gl_FragColor = vec4( fract(xPos), 0.0, 0.0, 1.0 ); //The X position
  // fraction as red gl_FragColor = vec4( 0.0, fract(yPos), 0.0, 1.0 ); //The Y
  // position fraction as green gl_FragColor = vec4( fract(xPos), fract(yPos),
  // 0.0, 1.0 ); //The X & Y position fractions gl_FragColor = vec4( 0.0, 0.0,
  // pos, 1.0 ); //The combined pos as blue

  // gl_FragColor = vec4( step(vUv.x, 0.5), 0.0, 0.0, 1.0 ); //U coord stepped
  // at 0.5 as red gl_FragColor = vec4( smoothstep(0.6, 0.5, vUv.x), 0.0,
  // 0.0, 1.0 ); //U coord smooth stepped from 0.4 to 0.6 as red
}