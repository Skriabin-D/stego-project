cmake_minimum_required(VERSION 3.14)

project(Stego LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenCV_DIR "D:/opencv/build")  
find_package(OpenCV REQUIRED)

set(CMAKE_PREFIX_PATH "D:/Qt/6.6.1/msvc2019_64/lib/cmake")
find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR}/include)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/main.cpp
    src/graphics/gui_interface.cpp
    src/graphics/mainwindow.cpp
    src/encoding/Hamming.cpp
    src/embedding_extracting/pvd.cpp
    src/embedding_extracting/lsb_dct.cpp
)

set(HEADERS
    include/graphics/mainwindow.hpp
)

set(UIS
    src/graphics/mainwindow.ui
)

add_executable(stego
    ${SOURCES}
    ${HEADERS}
    ${UIS}
)

target_link_libraries(stego
    Qt6::Widgets
    ${OpenCV_LIBS}
)

add_compile_options("/utf-8")

enable_testing()
add_subdirectory(tests)


