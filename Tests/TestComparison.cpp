//   UString - UTF-8 C++ Library
//     Copyright (c) 2016 Jeremy Harmon <jeremy.harmon@zoho.com>
//     http://github.com/zordtk/ustring
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "UString.h"
#include "catch.hpp"

TEST_CASE("Comparison", "[UString]") 
{
    REQUIRE( UString(u8"ά έ ή ί ΰ α") == UString(u8"ά έ ή ί ΰ α") );
    REQUIRE( UString("abcdef") == UString("abcdef") );
    REQUIRE( UString("def") != UString("abcdef") );
    REQUIRE( UString(u8"ήήήήήήήή") == u8"ήήήήήήήή" );
    REQUIRE( UString(u8"ήήήήήήήή").length() == 8 );
    REQUIRE( UString(u8"ήήήήήήήή").size() == 16 );
    REQUIRE( UString(std::string("testing")) == "testing" );
    
    UString tmp(u8"άέήίΰαa0djk");
    REQUIRE( tmp.at(1) == 0x03AD );
    REQUIRE( tmp.at(8) == 'd' );
}
