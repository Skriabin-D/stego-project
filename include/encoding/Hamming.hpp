#pragma once
#include <string>
#include <vector>
#include <cstdint>

/**
 * @file Hamming.hpp
 * @brief Hamming (8,4) encoding/decoding and bit-sequence utilities.
 *
 * Contains functions to encode 4 data bits into an 8-bit Hamming codeword,
 * decode it back, and convert between strings and bit sequences.
 */
#pragma once




/**
 * @brief Encode 4 data bits into an 8-bit Hamming (8,4) code word.
 *
 * Computes 4 parity bits for the nibble and assembles an 8-bit code.
 * @param nibble The low 4 bits contain the data to encode (0…15).
 * @return The 8-bit Hamming code (data+parity).
 */
uint8_t encodeHamming(uint8_t nibble);

/**
 * @brief Decode an 8-bit Hamming (8,4) code word.
 *
 * Extracts the original 4 data bits from the code word (no error correction).
 * @param byte The Hamming code byte.
 * @return The decoded 4-bit value (in low 4 bits of the return).
 */
uint8_t decodeHamming(uint8_t byte);

/**
 * @brief Encode a bit sequence using Hamming (8,4) blocks.
 * @param inputBits Vector of bits (0/1); groups of 4 form one code block.
 * @return Vector of bits, 8× longer for each 4-bit input group.
 */
std::vector<uint8_t> encodeBitSequence(const std::vector<uint8_t>& inputBits);


/**
 * @brief Decode a Hamming-encoded bit sequence.
 * @param encoded Vector of bits; groups of 8 are Hamming codewords.
 * @return The original bit sequence (4 bits per codeword).
 */
std::vector<uint8_t> decodeBitSequence(const std::vector<uint8_t>& encoded);


/**
 * @brief Convert text to a bit sequence (ASCII, MSB first).
 * @param message The input string.
 * @return A vector of 0/1 bits, 8 per character.
 */
std::vector<uint8_t> stringToBitSequence(const std::string& message);

/**
 * @brief Convert a bit sequence back to text.
 * @param bits Vector of bits; length must be a multiple of 8.
 * @return Reconstructed string, or empty on invalid input.
 */
std::string bitSequenceToString(const std::vector<uint8_t>& bits);