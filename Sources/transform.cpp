#include "../Headers/Scene/transform.h"

using namespace glm;

vec4 GetMatrixCol(mat4 matrix, int col)
{
    return vec4(
        matrix[col][0],
        matrix[col][1],
        matrix[col][2],
        matrix[col][3]
    );
}

vec3 Transform::Position() { return GetMatrixCol(this->transform, 3).xyz(); }

vec3 Transform::Forward() { return GetMatrixCol(this->transform, 2).xyz(); }

vec3 Transform::Up() { return GetMatrixCol(this->transform, 1).xyz(); }

vec3 Transform::Right() { return GetMatrixCol(this->transform, 0).xyz(); }