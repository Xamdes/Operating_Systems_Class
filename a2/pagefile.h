/*
Steven Colburn
masc0974
CS570
Assignment#2
pagefile.h
*/

#include<string>                                  /*For Strings*/
#include<vector>                                  /*For Vectors*/
#include<iostream>                                /**/
#include<fstream>                                 /**/
#include<sstream>
#include<pthread.h>
#include<semaphore.h>
#include <sys/types.h>
#include <iomanip>
using namespace std;

#ifndef PAGEFILE_H
#define PAGEFILE_H
class pagefile
{
    public:

/*Constructor for pagefile*/
        pagefile();

/*Basic print function*/
        void print(string);

/*For use in main a2.cc file to start the program*/
        void start();

    private:
/*Global variable for knowing how many frames user wants to use*/
        int num_frames;

/*Dynamic string frames array*/
        string* frames;

/*Dynamic int val array*/
        int* val;

/*Dynamic string gone array*/
        string* gone;

/*Dynamic string tmp_frames array*/
        string* tmp_frames;

/*Vector for storing the line from pages.txt*/
        vector<string> values;

/*Creates pages.txt file*/
        void create();

/*Writes first sequence for testing*/
        void write_0();

/*Writes second sequence for testing*/
        void write_1();

/*Convert Int to String*/
        string int2str(int);

/*Convert String to Int*/
        int str2int(string);

/*Gets the line from a file*/
        string getLine();

/*Convert Character to String*/
        string char2str(char);

/*Unused*/
        void check(string);

/*Used with getLine() to fill a vector with the page sequence*/
        int fill(string);

/*Starts the page replacement algorithms*/
        void page_replace();

/*Optimal*/
        void opt(int);

/*Least Recently Used*/
        void lru(int);

/*First In First Out*/
        void fifo(int);

/*Clock*/
        void clock(int);

/*User Prompt*/
        int ask();

/*Creates a dynamic frame array*/
        void create_frame();

/*Clears the dynamic frame array*/
        void clear_frame();

/*Looks for a given string in the frame else return -1 if not found*/
        int find(string);

/*Unused Looks for open_slot in the frame array*/
        int open_slot();

/*Use with LRU insets string first into make array*/
        void insert_first(string);

/*Print what is in the frame*/
        void print_frame();

/*Prints the line from pages.txt*/
        void print_line();

        void write_2();

        int find_g(string, int);

/*Write custom pages.txt*/
        void custom();

/*
Input string for the 4 algorithms in Chapter 3's slide #42:
Faults with 3 Frames
OPT: 6
LRU: 7
FIFO: 9
CLOCK: 8
*/
        void write_c3();
		
		void help();
		
		void current();
};
#endif
