#   UString - UTF-8 C++ Library
#     Copyright (c) 2016, 2017 Jeremy Harmon <jeremy.harmon@zoho.com>
#     http://github.com/zordtk/ustring
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

project(UString)
cmake_minimum_required(VERSION 3.0)

include_directories("${PROJECT_SOURCE_DIR}/Include/UString")

# Make sure we have python
find_program(PYTHON python DOC "Python executable path")
if( NOT PYTHON )
    # We really don't need python if we already have the generated source
    if( NOT EXISTS "${PROJECT_SOURCE_DIR}/Source/UnicodeData.cpp" OR NOT EXISTS "${PROJECT_SOURCE_DIR}/Include/UnicodeData.h")
        message(FATAL_ERROR "Python is required to generate needed source from UnicodeData.txt")
    endif()
endif()

option(BUILD_STATIC  "Build as Static library"          ON)
option(BUILD_DYNAMIC "Build as a Dynamic library"       OFF)
option(BUILD_TESTS   "Build tests"                      OFF)
option(RUN_TESTS     "Run tests when build is complete" OFF)

if( NOT BUILD_STATIC AND NOT BUILD_DYNAMIC )
    message(FATAL_ERROR "You need to build as either a Dynamic or Static library")
endif()

set(UNICODE_DATA_URL "ftp://unicode.org/Public/8.0.0/ucd/UnicodeData.txt")
if( NOT EXISTS "${PROJECT_SOURCE_DIR}/Include/UString/UnicodeData.h" 
    OR NOT EXISTS "${PROJECT_SOURCE_DIR}/Source/UnicodeData.cpp" 
    AND NOT EXISTS "${PROJECT_SOURCE_DIR}/UnicodeData.txt" )
    
    message("Must generate unicode data from sources, fetching UnicodeData.txt (~1.5MB)...")
    file(DOWNLOAD ${UNICODE_DATA_URL} "${PROJECT_SOURCE_DIR}/UnicodeData.txt")
endif()

if( ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin" )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

foreach( i ${CMAKE_CXX_COMPILE_FEATURES} )
    if( ${i} STREQUAL "cxx_noexcept" )
        add_definitions("-DHAVE_NOEXCEPT")
    endif()
endforeach()

add_subdirectory(Source)
add_subdirectory(Tests)
