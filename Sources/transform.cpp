#include "../Headers/Scene/transform.h"

using namespace glm;

vec4 GetMatrixRow(mat4 matrix, int row)
{
    return vec4(
        matrix[0][row],
        matrix[1][row],
        matrix[2][row],
        matrix[3][row]
    );
}

vec3 Transform::Position() { return GetMatrixRow(this->transform, 3).xyz(); }

vec3 Transform::Forward() { return GetMatrixRow(this->transform, 2).xyz(); }

vec3 Transform::Up() { return GetMatrixRow(this->transform, 1).xyz(); }

vec3 Transform::Right() { return GetMatrixRow(this->transform, 0).xyz(); }