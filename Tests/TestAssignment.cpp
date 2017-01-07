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

TEST_CASE("Assignment", "[UString]") 
{
    REQUIRE( UString().assign(u8"ά έ ή ί ΰ α") == u8"ά έ ή ί ΰ α" );
    REQUIRE( UString().append("testέέ").append("foo") == u8"testέέfoo" );
    REQUIRE( UString("test").append(0x2C09) == u8"test\u2c09" );
    REQUIRE( UString("test").append("blah") == "testblah" );
    REQUIRE( UString("est").prepend('t') == "test" );
    REQUIRE( UString("foo").prepend(u8"έέ").append("bar") == u8"έέfoobar" );
    REQUIRE( UString(nullptr).length() == 0 );
    REQUIRE( UString("test").append(nullptr) == "test" );
    REQUIRE( UString(nullptr).prepend("test") == "test" );
}

TEST_CASE("Inserts", "[UString]")
{
    REQUIRE( UString("thistest").insert(" is a ", 4) == "this is a test" );
    REQUIRE( UString("foo").insert("bar", 12) == "foobar" );
    REQUIRE( UString(u8"άέή").insert(u8"ί ΰ α", 0) == u8"ί ΰ αάέή" );
}
