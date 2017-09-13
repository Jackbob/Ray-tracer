//
// Created by Tobias on 2017-09-09.
//

#include "Triangle.h"


Triangle::Triangle(glm::vec4 &v1, glm::vec4 &v2, glm::vec4 &v3, glm::dvec3 &c):
vertex1{v1}, vertex2{v2}, vertex3{v3}, color{c}, normal{getNormal(v1,v2,v3)}
{



}

glm::vec4 Triangle::rayIntersection(ray rayarg)
{
    if(glm::dot(normal, glm::vec3(rayarg.endPoint - rayarg.startPoint)) < FLT_EPSILON)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    float D = glm::dot(normal, glm::vec3(vertex1));
    float t = - (glm::dot(normal, glm::vec3(rayarg.startPoint)) + D) / glm::dot(normal, glm::vec3(rayarg.endPoint));
    if(t < FLT_EPSILON)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    glm::vec4 intersectPoint = rayarg.startPoint + t * rayarg.endPoint;
    intersectPoint.w = 1.0f;

    return intersectPoint;
}

glm::vec3 Triangle::getNormal(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3) {

    glm::vec3 a = glm::vec3(v1.x, v1.y, v1.z);
    glm::vec3 b = glm::vec3(v2.x, v2.y, v2.z);
    glm::vec3 c = glm::vec3(v3.x, v3.y, v3.z);

    return glm::normalize(glm::cross(c-a, b-a));
}
