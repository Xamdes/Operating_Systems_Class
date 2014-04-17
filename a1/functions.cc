/*
Steven Colburn
masc0974
CS570
Assignment#1
functions.cc
*/
#include "functions.h"
using namespace std;

/*locker is the mutex, rando is for making sure
the next 3 threads are queued up*/
sem_t locker;
sem_t rando;

/*Prints string s*/
void prnt(string s)
{
    cout << s << endl;
}


/*Creates a child process which creates 4 threads
and prints to PTAB.txt*/
int create_process()
{

    int status;
    pid_t pid = fork();

    if(pid == 0)
    {
/* child process */
        pthread_t thread1;
        pthread_t thread2;
        pthread_t thread3;
        pthread_t thread4;

        create_file(int2str(getpid()), "PTAB.txt");
        sem_init(&locker, 0, 1);
        sem_init(&rando, 0, 2);

        pthread_create(&thread1, NULL, w_thread, NULL);
        pthread_create(&thread2, NULL, w_thread, NULL);
        pthread_create(&thread3, NULL, w_thread, NULL);
        pthread_create(&thread4, NULL, w_thread, NULL);

        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);
        pthread_join(thread3,NULL);
        pthread_join(thread4,NULL);

        sem_destroy(&locker);
        sem_destroy(&rando);
    }
    else
    {
/*Parent waits for child*/
        waitpid(pid, &status, 0);
    }
    return 1;
}


/*Writes to a file first argument is string to write
second argument is the filename and third is boolean value to end the line*/
int w_to_file(multi_args args)
{
    ofstream myfile;
    string s = args.arg1;
    string file_name = args.arg2;
    bool endline = args.arg3;
    myfile.open(file_name.c_str(), ios::out | ios::app);
    if (myfile.is_open())
    {
/*If arg3 is true then make newline
else stay on current line*/
        if (endline)
        {

            myfile << s << endl;
        }
        else
        {
            myfile << s;
        }
    }
    else
    {
        return 0;
    }
    myfile.close();
    return 1;
}


/*Creates a file and writes a string to first line.
It will overwrite any file with same name.*/
void create_file(string s, string file_name)
{
    ofstream myfile;
    myfile.open(file_name.c_str(), ios::out | ios::trunc);
    myfile << s << endl;
    myfile.close();
}


/*Converts an int to a string*/
string int2str(int a)
{
    stringstream ss;
    ss << a;
    string str = ss.str();
    return str;
}


/*Used to create a thread*/
void* w_thread(void* tmp)
{
    int i = (unsigned int)pthread_self();
    struct multi_args args;
    args.arg1 = ("Thread_id: " + int2str(i));
    args.arg2 = "PTAB.txt";
    args.arg3 = true;
/*Run 10 times for thread*/
    for(int counter = 0; counter < 10; counter++)
    {
        sem_wait(&rando);
        sem_wait(&locker);
        sem_post(&rando);
        cout << "Thread<" << i << "> is running" << endl;
        w_to_file(args);
        sem_post(&locker);

    }

    return NULL;
}
