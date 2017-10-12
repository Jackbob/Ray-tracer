#include <iostream>
#include "Triangle.h"
#include "ray.h"
#include "camera.h"
#include <glm/glm.hpp>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include "openglfunc.h"

GLFWwindow* window;

int main() {


    ray r(glm::vec4(0.2f,0.2f,1.0f,1.0f), glm::vec4(0.2f,0.2f,0.0f, 1.0f), glm::dvec3(1.0,1.0,1.0));
    Triangle tri(glm::vec4(0.0f,0.0f,0.0f,1.0f), glm::vec4(1.0f,0.0f,0.0f,1.0f), glm::vec4(0.0f,1.0f,0.0f,1.0f), glm::dvec3(1.0,0.0,0.0) );

    glm::vec4 p = tri.rayIntersection(r);

    if(p.w != -1.0f)
        std::cout << p.x << " " << p.y << " " << p.z << std::endl;
    else
        std::cout << "No intersection" << std::endl;


    camera cam;

    glm::vec4 pixelPos = cam.getPixelPos(1000, 1000);

    std::cout << pixelPos.x << " " << pixelPos.y << " " << pixelPos.z << std::endl;

    /*
    initOpenGL(window);
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "vertex.glsl", "fragment.glsl" );


    do{
        // Draw nothing, see you in tutorial 2 !
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programID);
        drawQuad();

        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
    */


    return 0;
}


