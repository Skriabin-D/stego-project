#pragma	once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

/**
 * @file lsb_dct.hpp
 * @brief Functions for embedding and extracting bits in DCT blocks using LSB.
 */

#pragma once


/**
 * @def BLOCK_SIZE
 * @brief Size (in pixels) of one DCT block (8×8).
 *
 * The image is divided into non-overlapping blocks of this size for DCT/IDCT processing.
 */
extern const int BLOCK_SIZE;


/**
 * @def QUANT_TABLE
 * @brief Standard 8×8 JPEG quantization table for luminance.
 *
 * Used to quantize and dequantize DCT coefficients. Lower values preserve more detail.
 */
extern const int QUANT_TABLE[8][8];


/**
 * @brief Apply DCT and quantize a single 8×8 block.
 *
 * Converts the block to floating point, applies the Discrete Cosine Transform (DCT),
 * then divides each coefficient by the corresponding value in @p quant_table
 * and rounds to the nearest integer.
 *
 * @param block[in,out]   Input 8×8 pixel block (CV_8U). On output it contains
 *                        quantized DCT coefficients (CV_32F).
 * @param quant_table     8×8 matrix of quantization values.
 */
void apply_dct_quantization(cv::Mat& block, const int quant_table[8][8]);


/**
 * @brief Dequantize and apply inverse DCT to a single 8×8 block.
 *
 * Multiplies each coefficient in @p block by the corresponding @p quant_table
 * value, applies the inverse DCT, then converts the result back to 8-bit pixels.
 *
 * @param block[in,out]   Input 8×8 block of quantized DCT coefficients (CV_32F).
 *                        On output it contains spatial-domain pixel values (CV_8U).
 * @param quant_table     8×8 matrix of quantization values used in the forward pass.
 */
void apply_idct_dequantization(cv::Mat& block, const int quant_table[8][8]);



/**
 * @brief Embed a sequence of bits in the least significant bits of DCT coefficients.
 *
 * Loads a grayscale image from @p image_path, splits it into non-overlapping
 * 8×8 blocks, applies DCT and quantization, and hides one bit per AC coefficient
 * by setting its LSB to the next bit in @p message_bits. After embedding all bits
 * (or reaching the image boundary), applies inverse DCT and saves the result.
 *
 * @param image_path     Path to the cover image (grayscale PNG, JPEG, etc.).
 * @param message_bits   Vector of bits (0 or 1) to embed.
 * @param output_path    Path where the stego-image will be written.
 * @return Number of bits actually embedded (equals @p message_bits.size() if all fit;
 *         returns 0 if the image failed to load or @p message_bits is empty).
 */
size_t embed_lsb_dct(const std::string& image_path, const std::vector<uint8_t> message_bits, const std::string& output_path);


/**
 * @brief Extract a sequence of bits from the LSBs of DCT coefficients.
 *
 * Loads a grayscale stego-image from @p stego_path, splits it into 8×8 blocks,
 * applies DCT and quantization, then reads the LSB of each AC coefficient in
 * block-order until @p num_bits bits have been collected or the image ends.
 *
 * @param stego_path  Path to the stego-image with hidden data.
 * @param num_bits    Number of bits to extract.
 * @return Vector of extracted bits. If the image cannot be read or fewer than
 *         @p num_bits bits are available, the return will be empty or shorter
 *         than @p num_bits.
 */
std::vector<uint8_t> extract_lsb_dct(const std::string& stego_path, size_t num_bits);