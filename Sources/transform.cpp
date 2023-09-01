#include "../Headers/Geometry/transform.h"

using namespace glm;

vec4 GetMatrixColumn(mat4 matrix, int column)
{
    return vec4(
        matrix[column][0],
        matrix[column][1],
        matrix[column][2],
        matrix[column][3]
    );
}

vec3 GetTransformAxis(mat4 transform, int axis)
{
    vec4 column = GetMatrixColumn(transform, axis);
    return glm::normalize(column.xyz());
}

vec3 Transform::Position() { return GetMatrixColumn(this->localToWorld, 3).xyz(); }

vec3 Transform::Forward() { return GetTransformAxis(this->localToWorld, 2).xyz(); }

vec3 Transform::Up() { return GetTransformAxis(this->localToWorld, 1).xyz(); }

vec3 Transform::Right() { return GetTransformAxis(this->localToWorld, 0).xyz(); }