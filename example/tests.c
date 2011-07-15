#include "interface.h"

ST_BOOL test1()
{
	// A simple suceeding test
	return ST_TRUE;
}

ST_BOOL test2()
{
	// A simple failing test
	return ST_FALSE;
}

ST_BOOL test3()
{
	// A slightly more interesting test
	return 'a' == 97;
}

