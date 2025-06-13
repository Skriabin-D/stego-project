cmake_minimum_required(VERSION 3.14)
project(StegoTests LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Пути к заголовкам проекта и doctest.h
include_directories(
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/tests
    ${OpenCV_INCLUDE_DIRS}
)

# --- HammingTest ---
add_executable(HammingTest
    HammingTest.cpp
    ${CMAKE_SOURCE_DIR}/src/encoding/Hamming.cpp
)
add_test(NAME HammingTest COMMAND HammingTest)

# --- LSB_DCT Test: cover DCT helpers, embed and extract ---
add_executable(lsb_dctTest
    lsb_dctTest.cpp
    ${CMAKE_SOURCE_DIR}/src/embedding_extracting/lsb_dct.cpp
)
target_link_libraries(lsb_dctTest PRIVATE ${OpenCV_LIBS})
target_compile_definitions(lsb_dctTest PRIVATE
    BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)
add_test(NAME lsb_dctTest COMMAND lsb_dctTest)

# --- PVD Test: cover get_pvd_range, embed_pvd, extract_pvd ---
add_executable(pvdTest
    pvdTest.cpp
    ${CMAKE_SOURCE_DIR}/src/embedding_extracting/pvd.cpp
)
target_link_libraries(pvdTest PRIVATE ${OpenCV_LIBS})
target_compile_definitions(pvdTest PRIVATE
    BINARY_DIR=\"${CMAKE_CURRENT_BINARY_DIR}\"
)
add_test(NAME pvdTest COMMAND pvdTest)
