cmake_minimum_required(VERSION 3.6)
project(Ray-tracer)

set(APP_NAME "Ray-tracer")


if (UNIX AND NOT APPLE)
    set(GLM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/glm")
        find_package(PkgConfig REQUIRED)
        pkg_search_module(GLFW REQUIRED glfw3)
        pkg_search_module(GLEW REQUIRED glew)
        find_package(Threads REQUIRED)

    if(THREADS_HAVE_PTHREAD_ARG)
        target_compile_options(${APP_NAME} PUBLIC "-pthread")
    endif()

        include_directories(
                ${GLM_SOURCE_DIR}
                ${GLEW_INCLUDE_DIRS}
                ${GLFW_INCLUDE_DIR}
        )

    set(CMAKE_CXX_STANDARD 14)

    set(SOURCE_FILES main.cpp Objects.cpp Objects.h ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h openglfunc.cpp openglfunc.h)

    add_executable(${APP_NAME} ${SOURCE_FILES})

    target_link_libraries(${APP_NAME} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} ${GLFW_STATIC_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})

    else()

        set(GLM_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/glm")
        set(THREADS_SOURCE_DIR "${CMAKE_SOURCE_DIR}/external/std-threads")

        set(CMAKE_PREFIX_PATH "C:/GLEW")
        set(CMAKE_LIBRARY_PATH "C:/GLEW/bin")

        set(glfw3_DIR "C:/GLFW/lib/cmake/glfw3")


    find_package(OpenGL REQUIRED)
    find_package(glfw3 CONFIG REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(Threads REQUIRED)

    if(GLEW_FOUND)
        include_directories(${GLEW_INCLUDE_DIRS})
        link_libraries(${GLEW_LIBRARIES})
    endif()

add_definitions(-DGLEW_STATIC)

    include_directories(
            ${GLM_SOURCE_DIR}
            ${GLFW_INCLUDE_DIR}
            ${THREADS_SOURCE_DIR})


    set(SOURCE_FILES main.cpp Objects.cpp Objects.h ray.cpp ray.h pixel.cpp pixel.h camera.cpp camera.h Scene.cpp Scene.h Triangle.cpp Triangle.h openglfunc.cpp openglfunc.h)

    add_executable(${APP_NAME} ${SOURCE_FILES})

    target_link_libraries(${APP_NAME} glfw ${GLFW_LIBRARIES})
    target_link_libraries(${APP_NAME} glfw ${OPENGL_glu_LIBRARY} ${GLFW_LIBRARIES} ${OPENGL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})


endif (UNIX AND NOT APPLE)



