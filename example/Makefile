TESTFOLDER := tests/
TESTDESCRIPTORS := $(shell find $(TESTFOLDER) -name "*.td")

.DEFAULT_GOAL = example

testdescriptors.h: Makefile $(TESTDESCRIPTORS)
	find $(TESTFOLDER) -name "*.td" | awk '{ print "#include\"" $$0 "\"" }' > testdescriptors.h

simpleTestTester.o: Makefile simpleTestTester.c testdescriptors.h interface.h

main.o: main.c simpleTest.h

tests.o: tests.c interface.h

example: simpleTestTester.o main.o tests.o
	gcc -o example simpleTestTester.o main.o tests.o

clean:
	rm -f simpleTestTester.o main.o tests.o testdescriptors.h example
