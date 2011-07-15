TESTFOLDER := test/
TESTDESCRIPTORS := $(shell find $(TESTFOLDER) -name "*.td")

testdescriptors.h: Makefile $(TESTDESCRIPTORS)
	find $(TESTFOLDER) -name "*.td" | awk '{ print "#include\"" $$0 "\"" }' > testedescriptors.h

simpleTestTester.o: Makefile simpleTestTester.c testdescriptors.h interface.h
