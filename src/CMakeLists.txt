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
    set(GLM_SOURCE_DIR "external/glm")
    find_package(GLFW REQUIRED glfw3)
    find_package(GLEW REQUIRED)

    include_directories(
            ${GLM_SOURCE_DIR}
            ${GLEW_INCLUDE_DIRS}
            ${GLFW_INCLUDE_DIR}
    )

    set(CMAKE_CXX_STANDARD 14)

    set(SOURCE_FILES main.cpp ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h openglfunc.cpp openglfunc.h)

    add_executable(${APP_NAME} ${SOURCE_FILES})

    target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLFW_STATIC_LIBRARIES})

endif (WIN32)


