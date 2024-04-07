#pragma once
#ifndef BROTLI_HPP_DECOMPRESS_HPP_INCLUDED
#define BROTLI_HPP_DECOMPRESS_HPP_INCLUDED

#ifndef BROTLI_HPP_DECOMPRESSION_BUFFER_SIZE
#define BROTLI_HPP_DECOMPRESSION_BUFFER_SIZE size_t(16384u)
#endif

// brotli
#include <brotli/decode.h>

// std
#include <string>
#include <array>

namespace brotli {

    class Decompressor {
    private:
        BrotliDecoderResult decoder_r;
        BrotliDecoderState *decoder_s = nullptr;
    public:

        Decompressor() noexcept {
            decoder_s = BrotliDecoderCreateInstance(0, 0, 0);
            decoder_r = decoder_s ? BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT
                          : BROTLI_DECODER_RESULT_ERROR;
        }

        ~Decompressor() noexcept {
            if (decoder_s) { BrotliDecoderDestroyInstance(decoder_s); }
        }

		template <typename OutputType>
		bool decompress(OutputType& output,
						const char* data,
						const std::size_t data_length) noexcept {
            if (decoder_r == BROTLI_DECODER_RESULT_SUCCESS ||
                decoder_r == BROTLI_DECODER_RESULT_ERROR) {
              return false;
            }

            const uint8_t *next_in = (const uint8_t *)data;
            size_t avail_in = data_length;
            size_t total_out;

            decoder_r = BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT;

            std::array<char, BROTLI_HPP_DECOMPRESSION_BUFFER_SIZE> buffer{};
            while (decoder_r == BROTLI_DECODER_RESULT_NEEDS_MORE_OUTPUT) {
                char *next_out = buffer.data();
                size_t avail_out = buffer.size();

                decoder_r = BrotliDecoderDecompressStream(
                    decoder_s,
                    &avail_in,
                    &next_in,
                    &avail_out,
                    reinterpret_cast<uint8_t **>(&next_out),
                    &total_out);

                if (decoder_r == BROTLI_DECODER_RESULT_ERROR) return false;

                auto output_bytes = buffer.size() - avail_out;
                if (output_bytes) {
                    output.append(reinterpret_cast<const char*>(buffer.data()), output_bytes);
                }
            }

            return (decoder_r == BROTLI_DECODER_RESULT_SUCCESS ||
                    decoder_r == BROTLI_DECODER_RESULT_NEEDS_MORE_INPUT);
		}
	};

	/** \brief Decompress data
     * \param data Pointer to char array of data
     * \param size Data array size
     * \return Decompressed string
     */
	inline std::string decompress(const char* data, std::size_t size) noexcept {
		Decompressor decomp;
		std::string output;
		decomp.decompress(output, data, size);
		return output;
	}

	/** \brief Decompress string data
     * \param data Data string to decompress
     * \return Decompressed string
     */
	inline std::string decompress(const std::string &data) noexcept {
		Decompressor decomp;
		std::string output;
		decomp.decompress(output, data.data(), data.size());
		return output;
	}
}; // brotli

#endif // BROTLI_HPP_DECOMPRESS_HPP_INCLUDED
