#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

class StackEval {

	static std::unordered_map<std::string, int> precedenceMap;
	static std::unordered_set<std::string> operators;
	struct Node {
		double value;
		std::string binaryOperator;
		bool isNumber;
		Node* prev;
		Node(double _value);
		Node(std::string _binaryOperator);
	};
	struct smallStack {
		Node* top;
		void pop();
		void push(Node* node);
		smallStack();
	};

public:
	static int comparePrecedence(std::string op1, std::string op2);
	static void convert(const std::vector<std::string>& tokens, std::vector<Node*>& postfix);
	static double evaluate(const std::vector<std::string>& tokens);
};