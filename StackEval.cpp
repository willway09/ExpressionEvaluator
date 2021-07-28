#include "StackEval.h"

// initialize precedenceMap
std::unordered_map<std::string, int> StackEval::precedenceMap = { {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"^", 5}};

// initialize operators
std::unordered_set<std::string> StackEval::operators = {"+", "-", "*", "/", "^"};

// used to determine whether op1 has greater precedence than op2
int StackEval::comparePrecedence(std::string op1, std::string op2) {
	return StackEval::precedenceMap[op1] - StackEval::precedenceMap[op2];
}

// pass in valid tokenized infix expression
// Dijkstra's shunting yard algorithm
void StackEval::convert(const std::vector<std::string>& tokens, std::vector<std::string>& postfix) {
	std::stack<std::string> operators;
	char* end = nullptr;

	for(auto iter = tokens.begin(); iter != tokens.end(); ++iter) {
		// determine if the token is a double
		double number = std::strtod((*iter).c_str(), &end);

		if(end != (*iter).c_str() && *end == '\0' && number != HUGE_VAL) {
			// the token is a number
			postfix.push_back(*iter);

		} else if(StackEval::operators.count(*iter) != 0) {
			// assert that the non-number tokens are valid tokens; see Parser.cpp
			while(operators.size() != 0 && operators.top() != "(" && (comparePrecedence(operators.top(), *iter) > 0 || (comparePrecedence(operators.top(), *iter) == 0 && *iter != "^"))) {
				postfix.push_back(operators.top());
				operators.pop();
			}

			operators.push(*iter);

		} else if(*iter == "(") {
			// left parentheses
			operators.push(*iter);

		} else if(*iter == ")") {
			// right parentheses; assume there is a corresponding left parenthesis
			while(operators.top() != "(") {
				postfix.push_back(operators.top());
				operators.pop();
			}

			operators.pop();
		}
	}

	// move remaining operators
	while(operators.size() != 0) {
		postfix.push_back(operators.top());
		operators.pop();
	}

	// debug print postfix expression
	/*
	for (int i = 0; i < postfix.size(); i++) {
	    std::cout << postfix[i];
	    if (i < postfix.size()-1) {
	        std::cout << " ";
	    }
	}
	std::cout << std::endl;
	*/
}

// pass in valid tokenized infix expression
double StackEval::evaluate(const std::vector<std::string>& tokens) {
	// convert to postfix notation first
	std::vector<std::string> postfix;
	StackEval::convert(tokens, postfix);
	// parse expression
	std::stack<double> operands;
	char* end = nullptr;

	for(auto iter = postfix.begin(); iter != postfix.end(); ++iter) {
		// determine if the token is a double
		double number = std::strtod((*iter).c_str(), &end);

		if(end != (*iter).c_str() && *end == '\0' && number != HUGE_VAL) {
			// the token is a number
			operands.push(number);

		} else if(StackEval::operators.count(*iter) != 0) {
			// the token is an operator
			double output = 0;
			double right = operands.top();
			operands.pop();
			double left = operands.top();
			operands.pop();

			if(*iter == "+") {
				output = left + right;

			} else if(*iter == "-") {
				output = left - right;

			} else if(*iter == "*") {
				output = left * right;

			} else if(*iter == "/") {
				output = left / right;

			} else if(*iter == "^") {
				output = pow(left, right);
			}

			operands.push(output);
		}
	}

	return operands.top();
}
