#pragma once
#include <string>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <cmath>

class StackEval {

    static std::unordered_map<std::string, int> precedenceMap;
    static std::unordered_set<std::string> operators;

public:
    static int comparePrecedence(std::string op1, std::string op2);
    static void convert(const std::vector<std::string>& tokens, std::vector<std::string>& postfix);
    static double evaluate(const std::vector<std::string>& tokens);
};