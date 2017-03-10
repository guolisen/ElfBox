# Copyright (c) 2016 Andrew Kelley
# This file is MIT licensed.
# See http://opensource.org/licenses/MIT

# TMXPARSER_FOUND
# TMXPARSER_INCLUDE_DIR
# TMXPARSER_LIBRARIES

MESSAGE(STATUS "Using bundled FindToLua.cmake...")
FIND_PATH(
   TOLUA_INCLUDE_DIR
   tolua.h
   /usr/include/
   /usr/local/include/
   )

FIND_LIBRARY(
   TOLUA_LIBRARIES NAMES  tolua
   PATHS /usr/lib/ /usr/local/lib/
   )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TOLUA DEFAULT_MSG TOLUA_LIBRARIES TOLUA_INCLUDE_DIR)

#mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARIES)
