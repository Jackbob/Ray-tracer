//
// Created by Tobias on 2017-09-09.
//


#include "Triangle.h"





Triangle::Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::dvec3 c):
vertex1{v1}, vertex2{v2}, vertex3{v3}, color{c}, normal{calculateNormal(v1,v2,v3)}
{
    BRDF_func.BRDF_type = LAMBERTIAN;
    BRDF_func.color = c;
}

glm::vec4 Triangle::rayIntersection(ray rayarg, float &t)
{
    glm::vec3 raydir = glm::normalize(glm::vec3(rayarg.endPoint - rayarg.startPoint));
    t = FLT_MAX;

    glm::vec3 v1v2 = vertex2 - vertex1;
    glm::vec3 v1v3 = vertex3 - vertex1;
    glm::vec3 pvec = glm::cross(raydir, v1v3);
    float det = glm::dot(v1v2, pvec);
    // if the determinant is negative the triangle is backfacing
    // if the determinant is close to 0, the ray misses the triangle
    if (det < FLT_EPSILON)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);
    // ray and triangle are parallel if det is close to 0
    if (fabs(det) < FLT_EPSILON)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    float invDet = 1 / det;

    glm::vec3 tvec = rayarg.startPoint - vertex1;
    float u = glm::dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    glm::vec3 qvec = glm::cross(tvec, v1v2);
    float v = glm::dot(raydir, qvec) * invDet;
    if (v < 0 || u + v > 1)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    t = glm::dot(v1v3, qvec) * invDet;

    return rayarg.startPoint + glm::vec4(raydir * t, 1.0f);
}

glm::vec3 Triangle::calculateNormal(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3) {

    glm::vec3 a = glm::vec3(v1.x, v1.y, v1.z);
    glm::vec3 b = glm::vec3(v2.x, v2.y, v2.z);
    glm::vec3 c = glm::vec3(v3.x, v3.y, v3.z);

    return glm::normalize(glm::cross(c-a, b-a));
}

glm::dvec3 Triangle::getColor() {
    return color;
}
