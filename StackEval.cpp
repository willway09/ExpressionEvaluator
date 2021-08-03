#include "StackEval.h"

// Node constructors
StackEval::Node::Node(double _value) {
	value = _value;
	prev = nullptr;
	isNumber = true;
}

StackEval::Node::Node(std::string _binaryOperator) {
	binaryOperator = _binaryOperator;
	prev = nullptr;
	isNumber = false;
}

StackEval::smallStack::smallStack() {
	top = nullptr;
}

void StackEval::smallStack::pop() {
	if(top != nullptr) {
		Node* temp = top;
		top = top->prev;
		delete temp;
	}
}

void StackEval::smallStack::push(Node* node) {
	Node* temp = top;
	top = node;
	node->prev = temp;
}

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
void StackEval::convert(const std::vector<std::string>& tokens, std::vector<Node*>& postfix) {

	smallStack operators;
	char* end = nullptr;

	for(auto iter = tokens.begin(); iter != tokens.end(); ++iter) {

		// determine if the token is a double
		double number = std::strtod((*iter).c_str(), &end);

		if(end != (*iter).c_str() && *end == '\0' && number != HUGE_VAL) {

			// the token is a number
			Node* numberNode = new Node(number);
			postfix.push_back(numberNode);

		} else if(StackEval::operators.count(*iter) != 0) {

			// the token is instead an operator
			while(operators.top != nullptr && operators.top->binaryOperator != "(" && (comparePrecedence(operators.top->binaryOperator, *iter) > 0 || (comparePrecedence(operators.top->binaryOperator, *iter) == 0 && *iter != "^"))) {
				Node* shuntOp = new Node(operators.top->binaryOperator);
				postfix.push_back(shuntOp);
				operators.pop();
			}

			Node* operatorNode = new Node(*iter);
			operators.push(operatorNode);

		} else if(*iter == "(") {

			// the token is a left parenthesis
			Node* operatorNode = new Node(*iter);
			operators.push(operatorNode);

		} else if(*iter == ")") {

			// the token is a right parenthesis
			while(operators.top->binaryOperator != "(") {
				Node* shuntOp = new Node(operators.top->binaryOperator);
				postfix.push_back(shuntOp);
				operators.pop();
			}

			operators.pop();
		}
	}

	// move remaining operators
	while(operators.top != nullptr) {
		Node* shuntOp = new Node(operators.top->binaryOperator);
		postfix.push_back(shuntOp);
		operators.pop();
	}
}

// pass in valid tokenized infix expression
double StackEval::evaluate(const std::vector<std::string>& tokens) {

	// convert to postfix notation first
	std::vector<Node*> postfix;
	StackEval::convert(tokens, postfix);

	// parse expression
	smallStack operands;

	for(int i = 0; i < postfix.size(); i++) {

		// determine if the token is a double
		if(postfix[i]->isNumber) {

			// the token is a number
			operands.push(postfix[i]);

		} else if(StackEval::operators.count(postfix[i]->binaryOperator) != 0) {

			// the token is an operator
			double output = 0;
			double right = operands.top->value;
			operands.pop();
			double left = operands.top->value;
			operands.pop();

			if(postfix[i]->binaryOperator == "+") {
				output = left + right;

			} else if(postfix[i]->binaryOperator == "-") {
				output = left - right;

			} else if(postfix[i]->binaryOperator == "*") {
				output = left * right;

			} else if(postfix[i]->binaryOperator == "/") {
				output = left / right;

			} else if(postfix[i]->binaryOperator == "^") {
				output = pow(left, right);
			}

			Node* outputNode = new Node(output);
			operands.push(outputNode);
		}
	}

	double toReturn = operands.top->value;
	operands.pop();
	return toReturn;
}
