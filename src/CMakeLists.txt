
#aux_source_directory(. LIB_SRCS)
file(GLOB_RECURSE SOURCES ./*.cpp)
file(GLOB_RECURSE HEADERS ./*.h)

#include_directories(${TINYXML2_INCLUDE_DIR})
#include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(libelfbox ${SOURCES} ${HEADERS})