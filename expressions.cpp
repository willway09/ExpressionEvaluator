#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <string>

char operators[] = {
	'+',
	'-',
	'*',
	'/'
};

std::string generateExpression(int level, int baseLevel) {
	int count = std::rand() % 5; // Maximum of 5 operands, between 0 and 4

	if(level == 0) count = 0; //Cap recursion at level

	if(count == 0 && baseLevel == level) {
		if(std::rand() % 1000 == 0) { //1 in 1000 chance of being a single-number expression
			std::cout << "Here" << std::endl;
		} else { //Otherwise
			count = std::rand() % 4 + 1; // Maximum of 5 operands, between 1 and 4
		}
	}

	if(count == 0) {
		double num = std::rand();
		num /= RAND_MAX;
		return std::to_string(num) + " ";
	} else {
		std::string rtn = "( ";

		for(int i = 0; i < count; i++) {

			rtn += generateExpression(level - 1, baseLevel);	

			if(i != count - 1) { //If not last element
				rtn += operators[std::rand() % 4];
				rtn += " ";
			}
		}

		rtn += ") ";
		return rtn;
	}
}

int main(int argc, char** argv) {
	//Initialize randomizer to time
	if(argc > 1) {
		std::srand(std::stoi(argv[1]));
	} else {
		std::srand(std::time(NULL));
	}

	//Program used to evaluate random expressions
	std::ofstream out("expressions.js");

	for(int i = 0; i < 100000; i++) {
		std::string expression = generateExpression(5, 5);
		out << "console.log(" << expression <<  " + \",\",\"" << expression << "\");" << std::endl;
	}
	out.close();

	system("node expressions.js");
}
