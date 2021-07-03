#pragma once
#include <string>
#include <vector>
#include <sstream>

static class Parser{

public:
    static void parse(std::string expression, std::vector<string>& tokens);
}

static void Parser::parse(std::string expression, std::vector<string>& tokens){
    std::stringstream tokenizer(expression);
    std::string token;

    // assumes tokens in expression are separated by ' '
    while (std::getline(tokenizer, token, ' ')){
        tokens.push_back(token);
    }
}