#include <catch2/catch_test_macros.hpp>
#include <string>
#include <vector>
#include "../parser/parser.hh"

Parser* parser = new Parser();

// EMPTY INPUT TEST

TEST_CASE("Parse Empty Input Failure", "[simple]") {
    std::string input = "";
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

// SIMPLE STRING TESTS

TEST_CASE("Parse Simple String Successful", "[simple]") {
    std::string input = "+OK\r\n";
    std::vector<std::string> expected = {"OK"};
    auto parsed = parser->parse_resp(input);
    REQUIRE(parsed == expected);
}

TEST_CASE("Parse Simple String Bad Input Failure", "[simple]") {
    std::string input = "+OK"; // missing \r\n
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}


// ERROR TESTS
TEST_CASE("Parse Error Successful", "[error]") {
    std::string input = "-Error Message\r\n";
    std::vector<std::string> expected = {"Error Message"};
    auto parsed = parser->parse_resp(input);
    REQUIRE(parsed == expected);
}

TEST_CASE("Parse Error Bad Input Failure", "[error]") {
    std::string input = "-Error Message"; // missing \r\n
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}


// BULK STRING TESTS

TEST_CASE("Parse Bulk String Successful", "[bulk]") {
    std::string input = "$6\r\nfoobar\r\n";
    std::vector<std::string> expected = {"foobar"};
    auto parsed = parser->parse_resp(input);
    REQUIRE(parsed == expected);
}

TEST_CASE("Parse Bulk String Bad Input Missing Length Failure", "[bulk]") {
    std::string input = "$\r\nfoobar\r\n"; // missing length
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

TEST_CASE("Parse Bulk String Bad Input Missing Data Failure", "[bulk]") {
    std::string input = "$6\r\n"; // missing data
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

TEST_CASE("Parse Bulk String Bad Input Missing CRLF Failure", "[bulk]") {
    std::string input = "$6foobar\r\n"; // missing CRLF
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

TEST_CASE("Parse Bulk String Bad Input Invalid Length Failure", "[bulk]") {
    std::string input = "$6foobarextra\r\nfoo"; // length given is 6, but actual length is 11
    REQUIRE_THROWS_AS(parser->parse_resp(input), std::runtime_error);
}

TEST_CASE("Parse Bulk String is null", "[bulk]") {
    std::string input = "$-1\r\n";
    REQUIRE(parser->parse_resp(input).empty());
}

