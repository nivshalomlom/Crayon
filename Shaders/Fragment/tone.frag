#version 430

uniform sampler2D textureSampler;

uniform float exposure;
uniform float gamma;

in vec2 texCoords;
out vec4 fragColor;

void main()
{
    vec3 color = texture2D(textureSampler, texCoords).rgb;
    vec3 mapped = vec3(1.0) - exp(-color * exposure);

    if (gamma != 1.0)
        mapped = pow(mapped, vec3(1.0 / gamma));

    fragColor = vec4(mapped, 1.0);
}