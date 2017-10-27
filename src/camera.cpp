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

    eye1 = glm::vec4(-1.0, 0.0, 0.0, 1.0);
    eye2 = glm::vec4(-2.0, 0.0, 0.0, 1.0);

    texdata = new uint8_t[SCREEN_HEIGHT * SCREEN_WIDTH * 3];
}

void camera::render() {

    renderprocent = 0;
    generateRays(0, SCREEN_HEIGHT);
    std::vector<std::thread*> threads;
    concurentThreadsSupported = std::thread::hardware_concurrency();
    if(concurentThreadsSupported == 0)
        concurentThreadsSupported = 1;

    unsigned int rowsPerThread = SCREEN_HEIGHT/concurentThreadsSupported;
    for(int i=0; i<concurentThreadsSupported;i++){
        unsigned int fromRow = i*rowsPerThread;
        unsigned int toRow = fromRow + rowsPerThread;
        if(toRow > SCREEN_HEIGHT)
            toRow = SCREEN_HEIGHT;
        threads.emplace_back(new std::thread(&camera::rayRendering, this, fromRow, toRow));
    }
    for(auto t : threads)
        t->join();
}

//Secondary render function
//Loop through rays between certain pixel rows
void camera::rayRendering(unsigned int fromRow, unsigned int toRow) {
    for(int r=fromRow; r<toRow; r++) {
        for(auto &p : pixels[r]) {
            for (auto &ray : p.pixelRay)
                ray.rayColor = scene.intersectedTriangle(ray);
        }
        if(r % (SCREEN_HEIGHT / 100) == 0)
            renderprocent++;
        std::cout << "Render: " << renderprocent << "%" << std::endl;
    }
}

//Public function for creating the texture to use
void camera::createImage() {

    double imax = findimax();
    double truncValue = 254.99/imax;

    std::vector<std::thread*> threads;
    unsigned int rowsPerThread = SCREEN_HEIGHT/concurentThreadsSupported;
    for(int i=0; i<concurentThreadsSupported;i++){
        unsigned int fromRow = i*rowsPerThread;
        unsigned int toRow = fromRow + rowsPerThread;
        if(toRow > SCREEN_HEIGHT)
            toRow = SCREEN_HEIGHT;
        threads.emplace_back(new std::thread(&camera::truncPixelValues, this, fromRow, toRow, truncValue));
    }
    for(auto t : threads)
        t->join();

    createTexture();
}

//Truncate pixel values from 0-255 using truncation value
void camera::truncPixelValues(unsigned int fromRow, unsigned int toRow, double truncValue) {
    for(int h = fromRow;h<toRow;h++) {
        for(int w = 0;w<SCREEN_WIDTH;w++) {

            pixels[h][w].pixelColor *= truncValue;
        }
    }
}

//Find highest subpixel value to set as max value (255)
double camera::findimax() {

    double imax = 0;

    for(int h = 0;h<SCREEN_HEIGHT;h++) {
        for(int w = 0;w<SCREEN_WIDTH;w++) {
            for (auto &ray : pixels[h][w].pixelRay)
                pixels[h][w].pixelColor += ray.rayColor;

            double pIntensity = pixels[h][w].getIntensity();
            if(imax < pIntensity)
                imax = pIntensity;
        }
    }

    return imax;
}

//Returns a 
glm::vec4 camera::getPixelPos(int h, int w, std::uniform_real_distribution<> dis, std::random_device &rd) {

    std::mt19937 gen(rd());
    auto samplePos = static_cast<float>(dis(rd));
    glm::vec4 pixelPos = pixelplane[0] + (planeWidthAxis * (w * pixelStep - samplePos));
    pixelPos += planeHeigthAxis * (h * pixelStep - samplePos);
    return pixelPos;

}

void camera::generateRays(unsigned int fromRow, unsigned int toRow) {

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, pixelStep);
    for(int h=fromRow; h<toRow; h++) {
        for(int w=0; w<SCREEN_WIDTH; w++) {
            for (auto &r : pixels[h][w].pixelRay) {
                r = ray(eye1, getPixelPos(h+1,w+1, dis, rd), glm::dvec3(1.0));
            }
        }
    }
}

void camera::createScene() {
    scene.createRoom();
}

void camera::createTexture() {
    unsigned int location;
    for(int w=0;  w < SCREEN_WIDTH; w++){
        for(int h=0;h<SCREEN_HEIGHT;h++) {
            location = static_cast<unsigned int>((h*SCREEN_HEIGHT+w)*3);

            texdata[location + 0] = static_cast<uint8_t>(pixels[SCREEN_HEIGHT-h-1][w].pixelColor.x);
            texdata[location + 1] = static_cast<uint8_t>(pixels[SCREEN_HEIGHT-h-1][w].pixelColor.y);
            texdata[location + 2] = static_cast<uint8_t>(pixels[SCREEN_HEIGHT-h-1][w].pixelColor.z);
        }
    }
}
