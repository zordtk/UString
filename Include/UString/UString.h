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
            
            UString() { }
            UString(const UString& str) USTRING_NOEXCEPT;
            UString(const char *str) USTRING_NOEXCEPT;
            explicit UString(UChar ch) USTRING_NOEXCEPT;
            
            static const size_t npos = std::string::npos;
            
            // Assignment
            UString& assign(const UString& str);
            UString& assign(const char* str);
            UString& operator=(const UString& str);
            UString& operator=(const char* str);

            // Append/Prepend
            UString& append(UChar ch);
            UString& append(const UString& str);
            UString& append(const char* str);
            UString& operator+=(const char *str);
            UString& operator+=(const UString& str);
            
            // push_back() is for STL compat and just calls append
            void push_back(UChar ch);
            void push_back(const UString& str);
            
            UString& prepend(UChar ch);
            UString& prepend(const UString& str);
            UString& prepend(const char* str);
            
            // push_front() is for STL compat and just calls prepend
            void push_front(UChar ch);
            void push_front(const UString& str);

            
            // Comparison
            bool operator==(const UString& str) const;
            bool operator==(const char* str) const;
            bool operator!=(const UString& str) const;
            bool operator!=(const char* str) const;
            
            // Type conversion 
            std::string toStdString() const;
            std::u16string toStdU16String() const;
            std::u32string toStdU32String() const;
            
            static UString fromStdU16String(const std::u16string& str);
            static UString fromStdU32String(const std::u32string& str);
            
            // Case Conversion
            UString toUpper() const;
            UString toLower() const;
            UString toTitleCase() const;
            
            // Character Indexing
            const UChar at(std::size_t i) const;
            const UChar operator[](std::size_t i) const;
            
            // Substring 
            UString subStr(std::size_t start, std::size_t len=npos) const;
            std::size_t find(UChar ch, std::size_t start=npos) const;
            std::size_t find(const UString& str, std::size_t start=npos) const;
            
            template<typename IterType>
            class IteratorBase : public std::iterator<std::bidirectional_iterator_tag, UChar>
            {
                public:
                    typedef UChar value_type;
                    using reference = UChar;
                    
                    IteratorBase() = default;
                    IteratorBase(const IterType& begin, const IterType& end, const IterType& pos)
                        : mRangeStart(begin), mRangeEnd(end), mIter(pos)
                    {

                    }
                    
                    IteratorBase& operator++() { utf8::next(mIter, mRangeEnd); return *this; }
                    IteratorBase  operator++(int) { IteratorBase temp = *this; utf8::next(mIter, mRangeStart); return temp; }
                    IteratorBase& operator--() { utf8::prior(mIter, mRangeStart); return *this; }
                    IteratorBase  operator--(int) { IteratorBase temp = *this; utf8::prior(mIter, mRangeEnd); return temp; }
                    
                    IterType base() const { return mIter; }
                    
                    const UChar operator*() const { auto temp = mIter; return UChar(utf8::next(temp, mRangeEnd)); }
               
                    bool operator!=(const IteratorBase& other) { return !operator==(other); }
                    bool operator==(const IteratorBase& other) 
                    {
                        return( mIter == other.mIter && mRangeStart == other.mRangeStart && mRangeEnd == other.mRangeEnd );
                    }

                protected:
                    IterType mRangeStart;
                    IterType mRangeEnd;
                    IterType mIter;
            };
            
            template<typename IterType>
            class ReverseIteratorBase : public std::reverse_iterator<IterType>
            {
                public:
                    using BaseIterator = std::reverse_iterator<IterType>;
                    
                    ReverseIteratorBase() = default;
                                        
                    ReverseIteratorBase(const ReverseIteratorBase<IterType>& iter)
                        : BaseIterator(iter)
                    {
                        
                    }
                    
                    ReverseIteratorBase(const std::reverse_iterator<IterType>& iter)
                        : BaseIterator(iter)
                    {
                        
                    }

                    ReverseIteratorBase(const IterType& iter)
                        : BaseIterator(iter)
                    {
                        
                    }
                    
                    ReverseIteratorBase& operator++()                   { BaseIterator::operator++(); return *this; }
                    ReverseIteratorBase  operator++(int)                { return BaseIterator::operator++(1); }
                    ReverseIteratorBase& operator--()                   { BaseIterator::operator--(); return *this; }
                    ReverseIteratorBase  operator--(int)                { return BaseIterator::operator--(1); }
                    IterType             base() const                   { return BaseIterator::base(); }
                    const UChar          operator*() const              { return BaseIterator::operator*(); }
                    bool operator!=(const ReverseIteratorBase& other)   { return( other.base() != this->base() ); }
                    bool operator==(const ReverseIteratorBase& other)   { return( other.base() == this->base() ); }
            };
            
            
            using Iterator              = IteratorBase<std::string::iterator>;
            using ConstIterator         = IteratorBase<std::string::const_iterator>;
            using ReverseIterator       = ReverseIteratorBase<Iterator>;
            using ConstReverseIterator  = ReverseIteratorBase<ConstIterator>;
           
            inline Iterator begin()                     { return Iterator(mData.begin(), mData.end(), mData.begin()); }
            inline Iterator end()                       { return Iterator(mData.begin(), mData.end(), mData.end()); }
            inline ConstIterator begin() const          { return ConstIterator(mData.begin(), mData.end(), mData.begin()); }
            inline ConstIterator end() const            { return ConstIterator(mData.begin(), mData.end(), mData.end()); }
            inline ReverseIterator rbegin()             { return ReverseIterator(end()); }
            inline ReverseIterator rend()               { return ReverseIterator(begin()); }
            inline ConstReverseIterator rbegin() const  { return ConstReverseIterator(end()); }
            inline ConstReverseIterator rend() const    { return ConstReverseIterator(begin()); }
            
            // For STL
            using iterator                  = Iterator;
            using const_iterator            = ConstIterator;
            using reverse_iterator          = ReverseIterator;
            using const_reverse_iterator    = ConstReverseIterator;

            // Size
            std::size_t length() const;
            std::size_t size() const;  
            std::size_t maxSize() const;  
        protected:
            std::string mData;
    };

#endif
