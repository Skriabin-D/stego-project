#pragma once

#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

// Диапазоны для PVD
extern const std::vector<std::pair<int, int>> pvd_ranges;

//// Преобразование строки битов в std::vector<uint8_t>
//std::vector<uint8_t> string_to_bits(const std::string& bit_string);

// Получение диапазона PVD
std::pair<int, int> get_pvd_range(int diff);

// Функция встраивания PVD
void embed_pvd(const std::string& image_path, const std::vector<uint8_t>& message_bits, const std::string& output_path);

// Функция извлечения PVD
std::vector<uint8_t> extract_pvd(const std::string& stego_path, size_t num_bits);