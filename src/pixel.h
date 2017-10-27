//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_PIXEL_H
#define RAY_TRACER_PIXEL_H

#include <glm/glm.hpp>
#include "ray.h"
#include <algorithm>
#include "constants.h"

class pixel {
public:
    pixel() = default;
    ~pixel() = default;

    glm::dvec3 pixelColor;
    ray pixelRay[ANTIALIASING];

    double getIntensity();
};


#endif //RAY_TRACER_PIXEL_H
