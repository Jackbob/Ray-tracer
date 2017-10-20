//
// Created by Jakob on 2017-09-09.
//

#include "camera.h"

camera::camera() {

    pixels.resize(SCREEN_HEIGHT, std::vector<pixel>(SCREEN_WIDTH, pixel()));

    pixelplane[0] = glm::vec4(0.0f,  1.0f, 1.0f, 1.0f);
    pixelplane[1] = glm::vec4(0.0f, -1.0f, 1.0f, 1.0f);
    pixelplane[2] = glm::vec4(0.0f, 1.0f, -1.0f, 1.0f);
    pixelplane[3] = glm::vec4(0.0f,-1.0f, -1.0f, 1.0f);

    planeWidthAxis = (pixelplane[1] - pixelplane[0]);
    planeHeigthAxis = (pixelplane[2] - pixelplane[0]);

    pixelStep = glm::length(planeHeigthAxis) / SCREEN_HEIGHT;

    planeWidthAxis = glm::normalize(planeWidthAxis);
    planeHeigthAxis = glm::normalize(planeHeigthAxis);

    eye1 = glm::vec4(0.0, 0.0, 1.0, 1.0);
    eye2 = glm::vec4(0.0, 0.0, 2.0, 1.0);
}

void camera::render() {

    generateRays();
    for(auto &pixelrow : pixels) {
        for(auto &p : pixelrow) {
            p.pixelColor = scene.intersectedTriangle(p.pixelRay);
        }
    }

}

void camera::createImage() {

    double imax = findimax();
    double truncValue = 254.99/imax;

    for(int h = 0;h<SCREEN_WIDTH;h++) {
        for(int w = 0;w<SCREEN_WIDTH;w++) {
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

void camera::generateRays() {
    for(int h=0; h<SCREEN_HEIGHT; h++) {
        for(int w=0; w<SCREEN_WIDTH; w++) {
            pixels[h][w].pixelRay = ray(eye1, getPixelPos(h+1,w+1), glm::dvec3(1.0,1.0,1.0));
        }
    }
}

void camera::createScene() {
    scene.createRoom();
}

void camera::createTexture(uint8_t texdata[]) {
    unsigned int location;
    for(int w=0;  w < SCREEN_WIDTH; w++){
        for(int h=0;h<SCREEN_HEIGHT;h++) {
            location = static_cast<unsigned int>((h*SCREEN_WIDTH+w));

            texdata[location + 0] = static_cast<uint8_t>(pixels[h][w].pixelColor.x);
            texdata[location + 1] = static_cast<uint8_t>(pixels[h][w].pixelColor.y);
            texdata[location + 2] = static_cast<uint8_t>(pixels[h][w].pixelColor.z);
        }
    }
}
