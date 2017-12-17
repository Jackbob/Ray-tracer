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
                ray.rayColor = createRayPath(ray);
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

glm::dvec3 camera::createRayPath(ray rayarg) {


    glm::vec4 intersectpoint = glm::vec4(0.0,0.0,0.0,-1.0f);
    float intersectdistance;
    BRDF brdf;
    glm::vec3 objNormal;
    if (!scene.intersectedObject(rayarg, intersectdistance, intersectpoint, brdf, objNormal))
        return glm::dvec3(0.0);

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis(0.0, 1.0);

        switch (brdf.BRDF_type) {
            case LAMBERTIAN: {
                std::uniform_real_distribution<> disAngle(0.0, M_PI);

                double incOffset = glm::orientedAngle(glm::normalize(glm::vec2(objNormal.x, objNormal.z)),
                                                      glm::normalize(glm::vec2(0.0, 1.0)));
                double asiOffset = glm::orientedAngle(glm::normalize(glm::vec2(objNormal.x, objNormal.y)),
                                                      glm::normalize(glm::vec2(0.0, 1.0)));
                double randAsi = 2.0 * disAngle(rd);
                double randInc = disAngle(rd);
                glm::vec4 reflDir = glm::vec4(glm::fastCos(randAsi + asiOffset),
                                              glm::fastSin(randAsi + asiOffset),
                                              glm::fastCos(randInc + incOffset), 1.0);

                ray reflRay = ray(intersectpoint, intersectpoint + reflDir, glm::dvec3(0.0));
                glm::dvec3 color(0.0);
                if (dis(gen) > ABSORPTION_CHANCE) {
                    color = createRayPath(reflRay);
                    color *= IMPORTANCE;
                }

                glm::vec4 shadowIntersect;
                float shadowDistance;
                BRDF brdfDummy;
                glm::vec3 dummyNormal;
                for(int i=0; i<N_SHADOWRAYS;i++) {
                    ray shadowray = scene.sampleShadowray(intersectpoint);
                    float lightdistance = glm::length(glm::vec3(shadowray.endPoint) - glm::vec3(intersectpoint));
                    scene.intersectedObject(shadowray, shadowDistance, shadowIntersect, brdfDummy, dummyNormal);
                        //return glm::dvec3(0.0);

                    if(shadowDistance > lightdistance){

                        double shadowAngle = glm::angle(glm::normalize(objNormal),
                                                        glm::normalize(glm::vec3(shadowray.getDirection())));
                        double lightfraction;
                        if(shadowAngle > 1.57)
                            lightfraction = 0;
                        else
                            lightfraction = glm::fastCos(shadowAngle);

                        color += glm::dvec3(brdf.color.r * lightfraction * scene.light.lightcolor.r,
                                            brdf.color.g * lightfraction * scene.light.lightcolor.g,
                                            brdf.color.b * lightfraction * scene.light.lightcolor.b);
                    }

                }
                return color;
            }
            case SPECULAR: {
                glm::vec4 newDir = glm::vec4(glm::reflect(glm::vec3(rayarg.getDirection()), objNormal), 1.0);
                return createRayPath(ray(intersectpoint, intersectpoint+newDir) );
            }
            case TRANSPERANT:{
                glm::dvec3 color(0.0);
                float ind;
                if(glm::angle(glm::normalize(objNormal), glm::normalize(glm::vec3(rayarg.getDirection()))) > 1.57)
                    ind = 1.5f;
                else
                    ind = 1.0f/1.5f;

                glm::vec4 refracted = glm::vec4(glm::refract(glm::vec3(rayarg.getDirection()), objNormal, ind), 1.0);
                glm::vec4 reflect = glm::vec4(glm::reflect(glm::vec3(rayarg.getDirection()), objNormal), 1.0);
                color += createRayPath(ray(intersectpoint, intersectpoint+refracted)) * 0.7;
                color += createRayPath(ray(intersectpoint, intersectpoint+reflect)) * 0.3;
                return color;
            }
            default:
                break;
        }
        return glm::dvec3(0.0);
}
