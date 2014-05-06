/*
Steven Colburn
masc0974
CS570
Assignment#3
a3.cc
*/

#include "functions.h"

int main(int argc, char *argv[])
{

	if (argc > 2)
	{
		cout << "Error, Invalid number of inputs [" << argc << "] No more than 1 input is allowed." << endl;
		exit(1);
	}

	functions fn;
	variables var;
	convert con;

	if(argc == 2)
	{
		var.setCounter(argv[1]);
	}
	
	try
	{
		fn.run_clock(var);
	}
	catch(error_exception excpt)
	{
		cout << "Error has occured: [" << excpt.getMessage() << "]" << endl;
	}	

	fn.print("Done");

}


/*EOF*/
