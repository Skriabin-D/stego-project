cmake_minimum_required(VERSION 3.10)
project(Stego LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)
set(SOURCES
    src/main.cpp
    src/encoding/Hamming.cpp
    src/embedding_extracting/lsb_dct.cpp
    src/embedding_extracting/pvd.cpp
)
add_executable(stego ${SOURCES})
target_link_libraries(stego ${OpenCV_LIBS})
