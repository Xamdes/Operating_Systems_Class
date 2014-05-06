/*
Steven Colburn
masc0974
CS570
Assignment#3
functions.h
*/

#include "variables.h"

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
class functions
{
	public:

/*Constructor for functions*/
		functions();

/*Basic print function*/
		void print(string);

		void print(int);

/*For use in main a2.cc file to start the program*/
		void run_clock(variables);

	private:

		struct shared_use
		{
			int kill;
		};

		void help();

		convert con;

		variables var;

/*User Prompt*/
		void ask();

		void make_children();

		string getTime(int*);

		int logger(pid_t,string,int,int*);

		int keeper(pid_t,string,int,int*);

		string prop_len(int);

};
#endif

/*EOF*/
