#   UString - UTF-8 C++ Library
#     Copyright (c) 2016 Jeremy Harmon <jeremy.harmon@zoho.com>
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

add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/Source/UnicodeData.cpp
                   COMMAND python ParseUnicodeData.py
                   DEPENDS ${PROJECT_SOURCE_DIR}/UnicodeData.txt
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(GenerateUnicodeData ALL 
                  DEPENDS ${PROJECT_SOURCE_DIR}/Source/UnicodeData.cpp)

add_custom_command(OUTPUT ${PROJECT_SOURCE_DIR}/Include/UString/UnicodeData.h
                   COMMAND python ParseUnicodeData.py
                   DEPENDS ${PROJECT_SOURCE_DIR}/UnicodeData.txt
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

add_custom_target(GenerateUnicodeDataHeader ALL 
                  DEPENDS ${PROJECT_SOURCE_DIR}/Include/UString/UnicodeData.h)

set(USTRING_SRCS UString.cpp UChar.cpp UnicodeData.cpp)
set(USTRING_HDRS 
    ${PROJECT_SOURCE_DIR}/Include/UString/UString.h 
    ${PROJECT_SOURCE_DIR}/Include/UString/UnicodeData.h 
    ${PROJECT_SOURCE_DIR}/Include/UString/UChar.h
)

install(FILES ${USTRING_HDRS} DESTINATION include/UString)

if( BUILD_STATIC )
    add_library(UStringStatic STATIC ${USTRING_SRCS})
    set_property(TARGET UStringStatic  PROPERTY CXX_STANDARD 11)
    set_property(TARGET UStringStatic PROPERTY OUTPUT_NAME UString)
    install(TARGETS UStringStatic DESTINATION lib)
endif()

if( BUILD_DYNAMIC )
    add_library(UString SHARED ${USTRING_SRCS})
    set_property(TARGET UString PROPERTY CXX_STANDARD 11)
    install(TARGETS UString DESTINATION lib)
endif()
