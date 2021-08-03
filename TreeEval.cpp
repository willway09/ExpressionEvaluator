#include "TreeEval.h"

// Node constructors
TreeEval::Node::Node(double _value, Node* _left, Node* _right) {
	value = _value;
	left = _left;
	right = _right;
	isNumber = true;
}

TreeEval::Node::Node(std::string _binaryOperator, Node* _left, Node* _right) {
	binaryOperator = _binaryOperator;
	left = _left;
	right = _right;
	isNumber = false;
}

// initialize precedenceMap
std::unordered_map<std::string, int> TreeEval::precedenceMap = { {"+", 2}, {"-", 2}, {"*", 3}, {"/", 3}, {"^", 5}};

// initialize operators
std::unordered_set<std::string> TreeEval::operators = {"+", "-", "*", "/", "^"};

// used to determine whether op1 has greater precedence than op2
int TreeEval::comparePrecedence(std::string op1, std::string op2) {
	return TreeEval::precedenceMap[op1] - TreeEval::precedenceMap[op2];
}

// pass in valid tokenized infix expression
// Dijkstra's shunting yard algorithm, modified to fit the tree implementation
TreeEval::Node* TreeEval::convert(const std::vector<std::string>& tokens) {
	std::stack<std::string> operators;
	std::stack<Node*> headstack;
	char* end = nullptr;

	for(auto iter = tokens.begin(); iter != tokens.end(); ++iter) {
		// determine if the token is a double
		double number = std::strtod((*iter).c_str(), &end);

		if(end != (*iter).c_str() && *end == '\0' && number != HUGE_VAL) {
			// the token is a number
			Node* number = new Node(std::strtod((*iter).c_str(), &end), nullptr, nullptr);
			headstack.push(number);

		} else if(TreeEval::operators.count(*iter) != 0) {
			// assert that the non-number tokens are valid tokens; link operators with higher precedence
			while(operators.size() != 0 && operators.top() != "(" && (comparePrecedence(operators.top(), *iter) > 0 || (comparePrecedence(operators.top(), *iter) == 0 && *iter != "^"))) {
				Node* right = headstack.top();
				headstack.pop();
				Node* left = headstack.top();
				headstack.pop();
				Node* binaryOperator = new Node(operators.top(), left, right);
				headstack.push(binaryOperator);
				operators.pop();
			}

			operators.push(*iter);

		} else if(*iter == "(") {
			// left parentheses
			operators.push(*iter);

		} else if(*iter == ")") {
			// right parentheses; assume there is a corresponding left parenthesis (linking)
			while(operators.top() != "(") {
				Node* right = headstack.top();
				headstack.pop();
				Node* left = headstack.top();
				headstack.pop();
				Node* binaryOperator = new Node(operators.top(), left, right);
				headstack.push(binaryOperator);
				operators.pop();
			}

			operators.pop();
		}
	}

	// move and link remaining operators
	while(operators.size() != 0) {
		Node* right = headstack.top();
		headstack.pop();
		Node* left = headstack.top();
		headstack.pop();
		Node* binaryOperator = new Node(operators.top(), left, right);
		headstack.push(binaryOperator);
		operators.pop();
	}

	return headstack.top();
}

// postorder traversal of tree, collapses operator nodes with two numerical children into the result of operator(left,right).
void TreeEval::condenseTree(Node* head) {
	if(head->left != nullptr && !(head->left->isNumber)) {
		condenseTree(head->left);
	}

	if(head->right != nullptr && !(head->right->isNumber)) {
		condenseTree(head->right);
	}

	if(head->left != nullptr && head->right != nullptr && head->left->isNumber && head->right->isNumber) {
		if(head->binaryOperator == "+") {
			head->value = head->left->value + head->right->value;

		} else if(head->binaryOperator == "-") {
			head->value = head->left->value - head->right->value;

		} else if(head->binaryOperator == "*") {
			head->value = head->left->value * head->right->value;

		} else if(head->binaryOperator == "/") {
			head->value = head->left->value / head->right->value;

		} else if(head->binaryOperator == "^") {
			head->value = pow(head->left->value, head->right->value);
		}

		head->isNumber = true;
		delete head->left;
		delete head->right;
		head->left = nullptr;
		head->right = nullptr;
	}
}

double TreeEval::evaluate(const std::vector<std::string>& tokens) {

	// convert into tree
	Node* head = convert(tokens);

	// evaluation
	condenseTree(head);
	return head->value;
}
