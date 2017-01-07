//   UString - UTF-8 C++ Library
//     Copyright (c) 2016, 2017 Jeremy Harmon <jeremy.harmon@zoho.com>
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

TEST_CASE("Iterator", "[UString]") 
{
    UString test(u8"abcdefghiάέήίΰα");
    UString::Iterator iter = test.begin();
    std::advance(iter, 5);
    
    REQUIRE( *iter == 'f' );
    
    --iter; 
    REQUIRE( *iter == 'e' );
    
    std::advance(iter, 5);
    REQUIRE( *iter == 0x03AC );
    
    UString tmp;
    std::copy(iter, test.end(), std::back_inserter(tmp));
    REQUIRE( tmp == u8"άέήίΰα" );
    
    iter = std::prev(iter, 3);
    REQUIRE( *iter == 'g' ); 

    UString::ReverseIterator riter;
    UChar reverseChars[] = { 0x3b1, 0x3b0, 0x3af, 0x3ae, 0x3ad, 0x3ac, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64, 0x63, 0x62, 0x61};
    uint32_t idx = 0;
    for( riter = test.rbegin(); riter != test.rend(); riter++, idx++ )
    {
        REQUIRE( *riter == reverseChars[idx] );
    }
}
