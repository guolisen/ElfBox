# Copyright (c) 2016 Andrew Kelley
# This file is MIT licensed.
# See http://opensource.org/licenses/MIT

# TMXPARSER_FOUND
# TMXPARSER_INCLUDE_DIR
# TMXPARSER_LIBRARIES

MESSAGE(STATUS "Using bundled FindTmxParser.cmake...")
FIND_PATH(
   TMXPARSER_INCLUDE_DIR
   tmxparser/Tmx.h
   /usr/include/
   /usr/include/tmxparser
   /usr/local/include/
   E:/code/lib2017/tmx/inc/
   )

FIND_LIBRARY(
   TMXPARSER_LIBRARIES NAMES  tmxparser
   PATHS /usr/lib/ /usr/local/lib/ E:/code/lib2017/tmx
   )


include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TMXPARSER DEFAULT_MSG TMXPARSER_LIBRARIES TMXPARSER_INCLUDE_DIR)

#mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARIES)
