#include <iostream>
#include <vector>
#include "Parser.h"

int main() {
	std::string expression = "( 3 + 2 ) * 5";
	std::vector<std::string> tokens;
	Parser::parse(expression, tokens);
	for (int i = 0; i < tokens.size(); i++) {
		std::cout << tokens[i] << std::endl;
	}
}
