#include "interface.h"
typedef ST_BOOL (*test)(void);

// Prepare: remove any existing definitions
#ifdef SIMPLETEST_START_SUITE
	#undef SIMPLETEST_START_SUITE
#endif
#ifdef SIMPLETEST_END_SUITE
	#undef SIMPLETEST_END_SUITE
#endif
#ifdef SIMPLETEST_START_GROUP
	#undef SIMPLETEST_START_GROUP
#endif
#ifdef SIMPLETEST_END_GROUP
	#undef SIMPLETEST_END_GROUP
#endif
#ifdef SIMPLETEST_TEST
	#undef SIMPLETEST_TEST
#endif


// Pass 1: collect function signatures
#define SIMPLETEST_START_SUITE(name)
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name)
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function) ST_BOOL function(void);
#include "testdescriptors.h"
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 2: create arrays for each test group
#define SIMPLETEST_START_SUITE(name)
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name) static test ST_##name[] = {
#define SIMPLETEST_END_GROUP(name) NULL};
#define SIMPLETEST_TEST(function) function,
#include "testdescriptors.h"
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 3: create arrays for each test suite
#define SIMPLETEST_START_SUITE(name) static test *ST_##name[] = {
#define SIMPLETEST_END_SUITE() NULL};
#define SIMPLETEST_START_GROUP(name) ST_##name,
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
#include "testdescriptors.h"
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 4: create master array of suites
#define SIMPLETEST_START_SUITE(name) ST_##name,
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name)
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
static test **ST_testSuites[] = {
#include "testdescriptors.h"
NULL};
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 5: create array of test names
#define SIMPLETEST_START_SUITE(name)
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name) static char *ST_testNames_##name[] = {
#define SIMPLETEST_END_GROUP() NULL};
#define SIMPLETEST_TEST(function) #function,
#include "testdescriptors.h"
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 6: create array for each suite containing references to test names
#define SIMPLETEST_START_SUITE(name) static char **ST_testNames_##name[] = {
#define SIMPLETEST_END_SUITE() NULL};
#define SIMPLETEST_START_GROUP(name) ST_testNames_##name,
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
#include "testdescriptors.h"
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 7: create global array with test names
#define SIMPLETEST_START_SUITE(name) ST_testNames_##name,
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name)
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
static char ***ST_testNames[] = {
#include "testdescriptors.h"
NULL};
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 8: create array with group names
#define SIMPLETEST_START_SUITE(name) static char *ST_groupNames_##name[] = {
#define SIMPLETEST_END_SUITE() NULL};
#define SIMPLETEST_START_GROUP(name) #name,
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
#include "testdescriptors.h"
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 9: create global array with group names
#define SIMPLETEST_START_SUITE(name) ST_groupNames_##name,
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name)
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
static char **ST_groupNames[] = {
#include "testdescriptors.h"
NULL};
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

// Pass 10: create array with suites names
#define SIMPLETEST_START_SUITE(name) #name,
#define SIMPLETEST_END_SUITE()
#define SIMPLETEST_START_GROUP(name)
#define SIMPLETEST_END_GROUP()
#define SIMPLETEST_TEST(function)
static char *ST_suiteNames[] = {
#include "testdescriptors.h"
NULL};
#undef SIMPLETEST_START_SUITE
#undef SIMPLETEST_END_SUITE
#undef SIMPLETEST_START_GROUP
#undef SIMPLETEST_END_GROUP
#undef SIMPLETEST_TEST

void ST_runTests(void)
{
	int totalSucceed=0, totalFail = 0;
	int suiteSucceed, suiteFail;
	int i,j,k;
	for (i=0; ST_testSuites[i] != NULL; i++)
	{
		suiteSucceed = suiteFail = 0;
		for (j=0; ST_testSuites[i][j] != NULL; j++)
		{
			for (k=0; ST_testSuites[i][j][k] != NULL; k++)
			{
				if (ST_testSuites[i][j][k]())
				{
					totalSucceed++;
					suiteSucceed++;
				}
				else
				{
					print("Failed test ");
					print(ST_groupNames[i][j]);
					print("/");
					print(ST_testNames[i][j][k]);
					print(" in suite ");
					print(ST_suiteNames[i]);
					print("\n");
					totalFail++;
					suiteFail++;
				}
			}
		}
		
		print("-----------------\nSuite ");
		print(ST_suiteNames[i]);
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
