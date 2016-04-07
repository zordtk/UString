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

    //! \brief UTF-8 String Class
    //! UString is a UTF-8 aware string class that provides the common manipulation
    //! functions.
    class UString
    {
        public:
            typedef UChar value_type;

            /*! Default constructor which creates an empty string.
             */
            UString() { }

            /*! Construct a UString as a copy of another UString.
             * @param other UString to copy
             */
            UString(const UString& other) USTRING_NOEXCEPT;
            /*! Construct a UString as a copy of another UString.
             * @param cstr C-string to copy.
             */
            UString(const char *cstr) USTRING_NOEXCEPT;

            /*! Construct a UString as a copy of a C string.
             * @param ch UChar character to assign
             */
            explicit UString(UChar ch) USTRING_NOEXCEPT;

            static const size_t npos = std::string::npos;

            /*! Assigns other to this string
             * @param other String to assign
             * @return Reference to this object
             */
            UString& assign(const UString& other);
            /*! Assigns other to this string
             * @param other String to assign
             * @return Reference to this object
             */
            UString& assign(const char* other);
            /*! Assigns other to this string
             * @param other String to assign
             * @return Reference to this object
             */
            UString& operator=(const UString& other);
            /*! Assigns other to this string
             * @param other String to assign
             * @return Reference to this object
             */
            UString& operator=(const char* other);

            /*! Append a character to the current string
             * @param ch Character to append
             * @return Reference to this object
             */
            UString& append(UChar ch);
            /*! Append a string to the current string
             * @param str String to append
             * @return Reference to this object
             */
            UString& append(const UString& str);

            /*! Append a C-string to the current string
             * @param str C-string string to append
             * @return Reference to this object
             */
            UString& append(const char* str);
            /*! Append a C-string to the current string
             * @param str C-string string to append
             * @return Reference to this object
             */
            UString& operator+=(const char *str);
            /*! Append a string to the current string
             * @param str String to append
             * @return Reference to this object
             */
            UString& operator+=(const UString& str);

            /*! Append a string to the current string
             *
             * This is provided for STL compatibility and simply calls append()
             * @param str String to append
             */
            void push_back(UChar ch);
            /*! Append a string to the current string
             *
             * This is provided for STL compatibility and simply calls append()
             * @param str String to append
             */
            void push_back(const UString& str);

            /*! Prepend a character to the current string
             * @param ch Character to prepend
             * @return Reference to this object
             */
            UString& prepend(UChar ch);
            /*! Prepend a string to the current string
             * @param str String to prepend
             * @return Reference to this object
             */
            UString& prepend(const UString& str);
            /*! Prepend a C-string to the current string
             * @param str C-string to prepend
             * @return Reference to this object
             */
            UString& prepend(const char* str);

            /*! Prepend a UChar to the current string
             *
             * This is provieded for STL compatibility and simply calls append()
             * @param ch Character to append
             */
            void push_front(UChar ch);
            /*! Prepend a UString to the current string
             *
             * This is provieded for STL compatibility and simply calls append()
             * @param str UString to append
             */
            void push_front(const UString& str);

            /*! Check if this string equals the other.
             * @return True if equal, False if not
             */
            bool operator==(const UString& other) const;
            /*! Check if this string equals the other.
             * @return True if equal, False if not
             */
            bool operator==(const char* other) const;
            /*! Check if this string not equals the other.
             * @return True if not equal, False if equal
             */
            bool operator!=(const UString& other) const;
            /*! Check if this string not equals the other.
             * @return True if not equal, False if equal
             */
            bool operator!=(const char* other) const;

            /*! Convert to std::string.
             * @return std::string
             */
            std::string toStdString() const;

            /*! Convert to UTF-16 and return it as a std::u16string
             * @return std::u16string
             */
            std::u16string toStdU16String() const;

            /*! Convert to UTF-32 std::u32string.
             * @return std::u32string
             */
            std::u32string toStdU32String() const;

            /*! Convert a string from UTF-16 and return a new UTF-8 encoded string
             * @param str UTF-16 encoded string to convert
             * @return UTF-16 encoded string
             */
            static UString fromStdU16String(const std::u16string& str);

            /*! Convert a string from UTF-32 and return a new UTF-8 encoded string
             * @param str UTF-32 encoded string to convert
             * @return New UTF-8 encoded string
             */
            static UString fromStdU32String(const std::u32string& str);

            /*! Convert any lowercase characters in the string to upper
             * @return Reference to this object
             */
            UString& toUpper();

            /*! Convert any uppercase characters in the string to lower
             * @return Reference to this object
             */
            UString& toLower();

            /*! Convert string to titleCase
             * @return Reference to this object
             */
            UString& toTitleCase();

            /*! Get character at position idx
             * @return Character
             */
            const UChar at(std::size_t idx) const;
            /*! Get character at position idx
             * @return Character
             */
            const UChar operator[](std::size_t idx) const;

            /*! Create a new string using a sub-section of this string
             * @param start Position to start copying characters from
             * @param len Number of characters to copy or until the end if len is npos
             * @return New string containing characters copied
             */
            UString subStr(std::size_t start, std::size_t len=npos) const;

            /*! Find a UChar character
             * @param ch character to find
             * @param start Position to begin searching from
             * @return Position of the character if found, npos if not.
             */
            std::size_t find(UChar ch, std::size_t start=0) const;
            /*! Find a string
             * @param what String to search for
             * @param start Position to begin searching from
             * @return Position of the first character of the string if found, npos if not.
             */
            std::size_t find(const UString& what, std::size_t start=0) const;
            /*! Find the last instance of a UChar character
             * @param ch Character to search for
             * @param pos Position of last character to include in search
             * @return Position of the character of the string if found, npos if not.
             */
            std::size_t findLastOf(UChar ch, std::size_t pos=npos) const;

            /*! Find the last instance of a string
             * @param what String to search for
             * @param pos Position of last character to include in search
             * @return Position of the character of the string if found, npos if not.
             */
            std::size_t findLastOf(const UString& what, std::size_t pos=npos) const;

            /*! Replace part of this string with another string
             * @param start Start of the section to replace
             * @param len Number of characters to replace counting from start
             * @param with String to replace cut subsection with
             * @return Reference to this object
             */
            UString& replace(std::size_t start, std::size_t len, const UString& with);
            /*! Replace all instances of a string with another
             * @param what String to search for
             * @param with String to use for replacement
             * @param start The position to begin searching at
             * @return Reference to this object
             */
            UString& replaceAll(const UString& what, const UString& with, std::size_t start=0);
            /*! Replace first instance of a string with another
             * @param what String to search for
             * @param with String to use for replacement
             * @param start The position to begin searching at
             * @return Reference to this object
             */
            UString& replaceFirst(const UString& what, const UString& with, std::size_t start=0);
            /*! Replace last instance of a string with another
             * @param what String to search for
             * @param with String to use for replacement
             * @param end The position to end our search at or npos
             * @return Reference to this object
             */
            UString& replaceLast(const UString& what, const UString& with, std::size_t end=npos);

            /*! Base class for Iterators used in UString
             *
             * This is a bidirectional iterator Random access can not be provided because all index operations
             * need to iterate through UTF-8 characters, which can be multiple bytes. The iterator is not writable
             * because UTF-8 characters are not a fixed size changing one codepoint to another could overwrite
             * another codepoint. This would invalidate any iterators to the string.
             */
            template<typename IterType>
            class IteratorBase : public std::iterator<std::bidirectional_iterator_tag, UChar>
            {
                public:
                    typedef UChar value_type;
                    using reference = UChar;

                    /*! Create a empty Iterator without a reference to any part of a string
                     */
                    IteratorBase() = default;
                    /*! Increment the iterator position
                     * @return Reference to this iterator
                     */
                    IteratorBase& operator++() { utf8::next(mIter, mRangeEnd); return *this; }
                    /*! Increment the iterator position
                     * @return Reference to this iterator
                     */
                    IteratorBase  operator++(int) { IteratorBase temp = *this; utf8::next(mIter, mRangeStart); return temp; }
                    /*! Decrement the iterator position
                     * @return Reference to this iterator
                     */
                    IteratorBase& operator--() { utf8::prior(mIter, mRangeStart); return *this; }
                    /*! Decrement the iterator position
                     * @return Reference to this iterator
                     */
                    IteratorBase  operator--(int) { IteratorBase temp = *this; utf8::prior(mIter, mRangeEnd); return temp; }
                    /*! The base iterator type
                     * @return Base iterator
                     */
                    IterType base() const { return mIter; }
                    /*! Return the value of the current position
                     * @return The value
                     */
                    const UChar operator*() const { auto temp = mIter; return UChar(utf8::next(temp, mRangeEnd)); }
                    /*! Compare this iterator with a other
                     * @param other The iterator to compare it to
                     * @return False if the iterators are equal, and True if they aren't
                     */
                    bool operator!=(const IteratorBase& other) { return !operator==(other); }
                    /*! Compare this iterator with a other
                     * @param other The iterator to compare it to
                     * @return True if the iterator is equal to other
                     */
                    bool operator==(const IteratorBase& other)
                    {
                        return( mIter == other.mIter && mRangeStart == other.mRangeStart && mRangeEnd == other.mRangeEnd );
                    }

                private:
                    friend class UString;

                    IteratorBase(const IterType& begin, const IterType& end, const IterType& pos)
                        : mRangeStart(begin), mRangeEnd(end), mIter(pos)
                    {

                    }


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

            /*! Returns a iterator pointing to the beginning of the string
             * @return Iterator pointing to the start of the string
             */
            inline Iterator begin()                     { return Iterator(mData.begin(), mData.end(), mData.begin()); }
            /*! Returns a iterator pointing to the end of the string
             * @return Iterator pointing to the end of the string
             */
            inline Iterator end()                       { return Iterator(mData.begin(), mData.end(), mData.end()); }
            /*! Returns a constant iterator pointing to the beginning of the string
             * @return Iterator pointing to the start of the string
             */
            inline ConstIterator begin() const          { return ConstIterator(mData.begin(), mData.end(), mData.begin()); }
            /*! Returns a constant iterator pointing to the beginning of the string
             * @return Iterator pointing to the start of the string
             */
            inline ConstIterator end() const            { return ConstIterator(mData.begin(), mData.end(), mData.end()); }
            /*! Returns a reverse iterator pointing to the reverse beginning of the string
             * @return Iterator pointing to the reverse beginning of the string
             */
            inline ReverseIterator rbegin()             { return ReverseIterator(end()); }
            /*! Returns a reverse iterator pointing to the reverse end of the string
             * @return Iterator pointing to the reverse end of the string
             */
            inline ReverseIterator rend()               { return ReverseIterator(begin()); }
            /*! Returns a constant reverse iterator pointing to the reverse beginning of the string
             * @return Iterator pointing to the reverse beginning of the string
             */
            inline ConstReverseIterator rbegin() const  { return ConstReverseIterator(end()); }
            /*! Returns a constant reverse iterator pointing to the reverse end of the string
             * @return Iterator pointing to the reverse end of the string
             */
            inline ConstReverseIterator rend() const    { return ConstReverseIterator(begin()); }

            // For STL compatibility
            using iterator                  = Iterator;
            using const_iterator            = ConstIterator;
            using reverse_iterator          = ReverseIterator;
            using const_reverse_iterator    = ConstReverseIterator;

            /*! Returns the length of characters in the string
             * @return The length of characters in the string starting from zero
             */
            std::size_t length() const;
            /*! Returns the size of the string in bytes
             * @return The size of the string in bytes
             */
            std::size_t size() const;
            /*! Returns the maximum length the string can reach
             *
             * From CplusPlus.com:
             * This is the maximum potential length the string can reach due to known system or library implementation limitations,
             * but the object is not guaranteed to be able to reach that length: it can still fail to allocate storage at any point
             * before that length is reached.
             */
            std::size_t maxSize() const;
        private:
            std::string mData;
    };

#endif
