# Copyright (c) 2016 Andrew Kelley
# This file is MIT licensed.
# See http://opensource.org/licenses/MIT


MESSAGE(STATUS "Using bundled FindZlib.cmake...")
FIND_PATH(
   ZLIB_INCLUDE_DIRS
   zlib.h
   /usr/include/
   /usr/local/include/
   E:/code/lib/zlib/inc/
   )

FIND_LIBRARY(
   ZLIB_LIBRARIES NAMES  zlibd libz.a
   PATHS  /usr/lib /usr/local/lib/ E:/code/lib/zlib
   )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(ZLIB DEFAULT_MSG ZLIB_LIBRARIES ZLIB_INCLUDE_DIRS)


