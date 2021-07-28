#pragma once
#include <ostream>

class Operator {
public:
	char character;
	unsigned int priority;
	unsigned int nesting;
	unsigned int index;

	Operator(char character, int index, int nesting);
};


bool operator<(const Operator& a, const Operator& b);
std::ostream& operator<< (std::ostream& out, const Operator& op);
