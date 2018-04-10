
// Define floating point precision for GLES.
#ifdef GL_ES
    precision highp float;
#endif

// Per-pixel (per-fragment) lighting.
varying vec3 position;
varying vec3 normal;
// TODO Use uniform for light position.
const vec3 lightPosition = vec3(0, -10, 30);

varying vec2 texCoord;

// Image to texture with.
uniform sampler2D image;

float lambertianReflectanceStrength(vec3 position, vec3 lightPosition)
{
    // Light direction.
    vec3 lightVector = normalize(lightPosition - position);
    // Light flux strength.
    float strength = dot(normal, lightVector);
    float diffuse = max(strength, 0.2);
    // Add attenuation.
    //float distance = length(lightPosition - position);
    //return diffuse * (1.0 / (1.0 + (0.25 * distance * distance)));
    return diffuse;
}

void main()
{
    vec2 pos = texCoord;
    vec3 color = texture2D(image, texCoord).rgb;

    // TODO:  Use pos instead of position?

    // Provide per-pixel (per-fragment) lighting.
    color *= lambertianReflectanceStrength(position, lightPosition);
    
    gl_FragColor = vec4(color, 1.0);
}

