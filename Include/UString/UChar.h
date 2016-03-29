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

    class UChar
    {
        public:
            typedef std::uint32_t ValueType;
            
            enum Category
            {
                MarkNonSpacing,          //   Mn
                MarkSpacingCombining,    //   Mc
                MarkEnclosing,           //   Me

                NumberDecimalDigit,      //   Nd
                NumberLetter,            //   Nl
                NumberOther,             //   No

                SeparatorSpace,          //   Zs
                SeparatorLine,           //   Zl
                SeparatorParagraph,      //   Zp

                OtherControl,            //   Cc
                OtherFormat,             //   Cf
                OtherSurrogate,          //   Cs
                OtherPrivateUse,         //   Co
                OtherNotAssigned,        //   Cn

                LetterUppercase,         //   Lu
                LetterLowercase,         //   Ll
                LetterTitlecase,         //   Lt
                LetterModifier,          //   Lm
                LetterOther,             //   Lo

                PunctuationConnector,    //   Pc
                PunctuationDash,         //   Pd
                PunctuationOpen,         //   Ps
                PunctuationClose,        //   Pe
                PunctuationInitialQuote, //   Pi
                PunctuationFinalQuote,   //   Pf
                PunctuationOther,        //   Po

                SymbolMath,              //   Sm
                SymbolCurrency,          //   Sc
                SymbolModifier,          //   Sk
                SymbolOther,             //   So

                CatInvalid
            };
            
            enum Direction
            {
                DirL, DirR, DirEN, DirES, DirET, DirAN, DirCS, DirB, DirS, DirWS, DirON,
                DirLRE, DirLRO, DirAL, DirRLE, DirRLO, DirPDF, DirNSM, DirBN,
                DirLRI, DirRLI, DirFSI, DirPDI, DirInvalid
            };
            
            enum Case
            {
                CaseNone, CaseUpper, CaseLower, CaseTitle, CaseInvalid
            };

            UChar() noexcept;
            UChar(ValueType codePoint) noexcept;
            
            // Get functions
            static Category  getCategory(ValueType ch) noexcept;
            static Direction getDirection(ValueType ch) noexcept;
            static Case      getCase(ValueType ch) noexcept;
            
            inline Category  getCategory() const noexcept { return getCategory(mChar); }
            inline Direction getDirection() const noexcept { return getDirection(mChar); }
            inline Case      getCase() const noexcept { return getCase(mChar); }
            
            // Assignment
            UChar& assign(UChar codePoint) noexcept;
            UChar& operator=(UChar codePoint) noexcept;
            
            // Comparison
            inline const bool operator==(UChar codePoint) const noexcept { return( mChar == codePoint ); }
            inline const bool operator==(int codePoint) const noexcept { return( mChar == codePoint ); }
            inline const bool operator!=(UChar codePoint) const noexcept { return( mChar != codePoint ); }

            // Case Conversion
            static UChar toUpper(ValueType codePoint) noexcept;
            static UChar toLower(ValueType codePoint) noexcept;
            static UChar toTitleCase(ValueType codePoint) noexcept;
            inline UChar toUpper() noexcept { return toUpper(mChar); } 
            inline UChar toLower() noexcept { return toLower(mChar); }
            inline UChar toTitleCase() noexcept { return toTitleCase(mChar); }
            
            // Is?? functions
            static bool isNull(ValueType codePoint) noexcept;
            static bool isSpace(ValueType codePoint) noexcept;        
            static bool isLetter(ValueType codePoint) noexcept;
            static bool isControl(ValueType codePoint) noexcept;
            static bool isSurrogate(ValueType codePoint) noexcept;
            static bool isPunctuation(ValueType codePoint) noexcept;
            static bool isSymbol(ValueType codePoint) noexcept;
            static bool isLineBreak(ValueType codePoint) noexcept;
            static bool isNumber(ValueType codePoint) noexcept;
            static bool isUpper(ValueType codePoint) noexcept;
            static bool isLower(ValueType codePoint) noexcept;
            static bool isTitleCase(ValueType codePoint) noexcept;
            
            inline bool isUpper() noexcept { return isUpper(mChar); }
            inline bool isLower() noexcept { return isLower(mChar); }
            inline bool isTitleCase() noexcept { return isTitleCase(mChar); }
            inline bool isSpace() const noexcept { return isSpace(mChar); }
            inline bool isLetter() const noexcept { return isLetter(mChar); }
            inline bool isControl() const noexcept { return isControl(mChar); }
            inline bool isSurrogate() const noexcept { return isSurrogate(mChar); } 
            inline bool isPunctuation() const noexcept { return isPunctuation(mChar); }
            inline bool isSymbol() const noexcept { return isSymbol(mChar); }
            inline bool isLineBreak() const noexcept { return isLineBreak(mChar); }
            inline bool isNumber() const noexcept { return isNumber(mChar); }
            inline bool isNull() const noexcept { return isNull(mChar); }
            
            // Type casting operators
            inline operator ValueType() noexcept { return mChar; }
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