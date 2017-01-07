#!/usr/bin/python 
#   UString - UTF-8 C++ Library
#     Copyright (c) 2016, 2017 Jeremy Harmon <jeremy.harmon@zoho.com>
#     http://github.com/zordtk/ustring
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# This script generates Unicode data for UString. The script is based on parse_unicode_data.py 
# by Stephan Boyer. This was changed to include more data and I split the actual data and definitions 
# into separate files.

import os.path
from collections import defaultdict

UNICODE_DATA_URL    = "unicode.org"
UNICODE_DATA_PATH   = "Public/8.0.0/ucd/UnicodeData.txt"
CODE_POINT_NULL     = "0"
CODE_POINT_MAX      = "10FFFF"
CASE_NONE           = "00"
CASE_UPPER          = "01"
CASE_LOWER          = "02"
CASE_TITLE          = "03"

# These have to be in the same order is the UChar::Category enum
categories          = [ ('Mn',  0), ('Mc',  1), ('Me',  2), ('Nd',  3), ('Nl',  4), ('No',  5), ('Zs',  6), ('Zl',  7), ('Zp',  8), ('Cc',  9), 
                        ('Cf', 10), ('Cs', 11), ('Co', 12), ('Cn', 13), ('Lu', 14), ('Ll', 15), ('Lt', 16), ('Lm', 17), ('Lo', 18), ('Pc', 19), 
                        ('Pd', 20), ('Ps', 21), ('Pe', 22), ('Pi', 23), ('Pf', 24), ('Po', 25), ('Sm', 26), ('Sc', 27), ('Sk', 28), ('So', 29) ]

# These have to be in the same order as the UChar::Direction enum
directions          = [ ('L', 0), ('R', 1), ('EN', 2), ('ES', 3), ('ET', 4), ('AN', 5), ('CS', 6), ('B', 7), ('S', 8), ('WS', 9), ('ON', 10), ('LRE', 11), 
                        ('LRO', 12), ('AL', 13), ('RLE', 14), ('RLO', 15), ('PDF', 16), ('NSM', 17), ('BN', 18), ('LRI', 19), ('RLI', 20), ('FSI', 21), ('PDI', 22) ]

letters             = []
numbers             = []
controls            = []
whitespace          = []
linebreaks          = []
punctuations        = []
symbols             = []
surrogates          = []
marks               = []
others              = []

SourceHeader        = """\
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
"""

def fetchUnicodeData():
    import ftplib

    ftp = ftplib.FTP(UNICODE_DATA_URL, "anonymous", "anon@anon.com")
    f = open("UnicodeData.txt", "w")
    ftp.retrbinary("RETR " + UNICODE_DATA_PATH, f.write)
    f.close()
    ftp.quit()
    
def searchDictionary(dictToSearch, whatToSearchFor):
    for t in dictToSearch:
        if t[0] == whatToSearchFor:
            return t[1]

def writeSimpleList(f, l, name):
    f.write("    UCharEntry " + name + "[" + str(len(l)+1) + "] = \n    {\n")
    for entry in l:
        f.write("        {0x" + entry[0] + ", " + str(entry[1]) + ", " + str(entry[2]) + "},\n")
    f.write("    };\n\n")

print("Unicode Data Parser")

if not os.path.isfile("UnicodeData.txt"):
    print(" - UnicodeData.txt is missing, downloading...")
    fetchUnicodeData()
    print(" - Dowloaded UnicodeData.txt")

for line in open("UnicodeData.txt"):
    if line.strip() == "":
        continue

    parts = [part.strip() for part in line[:-1].strip().split(";")]

    if len(parts) != 15:
        print "Error: line is invalid"
    if parts[12] == "":
        parts[12] = CODE_POINT_NULL
    if parts[13] == "":
        parts[13] = CODE_POINT_NULL
    if parts[14] == "":
        parts[14] = CODE_POINT_NULL
    if parts[2] == "Lu":
        letters.append((parts[0], CASE_UPPER, parts[12], parts[13], parts[14], searchDictionary(categories, parts[2]), parts[4]))
    if parts[2] == "Ll":
        letters.append((parts[0], CASE_LOWER, parts[12], parts[13], parts[14], searchDictionary(categories, parts[2]), parts[4]))
    if parts[2] == "Lt":
        letters.append((parts[0], CASE_TITLE, parts[12], parts[13], parts[14], searchDictionary(categories, parts[2]), parts[4]))
    if parts[2] == "Lm":
        letters.append((parts[0], CASE_NONE, parts[12], parts[13], parts[14], searchDictionary(categories, parts[2]), parts[4]))
    if parts[2] == "Lo":
        letters.append((parts[0], CASE_NONE, parts[12], parts[13], parts[14], searchDictionary(categories, parts[2]), parts[4]))

    # Numbers
    if parts[2] == "Nd" or parts[2] == "Nl" or parts[2] == "No":
        numbers.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Whitespace
    if parts[2] == "Zs":
        whitespace.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Controls
    if parts[2] == "Cc" or parts[2] == "Cf":
        controls.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Line Breaks
    if parts[2] == "Zl" or parts[2] == "Zp":
        linebreaks.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Punctuation
    if parts[2] == "Pc" or parts[2] == "Pd" or parts[2] == "Ps" or parts[2] == "Pe" or parts[2] == "Pi" or parts[2] == "Pf" or parts[2] == "Po":
        punctuations.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Symbols
    if parts[2] == "Sm" or parts[2] == "Sc" or parts[2] == "Sk" or parts[2] == "So":
        symbols.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Surrogates
    if parts[2] == "Cs":
        surrogates.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Marks
    if parts[2] == "Mn" or parts[2] == "Mc" or parts[2] == "Me":
        marks.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

    # Others
    if parts[2] == "Co" or parts[2] == "Cn":
        others.append((parts[0], searchDictionary(categories, parts[2]), searchDictionary(directions, parts[4])))

