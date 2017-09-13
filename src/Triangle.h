//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include <glm/glm.hpp>
#include "ray.h"


class Triangle {

private:
    glm::dvec3 color;
    glm::vec4 normal;
    glm::vec4 vertex1, vertex2, vertex3;

public:

    //Constructor
    Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::dvec3 c);

    glm::vec3 getNormal(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3);

    //Destructor
    ~Triangle();

    /*should compute the intersection between a ray and a triangle
      with the Möller- Trumbore algorithm*/
    glm::dvec4 rayIntersection(ray arg);
};


#endif //RAY_TRACER_TRIANGLE_H
