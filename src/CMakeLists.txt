
#aux_source_directory(. LIB_SRCS)

set (PRENAME "tolua")
file (MAKE_DIRECTORY "./${PRENAME}" )
file(GLOB_RECURSE LUA_PKG_FILES *.pkg)
foreach (API_PKG_FILE ${LUA_PKG_FILES})
    message("API_PKG_FILE: ${API_PKG_FILE}")
    get_filename_component (NAME ${API_PKG_FILE} NAME)
    message("NAME: ${NAME}")
    get_filename_component (NAME_TMP ${API_PKG_FILE} NAME_WE)
    string (CONCAT NAME_C "tolua_" ${NAME_TMP} ".cpp")
    message("NAME_C: ${NAME_C}")
    get_filename_component (DIRECTORY ${API_PKG_FILE} DIRECTORY)
    message("DIRECTORY: ${DIRECTORY}")
    string (CONCAT COMPLETE_NAME_C ${DIRECTORY} "/" ${NAME_C})
    message("COMPLETE_NAME_C: ${COMPLETE_NAME_C}")
    message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
    #    file (GLOB PKG_FILES LuaScript/pkgs/${DIR}/*.pkg)
    string (CONCAT COMMAND_TOLUA ${PROJECT_SOURCE_DIR} "/tool/tolua.exe")
	message("COMMAND_TOLUA: ${COMMAND_TOLUA}")
    add_custom_command (OUTPUT ${COMPLETE_NAME_C}
            COMMAND ${PROJECT_SOURCE_DIR}/tool/tolua.exe -n ${NAME_TMP} -o ${NAME_C} ${NAME}
            DEPENDS ${PROJECT_SOURCE_DIR}/tool/tolua.exe
            COMMENT "Creating Tolua Cpp File: ${COMPLETE_NAME_C}"
            WORKING_DIRECTORY "${DIRECTORY}")
    list (APPEND TOLUA_C_FILES ${COMPLETE_NAME_C})
endforeach ()

file(GLOB_RECURSE HEADERS ./*.h)
file(GLOB ROOT_SOURCES ./*.cpp)
file(GLOB_RECURSE COMMON_SOURCES ./common/*.cpp)
file(GLOB_RECURSE GRAPHICS_SOURCES ./graphics/*.cpp)
file(GLOB_RECURSE UTIL_SOURCES ./util/*.cpp)
file(GLOB_RECURSE RENDER_SOURCES ./render/*.cpp)
file(GLOB_RECURSE SCENE_SOURCES ./scene/*.cpp)
file(GLOB_RECURSE SM_SOURCES ./sm/*.cpp)
file(GLOB_RECURSE SCRIPT_SOURCES ./script/*.cpp ./script/*.c)
file(GLOB SYSTEM_SOURCES ./system/*.cpp)
file(GLOB SYSTEM_DETAIL_SOURCES ./system/detail/*.cpp)
file(GLOB_RECURSE GAMELOGIC_SOURCES ./gamelogic/*.cpp)

IF (WIN32)
    set(SYSTEM_DETAIL_SOURCES "${SYSTEM_DETAIL_SOURCES};system/detail/platform/TimeServiceWinImpl.cpp")
ELSE ()
    set(SYSTEM_DETAIL_SOURCES "${SYSTEM_DETAIL_SOURCES};system/detail/platform/TimeServiceOtherImpl.cpp")
ENDIF (WIN32)

message("@@@@ ${TMXPARSER_INCLUDE_DIR}")

include_directories(${TOLUAPP_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${TMXPARSER_INCLUDE_DIR})
include_directories(${TINYXML2_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

add_library(libelfbox ${HEADERS} ${ROOT_SOURCES} ${SYSTEM_SOURCES} ${COMMON_SOURCES}
        ${GRAPHICS_SOURCES} ${UTIL_SOURCES} ${SYSTEM_DETAIL_SOURCES} ${RENDER_SOURCES}
        ${SCENE_SOURCES} ${SM_SOURCES} ${SCRIPT_SOURCES} ${GAMELOGIC_SOURCES}
        ${TOLUA_C_FILES})


