//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <glm/glm.hpp>
#include "pixel.h"
#include <vector>
#include <iostream>

#define WIDTH 1000
#define HEIGHT 1000

class camera {
private:
    glm::vec4 eye1;
    glm::vec4 eye2;


    glm::vec4 pixelplane[4];
    glm::vec4 planeWidthAxis;
    glm::vec4 planeHeigthAxis;
    float pixelStep;

    std::vector<std::vector<pixel>> pixels;


    //Finds highest pixel intensity
    double findimax();

public:
    camera();
    ~camera() = default;

    glm::vec4 getPixelPos(int h, int w);
    //Renders scene connected to camera
    void render();
    //Creates image from pixel matrix
    void createImage();

};


#endif //RAY_TRACER_CAMERA_H
