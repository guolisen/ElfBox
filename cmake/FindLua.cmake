# Copyright (c) 2016 Andrew Kelley
# This file is MIT licensed.
# See http://opensource.org/licenses/MIT

# TMXPARSER_FOUND
# TMXPARSER_INCLUDE_DIR
# TMXPARSER_LIBRARIES

MESSAGE(STATUS "Using bundled FindLua.cmake...")
FIND_PATH(
   LUA_INCLUDE_DIR
   lua.h
   /usr/local/include/
   E:/code/lib2017/lua/inc
   
   )

FIND_LIBRARY(
   LUA_LIBRARIES NAMES  lua51 lua
   PATHS  /usr/local/lib/
   E:/code/lib2017/lua/x64
   )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LUA DEFAULT_MSG LUA_LIBRARIES LUA_INCLUDE_DIR)

#mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARIES)
