//
// Created by tobias on 2017-12-12.
//

#ifndef RAY_TRACER_SCENEOBJECT_H
#define RAY_TRACER_SCENEOBJECT_H
//class Triangle;
//class Sphere;

#include <glm/glm.hpp>
#include <vector>
#include "ray.h"
//#include "Triangle.h"
//#include "Sphere.h"
//#include "Scene.h"


struct BRDF {
    int BRDF_type;
    glm::dvec3 color;
};



class SceneObject {


public:
    BRDF BRDF_func;
    glm::dvec3 color;

    //SceneObject() = default;
    virtual ~SceneObject() = default;

    virtual glm::vec4 rayIntersection(ray rayarg, float &t) = 0;

    virtual glm::vec3 getNormal() = 0;
    virtual glm::vec3 getNormal(glm::vec3 pHit) = 0;

    virtual glm::dvec3 getColor() = 0;


private:


    //std::vector<SceneObject<obj>> objects;



};


#endif //RAY_TRACER_SCENEOBJECT_H
