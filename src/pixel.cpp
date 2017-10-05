//
// Created by Jakob on 2017-09-09.
//

#include "pixel.h"

double pixel::getIntensity()
{
    return std::max(std::max(pixelColor.x, pixelColor.y), pixelColor.z);
}

