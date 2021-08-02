#include "Parser.h"
#include <iostream>
#include <fstream>

void Parser::parse(std::string expression, std::vector<std::string>& tokens) {
	std::stringstream tokenizer(expression);
	std::string token;
	// assumes tokens in expression are separated by ' '
	while(std::getline(tokenizer, token, ' ')) {
		tokens.push_back(token);
	}
}
