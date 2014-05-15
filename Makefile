all:
	gcc -c ./*.cpp
	gcc -c *.cpp
	g++ ./examples/general_simple_sample/general_simple_sample.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o examples/general_simple_sample/general_simple_sample.bin -fPIC -O2 -g -Wall
	g++ ./examples/general_advanced_sample/general_advanced_sample.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o examples/general_advanced_sample/general_advanced_sample.bin -fPIC -O2 -g -Wall
	g++ ./tests/GeneralTest.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o tests/GeneralTest.bin -fPIC -O2 -g -Wall
	g++ ./tests/FuzzyTest.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o /usr/lib/libgtest.a -o tests/FuzzyTest.bin -fPIC -O2 -g -Wall -lpthread

clean:
	rm *.o
	rm ./examples/*/*.bin
	rm ./tests/*.bin