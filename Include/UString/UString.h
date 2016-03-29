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
    #include <string>
    #include <cstdint>

    class UString
    {
        public:
            UString() noexcept = default;
            UString(const UString& str) noexcept;
            explicit UString(UChar ch) noexcept;
            explicit UString(const char *str) noexcept;
            
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
            UString& prepend(UChar ch) noexcept;
            UString& prepend(const UString& str) noexcept;
            UString& prepend(const char* str) noexcept;
            UString& operator+=(const char *str) noexcept;
            UString& operator+=(const UString& str) noexcept;
            
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
            UString toUpper() noexcept;
            UString toLower() noexcept;
            UString toTitleCase() noexcept;
            
            // Character Indexing
            UChar at(std::size_t i) const noexcept;
            UChar operator[](std::size_t i) const noexcept;
            
            // Substring 
            UString subStr(std::size_t start, std::size_t len=npos) const noexcept;
            std::size_t find(UChar ch, std::size_t start=0) const noexcept;
            std::size_t find(const UString& str, std::size_t start=0) const noexcept;
            
            class iterator : public std::iterator<std::bidirectional_iterator_tag, UChar>
            {
                public:
                    iterator& operator++() noexcept;
                    iterator& operator++(int) noexcept;
                    iterator& operator--() noexcept;
                    iterator& operator--(int) noexcept;
                    
                    const UChar operator*() const noexcept;
                    
                    bool operator==(const iterator& other) noexcept;
                    bool operator!=(const iterator& other) noexcept;
                protected:
                    friend class UString;
                    
                    iterator(std::string::iterator begin, std::string::iterator end, std::string::iterator pos)
                        : mRangeStart(begin), mRangeEnd(end), mIter(pos)
                    {

                    }
                          
                    std::string::iterator mRangeStart;
                    std::string::iterator mRangeEnd;
                    std::string::iterator mIter;
            };
            
            iterator begin() noexcept;
            iterator end() noexcept;
            
            // Size
            std::size_t length() const;
            std::size_t size() const;  
            std::size_t maxSize() const;  
        protected:
            std::string mData;
    };

#endif
