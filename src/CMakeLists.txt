
#aux_source_directory(. LIB_SRCS)

file(GLOB_RECURSE HEADERS ./*.h)
file(GLOB ROOT_SOURCES ./*.cpp)
file(GLOB_RECURSE COMMON_SOURCES ./common/*.cpp)
file(GLOB_RECURSE GRAPHICS_SOURCES ./graphics/*.cpp)
file(GLOB_RECURSE UTIL_SOURCES ./util/*.cpp)
file(GLOB_RECURSE RENDER_SOURCES ./render/*.cpp)
file(GLOB_RECURSE SCENE_SOURCES ./scene/*.cpp)
file(GLOB SYSTEM_SOURCES ./system/*.cpp)
file(GLOB SYSTEM_DETAIL_SOURCES ./system/detail/*.cpp)

IF (WIN32)
    set(SYSTEM_DETAIL_SOURCES "${SYSTEM_DETAIL_SOURCES};system/detail/platform/TimeServiceWinImpl.cpp")
ELSE ()
    set(SYSTEM_DETAIL_SOURCES "${SYSTEM_DETAIL_SOURCES};system/detail/platform/TimeServiceOtherImpl.cpp")
ENDIF (WIN32)

include_directories(${TMXPARSER_INCLUDE_DIR})
include_directories(${TINYXML2_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(libelfbox ${HEADERS} ${ROOT_SOURCES} ${SYSTEM_SOURCES} ${COMMON_SOURCES}
        ${GRAPHICS_SOURCES} ${UTIL_SOURCES} ${SYSTEM_DETAIL_SOURCES} ${RENDER_SOURCES}
        ${SCENE_SOURCES})
