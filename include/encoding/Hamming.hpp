#pragma once
#include <string>
#include <vector>
#include <cstdint>


uint8_t encodeHamming(uint8_t nibble);


uint8_t decodeHamming(uint8_t byte);


std::vector<uint8_t> encodeBitSequence(const std::vector<uint8_t>& inputBits);

std::vector<uint8_t> decodeBitSequence(const std::vector<uint8_t>& encoded);

std::vector<uint8_t> stringToBitSequence(const std::string& message);

std::string bitSequenceToString(const std::vector<uint8_t>& bits);