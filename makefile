compiler=g++
flags=-g -std=c++11 -O3

all: allDecreaseOrNot addAllMaximalMatchings dumbbellGenerator computeAverageSubtreeOrder compareMuGMuGVAndMuGE generateDumbbellWithCycle generateDumbbellWithCycleAndStar

allDecreaseOrNot: allDecreaseOrNot.cpp 
	$(compiler) $(flags) allDecreaseOrNot.cpp -o allDecreaseOrNotExecutable

addAllMaximalMatchings: addAllMaximalMatchings.cpp 
	$(compiler) $(flags) addAllMaximalMatchings.cpp -o addAllMaximalMatchingsExecutable

dumbbellGenerator: dumbbellGenerator.cpp 
	$(compiler) $(flags) dumbbellGenerator.cpp -o dumbbellGeneratorExecutable

computeAverageSubtreeOrder: computeAverageSubtreeOrder.cpp 
	$(compiler) $(flags) computeAverageSubtreeOrder.cpp -o computeAverageSubtreeOrderExecutable

compareMuGMuGVAndMuGE: compareMuGMuGVAndMuGE.cpp 
	$(compiler) $(flags) compareMuGMuGVAndMuGE.cpp -o compareMuGMuGVAndMuGEExecutable

generateDumbbellWithCycle: generateDumbbellWithCycle.cpp 
	$(compiler) $(flags) generateDumbbellWithCycle.cpp -o generateDumbbellWithCycleExecutable

generateDumbbellWithCycleAndStar: generateDumbbellWithCycleAndStar.cpp 
	$(compiler) $(flags) generateDumbbellWithCycleAndStar.cpp -o generateDumbbellWithCycleAndStarExecutable

.PHONY: clean
clean:
	rm -f allDecreaseOrNotExecutable addAllMaximalMatchingsExecutable dumbbellGeneratorExecutable computeAverageSubtreeOrderExecutable compareMuGMuGVAndMuGEExecutable generateDumbbellWithCycleExecutable generateDumbbellWithCycleAndStarExecutable
