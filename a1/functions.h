/*
Steven Colburn
masc0974
CS570
Assignment#1
functions.h
*/
#include<string>                                  /*For Strings*/
#include<vector>                                  /*For Vectors*/
#include<iostream>                                /**/
#include<fstream>                                 /**/
#include<sstream>
#include<pthread.h>
#include<semaphore.h>
#include <sys/types.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
using namespace std;

struct multi_args
{
string arg1;
string arg2;
bool arg3;
};

/*Prints string s*/
void prnt(string s);

/*Creates a child process which creates 4 threads
and prints to PTAB.txt*/
int create_process();

/*Writes to a file first argument is string to write
second argument is the filename and third is boolean 
value to end the line if it is set to true*/
int w_to_file(multi_args args);

/*Creates a file and writes a string to first line.
It will overwrite any file with same name.*/
void create_file(string s, string file_name);

/*Converts an int to a string*/
string int2str(int a);

/*Used to create a thread*/
void* w_thread(void* tmp);


#endif

