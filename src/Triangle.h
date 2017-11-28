//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include <glm/glm.hpp>
#include "ray.h"
#include "constants.h"


struct BRDF {
    int BRDF_type;
};

class Triangle {

private:
    glm::dvec3 color;
    glm::vec3 normal;
    glm::vec4 vertex1, vertex2, vertex3;

public:
    BRDF BRDF_func;

    //Constructor
    Triangle() = default;
    Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::dvec3 c);

    glm::vec3 calculateNormal(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3);
    glm::vec3 getNormal(){return normal;}

    //Destructor
    ~Triangle() = default;

    /*should compute the intersection between a ray and a triangle
      with the Möller- Trumbore algorithm*/
    glm::vec4 rayIntersection(ray rayarg, float &t);
    glm::dvec3 getColor();
};


#endif //RAY_TRACER_TRIANGLE_H
