all: main.cpp Parser.o StackEval.o PriorityQueueEval.o TreeEval.o
	g++ -g -o main main.cpp Parser.o StackEval.o PriorityQueueEval.o TreeEval.o Operator.o
Parser.o: Parser.cpp Parser.h
	g++ -g -c -o Parser.o Parser.cpp
StackEval.o: StackEval.cpp StackEval.h
	g++ -g -c -o StackEval.o StackEval.cpp
PriorityQueueEval.o: PriorityQueueEval.cpp PriorityQueueEval.h Operator.o
	g++ -g -c -o PriorityQueueEval.o PriorityQueueEval.cpp
TreeEval.o: TreeEval.cpp TreeEval.h
	g++ -g -c -o TreeEval.o TreeEval.cpp
Operator.o: Operator.cpp Operator.h
	g++ -g -c -o Operator.o Operator.cpp
clean:
	@rm main
	@rm *.o
	@rm documentation.pdf
	@rm submission.zip
	@rm expressions expressions.js expressions.csv
	@rm *.orig
lint:
	astyle --style=java -t -xn -xc -xl -F -p -xg -U -k1 -j -S *.cpp *.h
zip: doc
	zip submission.zip *.cpp *.h Makefile documentation.pdf
doc:
	make -C documentation
	cp documentation/documentation.pdf .
expressions: expressions.cpp
	g++ -g -o expressions expressions.cpp
	./expressions 5829 > expressions.csv
