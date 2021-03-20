#include <iostream>
#include <brotli/compress.hpp>
#include <brotli/decompress.hpp>
#include <brotli/version.hpp>

int main() {
    std::string data = "Eat some more of these soft French rolls, but have some tea. Right now!";
    std::cout << "src data: " << data << std::endl;
    std::cout << "src data size: " << data.size() << std::endl;
    std::cout << std::endl;

    std::string compressed_data = brotli::compress(data.data(), data.size());

    std::cout << "brotli::compress v1" << std::endl;
    std::cout << "compressed data: " << compressed_data << std::endl;
    std::cout << "compressed data size: " << compressed_data.size() << std::endl;
    std::cout << std::endl;

    std::string compressed_data2 = brotli::compress(data);

    std::cout << "brotli::compress v2" << std::endl;
    std::cout << "compressed data: " << compressed_data2 << std::endl;
    std::cout << "compressed data size: " << compressed_data2.size() << std::endl;
    std::cout << std::endl;

    const char * compressed_pointer = compressed_data.data();
    std::string decompressed_data = brotli::decompress(compressed_pointer, compressed_data.size());

    std::cout << "brotli::decompress v1" << std::endl;
    std::cout << "decompressed data: " << decompressed_data << std::endl;
    std::cout << std::endl;

    std::string decompressed_data2 = brotli::decompress(compressed_data);

    std::cout << "brotli::decompress v2" << std::endl;
    std::cout << "decompressed data: " << decompressed_data << std::endl;
    std::cout << std::endl;
    return 0;
}
