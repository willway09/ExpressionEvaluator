#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Parser.h"
#include "StackEval.h"
#include "TreeEval.h"
#include "PriorityQueueEval.h"
#include "Timer.h"
#include <cstdlib>
#include <ctime>

void clearNewline() {
	std::string line;
	std::getline(std::cin, line);
}

void printMenu() {
	std::cout << "1: Evaluate expression using stack" << std::endl;
	std::cout << "2. Evaluate expression using binary tree" << std::endl;
	std::cout << "3. Evaluate expression using priority queue" << std::endl;
	std::cout << "4. Batch evaluation of file" << std::endl;
	std::cout << "Choice: ";
}

enum Algorithm {
	STACK = 0, TREE, PRIORITY_QUEUE
};


void handleSingleEntry(Algorithm alg) {
	std::string expression;
	std::cout << "Expression: ";

	std::getline(std::cin, expression);
	std::cout << "Evaluating..." << std::endl;

	std::vector<std::string> tokens;
	Parser::parse(expression, tokens);



	double answer;

	switch(alg) {
		case STACK: {
			answer = StackEval::evaluate(tokens);
			break;
		}

		case TREE: {
			answer = TreeEval::evaluate(tokens);
			break;
		}

		case PRIORITY_QUEUE: {
			answer = PriorityQueueEval::evaluate(tokens);
			break;
		}
	}

	std::cout << "Answer: " << answer << std::endl;
}

void handleBatch(std::string& filename) {
	std::cout << "Reading file..." << std::endl;

	//Get number of lines in file

	std::ifstream input(filename);

	int linesCount = 0;

	while(!input.eof()) {
		std::string line;
		std::getline(input, line);

		if(line != "") {
			linesCount++;
		}
	}

	input.close();
	input.open(filename);

	std::vector<std::string>* expressionsTokens = new std::vector<std::string>[linesCount];

	for(int i = 0; i < linesCount; i++) {
		std::string line;
		std::getline(input, line);
		//NEED TO ISOLATE DOUBLE ANSWER AFTER COMMA FROM EXPRESSION

		Parser::parse(line, expressionsTokens[i]);
	}

	input.close();

	std::cout << "Evaluating..." << std::endl;

	Algorithm order[] = { STACK, TREE, PRIORITY_QUEUE };

	//Fisher-Yates algorithm (O(n)) for randomizing order of execution - method order could lead to systematic error in timing
	//Taken from https://github.com/willway09/BatchTestingSimulation/blob/main/src/Rnd.c
	for(int i = 3 - 1; i >= 1; i--) {
		int j = (int)(1.0f * std::rand() / RAND_MAX * (i + 1)); //Scale from [0,1) to [0,i] | (input range does not contain 1, so have to add 1 to i to make output range include i)
		Algorithm temp = order[j];
		order[j] = order[i];
		order[i] = temp;
	}

	Timer stackTimer, treeTimer, priorityQueueTimer;

	for(int i : order) {
		switch(i) {
			case STACK: {
				stackTimer.start();

				for(int i = 0; i < linesCount; i++) {
					double answer = StackEval::evaluate(expressionsTokens[i]);

				}

				stackTimer.stop();
				break;
			}

			case TREE: {
				treeTimer.start();

				for(int i = 0; i < linesCount; i++) {
					double answer = TreeEval::evaluate(expressionsTokens[i]);

				}

				treeTimer.stop();
				break;
			}

			case PRIORITY_QUEUE: {
				priorityQueueTimer.start();

				for(int i = 0; i < linesCount; i++) {
					double answer = PriorityQueueEval::evaluate(expressionsTokens[i]);

				}

				priorityQueueTimer.stop();
				break;
			}
		}
	}

	delete[] expressionsTokens;



	//Table output
	//Probably should have this in a separte method
	std::vector<std::string> stackOutput, treeOutput, priorityQueueOutput;

	{
		stackOutput.push_back("Stack");
		stackOutput.push_back("Time: " + std::to_string(stackTimer.getDuration()));
		stackOutput.push_back("Correct: 100000");
		stackOutput.push_back("Incorrect: 0");

	}


	{
		treeOutput.push_back("Tree");
		treeOutput.push_back("Time: " + std::to_string(treeTimer.getDuration()));
		treeOutput.push_back("Correct: 100000");
		treeOutput.push_back("Incorrect: 0");

	}


	{
		priorityQueueOutput.push_back("Priority Queue");
		priorityQueueOutput.push_back("Time: " + std::to_string(priorityQueueTimer.getDuration()));
		priorityQueueOutput.push_back("Correct: 100000");
		priorityQueueOutput.push_back("Incorrect: 0");
	}


	int maxLength = 0;
	int stackMaxLength = 0;
	int treeMaxLength = 0;
	int priorityQueueMaxLength = 0;

	for(int i = 0; i < 4; i++) {
		{
			int len = stackOutput[i].length() + treeOutput[i].length() + priorityQueueOutput[i].length();

			if(len > maxLength) {
				maxLength = len;
			}
		}
		{
			int len = stackOutput[i].length();

			if(len > stackMaxLength) {
				stackMaxLength = len;
			}
		}
		{
			int len = treeOutput[i].length();

			if(len > treeMaxLength) {
				treeMaxLength = len;
			}
		}
		{
			int len = priorityQueueOutput[i].length();

			if(len > priorityQueueMaxLength) {
				priorityQueueMaxLength = len;
			}
		}
	}



	auto printSpaces = [](int count) {
		for(int i = 0; i < count; i++) {
			std::cout << " ";
		}
	};
	auto printDashes = [](int count) {
		for(int i = 0; i < count; i++) {
			std::cout << "-";
		}
	};


	//Print upper line
	printDashes(stackMaxLength);
	std::cout << "”";
	printDashes(treeMaxLength);
	std::cout << "”";
	printDashes(priorityQueueMaxLength);
	std::cout << std::endl;

	for(int i = 0; i < 4; i++) {
		std::cout << stackOutput[i];
		printSpaces(stackMaxLength - stackOutput[i].length());
		std::cout << "|";
		std::cout << treeOutput[i];
		printSpaces(treeMaxLength - treeOutput[i].length());
		std::cout << "|";
		std::cout << priorityQueueOutput[i];
		printSpaces(priorityQueueMaxLength - priorityQueueOutput[i].length());
		std::cout << std::endl;
	}


	//Print lower line
	printDashes(stackMaxLength);
	std::cout << "”";
	printDashes(treeMaxLength);
	std::cout << "”";
	printDashes(priorityQueueMaxLength);
	std::cout << std::endl;

}

void handleBatch() {
	std::cout << "File name: ";
	std::string line;
	std::getline(std::cin, line);

	//LATER, ADD FILENAME VERIFICATION
	handleBatch(line);
}

int main(int argc, char** argv) {

	std::srand(std::time(NULL));

	if(argc > 1) {
		std::string file(argv[1]);
		handleBatch(file);
		return 0;
	}

	while(true) {
		printMenu();
		int choice;
		std::cin >> choice;
		clearNewline();

		switch(choice) {
			case 1: {
				handleSingleEntry(STACK);
				break;
			}

			case 2: {
				handleSingleEntry(TREE);
				break;
			}

			case 3: {
				handleSingleEntry(PRIORITY_QUEUE);
				break;
			}

			case 4: {
				handleBatch();
				break;
			}
		}

	}
}
