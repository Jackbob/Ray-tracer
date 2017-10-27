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
    float height;
    glm::vec4 position;
    glm::dvec3 lightcolor;
};

class Scene {

private:
    std::vector<Triangle> triangles;
    lightsource light;

public:

    Scene() = default;
    ~Scene()  = default;

    glm::dvec3 intersectedTriangle(ray rayarg);

    void createRoom();

};


#endif //RAY_TRACER_SCENE_H
