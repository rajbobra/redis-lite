cmake_minimum_required(VERSION 3.14)
project(redis-lite CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Catch2 3 REQUIRED)
include_directories(/opt/homebrew/Cellar/catch2/3.8.1/include)

# Add the parser library
add_library(parser
    parser/parser.cc
    parser/parser.hh
)
target_include_directories(parser PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Add tests
add_executable(tests tests/parser_test.cc)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain parser)

# Enable testing
include(CTest)
include(Catch)
catch_discover_tests(tests) 