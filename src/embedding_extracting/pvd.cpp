#include "embedding_extracting/pvd.hpp"

// Определение диапазонов для PVD
const std::vector<std::pair<int, int>> pvd_ranges = {{0, 7}, {8, 15}, {16, 31}, {32, 63}, {64, 127}, {128, 255}};


std::pair<int, int> get_pvd_range(int diff) {
    for (const auto& pr : pvd_ranges) {
        if (diff >= pr.first && diff <= pr.second) {
            return pr;
        }
    }
    return pvd_ranges.back();
}

// Функция встраивания PVD
size_t embed_pvd(const std::string& image_path, const std::vector<uint8_t>& message_bits, const std::string& output_path) {
    cv::Mat img = cv::imread(image_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Ошибка: не удалось открыть контейнерное изображение: " << image_path << std::endl;
        return 0;
    }
    img.convertTo(img, CV_32S);

    int height = img.rows;
    int width = img.cols;

    if (message_bits.empty()) {
        return 0;
    }
    std::vector<uint8_t> original_message_bits = message_bits;
    size_t bit_pointer = 0;
    size_t total_bits = message_bits.size();

    for (int i = 0; i < height && bit_pointer < total_bits; ++i) {
        for (int j = 0; j + 1 < width && bit_pointer < total_bits; j += 2) {
            for (int k = 0; k < 3 && bit_pointer < total_bits; ++k) {
                int pixel1 = img.at<cv::Vec3i>(i, j)[k];
                int pixel2 = img.at<cv::Vec3i>(i, j + 1)[k];
                int diff = std::abs(pixel1 - pixel2);

                auto [lower, upper] = get_pvd_range(diff);
                int bits_per_pair = static_cast<int>(std::floor(std::log2(upper - lower + 1)));

                std::vector<uint8_t> bits_to_embed;
                for (int b = 0; b < bits_per_pair; ++b) {
                    if (bit_pointer < total_bits) {
                        bits_to_embed.push_back(message_bits[bit_pointer++]);
                    } else {
                        bits_to_embed.push_back(0);
                    }
                }

                int embed_value = 0;
                for (uint8_t b : bits_to_embed) {
                    embed_value = (embed_value << 1) | b;
                }

                int new_diff = lower + embed_value;
                int delta_diff = new_diff - diff;

                int pixel1_new, pixel2_new;
                if (pixel1 >= pixel2) {
                    pixel1_new = pixel1 + static_cast<int>(std::ceil(delta_diff / 2.0));
                    pixel2_new = pixel2 - static_cast<int>(std::floor(delta_diff / 2.0));
                } else {
                    pixel1_new = pixel1 - static_cast<int>(std::floor(delta_diff / 2.0));
                    pixel2_new = pixel2 + static_cast<int>(std::ceil(delta_diff / 2.0));
                }

                img.at<cv::Vec3i>(i, j)[k] = std::max(0, std::min(255, pixel1_new));
                img.at<cv::Vec3i>(i, j + 1)[k] = std::max(0, std::min(255, pixel2_new));
            }
        }
    }

    img.convertTo(img, CV_8U);
    if (!cv::imwrite(output_path, img)) {
        std::cerr << "Ошибка: не удалось сохранить стего-изображение: " << output_path << std::endl;
    } else {
        std::cout << "Стего-изображение сохранено как: " << output_path << std::endl;
    }

    return total_bits;
}

// Функция извлечения PVD
std::vector<uint8_t> extract_pvd(const std::string& stego_path, size_t num_bits) {
    cv::Mat img = cv::imread(stego_path, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Ошибка: не удалось открыть стего-изображение: " << stego_path << std::endl;
        return std::vector<uint8_t>();
    }
    img.convertTo(img, CV_32S);

    int height = img.rows;
    int width = img.cols;
    std::vector<uint8_t> extracted_bits;

    for (int i = 0; i < height && extracted_bits.size() < num_bits; ++i) {
        for (int j = 0; j + 1 < width && extracted_bits.size() < num_bits; j += 2) {
            for (int k = 0; k < 3 && extracted_bits.size() < num_bits; ++k) {
                int pixel1 = img.at<cv::Vec3i>(i, j)[k];
                int pixel2 = img.at<cv::Vec3i>(i, j + 1)[k];
                int diff = std::abs(pixel1 - pixel2);

                auto [lower, upper] = get_pvd_range(diff);
                int bits_per_pair = static_cast<int>(std::floor(std::log2(upper - lower + 1)));
                if (bits_per_pair == 0) continue;

                int embed_value = diff - lower;
                std::string bit_string;
                for (int b = bits_per_pair - 1; b >= 0; --b) {
                    bit_string.push_back(((embed_value >> b) & 1) + '0');
                }
                for (char c : bit_string) {
                    if (extracted_bits.size() < num_bits) {
                        extracted_bits.push_back(c - '0');
                    }
                }
            }
        }
    }

    if (extracted_bits.size() < num_bits) {
        std::cerr << "Ошибка: удалось извлечь только " << extracted_bits.size() << " битов, требуется " << num_bits << std::endl;
        return std::vector<uint8_t>();
    }

    std::cout << "Извлечённая последовательность битов: ";
    for (uint8_t bit : extracted_bits) {
        std::cout << static_cast<int>(bit);
    }
    std::cout << std::endl;

    return extracted_bits;
}
