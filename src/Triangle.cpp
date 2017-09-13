//
// Created by Tobias on 2017-09-09.
//

#include "Triangle.h"


Triangle::Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::dvec3 c):
vertex1{v1}, vertex2{v2}, vertex3{v3}, color{c}, getNormal(v1,v2,v3)
{



}

glm::dvec4 Triangle::rayIntersection(ray arg)
{
    //TODO
}

glm::vec3 Triangle::getNormal(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3) {

    glm::vec3 a = glm::vec3(v1.x, v1.y, v1.z);
    glm::vec3 b = glm::vec3(v2.x, v2.y, v2.z);
    glm::vec3 c = glm::vec3(v3.x, v3.y, v3.z);


    normal = glm::normalize(glm::cross(c-a, b-a));

}
