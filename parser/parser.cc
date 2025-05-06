#include "parser.hh"
#include <stdexcept>
#include <string>
#include <vector>
#include <iostream>

std::vector<std::string> Parser::parse_resp(const std::string& input) {
    
    if(input.empty()) {
        throw std::runtime_error("Empty input");
    }

    switch (input[0]) {
        case '+':
            return parse_simple(input);
        case '-':
            return parse_error(input);
            break;
        case '$':
            return parse_bulk(input);
            break;
        case '*':
            // return parse_array(input);
            break;
        default:
            break;
    }

    return std::vector<std::string>();
}


std::vector<std::string> Parser::parse_simple(const std::string& input) {
    std::vector<std::string> result;
    size_t end = input.find("\r\n");

    if(end == std::string::npos) {
        throw std::runtime_error("Invalid format for Simple String. Simple String should be of format +<string>\\r\\n");
    }

    std::string simple = input.substr(1, end-1);
    result.push_back(simple);
    return result;
}


std::vector<std::string> Parser::parse_error(const std::string& input) {
    std::vector<std::string> result;
    size_t end = input.find("\r\n");

    if(end == std::string::npos) {
        throw std::runtime_error("Invalid format for Errors. Error should be of format -<error>\\r\\n");
    }

    std::string error_msg = input.substr(1, end-1);
    result.push_back(error_msg);
    return result;
}


std::vector<std::string> Parser::parse_bulk(const std::string& input) {
    std::vector<std::string> result;
    size_t lengthEnd = input.find("\r\n");
    int length = 0;

    if(lengthEnd == std::string::npos) {
        throw std::runtime_error("Invalid bulk string. missing CRLF after length");
    }

    try {
        length = std::stoi(input.substr(1, lengthEnd-1));
    } catch (const std::invalid_argument& e) {
        throw std::runtime_error("Invalid bulk string. length is not an integer");
    }

    if(length < 0) {
        return result;
    }
    
    size_t strStart = lengthEnd+2;
    size_t strEnd = strStart+length;

    if(input.length() < strEnd) {
        throw std::runtime_error("Bulk String missing data");
    }

    if(input.substr(strEnd, strEnd+2) != "\r\n") {
        throw std::runtime_error("Invalid bulk string, missing CRLF after data");
    }

    std::string bulk = input.substr(strStart, length);
    result.push_back(bulk);
    return result;
}