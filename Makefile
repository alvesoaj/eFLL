all:
	gcc -c ./*.cpp
	gcc -c *.cpp
	g++ ./examples/sample01.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o examples/sample01.bin -fPIC -O2 -g -Wall
	g++ ./examples/sample02.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o examples/sample02.bin -fPIC -O2 -g -Wall
	g++ ./tests/FuzzyTest.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o /usr/lib/libgtest.a -o tests/FuzzyTest.bin -fPIC -O2 -g -Wall -lpthread
	g++ ./tests/GeneralTest.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o tests/GeneralTest.bin -fPIC -O2 -g -Wall

clean:
	rm *.o
	rm ./examples/*.bin
	rm ./tests/*.bin