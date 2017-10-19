cmake_minimum_required(VERSION 3.6)
project(Ray-tracer)

set(APP_NAME "Ray-tracer")
set(CMAKE_CXX_STANDARD 14)

if (UNIX AND NOT APPLE)
    set(GLM_SOURCE_DIR "external/glm")
        find_package(PkgConfig REQUIRED)
        pkg_search_module(GLFW REQUIRED glfw3)
        pkg_search_module(GLEW REQUIRED)

        include_directories(
                ${GLM_SOURCE_DIR}
                ${GLEW_INCLUDE_DIRS}
                ${GLFW_INCLUDE_DIR}
        )

    set(CMAKE_CXX_STANDARD 14)

    set(SOURCE_FILES main.cpp ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h openglfunc.cpp openglfunc.h)

    add_executable(${APP_NAME} ${SOURCE_FILES})

    target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})

endif (UNIX AND NOT APPLE)

if (WIN32)
    set(GLFW_SOURCE_DIR "external/glfw")
    set(GLM_SOURCE_DIR "external/glm")
    set(GLEW_SOURCE_DIR "external/glew")

    # Building only the GLFW lib
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
    set(GLFW_INSTALL OFF CACHE BOOL "")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -static-libgcc -static-libstdc++")
    set(CMAKE_CXX_STANDARD_REQUIRED ON) #...is required...
    set(CMAKE_CXX_EXTENSIONS OFF) #...without compiler extensions like gnu++11


    add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})

    include_directories(${GLFW_SOURCE_DIR}/include
            ${GLFW_SOURCE_DIR}/deps
            ${GLM_SOURCE_DIR}
            ${GLEW_SOURCE_DIR}/include)

    add_library(glew STATIC
            ${GLEW_SOURCE_DIR}/src/glew.c
            ${GLEW_SOURCE_DIR}/include
            )

    target_link_libraries(glew ${GLFW_LIBRARIES})

    add_definitions(
            -DGLEW_STATIC
    )

    set(CMAKE_CXX_STANDARD 14)

    set(SOURCE_FILES main.cpp ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h openglfunc.cpp openglfunc.h)

    add_executable(${APP_NAME} ${SOURCE_FILES})

    target_link_libraries(${APP_NAME} glfw ${GLFW_LIBRARIES} glew)

endif (WIN32)


