//
// Created by tobias on 2017-11-07.
//

#include "Sphere.h"


Sphere::Sphere(glm::vec4 sPosition, float sRadius, glm::dvec3 sColor):
    position{sPosition}, radius{sRadius}, color{sColor}
{
    BRDF_function.BRDF_type = LAMBERTIAN;
}

glm::vec4 Sphere::sphereIntersection(ray rayarg) {


    glm::vec3 rayDirection = glm::normalize(glm::vec3(rayarg.endPoint - rayarg.startPoint));

    glm::vec3 L = position - rayDirection;

    float tca = glm::dot(L, rayDirection);

    if(tca < FLT_EPSILON)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    float r2 = glm::pow(radius,2);

    float d2 = glm::dot(L,L) - glm::pow(tca,2);

    if(d2 > r2)
        return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);

    float thc = glm::sqrt(r2 - d2);

    float t0 = tca -thc;
    float t1 = tca + thc;

    if (t0 > t1)
        std::swap(t0,t1);

    if (t0 < FLT_EPSILON){
        t0 = t1;
        if(t0 < FLT_EPSILON)
            return glm::vec4(0.0f, 0.0f, 0.0f, -1.0f);
    }

    float t = t0;

    return rayarg.startPoint + glm::vec4(rayDirection * t, 1.0f);



}

glm::vec3 Sphere::getNormal(glm::vec3 pHit)
{
    return glm::normalize(pHit - glm::vec3(position));
}

glm::dvec3 Sphere::getColor() {

    return color;
}


