//
// Created by tobias on 2017-11-07.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "SceneObject.h"
#include <glm/glm.hpp>
#include "constants.h"
//#include "Triangle.h"


class SceneObject;

//struct BRDF;

class Sphere : public virtual SceneObject {

private:

    glm::vec4 position;
    float radius;
    glm::vec3 normal;
    glm::dvec3 color;


public:

    Sphere() = default;
    Sphere(glm::vec4 sPosition, float sRadius,glm::dvec3 color, int BRDFType);

    void calcNormal(glm::vec3 pHit);
    glm::vec3 getNormal() override {return normal;}
    glm::vec3 getNormal(glm::vec3 pHit) override {calcNormal(pHit); return normal;}


    ~Sphere() override = default;

    glm::vec4 rayIntersection(ray rayarg, float &t) override;
    glm::dvec3 getColor() override;
};


#endif //RAY_TRACER_SPHERE_H
