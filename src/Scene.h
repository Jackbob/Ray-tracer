//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H


#include <vector>
#include "SceneObject.h"
#include "Triangle.h"
#include "Sphere.h"
#include "ray.h"
#include "glm/glm.hpp"
#include "constants.h"
#include <random>
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/fast_trigonometry.hpp"

class SceneObject;


struct lightsource {
public:
    float width;
    float breadth;
    glm::vec4 position;
    glm::dvec3 lightcolor;
    glm::vec3 orientation;
};

class Scene {

private:
    //std::vector<SceneObject*> sceneO;
    //std::vector<Triangle> triangles;
    //std::vector<Sphere> spheres;
    std::vector<SceneObject*> objects;


public:
    lightsource light;

    ray sampleShadowray(glm::vec4 fromPoint);

    Scene() = default;
    ~Scene();

    bool intersectedObject(ray rayarg, float &t, glm::vec4 &intersectpoint, BRDF &brdf, glm::vec3 &objNormal);

    void createRoom();

};


#endif //RAY_TRACER_SCENE_H
