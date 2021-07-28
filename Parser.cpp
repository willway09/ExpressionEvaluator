#include "Parser.h"
#include <iostream>
#include <fstream>

void Parser::parse(std::string expression, std::vector<std::string>& tokens) {
    std::stringstream tokenizer(expression);
    std::string token;
    // TODO: verify if the expression is valid (match parentheses in correct locations, adjacent operators error, whitespace, etc.)
    // TODO: verify tokens are valid tokens (parentheses and the five binary operators), we can return bool for ease
    // assumes tokens in expression are separated by ' '
    while (std::getline(tokenizer, token, ' ')) {
        tokens.push_back(token);
    }
}
