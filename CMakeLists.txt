cmake_minimum_required(VERSION 3.2)

project(Engine VERSION 0.1)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(SDL2_INCLUDE_DIRS OPENGL_INCLUDE_DIRS ${PROJECT_SOURCE_DIR/include})

set(SOURCES 
  src/main.cpp
  src/ProgramController.cpp
)

add_executable(Engine ${SOURCES})

set(CMAKE_SYSTEMCXX_STANDARD 20)

target_link_libraries(Engine SDL2::SDL2 ${OPENGL_LIBRARIES})
