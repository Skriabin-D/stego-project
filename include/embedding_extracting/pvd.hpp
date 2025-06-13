#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>



/**
 * @file pvd.hpp
 * @brief Pixel-Value Differencing (PVD) steganography functions.
 *
 * Contains get_pvd_range(), embed_pvd(), and extract_pvd() to hide and
 * recover bit sequences based on pixel difference ranges.
 */
#pragma once



extern const std::vector<std::pair<int, int>> pvd_ranges;


/**
 * @brief Return the PVD range (lower,upper) containing diff.
 */
std::pair<int, int> get_pvd_range(int diff);

/**
 * @brief Embed a bit-vector into an image via pixel-value differencing.
 * @param image_path Cover image filename.
 * @param message_bits Bits to embed.
 * @param output_path Where to save the stego-image.
 * @return Number of bits embedded (0 on error or empty input).
 */
size_t embed_pvd(const std::string& image_path, const std::vector<uint8_t>& message_bits, const std::string& output_path);

/**
 * @brief Extract bits from a PVD stego-image.
 * @param stego_path Stego-image filename.
 * @param num_bits Number of bits to extract.
 * @return Extracted bit vector (empty on error or insufficient data).
 */
std::vector<uint8_t> extract_pvd(const std::string& stego_path, size_t num_bits);