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
   /usr/include/
   /usr/local/include/
   )

FIND_LIBRARY(
   LUA_LIBRARIES NAMES  lua
   PATHS /usr/lib/ /usr/local/lib/
   )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(LUA DEFAULT_MSG LUA_LIBRARIES LUA_INCLUDE_DIR)

#mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARIES)
