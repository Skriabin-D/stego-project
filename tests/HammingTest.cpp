#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "encoding/Hamming.hpp"
#include <cstdint>
#include <vector>
#include <string>

TEST_SUITE("Hamming (encode/decode + I/O)") {

    TEST_CASE("encodeHamming: базовые значения") {
        CHECK(encodeHamming(0x0) == 0x00);
        CHECK(encodeHamming(0xF) == 0xF0);
        CHECK(encodeHamming(0xA) == 0xAC);
    }

    TEST_CASE("decodeHamming: извлечение старших 4 бит") {
        CHECK(decodeHamming(0xAC) == 0xA);
        CHECK(decodeHamming(0xF0) == 0xF);
    }

    TEST_CASE("encodeHamming/decodeHamming взаимная обратимость") {
        for (uint8_t x = 0; x < 16; ++x) {
            CHECK(decodeHamming(encodeHamming(x)) == x);
        }
    }

    TEST_CASE("encodeBitSequence: базовые и граничные случаи") {
        CHECK(encodeBitSequence({}).empty());

        // 4 бита → 8 выходных
        std::vector<uint8_t> bits4 = {1,0,1,1};
        auto enc4 = encodeBitSequence(bits4);
        CHECK(enc4.size() == 8);

        // 8 бит → 16 выходных
        std::vector<uint8_t> bits8 = {1,0,1,1,1,1,0,0};
        auto enc8 = encodeBitSequence(bits8);  
        CHECK(enc8.size() == 16);

        // проверка обратимости функций для группы из 4 бит
        auto dec4 = decodeBitSequence(enc4);
        CHECK(dec4 == bits4);
    }

    TEST_CASE("decodeBitSequence: базовые случаи") {
        // пустой ввод
        CHECK(decodeBitSequence({}).empty());

        // проверка обратимости функций на 8 битах
        std::vector<uint8_t> bits8 = {0,1,0,1,1,0,0,1};
        auto enc16 = encodeBitSequence(bits8);
        auto dec8 = decodeBitSequence(enc16);
        CHECK(dec8 == bits8);
    }

    TEST_CASE("stringToBitSequence: положительные случаи") {
        // 1) одиночный символ 'A' (0x41 = 01000001)
        std::vector<uint8_t> bitsA = stringToBitSequence("A");
        REQUIRE(bitsA.size() == 8);
        CHECK(bitsA == std::vector<uint8_t>{0,1,0,0,0,0,0,1});

        // 2) строка "Hi"
        auto bitsHi = stringToBitSequence("Hi");
        REQUIRE(bitsHi.size() == 16);
        std::vector<uint8_t> expHi = {
            0,1,0,0,1,0,0,0,
            0,1,1,0,1,0,0,1
        };
        CHECK(bitsHi == expHi);

        // 3) пустая строка → пустой вектор
        CHECK(stringToBitSequence("") == std::vector<uint8_t>{});
    }

    TEST_CASE("bitSequenceToString: положительные и отрицательные случаи") {
        // 1) обратимость функций
        std::string text = "Test!";
        auto bits = stringToBitSequence(text);
        auto out  = bitSequenceToString(bits);
        CHECK(out == text);

        // 2) пустой вектор → пустая строка
        CHECK(bitSequenceToString({}) == "");
    }

}
