#pragma once
#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief  одирует 4 бита: [a, b, c, d] > 8 бит с контрольными XOR.
 * @param nibble ћладшие 4 бита содержат данные.
 * @return 8 бит: a,b,c,d,a^b,c^d,a^c,b^d.
 */
uint8_t encodeHamming(uint8_t nibble);

/**
 * @brief ƒекодирует 8-битный блок, возвраща€ исходные 4 бита.
 * @param byte 8 бит, закодированные как a,b,c,d,a^b,c^d,a^c,b^d.
 * @return nibble Ч 4 бита данных.
 */
uint8_t decodeHamming(uint8_t byte);

/**
 * @brief  одирует битовую последовательность (по 4 бита) в байты.
 * @param inputBits ѕоследовательность битов (0 или 1).
 * @return ћассив байтов, каждый кодирует 4 бита.
 */
std::vector<uint8_t> encodeBitSequence(const std::vector<uint8_t>& inputBits);

/**
 * @brief –аскодирует байты в исходную битовую последовательность (по 4 бита).
 * @param encoded ћассив байтов с кодами.
 * @return ѕоследовательность битов (0 или 1).
 */
std::vector<uint8_t> decodeBitSequence(const std::vector<uint8_t>& encoded);

std::vector<uint8_t> stringToBitSequence(const std::string& message);

std::string bitSequenceToString(const std::vector<uint8_t>& bits);