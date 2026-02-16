# Auto-detect gtest installation location (macOS Homebrew and Linux)
GTEST_LIB := $(shell \
	if [ -f /opt/homebrew/lib/libgtest.a ]; then \
		echo /opt/homebrew/lib/libgtest.a; \
	elif [ -f /usr/local/lib/libgtest.a ]; then \
		echo /usr/local/lib/libgtest.a; \
	elif [ -f /usr/lib/x86_64-linux-gnu/libgtest.a ]; then \
		echo /usr/lib/x86_64-linux-gnu/libgtest.a; \
	elif [ -f /usr/lib/libgtest.a ]; then \
		echo /usr/lib/libgtest.a; \
	else \
		echo ""; \
	fi)

GTEST_INC := $(shell \
	if [ -d /opt/homebrew/include ]; then \
		echo -I/opt/homebrew/include; \
	elif [ -d /usr/local/include ]; then \
		echo -I/usr/local/include; \
	elif [ -d /usr/include/gtest ]; then \
		echo -I/usr/include; \
	else \
		echo ""; \
	fi)

all:
	$(MAKE) lib
	$(MAKE) build-tests

lib:
	gcc -c ./*.cpp
	gcc -c *.cpp
	g++ ./examples/general_simple_sample/general_simple_sample.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o examples/general_simple_sample/general_simple_sample.bin -fPIC -O2 -g -Wall
	g++ ./examples/general_advanced_sample/general_advanced_sample.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o examples/general_advanced_sample/general_advanced_sample.bin -fPIC -O2 -g -Wall

build-tests:
	g++ ./tests/GeneralTest.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o -o tests/GeneralTest.bin -fPIC -O2 -g -Wall
	@if [ -z "$(GTEST_LIB)" ]; then \
		echo "Warning: Google Test library not found. Skipping FuzzyTest."; \
		echo "Install on macOS: brew install googletest"; \
		echo "Install on Ubuntu/Debian: sudo apt-get install libgtest-dev"; \
	else \
		echo "Building FuzzyTest with gtest from: $(GTEST_LIB)"; \
		g++ -std=c++17 ./tests/FuzzyTest.cpp Fuzzy.o FuzzyComposition.o FuzzyIO.o FuzzyInput.o FuzzyOutput.o FuzzyRule.o FuzzyRuleAntecedent.o FuzzyRuleConsequent.o FuzzySet.o $(GTEST_LIB) -o tests/FuzzyTest.bin -fPIC -O2 -g -Wall $(GTEST_INC) -lpthread; \
	fi

test: build-tests
	@echo ""
	@echo "=========================================="
	@echo "Running GeneralTest..."
	@echo "=========================================="
	@./tests/GeneralTest.bin
	@echo ""
	@if [ -f tests/FuzzyTest.bin ]; then \
		echo "=========================================="; \
		echo "Running FuzzyTest (Google Test)..."; \
		echo "=========================================="; \
		./tests/FuzzyTest.bin; \
	else \
		echo "FuzzyTest.bin not found. Run 'make build-tests' first or install Google Test."; \
	fi

clean:
	rm -f *.o
	rm -f ./examples/*/*.bin
	rm -f ./tests/*.bin
	rm -rf ./tests/*.bin.*

help:
	@echo "eFLL Makefile - Available targets:"
	@echo ""
	@echo "  make              - Build library, examples, and test binaries (same as 'make all')"
	@echo "  make lib          - Build library object files and examples"
	@echo "  make build-tests  - Build test binaries only"
	@echo "  make test         - Build and run all tests"
	@echo "  make clean        - Remove all built files"
	@echo "  make help         - Show this help message"
	@echo ""

.PHONY: all lib build-tests test clean help
