cmake_minimum_required(VERSION 3.6)
project(Ray-tracer)


set(GLM_SOURCE_DIR "external/glm")

if (UNIX AND NOT APPLE)
        find_package(PkgConfig REQUIRED)
        pkg_search_module(GLFW REQUIRED glfw3)
        pkg_search_module(GLEW REQUIRED)

        include_directories(
                ${GLM_SOURCE_DIR}
                ${GLEW_INCLUDE_DIRS}
                ${GLFW_INCLUDE_DIR}
        )

endif (UNIX AND NOT APPLE)

if (WIN32)
    set(GLFW_SOURCE_DIR "external/glfw")
    set(GLEW_SOURCE_DIR "external/glew")

    # Building only the GLFW lib
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "")
    set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "")
    set(GLFW_BUILD_TESTS OFF CACHE BOOL "")
    set(GLFW_BUILD_DOCS OFF CACHE BOOL "")
    set(GLFW_INSTALL OFF CACHE BOOL "")


    add_subdirectory(${GLFW_SOURCE_DIR} ${GLEW_SOURCE_DIR})

    include_directories(${GLFW_SOURCE_DIR}/include
            ${GLFW_SOURCE_DIR}/deps
            ${GLM_SOURCE_DIR}
            ${GLEW_SOURCE_DIR}/include)

    add_library(glew STATIC
            ${GLEW_SOURCE_DIR}/src/glew.c
            ${GLEW_SOURCE_DIR}/include
            )



endif (WIN32)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h openglfunc.cpp openglfunc.h)
set(APP_NAME "Ray-tracer")

add_executable(${APP_NAME} ${SOURCE_FILES})


if (UNIX AND NOT APPLE)
    target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})
    else()
    target_link_libraries(${APP_NAME} glew ${GLFW_LIBRARIES} glfw)

    add_definitions(
            -DGLEW_STATIC
    )
endif (UNIX AND NOT APPLE)
