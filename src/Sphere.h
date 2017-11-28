//
// Created by tobias on 2017-11-07.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H


#include <glm/glm.hpp>
#include "Triangle.h"
#include "constants.h"

class Sphere {

private:

    glm::vec3 position;
    glm::dvec3 color;
    float radius;
    BRDF BRDF_function;

public:

    Sphere() = default;
    Sphere(glm::vec4 sPosition, float sRadius,glm::dvec3 color);
    glm::vec4 sphereIntersection(ray rayarg);
    glm::vec3 getNormal(glm::vec3 pHit);
    glm::dvec3 getColor();

    ~Sphere() = default;
};


#endif //RAY_TRACER_SPHERE_H
