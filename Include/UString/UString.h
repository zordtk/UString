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
                                                        
#ifndef _USTRING_USTRING_H_
#define _USTRING_USTRING_H_

    #include "UChar.h"
    #include "utf8/utf8.h"
    #include <string>
    #include <cstdint>

    class UString
    {
        public:
            typedef UChar value_type;
            
            UString() noexcept { }
            UString(const UString& str) noexcept;
            UString(const char *str) noexcept;
            explicit UString(UChar ch) noexcept;
            
            static const size_t npos = -1;
            
            // Assignment
            UString& assign(const UString& str) noexcept;
            UString& assign(const char* str) noexcept;
            UString& operator=(const UString& str) noexcept;
            UString& operator=(const char* str) noexcept;

            // Append/Prepend
            UString& append(UChar ch) noexcept;
            UString& append(const UString& str) noexcept;
            UString& append(const char* str) noexcept;
            UString& operator+=(const char *str) noexcept;
            UString& operator+=(const UString& str) noexcept;
            
            // push_back() is for STL compat and just calls append
            void push_back(UChar ch) noexcept;
            void push_back(const UString& str) noexcept;
            
            UString& prepend(UChar ch) noexcept;
            UString& prepend(const UString& str) noexcept;
            UString& prepend(const char* str) noexcept;
            
            // push_front() is for STL compat and just calls prepend
            void push_front(UChar ch) noexcept;
            void push_front(const UString& str) noexcept;

            
            // Comparison
            bool operator==(const UString& str) const noexcept;
            bool operator==(const char* str) const noexcept;
            bool operator!=(const UString& str) const noexcept;
            bool operator!=(const char* str) const noexcept;
            
            // Type conversion 
            std::string toStdString() const noexcept;
            std::u16string toStdU16String() const noexcept;
            std::u32string toStdU32String() const noexcept;
            
            static UString fromStdU16String(const std::u16string& str) noexcept;
            static UString fromStdU32String(const std::u32string& str) noexcept;
            
            // Case Conversion
            UString toUpper() const noexcept;
            UString toLower() const noexcept;
            UString toTitleCase() const noexcept;
            
            // Character Indexing
            const UChar at(std::size_t i) const noexcept;
            const UChar operator[](std::size_t i) const noexcept;
            
            // Substring 
            UString subStr(std::size_t start, std::size_t len=npos) const noexcept;
            std::size_t find(UChar ch, std::size_t start=0) const noexcept;
            std::size_t find(const UString& str, std::size_t start=0) const noexcept;
            
            template<typename IterType>
            class IteratorBase : public std::iterator<std::bidirectional_iterator_tag, UChar>
            {
                public:
                    typedef UChar value_type;
                    
                    IteratorBase() = default;
                    IteratorBase(const IterType& begin, const IterType& end, const IterType& pos)
                        : mRangeStart(begin), mRangeEnd(end), mIter(pos)
                    {

                    }
                    
                    iterator& operator++() { utf8::next(mIter, mRangeEnd); return *this; }
                    iterator  operator++(int) { iterator temp = *this; utf8::next(mIter, mRangeStart); return temp; }
                    iterator& operator--() { utf8::prior(mIter, mRangeStart); return *this; }
                    iterator  operator--(int) { iterator temp = *this; utf8::prior(mIter, mRangeEnd); return temp; }
                    
                    IterType base() const { return mIter; }
                    
                    const UChar operator*() const { auto temp = mIter; return UChar(utf8::next(temp, mRangeEnd)); }
               
                    bool operator!=(const IteratorBase& other) noexcept { return !operator==(other); }
                    bool operator==(const IteratorBase& other) noexcept 
                    {
                        return( mIter == other.mIter && mRangeStart == other.mRangeStart && mRangeEnd == other.mRangeEnd );
                    }

                protected:
                    IterType mRangeStart;
                    IterType mRangeEnd;
                    IterType mIter;
            };
            
            typedef IteratorBase<std::string::iterator>        Iterator;
            typedef IteratorBase<std::string::const_iterator>  ConstIterator;
            
            Iterator begin() noexcept;
            Iterator end() noexcept;
            ConstIterator begin() const noexcept;
            ConstIterator end() const noexcept;
            
            // Size
            std::size_t length() const;
            std::size_t size() const;  
            std::size_t maxSize() const;  
        protected:
            std::string mData;
    };

#endif
