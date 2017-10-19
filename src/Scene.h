//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H


#include <vector>
#include "Triangle.h"
#include "ray.h"
#include "glm/glm.hpp"

class Scene {

private:
    std::vector<Triangle> triangles;

public:

    Scene() = default;
    ~Scene()  = default;

    glm::dvec3 intersectedTriangle(ray rayarg);

    void createRoom();

};


#endif //RAY_TRACER_SCENE_H
