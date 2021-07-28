#include "Operator.h"

Operator::Operator(char character, int index, int nesting) {
	//Initialize member variables
	this->character = character;
	this->index = index;
	this->nesting = nesting;

	//Assign priority, based on general mathematical hierarchies
	switch(character) {
		case '+':
			priority = 0;
			break;

		case '-':
			priority = 0;
			break;

		case '*':
			priority = 1;
			break;

		case '/':
			priority = 1;
			break;

		case '^':
			priority = 2;
			break;
	}

}

bool operator<(const Operator& a, const Operator& b) {
	//Ordering goes as follows:
	//Nesting (parenthesis depth)  trumps all else
	//	In (5 + 2) * 3, the plus is evaluated first
	//If at equivalent nesting, highest priority operator (from PEMDAS, but ignore P, because handled prior) is handled first
	//	In 5 + 2 * 3, the multiplication is evaluated first
	//If at equivalent nesting and at equivalent priority, then lowest index (order in expression) is evaluated first
	//	In 5 / 2 * 3, the division is evaluated first
	//Finally, the notion of "first" refers to the order a human would evaluate the expression.
	//Because it is done recursively, the highest-priority items called for evaluation last,
	//because the algorithm needs to "build up" to them
	//Thus, intuitive comparsions are negated

	if(a.nesting == b.nesting) {
		if(a.priority == b.priority) {
			//The lower the index, the higher the operator ranking (first come, first serve)
			return a.index < b.index;

		} else {
			//The higher the priority, the higher the operator ranking
			return a.priority > b.priority;
		}

	} else {
		//The higher the nesting, the higher the operator ranking
		return a.nesting > b.nesting;
	}
}

std::ostream& operator<< (std::ostream& out, const Operator& op) {
	out << op.character << " pr:" << op.priority << " idx:" << op.index << " nest:" << op.nesting;
	return out;
}
