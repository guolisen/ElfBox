
#aux_source_directory(. LIB_SRCS)
file(GLOB_RECURSE SOURCES ./*.cpp)
file(GLOB_RECURSE HEADERS ./*.h)

include_directories(${TINYXML2_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "/MDd")

add_library(libelfbox ${SOURCES} ${HEADERS})