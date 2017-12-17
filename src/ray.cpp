//
// Created by Jakob on 2017-09-09.
//

#include "ray.h"

ray::ray(glm::vec4 start, glm::vec4 end, glm::dvec3 color)
    : startPoint{start}, endPoint{end}, rayColor{color} {}

ray::ray(glm::vec4 start, glm::vec4 end)
        : startPoint{start}, endPoint{end} {
    rayColor = glm::dvec3(0.0);
}

double ray::getIntensity() {
    return std::max(std::max(rayColor.x, rayColor.y), rayColor.z);
}

glm::vec4 ray::getDirection() {
    return endPoint - startPoint;
}

