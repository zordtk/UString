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

#include "UChar.h"
#include "catch.hpp"

TEST_CASE("UChar Tests", "[UChar]") 
{
    REQUIRE( UChar('c').getCategory() == UChar::Category::LetterLowercase );
    REQUIRE( UChar::getCategory('A') == UChar::Category::LetterUppercase );
    REQUIRE( UChar::getCategory(0x311F) == UChar::Category::LetterOther );
    REQUIRE( UChar::getCategory(0xFB29) == UChar::Category::SymbolMath );
    REQUIRE( UChar::toUpper(0x1042F) == 0x10407 );
    REQUIRE( UChar().assign('F') == 'F' );
    REQUIRE( UChar('z').toUpper() == 'Z' );
    REQUIRE( UChar('L').toLower() == 'l' );
    REQUIRE( UChar('3').toUpper() == '3' );
    REQUIRE( UChar::isNull(UCHAR_CODE_NULL) );
    REQUIRE( UChar(' ').isSpace() );
    REQUIRE( UChar::isSpace(0x1680) );
    REQUIRE( UChar::isLetter('d') );
    REQUIRE( !UChar::isLetter('3') );
    REQUIRE( UChar::isLetter(0x2C09) );
    REQUIRE( UChar::isControl(0xE0053) );
    REQUIRE( UChar::isControl(0x000A) );
    REQUIRE( UChar::isSurrogate(0xDBFF) );
    REQUIRE( UChar::isPunctuation(';') );
    REQUIRE( UChar::isPunctuation(0x1CC1) );
    REQUIRE( UChar::isSymbol('$') );
    REQUIRE( UChar::isNumber('9') );
    REQUIRE( UChar::isNumber(0x3007) );
    REQUIRE( UChar::getCase(0x2C09) == UChar::Case::CaseUpper );
}
