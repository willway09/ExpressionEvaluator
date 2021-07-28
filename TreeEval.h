#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <cmath>
#include <iostream>

class TreeEval{

    static std::unordered_map<std::string, int> precedenceMap;
    static std::unordered_set<std::string> operators;
    struct Node {
        double value;
        std::string binaryOperator;
        bool isNumber;
        Node* left;
        Node* right;
        Node(double _value, Node* _left, Node* _right);
        Node(std::string _binaryOperator, Node* _left, Node* _right);
    };

public:
    static int comparePrecedence(std::string op1, std::string op2);
    static Node* convert(const std::vector<std::string>& tokens);
    static void condenseTree(Node* head);
    static double evaluate(const std::vector<std::string>& tokens);
};