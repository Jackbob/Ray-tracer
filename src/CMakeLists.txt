cmake_minimum_required(VERSION 3.6)
project(Ray-tracer)


set(GLM_SOURCE_DIR "external/glm")

include_directories(
        ${GLM_SOURCE_DIR}
        )

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h)
set(APP_NAME "Ray-tracer")

add_executable(${APP_NAME} ${SOURCE_FILES})