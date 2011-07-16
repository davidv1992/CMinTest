TESTFOLDER := tests/
TESTDESCRIPTORS := $(shell find $(TESTFOLDER) -name "*.td")

.DEFAULT_GOAL = example

testdescriptors.h: Makefile $(TESTDESCRIPTORS)
	find $(TESTFOLDER) -name "*.td" | awk '{ print "#include\"" $$0 "\"" }' > testdescriptors.h

CMinTestTester.o: Makefile CMinTestTester.c testdescriptors.h interface.h

main.o: main.c CMinTest.h

tests.o: tests.c interface.h

example: CMinTestTester.o main.o tests.o
	gcc -o example CMinTestTester.o main.o tests.o

clean:
	rm -f CMinTestTester.o main.o tests.o testdescriptors.h example
