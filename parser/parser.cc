#include "parser.hh"
#include <stdexcept>
#include <string>
#include <vector>


std::vector<std::string> Parser::parse_resp(const std::string& input) {
    
    if(input.empty()) {
        throw std::runtime_error("Empty input");
    }

    switch (input[0]) {
        case '+':
            return parse_simple(input);
        case '-':
            // return parse_errors(input);
            break;
        case '$':
            // return parse_bulk(input);
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