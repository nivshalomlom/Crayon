#version 430

vec3 bloomKernal[3] = {
    vec3(0.0625, 0.125, 0.0625),
    vec3(0.125, 0.25, 0.125),
    vec3(0.0625, 0.125, 0.0625)
};

uniform sampler2D textureSampler;
uniform vec2 textureSize;

uniform float bloomThreshold;
uniform float bloomIntensity;

in vec2 texCoords;
out vec4 fragColor;

bool isInBounds(vec2 point, vec2 bounds)
{
    if (point.x < 0 || point.x >= bounds.x)
        return false;

    if (point.y < 0 || point.y >= bounds.y)
        return false;

    return true;
}

void main()
{
    vec2 texelSize = 1.0 / textureSize;
    vec3 blurredColor = vec3(0.0);

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            vec2 samplePoint = vec2(i, j) * texelSize + texCoords;
            if (isInBounds(samplePoint, textureSize))
                blurredColor += texture2D(textureSampler, samplePoint).rgb * bloomKernal[i + 1][j + 1];
        }

    vec3 color = texture2D(textureSampler, texCoords).rgb;
    fragColor = vec4(color + blurredColor * bloomIntensity, 1.0);
}