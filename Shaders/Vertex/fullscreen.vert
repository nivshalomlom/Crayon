#version 430

const ivec2 vertcies[3] = {
    ivec2(-1, -1),
    ivec2( 3, -1),
    ivec2(-1,  3)
};

out vec2 texCoords;

void main()
{
    ivec2 vertex = vertcies[gl_VertexID];
    texCoords = vec2(vertex + 1) * 0.5;
    gl_Position = vec4(vertex, 0, 1);
}