print(" - Parsed UnicodeData.txt")

f = open("Include/UString/UnicodeData.h", "w")
f.write(SourceHeader)
f.write("\n#ifndef _USTRING_UNICODE_DATA_H_\n")
f.write("#define _USTRING_UNICODE_DATA_H_\n\n")
f.write("    #include <cstdint>\n")
f.write("    #include <map>\n")
f.write("    #include <cstring>\n")
f.write("\n")
f.write("    #define UCHAR_CODE_NULL    0x" + CODE_POINT_NULL + "\n")
f.write("    #define UCHAR_CODE_MAX     0x" + CODE_POINT_MAX + "\n")
f.write("    #define UCHAR_CASE_NONE          0\n")
f.write("    #define UCHAR_CASE_UPPER         1\n")
f.write("    #define UCHAR_CASE_LOWER         2\n")
f.write("    #define UCHAR_CASE_TITLE         3\n")
f.write("\n")
f.write("    #define UCHAR_NUM_LETTERS        " + str(len(letters)) + "\n")
f.write("    #define UCHAR_NUM_NUMBERS        " + str(len(numbers)) + "\n")
f.write("    #define UCHAR_NUM_WHITESPACE     " + str(len(whitespace)) + "\n")
f.write("    #define UCHAR_NUM_CONTROLS       " + str(len(controls)) + "\n")
f.write("    #define UCHAR_NUM_LINEBREAKS     " + str(len(linebreaks)) + "\n")
f.write("    #define UCHAR_NUM_PUNCTUATIONS   " + str(len(punctuations)) + "\n")
f.write("    #define UCHAR_NUM_SYMBOLS        " + str(len(symbols)) + "\n")
f.write("    #define UCHAR_NUM_MARKS          " + str(len(marks)) + "\n")
f.write("    #define UCHAR_NUM_SURROGATES     " + str(len(surrogates)) + "\n")
f.write("    #define UCHAR_NUM_OTHERS         " + str(len(others)) + "\n")
f.write("\n")

f.write("    struct UCharLetter\n")
f.write("    {\n")
f.write("        std::uint32_t  codePoint;\n")
f.write("        std::uint8_t   characterCase;\n")
f.write("        std::uint32_t  upperVersion;\n")
f.write("        std::uint32_t  lowerVersion;\n")
f.write("        std::uint32_t  titleVersion;\n")
f.write("        std::uint8_t   category;\n")
f.write("        std::uint8_t   direction;\n")
f.write("    };\n")
f.write("\n")

f.write("   struct UCharEntry\n")
f.write("   {\n")
f.write("       std::uint32_t  codePoint;\n")
f.write("       std::uint8_t   category;\n")
f.write("       std::uint8_t   direction;\n")
f.write("   };\n")
f.write("\n")

f.write("    extern UCharLetter UCharLetters[UCHAR_NUM_LETTERS+1];\n")
f.write("    extern UCharEntry  UCharNumbers[UCHAR_NUM_NUMBERS+1];\n")
f.write("    extern UCharEntry  UCharWhitespace[UCHAR_NUM_WHITESPACE+1];\n")
f.write("    extern UCharEntry  UCharControls[UCHAR_NUM_CONTROLS+1];\n")
f.write("    extern UCharEntry  UCharLinebreaks[UCHAR_NUM_LINEBREAKS+1];\n")
f.write("    extern UCharEntry  UCharPunctuations[UCHAR_NUM_PUNCTUATIONS+1];\n")
f.write("    extern UCharEntry  UCharSymbols[UCHAR_NUM_SYMBOLS+1];\n")
f.write("    extern UCharEntry  UCharSurrogates[UCHAR_NUM_SURROGATES+1];\n")
f.write("    extern UCharEntry  UCharOthers[UCHAR_NUM_OTHERS+1];\n")
f.write("    extern UCharEntry  UCharMarks[UCHAR_NUM_MARKS+1];\n")

f.write("\n")
f.write("#endif\n")
f.close()

print(" - Generated UnicodeData.h")

f = open("Source/UnicodeData.cpp", "w")
f.write(SourceHeader)
f.write("\n#include \"UnicodeData.h\"\n")
f.write("\n")

f.write("    UCharLetter UCharLetters[UCHAR_NUM_LETTERS+1] = \n    {\n")
for letter in letters:
  f.write("        {0x" + letter[0] + ", 0x" + letter[1] + ", 0x" + letter[2] + ", 0x" + letter[3] + ", 0x" + letter[4] + ", " + str(letter[5]) + ", " + str(searchDictionary(directions, letter[6])) + "},\n")
f.write("    };\n")
f.write("\n")

writeSimpleList(f, numbers, "UCharNumbers")
writeSimpleList(f, whitespace, "UCharWhitespace")
writeSimpleList(f, controls, "UCharControls")
writeSimpleList(f, linebreaks, "UCharLinebreaks")
writeSimpleList(f, punctuations, "UCharPunctuations")
writeSimpleList(f, symbols, "UCharSymbols")
writeSimpleList(f, surrogates, "UCharSurrogates")
writeSimpleList(f, marks, "UCharMarks")
writeSimpleList(f, others, "UCharOthers")

f.close();
print(" - Generated UnicodeData.cpp")    
