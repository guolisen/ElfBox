# Copyright (c) 2016 Andrew Kelley
# This file is MIT licensed.
# See http://opensource.org/licenses/MIT

# TMXPARSER_FOUND
# TMXPARSER_INCLUDE_DIR
# TMXPARSER_LIBRARIES

MESSAGE(STATUS "Using bundled FindToLua.cmake...")
FIND_PATH(
   TOLUAPP_INCLUDE_DIR
   tolua++.h
   /usr/local/include/
   E:/code/lib/tolua/inc
   )

FIND_LIBRARY(
   TOLUAPP_LIBRARIES NAMES  tolua++
   PATHS /usr/local/lib/ E:/code/lib/tolua/
   )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TOLUA DEFAULT_MSG TOLUAPP_LIBRARIES  TOLUAPP_INCLUDE_DIR)

#mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARIES)
