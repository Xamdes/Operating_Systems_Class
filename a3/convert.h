/*
Steven Colburn
masc0974
CS570
Assignment#3
convert.h
*/

#include "error_exception.h"

#ifndef CONVERT_H
#define CONVERT_H
class convert
{
	public:

		convert();

/*Convert Int to String*/
		string int2str(int);

/*Convert String to Int*/
		int str2int(string);

/*Convert Character to String*/
		string char2str(char);

	private:

};
#endif

/*EOF*/
