#pragma once
#include "Operator.h"
#include <string>
#include <vector>
#include <queue>

class PriorityQueueEval {
private:
	static double recursivelyEvaluate(std::priority_queue<Operator>& operators, const std::vector<std::string>& tokens, int lower, int upper);

public:
	static double evaluate(const std::vector<std::string>& tokens);
};
