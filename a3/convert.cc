/*
Steven Colburn
masc0974
CS570
Assignment#3
variables.h
*/

#include "convert.h"

convert::convert()
{
}


string  convert::int2str(int n)
{
	ostringstream outstr;
	outstr << n;
	return outstr.str();
}


//Function to convert string to int

int convert::str2int(string s)
{
	istringstream instr(s);
	int n = -1;
	instr >> n;
	return n;
}


string convert::char2str(char c)
{
	stringstream ss;
	string s;
	ss << c;
	ss >> s;
	return s;
}


/*EOF*/
