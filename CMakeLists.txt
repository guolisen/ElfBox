cmake_minimum_required(VERSION 2.8)
project(elfbox)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

set(VERSION_MAJOR 2)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")
set(CMAKE_CXX_STANDARD 11)

message("Configuring elfbox version ${VERSION}")

#option(USE_MINIZ "Use miniz.c instead of zlib" OFF)

#file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/src/*.cpp)
#file(GLOB_RECURSE HEADERS ${PROJECT_SOURCE_DIR}/src/*.h)

add_subdirectory(src)

find_package(TmxParser)
find_package(TinyXML2)
find_package(ZLIB)
find_package(SDL2)
find_package(LUA)
find_package(TOLUA)

#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

add_executable(run_tests test/testmain.cpp)

include_directories(${TOLUAPP_INCLUDE_DIR})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${TMXPARSER_INCLUDE_DIR})
include_directories(${TINYXML2_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${SDL_INCLUDE_DIR})
include_directories(${SDL_IMAGE_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

message("========== Var ==========")
message("SDL_INCLUDE_DIR: ${SDL_INCLUDE_DIR}")
message("SDL_LIBRARY: ${SDL_LIBRARY}")
message("SDL_IMAGE_INCLUDE_DIR: ${SDL_IMAGE_INCLUDE_DIR}")
message("SDL_IMAGE_LIBRARY: ${SDL_IMAGE_LIBRARY}")
message("LUA_INCLUDE_DIR: ${LUA_INCLUDE_DIR}")
message("LUA_LIBRARIES: ${LUA_LIBRARIES}")
message("ZLIB_LIBRARIES: ${ZLIB_LIBRARIES}")
message("ZLIB_INCLUDE_DIRS: ${ZLIB_INCLUDE_DIRS}")
message("TINYXML2_INCLUDE_DIR: ${TINYXML2_INCLUDE_DIR}")
message("TINYXML2_LIBRARIES: ${TINYXML2_LIBRARIES}")
message("TOLUAPP_LIBRARIES: ${TOLUAPP_LIBRARIES}")
message("TOLUAPP_INCLUDE_DIR: ${TOLUAPP_INCLUDE_DIR}")
message("TMXPARSER_INCLUDE_DIR: ${TMXPARSER_INCLUDE_DIR}")
message("TMXPARSER_LIBRARIES: ${TMXPARSER_LIBRARIES}")


#target_link_libraries(run_tests libelfbox ${TINYXML2_LIBRARIES} ${ZLIB_LIBRARIES} 
#	${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDLMAIN_LIBRARY})
#target_link_libraries(run_tests libelfbox
#        ${SDL2_IMAGE_LIBRARY} ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
#        ${TMXPARSER_LIBRARIES} ${TINYXML2_LIBRARIES} ${ZLIB_LIBRARIES} ${LUA_LIBRARIES}
#        ${TOLUAPP_LIBRARIES} ${TOLUA_LIBRARIES})
target_link_libraries(run_tests libelfbox
		 ${SDL_IMAGE_LIBRARY} ${SDL_LIBRARY} ${SDLMAIN_LIBRARY}
		 ${TMXPARSER_LIBRARIES} ${TINYXML2_LIBRARIES} ${ZLIB_LIBRARIES}
		 ${LUA_LIBRARIES} ${TOLUAPP_LIBRARIES})


#install(FILES ${HEADERS} DESTINATION include/tmxparser)
#install(TARGETS tmxparser tmxparser_static DESTINATION lib)

#configure_file(src/tmxparser.pc.in tmxparser.pc @ONLY)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tmxparser.pc DESTINATION lib/pkgconfig)
