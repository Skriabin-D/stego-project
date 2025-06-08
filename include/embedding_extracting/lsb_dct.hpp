#pragma	once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>

extern const int BLOCK_SIZE;
extern const int QUANT_TABLE[8][8];

void apply_dct_quantization(cv::Mat& block, const int quant_table[8][8]);

void apply_idct_dequantization(cv::Mat& block, const int quant_table[8][8]);

size_t embed_lsb_dct(const std::string& image_path, const std::vector<uint8_t> message_bits, const std::string& output_path);

std::vector<uint8_t> extract_lsb_dct(const std::string& stego_path, size_t num_bits);