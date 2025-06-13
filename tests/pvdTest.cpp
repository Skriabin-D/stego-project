#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include <opencv2/opencv.hpp>
#include "embedding_extracting/pvd.hpp"

#include <vector>
#include <string>

TEST_SUITE("PVD Module") {

    TEST_CASE("get_pvd_range: диапазоны и выход за пределы") {
        CHECK(get_pvd_range(0)   == std::make_pair(0,  7));
        CHECK(get_pvd_range(255) == std::make_pair(128,255));
        CHECK(get_pvd_range(-1)  == std::make_pair(128,255));
        CHECK(get_pvd_range(300) == std::make_pair(128,255));
    }

    TEST_CASE("embed_pvd: положительные и отрицательные случаи") {
        cv::Mat cover(2, 2, CV_8UC3, cv::Scalar(128,128,128));
        std::string coverPath = std::string(BINARY_DIR) + "/cover_pvd_embed.png";
        REQUIRE(cv::imwrite(coverPath, cover));

        // Хороший кейс
        std::vector<uint8_t> msgGood = {1,0,1,1,0,1};
        std::string outGood = std::string(BINARY_DIR) + "/stego_pvd_good.png";
        size_t retGood = embed_pvd(coverPath, msgGood, outGood);
        CHECK(retGood == msgGood.size());

        // Пустое сообщение
        std::vector<uint8_t> msgEmpty;
        std::string outEmpty = std::string(BINARY_DIR) + "/stego_pvd_empty.png";
        size_t retEmpty = embed_pvd(coverPath, msgEmpty, outEmpty);
        CHECK(retEmpty == 0);

        // Некорректный файл
        std::vector<uint8_t> msgBad = {0,1};
        std::string badPath = std::string(BINARY_DIR) + "/no_such.png";
        std::string outBad  = std::string(BINARY_DIR) + "/stego_pvd_bad.png";
        size_t retBad = embed_pvd(badPath, msgBad, outBad);
        CHECK(retBad == 0);
    }

    TEST_CASE("extract_pvd: положительный кейс") {
        cv::Mat cover(2, 2, CV_8UC3, cv::Scalar(128,128,128));
        std::string coverPath = std::string(BINARY_DIR) + "/cover_pvd_extract.png";
        REQUIRE(cv::imwrite(coverPath, cover));

        std::vector<uint8_t> msg = {1,0,1,1,0,1};
        std::string stegoPath = std::string(BINARY_DIR) + "/stego_pvd_extract.png";
        size_t embedded = embed_pvd(coverPath, msg, stegoPath);
        REQUIRE(embedded == msg.size());

        auto extracted = extract_pvd(stegoPath, msg.size());
        CHECK(extracted == msg);
    }

    TEST_CASE("extract_pvd: запрос большего числа бит") {
        cv::Mat cover(2, 2, CV_8UC3, cv::Scalar(128,128,128));
        std::string coverPath = std::string(BINARY_DIR) + "/cover_pvd_over.png";
        REQUIRE(cv::imwrite(coverPath, cover));

        // Встраиваем 3 бита
        std::vector<uint8_t> msg = {1,1,0};
        std::string stegoPath = std::string(BINARY_DIR) + "/stego_pvd_over.png";
        size_t embedded = embed_pvd(coverPath, msg, stegoPath);
        REQUIRE(embedded == msg.size());

        // Запрашиваем 5 бит
        size_t request = 5;
        auto extracted = extract_pvd(stegoPath, request);
        // Должно вернуться ровно request бит
        CHECK(extracted.size() == request);
        // Первые embedded == msg
        for (size_t i = 0; i < embedded; ++i) {
            CHECK(extracted[i] == msg[i]);
        }
    }

    TEST_CASE("extract_pvd: неверный путь") {
        auto ext = extract_pvd(std::string(BINARY_DIR) + "/nonexistent.png", 4);
        CHECK(ext.empty());
    }

}
