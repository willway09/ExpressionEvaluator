#pragma once
#include <string>
#include <vector>
#include <stack>

static class StackEval{

public:
    static double evaluate(std::vector<std::string>& tokens);
}

static double StackEval::evaluate(std::vector<std::string>& tokens){
    
    // convert to postfix notation first
    }