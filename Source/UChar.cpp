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
#include "UnicodeData.h"
#include <cstring>

struct UCharCategoriesComp {
    bool operator()(const char* a, const char *b) const {
        return( std::strncmp(a, b, 2) == 0 );
    }
};

UChar::UChar() USTRING_NOEXCEPT
    : mChar(UCHAR_CODE_NULL)
{

}

UChar::UChar(ValueType codePoint) USTRING_NOEXCEPT
    : mChar(codePoint)
{
    
}

UChar& UChar::assign(UChar codePoint)
{
    mChar = codePoint;
    return *this;
}

UChar& UChar::operator=(UChar codePoint)
{
    mChar = codePoint;
    return *this;
}

bool UChar::isSpace(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    
    return( codePoint == 0x20 || ( codePoint <= 0x0D && codePoint >= 0x09 ) || ( codePoint > 127 && ( codePoint == 0x85 || 
            codePoint == 0xA0 || isCodePointInArray(UCharWhitespace, UCHAR_NUM_WHITESPACE, codePoint))) );
}

bool UChar::isLetter(ValueType codePoint)
{
    for( std::uint32_t i = 0; i < UCHAR_NUM_LETTERS; i++ )
    {
        if( UCharLetters[i].codePoint == codePoint )
            return true;
    }
    return false;
}

bool UChar::isControl(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    return( isCodePointInArray(UCharControls, UCHAR_NUM_CONTROLS, codePoint) );
}

bool UChar::isNumber(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    return( isCodePointInArray(UCharNumbers, UCHAR_NUM_NUMBERS, codePoint) );
}

bool UChar::isLineBreak(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    return( isCodePointInArray(UCharLinebreaks, UCHAR_NUM_LINEBREAKS, codePoint) );
}

bool UChar::isSymbol(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    return( isCodePointInArray(UCharSymbols, UCHAR_NUM_SYMBOLS, codePoint) );
}

bool UChar::isPunctuation(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    return( isCodePointInArray(UCharPunctuations, UCHAR_NUM_PUNCTUATIONS, codePoint) );
}

bool UChar::isSurrogate(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;
    return( isCodePointInArray(UCharSurrogates, UCHAR_NUM_SURROGATES, codePoint) );
} 

bool UChar::isNull(ValueType codePoint)
{
    return( codePoint == UCHAR_CODE_NULL );
}

bool UChar::isLower(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;   
    UCharLetter *l = findLetter(codePoint);
    if( !l ) return false;
    return ( l->characterCase == Case::CaseLower );
}

bool UChar::isUpper(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;   
    UCharLetter *l = findLetter(codePoint);
    if( !l ) return false;
    return ( l->characterCase == Case::CaseUpper );
}

bool UChar::isTitleCase(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return false;   
    UCharLetter *l = findLetter(codePoint);
    if( !l ) return false;
    return ( l->characterCase == Case::CaseTitle );
}

UChar UChar::toLower(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return UChar(codePoint);   
    UCharLetter *l = findLetter(codePoint);
    if( !l ) 
        return UChar(codePoint);
    if( l->characterCase == Case::CaseLower )
        return UChar(codePoint);
    return l->lowerVersion;
}

UChar UChar::toUpper(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return UChar(codePoint);   
    UCharLetter *l = findLetter(codePoint);
    if( !l ) 
        return UChar(codePoint);
    if( l->characterCase == Case::CaseUpper )
        return UChar(codePoint);
    return l->upperVersion;
}

UChar UChar::toTitleCase(ValueType codePoint)
{
    if( codePoint > UCHAR_CODE_MAX )
        return UChar(codePoint);   
    UCharLetter *l = findLetter(codePoint);
    if( !l ) 
        return UChar(codePoint);
    if( l->characterCase == Case::CaseTitle )
        return UChar(codePoint);
    return l->titleVersion;
}

