/*
Steven Colburn
masc0974
CS570
Assignment#3
error_exception.h
*/

#include "import.h"

#ifndef ERROR_EXCEPTION_H
#define ERROR_EXCEPTION_H

class error_exception
{

	public:
		error_exception(string s)
		{
			message = s;
		}

		error_exception()
		{
			message = "An error has occurred";
		}

		string getMessage()
		{
			return message;
		}

	private:
		string message;
};
#endif

/*EOF*/
