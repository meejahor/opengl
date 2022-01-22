cmake_minimum_required(VERSION 3.21)
project(spinning_cube_clion)

set(CMAKE_CXX_STANDARD 17)

include_directories(/Library/Frameworks/SDL2.framework/Headers/)
link_directories(/Library/Frameworks/)

#find_package(SDL2 REQUIRED)
#find_package(OpenGL REQUIRED)

find_library(SDL2 SDL2)
find_library(OPENGL OpenGL)

set(SOURCE_FILES
        deltatime.cpp
        light.cpp
        main.cpp
        model.cpp
        object.cpp
        rendering.cpp
        renderTexture.cpp
        shader.cpp
        utils.cpp
        window.cpp
        stb_image.h
        )

add_executable(spinning_cube_clion ${SOURCE_FILES})

target_link_libraries(spinning_cube_clion ${SDL2} ${OPENGL})

file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})
file(COPY models DESTINATION ${CMAKE_BINARY_DIR})
file(COPY images DESTINATION ${CMAKE_BINARY_DIR})
