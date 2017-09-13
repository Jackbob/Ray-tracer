//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include <glm/glm.hpp>


class ray {
private:


public:
    glm::vec4 startPoint;
    glm::vec4 endPoint;
    glm::dvec3 rayColor;

};


#endif //RAY_TRACER_RAY_H
