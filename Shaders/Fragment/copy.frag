#version 430

uniform sampler2D textureSampler;

in vec2 texCoords;
out vec4 fragColor;

void main()
{
    fragColor = texture2D(textureSampler, texCoords);
}