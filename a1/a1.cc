/*
Steven Colburn
masc0974
CS570
Assignment#1
a1.cc
*/

#include "functions.h"
using namespace std;

int main()
{
    int i;

    string s = "";

    string myfile = "PTAB.txt";
    int prompt;

    cout << "Enter 1 to run program, or anything else to exit: " << endl;
    cin >> prompt;

/*Exit Method*/
    if (prompt != 1)
    {
        cout << "Exiting program" << endl;
        exit(1);
    }

    create_process();
    exit(1);
}
