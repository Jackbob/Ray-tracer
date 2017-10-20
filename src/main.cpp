#include <iostream>
#include "Triangle.h"
#include "ray.h"
#include "camera.h"
#include <glm/glm.hpp>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "Objects.h"
#include <fstream>
#include "openglfunc.h"

int main() {

    GLFWwindow* window;

    camera cam;
    cam.createScene();
    cam.render();
    cam.createImage();

    auto* texdata = new uint8_t[SCREEN_HEIGHT * SCREEN_WIDTH * 3];

    //cam.createTexture(texdata);
    unsigned int location;
    for(int w=900;  w < 1000; w++){
        for(int h=0;h<100;h++) {
            location = static_cast<unsigned int>((h*SCREEN_HEIGHT+w)*3);

            texdata[location + 0] = 255;
            texdata[location + 1] = 0;
            texdata[location + 2] = 0;
        }
    }

    initOpenGL(window);

    GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");

    GLuint t = 0;

    glEnable(GL_TEXTURE_2D); // Required for glBuildMipmap() to work (!)
    glGenTextures( 1, &t );
    glBindTexture(GL_TEXTURE_2D, t);

    // Set parameters to determine how the texture is resized
    glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MIN_FILTER , GL_LINEAR_MIPMAP_LINEAR );
    glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_MAG_FILTER , GL_LINEAR );
    // Set parameters to determine how the texture wraps at edges
    glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_S , GL_REPEAT );
    glTexParameteri ( GL_TEXTURE_2D , GL_TEXTURE_WRAP_T , GL_REPEAT );
    glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
    // Read the texture data from file and upload it to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0,
                 GL_RGB, GL_UNSIGNED_BYTE, texdata);
    glGenerateMipmap(GL_TEXTURE_2D);


    glUseProgram(programID);
    // Create and compile our GLSL program from the shaders


    Objects screenquad;
    screenquad.createQuad();

    do{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        //drawQuad();
        screenquad.render();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );



    return 0;
}


