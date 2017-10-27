//
// Created by Tobias on 2017-09-09.
//

#include "Scene.h"


glm::dvec3 Scene::intersectedTriangle(ray rayarg) {

    glm::vec4 intersectpoint;
    glm::dvec3 color = glm::dvec3(0.0);
    Triangle* tri;
    float length = FLT_MAX;
        for(auto &i:triangles) {
            intersectpoint = glm::vec4(i.rayIntersection(rayarg));
            if(intersectpoint.w != -1.0f) {
                if((rayarg.startPoint - intersectpoint).length() < length){
                    length = (rayarg.startPoint - intersectpoint).length();
                    tri = &i;
                }
            }
        }
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);
    if(dis(gen) > ABSORPTION_CHANCE || intersectpoint.w != -1.0f) {
        switch (tri->BRDF_func.BRDF_type) {
            case LAMBERTIAN: {
                std::uniform_real_distribution<> disAngle(0.0, M_PI);
                glm::vec3 normal = tri->getNormal();
                double incOffset = abs(glm::orientedAngle(glm::normalize(glm::vec2(normal.x, normal.z)),
                                                          glm::vec2(0.0, 1.0)));
                double asiOffset = glm::orientedAngle(glm::normalize(glm::vec2(normal.x, normal.y)),
                                                      glm::vec2(1.0, 0.0));
                double randAsi = 2.0 * disAngle(rd);
                double randInc = disAngle(rd);
                glm::vec4 reflDir = glm::vec4(glm::fastCos(randAsi + asiOffset),
                                              glm::fastSin(randAsi + asiOffset),
                                              glm::fastCos(randInc + incOffset),1.0);

                ray reflRay = ray(intersectpoint, intersectpoint + reflDir, glm::dvec3(0.0));
                color = intersectedTriangle(reflRay);
                color *= IMPORTANCE;
                color += tri->getColor();
                return color;
            }
            default:
                break;
        }
    }
        /*
            glm::vec3 rayDir = glm::vec3(rayarg.endPoint - rayarg.startPoint);
            glm::vec4 reflDir = glm::vec4(glm::reflect(rayDir, tri->getNormal()), 1.0f);
            ray reflRay = ray(*intersectpoint, *intersectpoint + reflDir, glm::dvec3(0.0));
            color += intersectedTriangle(reflRay);
        }
        else
         */

        return tri->getColor();
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

    light.width = 1;
    light.height = 1;
    light.lightcolor = glm::dvec3(1.0);
    light.position = glm::vec4(5.0, 0.0, 4.9, 1.0);
}
