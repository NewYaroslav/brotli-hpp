#pragma once
#ifndef BROTLI_HPP_COMPRESS_HPP_INCLUDED
#define BROTLI_HPP_COMPRESS_HPP_INCLUDED

#ifndef BROTLI_HPP_COMPRESSION_BUFFER_SIZE
#define BROTLI_HPP_COMPRESSION_BUFFER_SIZE size_t(16384u)
#endif

// brotli
#include <brotli/encode.h>

// std
#include <string>
#include <array>

namespace brotli {

    class Compressor {
    private:
        BrotliEncoderState *state = nullptr;
    public:

        Compressor() noexcept {
            state = BrotliEncoderCreateInstance(nullptr, nullptr, nullptr);
        }

        ~Compressor() noexcept {
            BrotliEncoderDestroyInstance(state);
        }

        template <typename InputType>
		bool compress(InputType& output,
					  const char* data,
					  const std::size_t data_length) const noexcept {
            std::array<uint8_t, BROTLI_HPP_COMPRESSION_BUFFER_SIZE> buffer{};
            auto operation = BROTLI_OPERATION_FINISH;
            auto available_in = data_length;
            auto next_in = reinterpret_cast<const uint8_t *>(data);
            while(true) {
                if (BrotliEncoderIsFinished(state)) { break; }

                auto available_out = buffer.size();
                auto next_out = buffer.data();

                if (!BrotliEncoderCompressStream(
                        state,
                        operation,
                        &available_in,
                        &next_in,
                        &available_out,
                        &next_out,
                        nullptr)) {
                    std::cout << "false" << std::endl;
                    return false;
                }

                auto output_bytes = buffer.size() - available_out;
                if (output_bytes) {
                    output.append(reinterpret_cast<const char*>(buffer.data()), output_bytes);
                }
            } // while
            return true;
        };
    };

    /** \brief Compress data
     * \param data Pointer to char array of data
     * \param size Data array size
     * \return Compressed string
     */
	inline std::string compress(
		const char* data,
		const std::size_t size) noexcept {
		Compressor comp;
		std::string output;
		comp.compress(output, data, size);
		return std::move(output);
	}

    /** \brief Compress string data
     * \param data Data string to compress
     * \return Compressed string
     */
	inline std::string compress(const std::string &data) noexcept {
		Compressor comp;
		std::string output;
		comp.compress(output, data.data(), data.size());
		return std::move(output);
	}

}; // brotli

#endif // BROTLI_HPP_COMPRESS_HPP_INCLUDED
