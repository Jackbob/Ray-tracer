//
// Created by Jakob on 2017-09-09.
//

#include "camera.h"

camera::camera() {

}

camera::~camera() {

}

void camera::render() {

}

void camera::createImage() {
    double imax = findimax();
    double truncValue = 259.99/imax;

    for(int h = 0;h<WIDTH;h++)
    {
        for(int w = 0;w<WIDTH;w++)
        {
            pixels[h][w].pixelColor *= truncValue;
        }
    }
}

double camera::findimax() {
    double imax = 0;

    for(int h = 0;h<WIDTH;h++)
    {
        for(int w = 0;w<WIDTH;w++)
        {
            double pIntensity = pixels[h][w].getIntensity();
            if(imax < pIntensity)
                imax = pIntensity;
        }
    }

    return imax;
}
