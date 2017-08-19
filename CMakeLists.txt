cmake_minimum_required (VERSION 3.5.1)
set (CMAKE_CXX_STANDARD 11)
project (ETGG2802)

set(CMAKE_BUILD_TYPE Debug)

include (FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
find_package (OpenGL REQUIRED)
find_package (GLUT REQUIRED)

file (GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

add_executable (execute ${SRC_FILES})

include_directories (${SDL2_INCLUDE_DIR} ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})
target_link_libraries (execute -ldl -lpng ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
