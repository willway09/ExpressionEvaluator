all: main.cpp Parser.o StackEval.o PriorityQueueEval.o TreeEval.o
	g++ -g -o main main.cpp Parser.o StackEval.o PriorityQueueEval.o TreeEval.o
Parser.o: Parser.cpp Parser.h
	g++ -g -c -o Parser.o Parser.cpp
StackEval.o: StackEval.cpp StackEval.h
	g++ -g -c -o StackEval.o StackEval.cpp
PriorityQueueEval.o: PriorityQueueEval.cpp PriorityQueueEval.h
	g++ -g -c -o PriorityQueueEval.o PriorityQueueEval.cpp
TreeEval.o: TreeEval.cpp TreeEval.h
	g++ -g -c -o TreeEval.o TreeEval.cpp
