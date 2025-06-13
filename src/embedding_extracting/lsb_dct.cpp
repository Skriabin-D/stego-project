#include "embedding_extracting/lsb_dct.hpp" 

static const int BLOCK_SIZE = 8;

static const int QUANT_TABLE[8][8] = {
    {16, 11, 10, 16, 24, 40, 51, 61},
    {12, 12, 14, 19, 26, 58, 60, 55},
    {14, 13, 16, 24, 40, 57, 69, 56},
    {14, 17, 22, 29, 51, 87, 80, 62},
    {18, 22, 37, 56, 68,109,103, 77},
    {24, 35, 55, 64, 81,104,113, 92},
    {49, 64, 78, 87,103,121,120,101},
    {72, 92, 95, 98,112,100,103, 99}
};

void apply_dct_quantization(cv::Mat& block, const int quant_table[8][8]) {
    block.convertTo(block, CV_32F);
    cv::dct(block, block);
    for (int i = 0; i < BLOCK_SIZE; ++i)
        for (int j = 0; j < BLOCK_SIZE; ++j)
            block.at<float>(i, j) = std::round(block.at<float>(i, j) / quant_table[i][j]);
}
void apply_idct_dequantization(cv::Mat& block, const int quant_table[8][8]) {
    for (int i = 0; i < BLOCK_SIZE; ++i)
        for (int j = 0; j < BLOCK_SIZE; ++j)
            block.at<float>(i, j) *= quant_table[i][j];
    cv::idct(block, block);
    block.convertTo(block, CV_8U);
}

size_t embed_lsb_dct(const std::string& image_path,
    const std::vector<uint8_t> message_bits,
    const std::string& output_path)
{
    cv::Mat img = cv::imread(image_path, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Ошибка: не удалось открыть контейнерное изображение: "
            << image_path << std::endl;
        return 0;
    }

    size_t bit_index = 0;
    size_t total_bits = message_bits.size();

    for (int y = 0; y + BLOCK_SIZE <= img.rows && bit_index < total_bits; y += BLOCK_SIZE) {
        for (int x = 0; x + BLOCK_SIZE <= img.cols && bit_index < total_bits; x += BLOCK_SIZE) {
       
            cv::Mat block = img(cv::Rect(x, y, BLOCK_SIZE, BLOCK_SIZE)).clone();
            apply_dct_quantization(block, QUANT_TABLE);

            int coeff = static_cast<int>(block.at<float>(2, 2));
            coeff = (coeff & ~1) | (message_bits[bit_index] & 1);
            block.at<float>(2, 2) = static_cast<float>(coeff);
            ++bit_index;

            apply_idct_dequantization(block, QUANT_TABLE);
            block.copyTo(img(cv::Rect(x, y, BLOCK_SIZE, BLOCK_SIZE)));
        }
    }

    if (!cv::imwrite(output_path, img)) {
        std::cerr << "Ошибка: не удалось сохранить стего-изображение: "
            << output_path << std::endl;
    }

    return total_bits;
}

std::vector<uint8_t> extract_lsb_dct(const std::string& stego_path,
    size_t num_bits)
{
    cv::Mat img = cv::imread(stego_path, cv::IMREAD_GRAYSCALE);
    if (img.empty()) {
        std::cerr << "Ошибка: не удалось открыть стего-изображение: "
            << stego_path << std::endl;
        return {};
    }

    std::vector<uint8_t> extracted;
    extracted.reserve(num_bits);

    for (int y = 0; y + BLOCK_SIZE <= img.rows && extracted.size() < num_bits; y += BLOCK_SIZE) {
        for (int x = 0; x + BLOCK_SIZE <= img.cols && extracted.size() < num_bits; x += BLOCK_SIZE) {
            cv::Mat block = img(cv::Rect(x, y, BLOCK_SIZE, BLOCK_SIZE)).clone();
            apply_dct_quantization(block, QUANT_TABLE);
            int coeff = static_cast<int>(block.at<float>(2, 2));
            extracted.push_back(static_cast<uint8_t>(coeff & 1));
        }
    }

    return extracted;
}
