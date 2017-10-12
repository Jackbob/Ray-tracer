//
// Created by jakob on 2017-10-12.
//

#ifndef RAY_TRACER_OPENGLFUNC_H
#define RAY_TRACER_OPENGLFUNC_H

#include <glm/glm.hpp>
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <fstream>
#include <vector>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

void initOpenGL(GLFWwindow*& window);
GLuint drawQuad();
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);


#endif //RAY_TRACER_OPENGLFUNC_H