UChar::Direction UChar::getDirection(ValueType ch)
{
     // Search UCharLetters
    for( std::uint32_t i = 0; i< UCHAR_NUM_LETTERS; i++ )
    {
        if( UCharLetters[i].codePoint == ch )
            return static_cast<Direction>(UCharLetters[i].direction);
    }    
    
    // Search UCharNumbers
    for( std::uint32_t i = 0; i< UCHAR_NUM_NUMBERS; i++ )
    {
        if( UCharNumbers[i].codePoint == ch )
            return static_cast<Direction>(UCharNumbers[i].direction);
    }    
    
    // Search UCharWhitespace
    for( std::uint32_t i = 0; i< UCHAR_NUM_WHITESPACE; i++ )
    {
        if( UCharWhitespace[i].codePoint == ch )
            return static_cast<Direction>(UCharWhitespace[i].direction);
    }    
    
    // Search UCharLinebreaks
    for( std::uint32_t i = 0; i< UCHAR_NUM_LINEBREAKS; i++ )
    {
        if( UCharLinebreaks[i].codePoint == ch )
            return static_cast<Direction>(UCharLinebreaks[i].direction);
    }    
    // Search punctuation
    for( std::uint32_t i = 0; i< UCHAR_NUM_PUNCTUATIONS; i++ )
    {
        if( UCharPunctuations[i].codePoint == ch )
            return static_cast<Direction>(UCharPunctuations[i].direction);
    }    
    
    // Search UCharSymbols
    for( std::uint32_t i = 0; i< UCHAR_NUM_SYMBOLS; i++ )
    {
        if( UCharSymbols[i].codePoint == ch )
            return static_cast<Direction>(UCharSymbols[i].direction);
    }    
    
    // Search UCharMarks
    for( std::uint32_t i = 0; i< UCHAR_NUM_MARKS; i++ )
    {
        if( UCharMarks[i].codePoint == ch )
            return static_cast<Direction>(UCharMarks[i].direction);
    }    
    
    // Search UCharControls 
    for( std::uint32_t i = 0; i< UCHAR_NUM_CONTROLS; i++ )
    {
        if( UCharControls[i].codePoint == ch )
            return static_cast<Direction>(UCharControls[i].direction);
    }    
    
    // Search UCharControls 
    for( std::uint32_t i = 0; i< UCHAR_NUM_SURROGATES; i++ )
    {
        if( UCharSurrogates[i].codePoint == ch )
            return static_cast<Direction>(UCharSurrogates[i].direction);
    }    
    
    // Search others
    for( std::uint32_t i = 0; i< UCHAR_NUM_MARKS; i++ )
    {
        if( UCharOthers[i].codePoint == ch )
            return static_cast<Direction>(UCharOthers[i].direction);
    }    
    
    return DirInvalid;
}

UChar::Category UChar::getCategory(ValueType ch)
{
    // TODO: Should this be replaced with something faster? Really how much
    //       is it going to be used??
    
    // Search UCharLetters
    for( std::uint32_t i = 0; i< UCHAR_NUM_LETTERS; i++ )
    {
        if( UCharLetters[i].codePoint == ch )
            return static_cast<Category>(UCharLetters[i].category);
    }    
    
    // Search UCharNumbers
    for( std::uint32_t i = 0; i< UCHAR_NUM_NUMBERS; i++ )
    {
        if( UCharNumbers[i].codePoint == ch )
            return static_cast<Category>(UCharNumbers[i].category);
    }    
    
    // Search UCharWhitespace
    for( std::uint32_t i = 0; i< UCHAR_NUM_WHITESPACE; i++ )
    {
        if( UCharWhitespace[i].codePoint == ch )
            return static_cast<Category>(UCharWhitespace[i].category);
    }    
    
    // Search UCharLinebreaks
    for( std::uint32_t i = 0; i< UCHAR_NUM_LINEBREAKS; i++ )
    {
        if( UCharLinebreaks[i].codePoint == ch )
            return static_cast<Category>(UCharLinebreaks[i].category);
    }    
    // Search punctuation
    for( std::uint32_t i = 0; i< UCHAR_NUM_PUNCTUATIONS; i++ )
    {
        if( UCharPunctuations[i].codePoint == ch )
            return static_cast<Category>(UCharPunctuations[i].category);
    }    
    
    // Search UCharSymbols
    for( std::uint32_t i = 0; i< UCHAR_NUM_SYMBOLS; i++ )
    {
        if( UCharSymbols[i].codePoint == ch )
            return static_cast<Category>(UCharSymbols[i].category);
    }    
    
    // Search UCharMarks
    for( std::uint32_t i = 0; i< UCHAR_NUM_MARKS; i++ )
    {
        if( UCharMarks[i].codePoint == ch )
            return static_cast<Category>(UCharMarks[i].category);
    }    
    
    // Search UCharControls 
    for( std::uint32_t i = 0; i< UCHAR_NUM_CONTROLS; i++ )
    {
        if( UCharControls[i].codePoint == ch )
            return static_cast<Category>(UCharControls[i].category);
    }    
    
    // Search UCharControls 
    for( std::uint32_t i = 0; i< UCHAR_NUM_SURROGATES; i++ )
    {
        if( UCharSurrogates[i].codePoint == ch )
            return static_cast<Category>(UCharSurrogates[i].category);
    }    
    
    // Search others
    for( std::uint32_t i = 0; i< UCHAR_NUM_MARKS; i++ )
    {
        if( UCharOthers[i].codePoint == ch )
            return static_cast<Category>(UCharOthers[i].category);
    }    
    
    // Really shouldn't happen
    return CatInvalid;
}

UChar::Case UChar::getCase(ValueType ch)
{
    for( std::uint32_t i=0; i<UCHAR_NUM_LETTERS; i++ )
    {
        if( UCharLetters[i].codePoint == ch )
            return static_cast<Case>(UCharLetters[i].characterCase);
    }
    
    return CaseInvalid;
}
