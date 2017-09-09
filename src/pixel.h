//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_PIXEL_H
#define RAY_TRACER_PIXEL_H

#include <glm/glm.hpp>
#include "ray.h"
#include <algorithm>

class pixel {
public:
    glm::dvec3 pixelColor;
    ray* pixelRay;

    double getIntensity();
};


#endif //RAY_TRACER_PIXEL_H
