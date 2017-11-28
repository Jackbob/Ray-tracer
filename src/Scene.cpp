//
// Created by Tobias on 2017-09-09.
//

#include "Scene.h"


bool Scene::intersectedTriangle(ray rayarg, float &t, glm::vec4 &intersectpoint, Triangle &tri) {

    glm::vec4 testpoint;
    intersectpoint = glm::vec4(0.0,0.0,0.0,-1.0f);
    t = FLT_MAX;
    float length = FLT_MAX;
        for(auto &i:triangles) {
            testpoint = i.rayIntersection(rayarg, t);
            if(testpoint.w != -1.0f) {
                if(t < length){
                    length = t;
                    tri = i;
                    intersectpoint = testpoint;
                }
            }
        }
    return intersectpoint.w != -1.0f;
}

ray Scene::sampleShadowray(glm::vec4 fromPoint) {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    glm::vec4 light_sample_point = glm::vec4(dis(rd)*light.width + light.position.x,
                                             light.position.y,
                                             light.position.z,
                                             light.position.w);

    return ray(fromPoint, light_sample_point, glm::dvec3(0.0));
}

void Scene::createRoom() {

    //Floor
    triangles.emplace_back(Triangle(glm::vec4(5,0,-5,1), glm::vec4(0,-6,-5,1), glm::vec4(10,-6,-5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,-5,1), glm::vec4(-3,0,-5,1), glm::vec4(0,-6,-5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,-5,1), glm::vec4(0,6,-5,1), glm::vec4(-3,0,-5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,-5,1), glm::vec4(10,6,-5,1), glm::vec4(0,6,-5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,-5,1), glm::vec4(13,0,-5,1), glm::vec4(10,6,-5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,-5,1), glm::vec4(10,-6,-5,1), glm::vec4(13,0,-5,1), glm::dvec3(1.0,1.0,1.0)));

    //Roof
    triangles.emplace_back(Triangle(glm::vec4(5,0,5,1), glm::vec4(13,0,5,1),glm::vec4(10,-6,5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,5,1), glm::vec4(10,-6,5,1), glm::vec4(0,-6,5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,5,1), glm::vec4(0,-6,5,1), glm::vec4(-3,0,5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,5,1), glm::vec4(-3,0,5,1), glm::vec4(0,6,5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,5,1), glm::vec4(0,6,5,1), glm::vec4(10,6,5,1), glm::dvec3(1.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(5,0,5,1), glm::vec4(10,6,5,1), glm::vec4(13,0,5,1), glm::dvec3(1.0,1.0,1.0)));

    //Walls
    triangles.emplace_back(Triangle(glm::vec4(10,-6,5,1), glm::vec4(0,-6,-5,1), glm::vec4(0,-6,5,1), glm::dvec3(0.0,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(10,-6,5,1), glm::vec4(10,-6,-5,1), glm::vec4(0,-6,-5,1), glm::dvec3(0.0,1.0,1.0)));

    triangles.emplace_back(Triangle(glm::vec4(0,-6,5,1), glm::vec4(0,-6,-5,1), glm::vec4(-3,0,-5,1), glm::dvec3(1.0,0.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(0,-6,5,1), glm::vec4(-3,0,-5,1), glm::vec4(-3,0,5,1), glm::dvec3(1.0,0.0,1.0)));

    triangles.emplace_back(Triangle(glm::vec4(-3,0,5,1), glm::vec4(-3,0,-5,1), glm::vec4(0,6,-5,1), glm::dvec3(1.0,1.0,0.0)));
    triangles.emplace_back(Triangle(glm::vec4(-3,0,5,1), glm::vec4(0,6,-5,1), glm::vec4(0,6,5,1), glm::dvec3(1.0,1.0,0.0)));

    triangles.emplace_back(Triangle(glm::vec4(0,6,5,1), glm::vec4(0,6,-5,1), glm::vec4(10,6,5,1), glm::dvec3(1.0,0.0,0.0)));
    triangles.emplace_back(Triangle(glm::vec4(10,6,5,1), glm::vec4(0,6,-5,1), glm::vec4(10,6,-5,1), glm::dvec3(1.0,0.0,0.0)));

    triangles.emplace_back(Triangle(glm::vec4(10,6,5,1), glm::vec4(13,0,-5,1), glm::vec4(13,0,5,1), glm::dvec3(0.0,0.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(10,6,5,1), glm::vec4(10,6,-5,1), glm::vec4(13,0,-5,1), glm::dvec3(0.0,0.0,1.0)));

    triangles.emplace_back(Triangle(glm::vec4(13,0,5,1), glm::vec4(13,0,-5,1), glm::vec4(10,-6,-5,1), glm::dvec3(0.0,1.0,0.0)));
    triangles.emplace_back(Triangle(glm::vec4(13,0,5,1), glm::vec4(10,-6,-5,1), glm::vec4(10,-6,5,1), glm::dvec3(0.0,1.0,0.0)));

    light.width = 1;
    light.breadth = 1;
    light.lightcolor = glm::dvec3(1.0);
    light.position = glm::vec4(5.0, 0.0, 4.9, 1.0);
}