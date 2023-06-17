#version 430

vec3 bloomKernal[3] = {
    vec3(1.0, 2.0, 1.0),
    vec3(2.0, 4.0, 2.0),
    vec3(1.0, 2.0, 1.0)
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
    vec3 color = texture2D(textureSampler, texCoords).rgb;
    vec2 texelSize = 1.0 / textureSize;

    vec3 bloomColor = color * step(bloomThreshold, color);
    vec3 blurredColor = vec3(0.0);

    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
        {
            vec2 samplePoint = vec2(i, j) * texelSize + texCoords;
            if (isInBounds(samplePoint, textureSize))
                blurredColor += texture2D(textureSampler, samplePoint).rgb * bloomKernal[i + 1][j + 1];
        }

    fragColor = vec4(color + blurredColor * bloomIntensity + bloomColor, 1.0);
}