/*
Copyright (c) 2011, David Venhoek
All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "interface.h"
typedef CMT_BOOL (*test)(void);

// Prepare: remove any existing definitions
#ifdef CMINTEST_START_SUITE
	#undef CMINTEST_START_SUITE
#endif
#ifdef CMINTEST_END_SUITE
	#undef CMINTEST_END_SUITE
#endif
#ifdef CMINTEST_START_GROUP
	#undef CMINTEST_START_GROUP
#endif
#ifdef CMINTEST_END_GROUP
	#undef CMINTEST_END_GROUP
#endif
#ifdef CMINTEST_TEST
	#undef CMINTEST_TEST
#endif


// Pass 1: collect function signatures
#define CMINTEST_START_SUITE(name)
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name)
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function) CMT_BOOL function(void);
#include "testdescriptors.h"
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 2: create arrays for each test group
#define CMINTEST_START_SUITE(name)
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name) static test CMT_##name[] = {
#define CMINTEST_END_GROUP(name) NULL};
#define CMINTEST_TEST(function) function,
#include "testdescriptors.h"
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 3: create arrays for each test suite
#define CMINTEST_START_SUITE(name) static test *CMT_##name[] = {
#define CMINTEST_END_SUITE() NULL};
#define CMINTEST_START_GROUP(name) CMT_##name,
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
#include "testdescriptors.h"
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 4: create master array of suites
#define CMINTEST_START_SUITE(name) CMT_##name,
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name)
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
static test **CMT_testSuites[] = {
#include "testdescriptors.h"
NULL};
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 5: create array of test names
#define CMINTEST_START_SUITE(name)
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name) static char *CMT_testNames_##name[] = {
#define CMINTEST_END_GROUP() NULL};
#define CMINTEST_TEST(function) #function,
#include "testdescriptors.h"
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 6: create array for each suite containing references to test names
#define CMINTEST_START_SUITE(name) static char **CMT_testNames_##name[] = {
#define CMINTEST_END_SUITE() NULL};
#define CMINTEST_START_GROUP(name) CMT_testNames_##name,
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
#include "testdescriptors.h"
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 7: create global array with test names
#define CMINTEST_START_SUITE(name) CMT_testNames_##name,
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name)
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
static char ***CMT_testNames[] = {
#include "testdescriptors.h"
NULL};
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 8: create array with group names
#define CMINTEST_START_SUITE(name) static char *CMT_groupNames_##name[] = {
#define CMINTEST_END_SUITE() NULL};
#define CMINTEST_START_GROUP(name) #name,
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
#include "testdescriptors.h"
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 9: create global array with group names
#define CMINTEST_START_SUITE(name) CMT_groupNames_##name,
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name)
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
static char **CMT_groupNames[] = {
#include "testdescriptors.h"
NULL};
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

// Pass 10: create array with suites names
#define CMINTEST_START_SUITE(name) #name,
#define CMINTEST_END_SUITE()
#define CMINTEST_START_GROUP(name)
#define CMINTEST_END_GROUP()
#define CMINTEST_TEST(function)
static char *CMT_suiteNames[] = {
#include "testdescriptors.h"
NULL};
#undef CMINTEST_START_SUITE
#undef CMINTEST_END_SUITE
#undef CMINTEST_START_GROUP
#undef CMINTEST_END_GROUP
#undef CMINTEST_TEST

void CMT_runTests(void)
{
	int totalSucceed=0, totalFail = 0;
	int suiteSucceed, suiteFail;
	int i,j,k;
	for (i=0; CMT_testSuites[i] != NULL; i++)
	{
		suiteSucceed = suiteFail = 0;
		for (j=0; CMT_testSuites[i][j] != NULL; j++)
		{
			for (k=0; CMT_testSuites[i][j][k] != NULL; k++)
			{
				if (CMT_testSuites[i][j][k]())
				{
					totalSucceed++;
					suiteSucceed++;
				}
				else
				{
					print("Failed test ");
					print(CMT_groupNames[i][j]);
					print("/");
					print(CMT_testNames[i][j][k]);
					print(" in suite ");
					print(CMT_suiteNames[i]);
					print("\n");
					totalFail++;
					suiteFail++;
				}
			}
		}
		
		print("-----------------\nSuite ");
		print(CMT_suiteNames[i]);
		print(":\nSucceeded: ");
		print_num(suiteSucceed);
		print("\nFailed:    ");
		print_num(suiteFail);
		print("\n-----------------\n");
	}
	
	print("-----------------\nOveral:\nSucceeded: ")
	print_num(totalSucceed);
	print("\nFailed:    ");
	print_num(totalFail);
	print("\n-----------------\nTests Finished.\n");
}
