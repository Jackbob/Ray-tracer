//
// Created by Tobias on 2017-09-09.
//

#ifndef RAY_TRACER_TRIANGLE_H
#define RAY_TRACER_TRIANGLE_H

#include "SceneObject.h"
#include <glm/glm.hpp>
#include "constants.h"

class SceneObject;

/*struct BRDF {
    int BRDF_type;
};*/

//template<class obj>
class Triangle: public virtual SceneObject {

private:
    glm::dvec3 color;
    glm::vec3 normal;
    glm::vec4 vertex1, vertex2, vertex3;

public:

    //Constructor
    Triangle() = default;
    Triangle(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3, glm::dvec3 c, int BRDFType);

    glm::vec3 calculateNormal(glm::vec4 v1, glm::vec4 v2, glm::vec4 v3);
    glm::vec3 getNormal() override {return normal;}

    //Destructor
    ~Triangle() = default;

    /*should compute the intersection between a ray and a triangle
      with the Möller- Trumbore algorithm*/
    glm::vec4 rayIntersection(ray rayarg, float &t);
    glm::dvec3 getColor();
};


#endif //RAY_TRACER_TRIANGLE_H
