//
// Created by tobias on 2017-12-12.
//

//#include "SceneObject.h"


/*

bool SceneObject::intersectedObject(ray rayarg, float &t, glm::vec4 &intersectpoint,
                                                             obj &object)
{
    glm::vec4 testpoint;
    intersectpoint = glm::vec4(0.0,0.0,0.0,-1.0f);
    t = FLT_MAX;
    float length = FLT_MAX;
    for(auto &i:object) {
        testpoint = i.rayIntersection(rayarg, t);
        if(testpoint.w != -1.0f) {
            if(t < length){
                length = t;
                object = i;
                intersectpoint = testpoint;
            }
        }
    }
    return intersectpoint.w != -1.0f;
}



glm::dvec3 SceneObject::getColor() {
    return color;
}

template <class obj> void SceneObject<obj>::addToObjectVec(std::vector<obj> &o) {
    objects.emplace_back(o);
}

template <class obj> std::vector<SceneObject<obj>> SceneObject<obj>::getObjects() {
    return objects;
}




template <class obj> glm::vec4 SceneObject<obj>::rayIntersection(ray rayarg, float &t)
{

}
*/
