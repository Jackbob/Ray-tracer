cmake_minimum_required(VERSION 3.6)
project(TNCG15)


set(GLM_SOURCE_DIR "external/glm")



include_directories(
        ${GLM_SOURCE_DIR}
        )

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp)
set(APP_NAME "Ray tracer")

add_executable(TNCG15 ${SOURCE_FILES})