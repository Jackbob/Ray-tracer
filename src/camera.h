//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <glm/glm.hpp>
#include "pixel.h"

#define WIDTH 1000
#define HEIGHT 1000

class camera {
private:
    glm::vec4 eye1;
    glm::vec4 eye2;

    pixel pixels[HEIGHT][WIDTH];

    //Finds highest pixel intensity
    double findimax();

public:
    camera();
    ~camera();

    //Renders scene connected to camera
    void render();
    //Creates image from pixel matrix
    void createImage();

};


#endif //RAY_TRACER_CAMERA_H
