UString - C++11 UTF-8 String Library
====================================
UString is a open-source C++11 UTF-8 String library, that is free for personal and commercial use. It uses std::string as it's data container and offers conversion to and from UTF-8/16/32.

[![Build Status](https://travis-ci.org/zordtk/ustring.svg?branch=master)](https://travis-ci.org/zordtk/ustring)

## Features ##
 * Unicode character database
  * Case conversion
  * Category information
  * Type information
 * Encoding conversion between UTF-8/16/32
 * STL compatible iterators
 * Character-based access
 * Unit tests
 
## Building ##
Building is very easy using the CMake build system. It will automatically download and generate the required Unicode data using a simple python script. In the future I may include the generated source in the git repository, but for now you must generate it using the script.
```
mkdir build; cd build
cmake ..
make
```
You can use ccmake to see the variables you can set. Such as building dynamic or static library, building the unit tests, and automatically running the unit tests on build.

## Development ##
UString is still in VERY early stages, so the API is still subject to much change. I welcome any contributions such as code, bug fixes, etc.

## TODO ##
- [ ] Documentation
- [ ] Replace methods
- [ ] Erase methods (erase (by iter, index, etc), clear, ...)
- [ ] Compare methods & operators (<, >, ...)
- [ ] More find methods (~~findLastOf~~, findFirstOf, etc)
- [ ] UTF-8 validation 
- [ ] Compose and formatting functions

## License (MIT) ##
Copyright (c) 2016 Jeremy Harmon

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
