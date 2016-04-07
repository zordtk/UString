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

set(USTRING_TEST_SRCS
    TestIterator.cpp
    Test.cpp
    TestConversion.cpp
    TestComparison.cpp
    TestAssignment.cpp
    TestSubstring.cpp
    TestFind.cpp
    TestUChar.cpp
    TestReplace.cpp
    TestErase.cpp
)

if( BUILD_TESTS )
    add_executable(ustring_test ${USTRING_TEST_SRCS})
    if( BUILD_STATIC )
        target_link_libraries(ustring_test UStringStatic)
    else()
        target_link_libraries(ustring_test UString)
    endif()
    set_property(TARGET ustring_test PROPERTY CXX_STANDARD 11)

    if( RUN_TESTS )
        add_custom_command(TARGET ustring_test POST_BUILD COMMAND ustring_test)
    endif()
endif()
