#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include "../parser/parser.hh"

Parser* parser = new Parser();

TEST_CASE("Parse Simple String Successful", "[simple]") {
    std::string input = "+OK\r\n";
    std::vector<std::string> expected = {"OK"};
    auto parsed = parser->parse_resp(input);
    REQUIRE(parsed == expected);
}


TEST_CASE("Parse Simple String Empty Input Failure", "[simple]") {
    std::string input = "";
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

TEST_CASE("Parse Simple String Bad Input Failure", "[simple]") {
    std::string input = "+OK"; // missing \r\n
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}


TEST_CASE("Parse Error Successful", "[error]") {
    std::string input = "-Error Message\r\n";
    std::vector<std::string> expected = {"Error Message"};
    auto parsed = parser->parse_resp(input);
    REQUIRE(parsed == expected);
}


TEST_CASE("Parse Error Empty Input Failure", "[error]") {
    std::string input = "";
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

TEST_CASE("Parse Error Bad Input Failure", "[error]") {
    std::string input = "-Error Message"; // missing \r\n
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}