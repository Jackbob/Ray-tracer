//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include <glm/glm.hpp>
#include <algorithm>


class ray {
private:


public:
    glm::vec4 startPoint;
    glm::vec4 endPoint;
    glm::dvec3 rayColor;

    ray() = default;
    ray(glm::vec4 start, glm::vec4 end, glm::dvec3 color);
    ray(glm::vec4 start, glm::vec4 end);

    ~ray() = default;

    double getIntensity();
    glm::vec4 getDirection();
};


#endif //RAY_TRACER_RAY_H
