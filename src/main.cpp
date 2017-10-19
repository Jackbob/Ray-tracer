#include <iostream>
#include "Triangle.h"
#include "ray.h"
#include "camera.h"
#include <glm/glm.hpp>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include "openglfunc.h"

int main() {

    GLFWwindow* window;

    camera cam;
    cam.createScene();
    cam.render();
    cam.createImage();
    unsigned char texdata[SCREEN_HEIGHT * SCREEN_WIDTH * 3];
    std::fill_n(texdata, SCREEN_HEIGHT * SCREEN_WIDTH * 3, 255);
    cam.createTexture(texdata);

    initOpenGL(window);

    GLuint t = 0;

    glGenTextures( 1, &t );
    glBindTexture(GL_TEXTURE_2D, t);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SCREEN_WIDTH, SCREEN_HEIGHT, 0, GL_RGB, GL_UNSIGNED_BYTE, texdata );


    GLuint programID = LoadShaders("vertex.glsl", "fragment.glsl");
    glUseProgram(programID);
    // Create and compile our GLSL program from the shaders


    do{

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        drawQuad();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );



    return 0;
}


