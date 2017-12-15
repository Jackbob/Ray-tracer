//
// Created by tobias on 2017-11-07.
//

#include "Sphere.h"


Sphere::Sphere(glm::vec4 sPosition, float sRadius, glm::dvec3 sColor):
    position{sPosition}, radius{sRadius}, color{sColor}
{
    BRDF_func.BRDF_type = LAMBERTIAN;
    BRDF_func.color = sColor;
}

glm::vec4 Sphere::rayIntersection(ray rayarg, float &t) {


    glm::vec3 rayDirection = glm::normalize(glm::vec3(rayarg.endPoint - rayarg.startPoint));
    t = FLT_MAX;

    glm::vec3 L = glm::vec3(position) - rayDirection;

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

     t = t0;

    glm::vec4 hitPoint = rayarg.startPoint + glm::vec4(rayDirection * t, 1.0f);

    calcNormal(glm::vec3(hitPoint));


    return hitPoint;



}

void Sphere::calcNormal(glm::vec3 pHit)
{
    normal = glm::normalize(pHit - glm::vec3(position));
}

glm::dvec3 Sphere::getColor() {

    return color;
}


