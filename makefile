compiler=g++
flags=-g -std=c++11 -O3

all: allDecreaseOrNot addAllMaximalMatchings dumbbellGenerator computeAverageSubtreeOrder

allDecreaseOrNot: allDecreaseOrNot.cpp 
	$(compiler) $(flags) allDecreaseOrNot.cpp -o allDecreaseOrNotExecutable

addAllMaximalMatchings: addAllMaximalMatchings.cpp 
	$(compiler) $(flags) addAllMaximalMatchings.cpp -o addAllMaximalMatchingsExecutable

dumbbellGenerator: dumbbellGenerator.cpp 
	$(compiler) $(flags) dumbbellGenerator.cpp -o dumbbellGeneratorExecutable

computeAverageSubtreeOrder: computeAverageSubtreeOrder.cpp 
	$(compiler) $(flags) computeAverageSubtreeOrder.cpp -o computeAverageSubtreeOrderExecutable

.PHONY: clean
clean:
	rm -f allDecreaseOrNotExecutable addAllMaximalMatchingsExecutable dumbbellGeneratorExecutable computeAverageSubtreeOrderExecutable
