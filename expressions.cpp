#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>

char operators[] = {
	'+',
	'-',
	'*',
	'/'
};

std::string generateExpression(int level) {
	int count = std::rand() % 5; // Maximum of 5 operators, between 0 and 4

	if(level == 0) count = 0; //Cap recursion at level

	if(count == 0) {
		double num = std::rand();
		num /= RAND_MAX;
		return std::to_string(num) + " ";
	} else {
		std::string rtn = "( ";

		for(int i = 0; i < count; i++) {

			rtn += generateExpression(level - 1);	

			if(i != count - 1) { //If not last element
				rtn += operators[std::rand() % 4];
				rtn += " ";
			}
		}

		rtn += ") ";
		return rtn;
	}
}

int main() {
	//Initialize randomizer to time
	std::srand(std::time(NULL));

	//Program used to evaluate random expressions
	std::ofstream out("expressions.js");

	for(int i = 0; i < 100000; i++) {
		std::string expression = generateExpression(5);
		out << "console.log(" << expression <<  " + \",\",\"" << expression << "\");" << std::endl;
	}
	out.close();

	system("node expressions.js");
}
