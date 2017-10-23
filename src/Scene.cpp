//
// Created by Tobias on 2017-09-09.
//

#include "Scene.h"


glm::dvec3 Scene::intersectedTriangle(ray rayarg) {

    glm::vec4* intersectpoint = nullptr;
    glm::dvec3 color = glm::dvec3(0.0, 0.0, 0.0);
    float length = FLT_MAX;
        for(auto &i:triangles) {
            intersectpoint = new glm::vec4(i.rayIntersection(rayarg));
            if(intersectpoint->w != -1.0f) {
                if((rayarg.startPoint - *intersectpoint).length() < length){
                    length = (rayarg.startPoint - *intersectpoint).length();
                    color = i.getColor();
                }
            }
        }

    return color;
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

    triangles.emplace_back(Triangle(glm::vec4(13,0,5,1), glm::vec4(13,0,-5,1), glm::vec4(10,-6,-5,1), glm::dvec3(0.5,1.0,1.0)));
    triangles.emplace_back(Triangle(glm::vec4(13,0,5,1), glm::vec4(10,-6,-5,1), glm::vec4(10,-6,5,1), glm::dvec3(0.5,1.0,1.0)));


}
