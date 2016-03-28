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
#include "utf8/utf8.h"

UString::UString(UChar ch) noexcept
{
    append(ch);
}

UString::UString(const char *str) noexcept
{
    mData.assign(str);
}

UString::UString(const UString& str) noexcept
{
    mData.assign(str.mData);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Assignment                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////
UString& UString::assign(const UString& str) noexcept
{
    mData.assign(str.mData);
    return *this;
}

UString& UString::assign(const char* str) noexcept
{
    mData.assign(str);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Append                                                                            ///
/////////////////////////////////////////////////////////////////////////////////////////
UString& UString::append(UChar ch) noexcept
{
    utf8::append(ch, std::back_inserter(mData));
    return *this;
}

UString& UString::append(const char* str) noexcept
{
    mData.assign(str);
    return *this;
}

UString& UString::append(const UString& str) noexcept
{
    mData.append(str.mData);
    return *this;
}

UString& UString::operator+=(const UString& str) noexcept
{
    append(str);
    return *this;
}

UString& UString::operator+=(const char* str) noexcept
{
    append(str);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Comparison                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////
bool UString::operator==(const UString& str) const noexcept
{
    return( mData == str.mData );
}

bool UString::operator==(const char* str) const noexcept
{
    return( mData == str );
}

bool UString::operator!=(const UString& str) const noexcept
{
    return( mData != str.mData );
}

bool UString::operator!=(const char* str) const noexcept
{
    return( mData != str );
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Case Conversion                                                                   ///
/////////////////////////////////////////////////////////////////////////////////////////
UString UString::toLower() noexcept
{
    UString tmp;
    for( UChar ch : *this )
        tmp.append(ch.toLower());
    return tmp;
}

UString UString::toUpper() noexcept
{
    UString tmp;
    for( UChar ch : *this )
        tmp.append(ch.toUpper());
    return tmp;
}

UString UString::toTitleCase() noexcept
{
    UString tmp;
    for( UChar ch : *this )
        tmp.append(ch.toTitleCase());
    return tmp;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Type-Casting                                                                      ///
/////////////////////////////////////////////////////////////////////////////////////////
std::string UString::toStdString() const noexcept
{
    return mData;
}

std::u16string UString::toStdU16String() const noexcept
{
    std::u16string u16str;
    utf8::utf8to16(mData.begin(), mData.end(), std::back_inserter(u16str));
    return u16str;
}

std::u32string UString::toStdU32String() const noexcept
{
    std::u32string u32str;
    utf8::utf8to32(mData.begin(), mData.end(), std::back_inserter(u32str));
    return u32str;
}

UString UString::fromStdU16String(const std::u16string& str) noexcept
{
    UString retStr;
    utf8::utf16to8(str.begin(), str.end(), std::back_inserter(retStr.mData));
    return retStr;
}

UString UString::fromStdU32String(const std::u32string& str) noexcept
{
    UString retStr;
    utf8::utf32to8(str.begin(), str.end(), std::back_inserter(retStr.mData));
    return retStr;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Iterator                                                                          ///
/////////////////////////////////////////////////////////////////////////////////////////
UString::iterator& UString::iterator::operator++() noexcept
{
    utf8::next(mIter, mRangeEnd);
    return *this;
}

UString::iterator& UString::iterator::operator--() noexcept
{
    utf8::prior(mIter, mRangeStart);
    return *this;
}

bool UString::iterator::operator!=(const iterator& other) noexcept
{
    return !operator==(other);
}

bool UString::iterator::operator==(const iterator& other) noexcept
{
    return( mIter == other.mIter && mRangeStart == other.mRangeStart && mRangeEnd == other.mRangeEnd );
}

const UChar UString::iterator::operator*() const noexcept
{
    auto temp = mIter;
    return UChar(utf8::next(temp, mRangeEnd));
}

UString::iterator UString::begin() noexcept
{
    return iterator(mData.begin(), mData.end(), mData.begin());
}

UString::iterator UString::end() noexcept
{
    return iterator(mData.begin(), mData.end(), mData.end());
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Size                                                                              ///
/////////////////////////////////////////////////////////////////////////////////////////
std::size_t UString::length() const
{
    return utf8::distance(mData.begin(), mData.end());
}

std::size_t UString::size() const
{
    return mData.size();
}

std::size_t UString::maxSize() const
{
    return mData.max_size();
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Character Indexing                                                                ///
/////////////////////////////////////////////////////////////////////////////////////////
UChar UString::at(std::size_t i) const noexcept
{
    utf8::iterator<std::string::const_iterator> iter(mData.begin(), mData.begin(), mData.end());
    for(std::size_t j = 0; j < utf8::distance(mData.begin(), mData.end()); j++, ++iter)
    {
        if( j == i )
            return *iter;
    }

    return UCHAR_CODE_NULL;
}

UChar UString::operator[](std::size_t i) const noexcept
{
    return at(i);
}