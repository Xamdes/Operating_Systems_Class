/*
Steven Colburn
masc0974
CS570
Assignment#3
variables.cc
*/

#include "variables.h"

variables::variables()
{
	start_counter = DEFAULT;
	run = 0;
}


void variables::setCounter(string a)
{
	start_counter = con.str2int(a);
}

void variables::setCounter(int a)
{
	start_counter = a;
}

int variables::getCounter()
{
	return start_counter;
}

void variables::set(int a)
{
	run = a;
}

int variables::get()
{
	return run;
}


/*EOF*/
