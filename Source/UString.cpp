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
#include "utf8/utf8.h"
#include <algorithm>
#include <iterator>

UString::UString(UChar ch) USTRING_NOEXCEPT
{
    append(ch);
}

UString::UString(const char *str) USTRING_NOEXCEPT
{
    if( str != nullptr )
        mData.assign(str);
}

UString::UString(const UString& str) USTRING_NOEXCEPT
{
    mData.assign(str.mData);
}

UString::UString(const std::string& str) USTRING_NOEXCEPT
{
    mData.assign(str);
}

UString& UString::insert(const UString& what, std::size_t where)
{
    if( where == 0 )
    {
        prepend(what);
        return *this;
    }
    else if( where > length()-1 )
    {
        append(what);
        return *this;
    }

    UString retStr;

    std::copy(begin(), std::next(begin(), where), std::back_inserter(retStr));
    retStr.append(what);
    std::copy(std::next(begin(), where), end(), std::back_inserter(retStr));

    assign(retStr);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Assignment                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////
UString& UString::assign(const UString& str)
{
    mData.assign(str.mData);
    return *this;
}

UString& UString::assign(const char* str)
{
    if( str != nullptr )
        mData.assign(str);
    return *this;
}

UString& UString::operator=(const UString& str)
{
    return assign(str);
}

UString& UString::operator=(const char* str)
{
    return assign(str);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Append/Prepend                                                                    ///
/////////////////////////////////////////////////////////////////////////////////////////
UString& UString::append(UChar ch)
{
    utf8::append(ch, std::back_inserter(mData));
    return *this;
}

UString& UString::append(const char* str)
{
    if( str != nullptr )
        mData.append(str);
    return *this;
}

UString& UString::append(const UString& str)
{
    mData.append(str.mData);
    return *this;
}

void UString::push_back(UChar ch)
{
    append(ch);
}

void UString::push_back(const UString& str)
{
    append(str);
}

UString& UString::prepend(UChar ch)
{
    mData = UString(ch).append(*this).mData;
    return *this;
}

UString& UString::prepend(const char *str)
{
    mData = UString(str).append(*this).mData;
    return *this;
}

UString& UString::prepend(const UString& str)
{
    mData = UString(str).append(*this).mData;
    return *this;
}

void UString::push_front(UChar ch)
{
    prepend(ch);
}

void UString::push_front(const UString& str)
{
    prepend(str);
}

UString& UString::operator+=(const UString& str)
{
    append(str);
    return *this;
}

UString& UString::operator+=(const char* str)
{
    append(str);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Comparison                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////
bool UString::operator==(const UString& str) const
{
    return( mData == str.mData );
}

bool UString::operator==(const char* str) const
{
    return( str && mData == str );
}

bool UString::operator!=(const UString& str) const
{
    return( mData != str.mData );
}

bool UString::operator!=(const char* str) const
{
    return( str && mData != str );
}

int UString::compare(const UString& other) const
{
    return mData.compare(other.mData);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Case Conversion                                                                   ///
/////////////////////////////////////////////////////////////////////////////////////////
UString& UString::toLower()
{
    UString tmp;
    for( UChar ch : *this )
        tmp.append(ch.toLower());

    assign(tmp);
    return *this;
}

UString& UString::toUpper()
{
    UString tmp;
    for( UChar ch : *this )
        tmp.append(ch.toUpper());

    assign(tmp);
    return *this;
}

UString& UString::toTitleCase()
{
    UString tmp;
    for( UChar ch : *this )
        tmp.append(ch.toTitleCase());

    assign(tmp);
    return *this;
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Type-Casting                                                                      ///
/////////////////////////////////////////////////////////////////////////////////////////
const std::string& UString::toStdString() const
{
    return mData;
}

const std::u16string UString::toStdU16String() const
{
    std::u16string u16str;
    utf8::utf8to16(mData.begin(), mData.end(), std::back_inserter(u16str));
    return u16str;
}

const std::u32string UString::toStdU32String() const
{
    std::u32string u32str;
    utf8::utf8to32(mData.begin(), mData.end(), std::back_inserter(u32str));
    return u32str;
}

UString UString::fromStdU16String(const std::u16string& str)
{
    UString retStr;
    utf8::utf16to8(str.begin(), str.end(), std::back_inserter(retStr.mData));
    return retStr;
}

UString UString::fromStdU32String(const std::u32string& str)
{
    UString retStr;
    utf8::utf32to8(str.begin(), str.end(), std::back_inserter(retStr.mData));
    return retStr;
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
const UChar UString::at(std::size_t i) const
{
    utf8::iterator<std::string::const_iterator> iter(mData.begin(), mData.begin(), mData.end());
    for(std::size_t j = 0; j < utf8::distance(mData.begin(), mData.end()); j++, ++iter)
    {
        if( j == i )
            return *iter;
    }

    return UCHAR_CODE_NULL;
}

const UChar UString::operator[](std::size_t i) const
{
    return at(i);
}

/////////////////////////////////////////////////////////////////////////////////////////
/// Sub-String                                                                        ///
/////////////////////////////////////////////////////////////////////////////////////////
UString UString::subStr(std::size_t start, std::size_t len) const
{
    UString retStr;
    auto startIter = mData.begin();
    auto endIter   = mData.begin();

    utf8::advance(startIter, start, mData.end());
    if( len != npos )
    {
        endIter = startIter;
        utf8::advance(endIter, len, mData.end());
    }
    else
        endIter = mData.end();

    std::copy(startIter, endIter, std::back_inserter(retStr.mData));
    return retStr;
}

std::size_t UString::find(UChar ch, std::size_t pos) const
{
    auto startIter = begin();
    if( pos != npos )
        std::advance(startIter, pos);

    auto iter = std::find(startIter, end(), ch);
    if( iter != end() )
        return std::distance(begin(), iter);

    return npos;
}

std::size_t UString::find(const UString& find, std::size_t start) const
{
    auto startIter = begin();
    if( start != npos )
        std::advance(startIter, start);

    auto iter = std::search(startIter, end(), find.begin(), find.end());
    if( iter != end() )
        return std::distance(begin(), iter);

    return npos;
}

std::size_t UString::findLastOf(UChar ch, std::size_t pos) const
{
    auto startIter = rbegin();
    if( pos != npos )
        std::advance(startIter, pos);

    auto iter = std::find(startIter, rend(), ch);
    if( iter != rend() )
        return length() - std::distance(rbegin(), iter) - 1;

    return npos;
}

std::size_t UString::findLastOf(const UString& find, std::size_t pos) const
{
    auto startIter = rbegin();
    if( pos != npos )
        std::advance(startIter, pos);

    auto iter = std::search(startIter, rend(), find.rbegin(), find.rend());
    if( iter != rend() )
        return length() - std::distance(rbegin(), iter) - 1;

    return npos;
}

UString& UString::replace(std::size_t start, std::size_t len, const UString& with)
{
    UString retStr;

    auto firstHalfIter = begin();
    std::advance(firstHalfIter, start);
    std::copy(begin(), firstHalfIter, std::back_inserter(retStr));

    retStr.append(with);
    auto secondHalfIter = begin();
    std::advance(secondHalfIter, start+len);
    std::copy(secondHalfIter, end(), std::back_inserter(retStr));

    assign(retStr);
    return *this;
}

UString& UString::replaceAll(const UString& what, const UString& with, std::size_t start)
{
    UString retStr = *this;

    std::size_t startPos = start;
    while( (startPos = retStr.find(what, startPos)) != npos )
    {
        retStr    = retStr.replace(startPos, what.length(), with);
        startPos += with.length();
    }

    assign(retStr);
    return *this;
}

UString& UString::replaceFirst(const UString& what, const UString& with, std::size_t start)
{
    UString retStr = *this;

    std::size_t pos = retStr.find(what, start);
    if( pos != npos )
        retStr = retStr.replace(pos, what.length(), with);

    assign(retStr);
    return *this;
}

UString& UString::replaceLast(const UString& what, const UString& with, std::size_t end)
{
    UString retStr = *this;
    if( end != npos )
        end = length() - end;

    std::size_t pos = retStr.findLastOf(what, end);

    if( pos != npos )
        retStr = retStr.replace(pos-what.length()+1, what.length(), with);

    assign(retStr);
    return *this;
}

UString& UString::clear()
{
    mData.clear();
    return *this;
}

UString& UString::erase(const UString::Iterator& start, const UString::Iterator& stop)
{
    UString retStr;

    std::copy(begin(), start, std::back_inserter(retStr));
    std::copy(stop, end(), std::back_inserter(retStr));

    assign(retStr);
    return *this;
}

UString& UString::erase(std::size_t start, std::size_t num)
{
    if( start == 0 )
    {
        assign(subStr(num));
        return *this;
    }
    else if( start == length()-1 )
    {
        assign(subStr(0, length()-1));
        return *this;
    }

    UString retStr;
    auto firstHalfIter = begin();
    auto secondHalfIter = begin();

    std::advance(firstHalfIter, start);
    std::advance(secondHalfIter, start+num);

    std::copy(begin(), firstHalfIter, std::back_inserter(retStr));
    std::copy(secondHalfIter, end(), std::back_inserter(retStr));

    assign(retStr);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const UString& str)
{
    os << str.toStdString();
    return os;
}

bool operator<(const UString &str1, const UString &str2)
{
    return( str1.compare(str2) );
}