//
// Created by jakob on 2017-10-26.
//

#ifndef RAY_TRACER_CONSTANTS_H
#define RAY_TRACER_CONSTANTS_H

#define GLM_ENABLE_EXPERIMENTAL

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400
//Rays per pixel
#define ANTIALIASING 1
//Chance of rays being absorbed by surface
#define ABSORPTION_CHANCE 0.5
//Fraction of importance from a ray reflection
#define IMPORTANCE 0.3
//Number of shadowrays per lightsource
#define N_SHADOWRAYS 2

const int pixelAmount = SCREEN_HEIGHT * SCREEN_WIDTH;

//BRDF types
#define LAMBERTIAN 0
#define SPECULAR 1
#define TRANSPERANT 2

#endif //RAY_TRACER_CONSTANTS_H
