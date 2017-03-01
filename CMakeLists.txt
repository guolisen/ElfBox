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

#set(SDL2_INCLUDE_DIR "E:/code/lib/SDL2-2.0.5/include")
#set(SDL2_IMAGE_INCLUDE_DIR "E:/code/lib/SDL2_image-2.0.1/include")
#set(SDL2MAIN_LIBRARY "E:/code/lib/SDL2-2.0.5/lib/x86/SDL2main.lib")
#set(SDL2_LIBRARY "E:/code/lib/SDL2-2.0.5/lib/x86/SDL2.lib")
#set(SDL2_IMAGE_LIBRARY "/usr/lib/libSDL2_image.dll.a")
#set(SDL2_IMAGE_LIBRARY "E:/code/lib/SDL2_image-2.0.1/lib/x86/SDL2_image.lib")

#添加C++11支持及其他选项
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

add_executable(run_tests test/testmain.cpp)

include_directories(${TMXPARSER_INCLUDE_DIR})
include_directories(${TINYXML2_INCLUDE_DIR})
include_directories(${ZLIB_INCLUDE_DIRS})
include_directories(${SDL2_INCLUDE_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")

#target_link_libraries(run_tests libelfbox ${TINYXML2_LIBRARIES} ${ZLIB_LIBRARIES} 
#	${SDL_LIBRARY} ${SDL_IMAGE_LIBRARY} ${SDLMAIN_LIBRARY})
target_link_libraries(run_tests libelfbox
		 ${SDL2_IMAGE_LIBRARY} ${SDL2_LIBRARY} ${SDL2MAIN_LIBRARY}
		 ${TMXPARSER_LIBRARIES} ${TINYXML2_LIBRARIES} ${TINYXML2_LIBRARIES}
		 ${ZLIB_LIBRARIES} )

message("@@@@ ${TMXPARSER_INCLUDE_DIR}")
message("@@@@ ${TMXPARSER_LIBRARIES}")

#install(FILES ${HEADERS} DESTINATION include/tmxparser)
#install(TARGETS tmxparser tmxparser_static DESTINATION lib)

#configure_file(src/tmxparser.pc.in tmxparser.pc @ONLY)
#install(FILES ${CMAKE_CURRENT_BINARY_DIR}/tmxparser.pc DESTINATION lib/pkgconfig)
