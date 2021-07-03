#pragma once
#include <string>
#include <vector>
#include <sstream>

class Parser {

public:
    static void parse(std::string expression, std::vector<std::string>& tokens);
};