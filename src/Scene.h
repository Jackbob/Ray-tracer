//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_SCENE_H
#define RAY_TRACER_SCENE_H


#include <vector>
#include "Triangle.h"

class Scene {
private:
    std::vector<Triangle> triangles;

public:
    Scene()
    {

    }

    void intersectedTriangle();



};


#endif //RAY_TRACER_SCENE_H
