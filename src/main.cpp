#include <iostream>
#include "Triangle.h"
#include "ray.h"
#include <glm/glm.hpp>

int main() {

    ray r(glm::vec4(0.2f,0.2f,1.0f,1.0f), glm::vec4(0.2f,0.2f,0.0f, 1.0f), glm::dvec3(1.0,1.0,1.0));
    Triangle tri(glm::vec4(0.0f,0.0f,0.0f,1.0f), glm::vec4(1.0f,0.0f,0.0f,1.0f), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::dvec3(1.0,0.0,0.0) );

    glm::vec4 p = tri.rayIntersection(r);

    if(p.w != -1.0f)
        std::cout << p.x << " " << p.y << " " << p.z << std::endl;
    else
        std::cout << "No intersection" << std::endl;

    return 0;
}