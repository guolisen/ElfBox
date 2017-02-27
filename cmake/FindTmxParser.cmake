# Copyright (c) 2016 Andrew Kelley
# This file is MIT licensed.
# See http://opensource.org/licenses/MIT

# TMXPARSER_FOUND
# TMXPARSER_INCLUDE_DIR
# TMXPARSER_LIBRARIES

MESSAGE(STATUS "Using bundled FindTmxParser.cmake...")
FIND_PATH(
   TMXPARSER_INCLUDE_DIR
   Tmx.h
   /usr/include/
   /usr/local/include/
   )

FIND_LIBRARY(
   TMXPARSER_LIBRARIES NAMES  tmxparser
   PATHS /usr/lib/ /usr/local/lib/
   )

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TMXPARSER DEFAULT_MSG TMXPARSER_LIBRARIES TMXPARSER_INCLUDE_DIR)

#mark_as_advanced(TMXPARSER_INCLUDE_DIR TMXPARSER_LIBRARIES)
