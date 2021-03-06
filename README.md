UString - C++11 UTF-8 String Library
====================================
UString is a open-source C++11 UTF-8 String library, that is free for personal and commercial use. It uses std::string as it's data container and offers conversion to and from UTF-8/16/32.

[![Build Status](https://travis-ci.org/zordtk/ustring.svg?branch=master)](https://travis-ci.org/zordtk/ustring)

## Features ##
 * Unicode character information (typecase, category, direction, etc)
 * Encoding conversion between UTF-8/16/32
 * STL compatible iterators
 * Manipulation functions
  * Case conversion
  * Substring searching and replacment
  * Full text replacement
 * Documented (very basic)
 * Fully unit tested!
 
## Building ##
Building is very easy using the CMake build system. It will automatically download and generate the required Unicode data using a simple python script. In the future I may include the generated source in the git repository, but for now you must generate it using the script.
```
mkdir build; cd build
cmake ..
make
```
You can use ccmake to see the variables you can set. Such as building dynamic or static library, building the unit tests, and automatically running the unit tests on build.

## Documentation ##
Documentation is still very sparse, but you can browse the documentation online at http://zordtk.github.io/ustring_docs/. Alternatively you can generate offline docs using Doxygen.

## Development ##
I welcome any contributions such as code, bug fixes, etc.

## TODO ##
- [ ] Compare methods & operators (<, >, ...)
- [ ] Need to catch every UTF8-CPP exception that can be thrown and either wrap it into a custom or translate to existing exceptions in the STL
- [ ] UTF-8 validation 
- [ ] Compose and formatting functions

## License (MIT) ##
Copyright (c) 2016 Jeremy Harmon

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
