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
#include <pthread.h>
#include "constants.h"

#ifdef _WIN32
    #include <mingw.thread.h>
#endif

#ifdef linux
    #include <thread>
#endif


class camera {
private:
    glm::vec4 eye1;
    glm::vec4 eye2;
    Scene scene;

    glm::vec4 pixelplane[4];
    glm::vec4 planeWidthAxis;
    glm::vec4 planeHeigthAxis;
    float pixelStep;

    unsigned int concurentThreadsSupported;
    double renderprocent;

    std::vector<std::vector<pixel>> pixels;


    //Finds highest pixel intensity
    double findimax();
    //Shoot rays from camera
    void generateRays(unsigned int fromRow, unsigned int toRow);

    //Render pixels that are in row
    void rayRendering(unsigned int fromRow, unsigned int toRow);

    //Normalize all pixels between 0-255
    void truncPixelValues(unsigned int fromRow, unsigned int toRow, double truncValue);

    //Creates texture to show on screen
    void createTexture();

    glm::dvec3 createRayPath(ray rayarg);

public:
    uint8_t* texdata;

    camera();
    ~camera() = default;

    glm::vec4 getPixelPos(int h, int w, std::uniform_real_distribution<> dis, std::random_device &rd);
    //Renders scene connected to camera
    void render();
    //Creates image from pixel matrix
    void createImage();

    void createScene();


};


#endif //RAY_TRACER_CAMERA_H
