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

vec3 Transform::Position() { return GetMatrixCol(this->localToWorld, 3).xyz(); }

vec3 Transform::Forward() { return GetMatrixCol(this->localToWorld, 2).xyz(); }

vec3 Transform::Up() { return GetMatrixCol(this->localToWorld, 1).xyz(); }

vec3 Transform::Right() { return GetMatrixCol(this->localToWorld, 0).xyz(); }