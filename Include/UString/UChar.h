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
                           
                                                        
#ifndef _USTRING_UCHAR_H_
#define _USTRING_UCHAR_H_

    #include <cstdint>
    #include <map>
    #include "UnicodeData.h"

    #if defined(HAVE_NOEXCEPT)
        #define USTRING_NOEXCEPT noexcept
    #else
        #define    
    #endif

    /*! UChar is used to represent a UTF-8 character
     */ 
    class UChar
    {
        public:
            typedef std::uint32_t ValueType;
       
            /*! Unicode categoiry types
             */
            enum Category
            {
                MarkNonSpacing,          //!<   Mn
                MarkSpacingCombining,    //!<   Mc
                MarkEnclosing,           //!<   Me

                NumberDecimalDigit,      //!<   Nd
                NumberLetter,            //!<   Nl
                NumberOther,             //!<   No

                SeparatorSpace,          //!<   Zs
                SeparatorLine,           //!<   Zl
                SeparatorParagraph,      //!<   Zp

                OtherControl,            //!<   Cc
                OtherFormat,             //!<   Cf
                OtherSurrogate,          //!<   Cs
                OtherPrivateUse,         //!<   Co
                OtherNotAssigned,        //!<   Cn

                LetterUppercase,         //!<   Lu
                LetterLowercase,         //!<   Ll
                LetterTitlecase,         //!<   Lt
                LetterModifier,          //!<   Lm
                LetterOther,             //!<   Lo

                PunctuationConnector,    //!<   Pc
                PunctuationDash,         //!<   Pd
                PunctuationOpen,         //!<   Ps
                PunctuationClose,        //!<   Pe
                PunctuationInitialQuote, //!<   Pi
                PunctuationFinalQuote,   //!<   Pf
                PunctuationOther,        //!<   Po

                SymbolMath,              //!<   Sm
                SymbolCurrency,          //!<   Sc
                SymbolModifier,          //!<   Sk
                SymbolOther,             //!<   So

                CatInvalid               //!<   Internal
            };
            
            /*! Unicode text direction
             */
            enum Direction
            {
                DirL,       //!< Left-to-Right
                DirR,       //!< Right-to-Left
                DirEN,      //!< European Number
                DirES,      //!< European Number Separator
                DirET,      //!< European Number Terminator
                DirAN,      //!< Arabic Number
                DirCS,      //!< Common Number Separator
                DirB,       //!< Paragraph Separator
                DirS,       //!< Segment Separator
                DirWS,      //!< Whitespace
                DirON,      //!< Other Neutrals
                DirLRE,     //!< Left-to-Right Embedding
                DirLRO,     //!< Left-to-Right Override
                DirAL,      //!< Right-to-Left Arabic
                DirRLE,     //!< Right-to-Left Embedding
                DirRLO,     //!< Right-to-Left Override
                DirPDF,     //!< Pop Directional Format
                DirNSM,     //!< Non-Spacing Mark
                DirBN,      //!< Boundary Neutral
                DirLRI,     //!< Left-to-Right Isolate
                DirRLI,     //!< Right-to-Left Isolate
                DirFSI,     //!< First Strong Isolate
                DirPDI,     //!< Pop Directional Isolate
                DirInvalid  //!< Internal
            };


            /*! Unicode text case
             */
            enum Case
            {
                CaseNone, CaseUpper, CaseLower, CaseTitle, CaseInvalid
            };

            /*! Create a character with a Null value
             */
            UChar() USTRING_NOEXCEPT;
            /*! Create a character from the given code-point
             * @param codePoin The UTF-8 code-point
             */
            UChar(ValueType codePoint) USTRING_NOEXCEPT;
            
            /*! Get the unicode Category of a given code-point
             * @param ch The code-point
             * @return The unicode Category
             */
            static Category  getCategory(ValueType ch);
            /*! Get the unicode Direction of a given code-point
             * @param ch The code-point
             * @return The unicode Direction
             */
            static Direction getDirection(ValueType ch);
            /*! Get the unicode Case of a given code-point
             * @param ch The code-point
             * @return The unicode Case
             */
            static Case      getCase(ValueType ch);

            /*! Get the unicode Category of this char
             * @return The unicode Category
             */
            inline Category  getCategory() const { return getCategory(mChar); }
            /*! Get the unicode Direction of this char
             * @return The unicode Direction
             */
            inline Direction getDirection() const { return getDirection(mChar); }
            /*! Get the unicode Case of this char
             * @return The unicode Case
             */
            inline Case      getCase() const { return getCase(mChar); }
            
            /*! Assign another UChar to this one
             * @return A reference to this object
             */
            UChar& assign(UChar codePoint);
            /*! Assign another UChar to this one
             * @return A reference to this object
             */
            UChar& operator=(UChar codePoint);
            
            /*! Compare this character to another
             * @return True if it is equal, False if it isn't
             */
            inline const bool operator==(UChar codePoint) const { return( mChar == codePoint ); }

            /*! Compare this character to another
             * @return True if it is equal, False if it isn't
             */
            inline const bool operator==(int codePoint) const { return( mChar == codePoint ); }

            /*! Compare this character to another
             * @return True if it is not equal, False if it is equal
             */
            inline const bool operator!=(UChar codePoint) const { return( mChar != codePoint ); }

            /*! Convert a code point to the upper case version
             * @param codePoint The code-point to convert
             * @return A Uchar containing the uppercase version 
             */
            static UChar toUpper(ValueType codePoint);
            /*! Convert a code point to the lower case version
             * @param codePoint The code-point to convert
             * @return A Uchar containing the lowercase version 
             */
            static UChar toLower(ValueType codePoint);
            /*! Convert a code point to the title case version
             * @param codePoint The code-point to convert
             * @return A Uchar containing the titlecase version 
             */
            static UChar toTitleCase(ValueType codePoint);
            /*! Return a new UChar containing a uppercase version of this 
             * @return A Uchar containing the uppercase version 
             */
            inline UChar toUpper() const { return toUpper(mChar); } 
            /*! Return a new UChar containing a lowercase version of this 
             * @return A Uchar containing the lowercase version 
             */
            inline UChar toLower() const { return toLower(mChar); }
            /*! Return a new UChar containing a titlecase version of this 
             * @return A Uchar containing the titlecase version 
             */
            inline UChar toTitleCase() const { return toTitleCase(mChar); }
            
            // Is?? functions
            static bool isNull(ValueType codePoint);
            static bool isSpace(ValueType codePoint);        
            static bool isLetter(ValueType codePoint);
            static bool isControl(ValueType codePoint);
            static bool isSurrogate(ValueType codePoint);
            static bool isPunctuation(ValueType codePoint);
            static bool isSymbol(ValueType codePoint);
            static bool isLineBreak(ValueType codePoint);
            static bool isNumber(ValueType codePoint);
            static bool isUpper(ValueType codePoint);
            static bool isLower(ValueType codePoint);
            static bool isTitleCase(ValueType codePoint);
            
            inline bool isUpper() { return isUpper(mChar); }
            inline bool isLower() { return isLower(mChar); }
            inline bool isTitleCase() { return isTitleCase(mChar); }
            inline bool isSpace() const { return isSpace(mChar); }
            inline bool isLetter() const { return isLetter(mChar); }
            inline bool isControl() const { return isControl(mChar); }
            inline bool isSurrogate() const { return isSurrogate(mChar); } 
            inline bool isPunctuation() const { return isPunctuation(mChar); }
            inline bool isSymbol() const { return isSymbol(mChar); }
            inline bool isLineBreak() const { return isLineBreak(mChar); }
            inline bool isNumber() const { return isNumber(mChar); }
            inline bool isNull() const { return isNull(mChar); }
            
            // Type casting operators
            inline operator ValueType() { return mChar; }
        private:
            static inline bool isCodePointInArray(UCharEntry *array, std::size_t arraySize, UChar::ValueType codePoint)
            {
                for( std::uint32_t i=0; i<arraySize; i++ )
                {
                    if( array[i].codePoint == codePoint )
                        return true;
                }
                return false;
            }

            static inline UCharLetter* findLetter(ValueType codePoint)
            {
                for( std::uint32_t i=0; i<UCHAR_NUM_LETTERS; i++ )
                {
                    if( UCharLetters[i].codePoint == codePoint )
                        return &UCharLetters[i];
                }
                
                return nullptr;
            }
            
            static inline UCharEntry* findEntry(UCharEntry *array, std::size_t arraySize, ValueType codePoint)
            {
                for( std::uint32_t i=0; i<arraySize; i++ )
                {
                    if( array[i].codePoint == codePoint )
                        return &array[i];
                }
                
                return nullptr;
            }
            
            ValueType   mChar;
    };

#endif
