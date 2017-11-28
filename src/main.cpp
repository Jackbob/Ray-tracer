#include <iostream>
#include "camera.h"
#include "GLFW/glfw3.h"
#include "Objects.h"
#include "openglfunc.h"
#include <chrono>

int main() {

    std::chrono::high_resolution_clock::time_point starttime = std::chrono::high_resolution_clock::now();
    GLFWwindow* window;

    camera cam;
    cam.createScene();
    cam.render();
    cam.createImage();

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
                 GL_RGB, GL_UNSIGNED_BYTE, cam.texdata);
    glGenerateMipmap(GL_TEXTURE_2D);


    glUseProgram(programID);
    // Create and compile our GLSL program from the shaders


    Objects screenquad;
    screenquad.createQuad();

    std::chrono::high_resolution_clock::time_point endtime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> time_span = endtime - starttime;
    std::cout << "Render time: " << time_span.count() << " ms,   ";
    std::cout << (int)(time_span.count() / (1000 * 60)) << "m " << ((int)time_span.count() / 1000)%60 << "s" << std::endl;

    double asiOffset = glm::orientedAngle(glm::normalize(glm::vec2(1.0,0.0)),
                                          glm::normalize(glm::vec2(1.0,1.0)));
    std::cout << asiOffset << std::endl;

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


