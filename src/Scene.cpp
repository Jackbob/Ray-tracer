//
// Created by Tobias on 2017-09-09.
//

#include "Scene.h"

bool Scene::intersectedObject(ray rayarg, float &t, glm::vec4 &intersectpoint, BRDF &brdf, glm::vec3 &objNormal) {

    glm::vec4 testpoint;
    intersectpoint = glm::vec4(0.0,0.0,0.0,-1.0f);
    t = FLT_MAX;
    float length = FLT_MAX;
        for(auto i:objects) {
            testpoint = i->rayIntersection(rayarg, t);
            if(testpoint.w != -1.0f) {
                if(t < length){
                    length = t;
                    brdf = i->BRDF_func;
                    objNormal = i->getNormal(glm::vec3(testpoint));
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
    glm::vec4 light_sample_point = glm::vec4(dis(rd)*light.width - light.width/2.0f + light.position.x,
                                             dis(rd)*light.breadth - light.breadth/2.0f + light.position.y,
                                             light.position.z,
                                             light.position.w);

    return ray(fromPoint, light_sample_point);
}

void Scene::createRoom() {

    //Floor
    objects.emplace_back(new Triangle(glm::vec4(5,0,-5,1), glm::vec4(0,-6,-5,1), glm::vec4(10,-6,-5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,-5,1), glm::vec4(-3,0,-5,1), glm::vec4(0,-6,-5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,-5,1), glm::vec4(0,6,-5,1), glm::vec4(-3,0,-5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,-5,1), glm::vec4(10,6,-5,1), glm::vec4(0,6,-5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,-5,1), glm::vec4(13,0,-5,1), glm::vec4(10,6,-5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,-5,1), glm::vec4(10,-6,-5,1), glm::vec4(13,0,-5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));

    //Roof
    objects.emplace_back(new Triangle(glm::vec4(5,0,5,1), glm::vec4(13,0,5,1),glm::vec4(10,-6,5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,5,1), glm::vec4(10,-6,5,1), glm::vec4(0,-6,5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,5,1), glm::vec4(0,-6,5,1), glm::vec4(-3,0,5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,5,1), glm::vec4(-3,0,5,1), glm::vec4(0,6,5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,5,1), glm::vec4(0,6,5,1), glm::vec4(10,6,5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(5,0,5,1), glm::vec4(10,6,5,1), glm::vec4(13,0,5,1), glm::dvec3(1.0,1.0,1.0), LAMBERTIAN));

    //Walls
    objects.emplace_back(new Triangle(glm::vec4(10,-6,5,1), glm::vec4(0,-6,-5,1), glm::vec4(0,-6,5,1), glm::dvec3(0.0,1.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(10,-6,5,1), glm::vec4(10,-6,-5,1), glm::vec4(0,-6,-5,1), glm::dvec3(0.0,1.0,1.0), LAMBERTIAN));

    objects.emplace_back(new Triangle(glm::vec4(0,-6,5,1), glm::vec4(0,-6,-5,1), glm::vec4(-3,0,-5,1), glm::dvec3(1.0,0.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(0,-6,5,1), glm::vec4(-3,0,-5,1), glm::vec4(-3,0,5,1), glm::dvec3(1.0,0.0,1.0), LAMBERTIAN));

    objects.emplace_back(new Triangle(glm::vec4(-3,0,5,1), glm::vec4(-3,0,-5,1), glm::vec4(0,6,-5,1), glm::dvec3(1.0,1.0,0.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(-3,0,5,1), glm::vec4(0,6,-5,1), glm::vec4(0,6,5,1), glm::dvec3(1.0,1.0,0.0), LAMBERTIAN));

    objects.emplace_back(new Triangle(glm::vec4(0,6,5,1), glm::vec4(0,6,-5,1), glm::vec4(10,6,5,1), glm::dvec3(1.0,0.0,0.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(10,6,5,1), glm::vec4(0,6,-5,1), glm::vec4(10,6,-5,1), glm::dvec3(1.0,0.0,0.0), LAMBERTIAN));

    objects.emplace_back(new Triangle(glm::vec4(10,6,5,1), glm::vec4(13,0,-5,1), glm::vec4(13,0,5,1), glm::dvec3(0.0,0.0,1.0), LAMBERTIAN));
    objects.emplace_back(new Triangle(glm::vec4(10,6,5,1), glm::vec4(10,6,-5,1), glm::vec4(13,0,-5,1), glm::dvec3(0.0,0.0,1.0), LAMBERTIAN));

    objects.emplace_back(new Triangle(glm::vec4(13,0,5,1), glm::vec4(13,0,-5,1), glm::vec4(10,-6,-5,1), glm::dvec3(0.0,1.0,0.0), SPECULAR));
    objects.emplace_back(new Triangle(glm::vec4(13,0,5,1), glm::vec4(10,-6,-5,1), glm::vec4(10,-6,5,1), glm::dvec3(0.0,1.0,0.0), SPECULAR));

    objects.emplace_back(new Sphere(glm::vec4(10, 4, -5, 1), 2.0, glm::dvec3(0.8, 0.4, 0.4), LAMBERTIAN));

    objects.emplace_back(new Sphere(glm::vec4(12, -4, -3, 1), 1.5, glm::dvec3(0.5, 0.5, 0.5), TRANSPERANT));

    light.width = 1.0;
    light.breadth = 1.0;
    light.lightcolor = glm::dvec3(1.0,0.94,0.88);
    light.position = glm::vec4(5.0, 0.0, 4.5, 1.0);

}

Scene::~Scene() {

    for(auto it = objects.begin(); it != objects.end(); ++it)
    {
        delete *it;
        it = objects.erase(it);
    }
    objects.clear();
}






