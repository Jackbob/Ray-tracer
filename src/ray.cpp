//
// Created by Jakob on 2017-09-09.
//

#include "ray.h"

ray::ray(glm::vec4 start, glm::vec4 end, glm::dvec3 color)
    : endPoint{end}, startPoint{start}, rayColor{color}
{

}
