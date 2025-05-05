#pragma once

#include <string>
#include <vector>


class Parser {
    public:
        std::vector<std::string> parse_resp(const std::string& input);

    private:
        std::vector<std::string> parse_simple(const std::string& input);

        // yet to be implemented
        std::vector<std::string> parse_error(const std::string& input);
        std::vector<std::string> parse_bulk(const std::string& input);
        std::vector<std::string> parse_array(const std::string& input);

};
