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
#include "constants.h"

void initOpenGL(GLFWwindow*& window);
void drawQuad();
void drawQuad2();
GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path);



#endif //RAY_TRACER_OPENGLFUNC_H
