cmake_minimum_required(VERSION 3.16.0)
project(atmcontroller VERSION 1.0.0 LANGUAGES CXX)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt5 ${QT_VERSION} REQUIRED COMPONENTS
    Core
    Test
)

add_subdirectory(src)
