#include "interface.h"

CMT_BOOL test1()
{
	// A simple suceeding test
	return CMT_TRUE;
}

CMT_BOOL test2()
{
	// A simple failing test
	return CMT_FALSE;
}

CMT_BOOL test3()
{
	// A slightly more interesting test
	return 'a' == 97;
}

