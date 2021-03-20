# brotli-hpp
Brotli header-only C++ library

## Usage

```cpp
// Include the specific brotli headers your code needs, for example...
#include <brotli/compress.hpp>
#include <brotli/decompress.hpp>
#include <brotli/version.hpp>

// All function calls must pass in a pointer of an 
// immutable character sequence (aka a string in C) and its size
std::string data = "hello";
const char * pointer = data.data();
std::size_t size = data.size();

// Compress returns a std::string
std::string compressed_data = brotli::compress(pointer, size);

// Decompress returns std::string and decode brotli
const char * compressed_pointer = compressed_data.data();
std::string decompressed_data = brotli::decompress(compressed_pointer, compressed_data.size());

// Or like so
std::string compressed_data = brotli::compress(data);
std::string decompressed_data = brotli::decompress(compressed_data);

```

See an example project for *Code::Blocks* here: */code-blocks/*

## Dependencies

Brotli compression is implemented using the *https://github.com/google/brotli* library. 
See *https://github.com/google/brotli* for more details.

To compile, include brotli library files in the project:

* *brotli/c/common/*
* *brotli/c/dec/*
* *brotli/c/enc/*
* *brotli/c/include/brotli/*


## Versioning
This library is semantically versioned using the */include/brotli/version.hpp* file. 
This defines a number of macros that can be used to check the current major, minor, or patch versions, as well as the full version string.

Here's how you can check for a particular version to use specific API methods

```cpp
#if BROTLI_HPP_VERSION_MAJOR > 2
// use version 2 api
#else
// use older verion apis
#endif
```

Here's how to check the version string

```cpp
std::cout << "version: " << BROTLI_HPP_VERSION_STRING << "/n";
// => version: 1.0.0
```

And lastly, mathematically checking for a specific version:

```cpp
#if BROTLI_HPP_VERSION_CODE > 20001
// use feature provided in v2.0.1
#endif
```