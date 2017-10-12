//
// Created by Jakob on 2017-09-09.
//

#include "camera.h"

camera::camera() {

    pixels.resize(SCREEN_HEIGHT);
    for(auto h: pixels)
        h.resize(SCREEN_WIDTH);

    pixelplane[0] = glm::vec4(0.0f,  1.0f, 1.0f, 1.0f);
    pixelplane[1] = glm::vec4(0.0f, -1.0f, 1.0f, 1.0f);
    pixelplane[2] = glm::vec4(0.0f, 1.0f, -1.0f, 1.0f);
    pixelplane[3] = glm::vec4(0.0f,-1.0f, -1.0f, 1.0f);

    planeWidthAxis = (pixelplane[1] - pixelplane[0]);
    planeHeigthAxis = (pixelplane[2] - pixelplane[0]);

    pixelStep = glm::length(planeHeigthAxis) / SCREEN_HEIGHT;

    planeWidthAxis = glm::normalize(planeWidthAxis);
    planeHeigthAxis = glm::normalize(planeHeigthAxis);

    std::cout << pixelStep << std::endl;
}

void camera::render() {
    for(int h=1; h<= SCREEN_HEIGHT; h++){
        for(int w=1;w <= SCREEN_WIDTH; w++){
            pixels[h][w].pixelRay = new ray(eye1, getPixelPos(h,w), glm::dvec3(1.0,1.0,1.0));
        }
    }
}

void camera::createImage() {

    double imax = findimax();
    double truncValue = 259.99/imax;

    for(int h = 0;h<SCREEN_WIDTH;h++)
    {
        for(int w = 0;w<SCREEN_WIDTH;w++)
        {
            pixels[h][w].pixelColor *= truncValue;
        }
    }

}

double camera::findimax() {

    double imax = 0;

    for(int h = 0;h<SCREEN_WIDTH;h++)
    {
        for(int w = 0;w<SCREEN_WIDTH;w++)
        {
            double pIntensity = pixels[h][w].getIntensity();
            if(imax < pIntensity)
                imax = pIntensity;
        }
    }

    return imax;
}

glm::vec4 camera::getPixelPos(int h, int w) {

    glm::vec4 pixelPos = pixelplane[0] + (planeWidthAxis * (w * pixelStep - pixelStep/2));
    pixelPos += planeHeigthAxis * (h * pixelStep - pixelStep/2);
    return pixelPos;

}
