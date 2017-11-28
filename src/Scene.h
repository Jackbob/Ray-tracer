//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H


#include <vector>
#include "Triangle.h"
#include "ray.h"
#include "glm/glm.hpp"
#include "constants.h"
#include <random>
#include "glm/gtx/vector_angle.hpp"
#include "glm/gtx/fast_trigonometry.hpp"

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
    std::vector<Triangle> triangles;

public:
    lightsource light;

    ray sampleShadowray(glm::vec4 fromPoint);

    Scene() = default;
    ~Scene()  = default;

    bool intersectedTriangle(ray rayarg, float &t, glm::vec4 &intersectpoint, Triangle &tri);

    void createRoom();

};


#endif //RAY_TRACER_SCENE_H
