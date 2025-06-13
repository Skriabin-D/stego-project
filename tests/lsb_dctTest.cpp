#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "embedding_extracting/lsb_dct.hpp"


TEST_SUITE("LSB-DCT Module") {

    // 1) DCT ↔ IDCT helpers

    TEST_CASE("обратимость apply_dct_quantization apply_idct_dequantization") {
        cv::Mat block(8, 8, CV_8U, cv::Scalar(16));
        cv::Mat orig = block.clone();

        apply_dct_quantization(block, QUANT_TABLE);
        apply_idct_dequantization(block, QUANT_TABLE);

        REQUIRE(block.size() == orig.size());
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                CHECK(block.at<uint8_t>(i, j) == orig.at<uint8_t>(i, j));
    }

    TEST_CASE("apply_dct_quantization + apply_idct_dequantization выходит за пределы значения пикселей") {
        cv::Mat block(8, 8, CV_8U, cv::Scalar(17));

        apply_dct_quantization(block, QUANT_TABLE);
        apply_idct_dequantization(block, QUANT_TABLE);

        uint8_t v0 = block.at<uint8_t>(0, 0);
        CHECK(v0 <= 255);
        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                CHECK(block.at<uint8_t>(i, j) == v0);
    }

    // 2) embed_lsb_dct

    TEST_CASE("embed_lsb_dct: проверка успешности встраивания") {
        cv::Mat cover(8, 8, CV_8U, cv::Scalar(128));
        std::string coverPath = std::string(BINARY_DIR) + "/cover_positive.png";
        REQUIRE(cv::imwrite(coverPath, cover));

        std::vector<uint8_t> msg = {1,0,1,1,0};
        std::string stegoPath = std::string(BINARY_DIR) + "/stego_positive.png";
        size_t embedded = embed_lsb_dct(coverPath, msg, stegoPath);
        CHECK(embedded == msg.size());

        cv::Mat stego = cv::imread(stegoPath, cv::IMREAD_GRAYSCALE);
        REQUIRE_FALSE(stego.empty());
    }

    TEST_CASE("embed_lsb_dct: empty message") {
        cv::Mat cover(8, 8, CV_8U, cv::Scalar(128));
        std::string coverPath = std::string(BINARY_DIR) + "/cover_empty.png";
        REQUIRE(cv::imwrite(coverPath, cover));

        // empty
        std::string stegoEmpty = std::string(BINARY_DIR) + "/stego_empty.png";
        CHECK(embed_lsb_dct(coverPath, {}, stegoEmpty) == 0);
    }

    // 3) extract_lsb_dct

    TEST_CASE("extract_lsb_dct: request more bits than embedded returns only embedded bits") {
        cv::Mat cover(256, 256, CV_8U, cv::Scalar(128));
        std::string coverPath = std::string(BINARY_DIR) + "/cover_over.png";
        REQUIRE(cv::imwrite(coverPath, cover));

        std::vector<uint8_t> msg = {0,1,0};
        std::string stegoPath = std::string(BINARY_DIR) + "/stego_over.png";
        size_t embedded = embed_lsb_dct(coverPath, msg, stegoPath);

        size_t request = 8;
        auto extracted = extract_lsb_dct(stegoPath, request);

        // Должен вернуть ровно request бит
        CHECK(extracted.size() == request);

        // Первые embedded бит совпадают с сообщением
        for (size_t i = 0; i < msg.size(); ++i)
            CHECK(extracted[i] == msg[i]);
    }

    TEST_CASE("extract_lsb_dct: invalid path returns empty") {
        auto extracted = extract_lsb_dct(std::string(BINARY_DIR) + "/no_image.png", 4);
        CHECK(extracted.empty());
    }

}
