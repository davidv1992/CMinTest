TESTFOLDER := test/
TESTDESCRIPTORS := $(shell find $(TESTFOLDER) -name "*.td")

testdescriptors.h: Makefile $(TESTDESCRIPTORS)
	find $(TESTFOLDER) -name "*.td" | awk '{ print "#include\"" $$0 "\"" }' > testdescriptors.h

CMinTestTester.o: Makefile CMinTestTester.c testdescriptors.h interface.h
