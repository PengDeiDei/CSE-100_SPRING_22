# use g++ with C++11 support
CXX=g++
CXXFLAGS?=-Wall -pedantic -g -O0 -std=c++11
OUTFILES=BinaryTreeTest

all: $(OUTFILES) STYLECHECK

BinaryTreeTest: BinaryTreeTest.cpp BinaryTree.cpp BinaryTree.h STYLECHECK
	$(CXX) $(CXXFLAGS) -o BinaryTreeTest BinaryTreeTest.cpp BinaryTree.cpp

clean:
	$(RM) $(OUTFILES) *.o

# File(s) to check for code style problems.
STYLECHECKFILES=BinaryTree.cpp

# Phony target to report code style problems.
.PHONY: STYLECHECK
STYLECHECK:
	@echo 'for file in $(STYLECHECKFILES); do expand "$$file" | grep -n -E ".{81}" | sed "s#^#$$(tput setab 1)Line exceeds 80 chars!$$(tput sgr0) $$file:#"; done' | bash
