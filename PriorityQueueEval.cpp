#include "PriorityQueueEval.h"
#include <cmath>
#include <cctype>

double PriorityQueueEval::evaluate(const std::vector<std::string>& constTokens) {
	//Initialize operator priority queue
	std::priority_queue<Operator> operators;

	//This method needs no parentheses in tokens array, declare one to be populated later
	std::vector<std::string> tokens;

	unsigned int nesting = 0; //Initially no nesting
	unsigned int idx = 0; //Start at first index

	//Fill operator priority queue, and clear parenthesis
	//Cannot use for loop, because need more precise control over iterator incrementation
	for(auto it = constTokens.begin(); it != constTokens.end(); ++it) {
		if(*it == "(") {
			nesting++; //One deeper in nesting
			continue; //Do not insert parenthesis into new tokens array, and do not increment index

		} else if(*it == ")") {
			nesting--; //One shallower in nesting
			continue; //Do not insert parenthesis into new tokens array, and do not increment index

		} else if(it->length() == 1 && !(std::isdigit((*it)[0]))) { //If of length 1 and not a number, then must be an operator
			//Cannot be a negative number, because those have length of at least 2 characters
			//Construct and insert operator with correct symbol, index, and nesting
			Operator temp((*it)[0], idx, nesting);
			operators.push(temp);

		} else {
			//Is number, don't need to do anything special
		}

		tokens.push_back(*it);
		idx++;
	}

	//Now have tokens, which is constTokens without parenthesis,
	//and operators, which has all operators in order in a priority queue

	return recursivelyEvaluate(operators, tokens, 0, tokens.size() - 1);
}


double PriorityQueueEval::recursivelyEvaluate(std::priority_queue<Operator>& operators, const std::vector<std::string>& tokens, int lower, int upper) {
	if(upper == lower) { //This will end up being a number
		return std::stod(tokens[upper]);

	} else { //This will end up being an operator
		Operator op = operators.top();
		operators.pop();

		std::priority_queue<Operator> upperOps;
		std::priority_queue<Operator> lowerOps;

		while(!operators.empty()) {
			Operator temp = operators.top();

			if(temp.index > op.index) {
				upperOps.push(temp);

			} else { //Lower in index than op
				lowerOps.push(temp);
			}

			operators.pop();
		}

		double val1 = recursivelyEvaluate(lowerOps, tokens, lower, op.index - 1);
		double val2 = recursivelyEvaluate(upperOps, tokens, op.index + 1, upper);

		switch(op.character) {
			case '+':
				return val1 + val2;

			case '-':
				return val1 - val2;

			case '*':
				return val1 * val2;

			case '/':
				return val1 / val2;

			case '^':
				return std::pow(val1, val2);
		}

		return 0; //Technically impossible to reach under constraints, but needed to passify compiler
	}
}
