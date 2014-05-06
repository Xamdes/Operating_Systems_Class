/*
Steven Colburn
masc0974
CS570
Assignment#3
variables.h
*/

#include "convert.h"
#define DEFAULT 6
#define MEM_SZ 4096

#ifndef VARIABLES_H
#define VARIABLES_H
class variables
{
	public:

		variables();
		
		void setCounter(string);
		
		void setCounter(int);
		
		int getCounter();
		
		int get();

		void set(int);
		
	private:
	
	convert con;
	
	int start_counter;
	int run;
	

};
#endif

/*EOF*/
