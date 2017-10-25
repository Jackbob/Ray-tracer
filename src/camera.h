//
// Created by Jakob on 2017-09-09.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include <glm/glm.hpp>
#include "pixel.h"
#include <vector>
#include <iostream>
#include <GL/glew.h>
#include "Scene.h"
#include <mingw.thread.h>
#include <pthread.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

class camera {
private:
    glm::vec4 eye1;
    glm::vec4 eye2;
    Scene scene;

    glm::vec4 pixelplane[4];
    glm::vec4 planeWidthAxis;
    glm::vec4 planeHeigthAxis;
    float pixelStep;

    std::vector<std::vector<pixel>> pixels;


    //Finds highest pixel intensity
    double findimax();
    //Shoot rays from camera
    void generateRays(unsigned int fromRow, unsigned int toRow);

    void rayRendering(unsigned int fromRow, unsigned int toRow);

public:
    camera();
    ~camera() = default;

    glm::vec4 getPixelPos(int h, int w);
    //Renders scene connected to camera
    void render();
    //Creates image from pixel matrix
    void createImage();

    void createScene();

    void createTexture(uint8_t texdata[]);


};


#endif //RAY_TRACER_CAMERA_H
