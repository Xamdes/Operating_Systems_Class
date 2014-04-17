/*
Steven Colburn
masc0974
CS570
Assignment#2
pagefile.cc

*/
#include "pagefile.h"

pagefile::pagefile()
{
    values.reserve(500);
    frames = NULL;
}


void pagefile::start()
{
    int frame = 0;
    while(frame != -1)
    {
        frame = ask();

        if (frame != -1)
        {
            num_frames = frame;
            page_replace();
        }
    }

}


int pagefile::ask()
{
    bool running = true;
    int num;
    print("The program will continue running until you type [exit] or [end]");
    while (running)
    {
        num = 0;
        string s;
        print("If you need help enter [help] or [?] for more commands.");
        cout << "Enter number of frames you would like to use from [1-99]: ";
        cin >> s;

        num = str2int(s);

        if (s == "end")
        {
            num = -1;
            running = false;
        }
        else if(s == "exit")
        {
            num = -1;
            running = false;
        }
        else if (s == "create_0")
        {
            create();
            write_0();
            print("pages.txt has been created");
            num = -1;
			running = false;
        }
        else if (s == "create_1")
        {
            create();
            write_1();
            print("pages.txt has been created");
            num = -1;
			running = false;
        }
        else if(s == "create_2")
        {
            create();
            write_2();
            print("pages.txt has been created");
            num = -1;
			running = false;
        }
        else if(s == "c3")
        {
            create();
            write_c3();
            print("pages.txt has been created");
            num = -1;
			running = false;
        }
        else if(s == "ans")
        {
            print("Input string for the 4 algorithms in Chapter 3's slide #42:");
            print("Faults with 3 Frames");
            print("OPT: 6");
            print("LRU: 7");
            print("FIFO: 9");
            print("CLOCK: 8");
        }
        else if (s == "clear")
        {
            create();
            print("pages.txt has been cleared");
        }
        else if (s == "help")
        {
            help();
        }
        else if(s == "custom")
        {
            create();
            custom();
            num = -1;
			running = false;
        }
        else if(s == "?")
        {
            help();
        }
        else if(s == "current")
        {
            current();
        }
        else if (num > 0 && num < 100)
        {
            running = false;
        }
        else
        {
            print("Invalid number for system frames");
            print("Number must be greater then 0 and less then 100");
            cout << "You entered [" << s << "]" << endl;
        }
    }
    return num;
}


void pagefile::page_replace()
{
    string line;
    line = getLine();
    int count = fill(line);

    opt(count);
    lru(count);
    fifo(count);
    clock(count);
}


void pagefile::opt(int count)
{
    val = NULL;
    gone = NULL;
    tmp_frames = NULL;

    val = new int[num_frames];
    gone = new string[count];
    tmp_frames = new string[num_frames];

    create_frame();
    string value;
    string future;
    int num1;
    int num2;
    int faults = 0;
    int tmp = -1;
    int replace = 0;
    int lock = 0;
    for(int i = 0; i < count; i++)
    {
        gone[i] = values[i];
    }
    for (int i = 0; i < num_frames; i++)
    {
        val[i] = 0;
    }
    for (int i = 0; i < count; i++)
    {
        gone[i] = "";
        value  = values[i];
        num1 = find(value);
        if (num1 == -1)
        {
            bool done = false;
            for (int j = 0; j < num_frames; j++)
            {
                num2 = find("");
                if (num2 != -1 && done == false)
                {
                    frames[num2] = value;
                    done = true;
                }
                else if (done == false)
                {
                    for (int f = 0; f < num_frames; f++)
                    {
                        tmp_frames[f] = frames[f];
                    }

                    for (int k = (i+1); k < count; k++)
                    {
                        future = values[k];
                        tmp = find(future);
                        if (tmp != -1)
                        {
                            val[tmp] = k;
                            tmp_frames[tmp] = frames[tmp];
                            frames[tmp] = "";
                        }
                    }
                    for (int f = 0; f < num_frames; f++)
                    {
                        frames[f] = tmp_frames[f];
                    }
                    tmp = -1;
                    lock = 0;
                    for (int k = 0; k < num_frames; k++)
                    {
                        if (val[k] > tmp)
                        {
                            tmp = val[k];
                            if(i > tmp)
                            {
                                print_frame();
                                cout << values[val[k]] << endl;
                                cout << value << endl;
                                cout << val[k] << endl;
                                replace = find(values[val[k]]);
                                lock = 1;
                            }
                        }
                    }

                    future = values[tmp];
                    tmp = find(future);
                    if (lock == 1)
                    {
                        cout << replace << endl;
                        frames[replace] = value;
                    }
                    else
                    {
                        frames[tmp] = value;
                    }
                    done = true;
                }
            }
            faults++;
/*Set values in frame to "" since pages will no longer show up in the future*/
            for(int iei = 0; iei < num_frames; iei++)
            {
                if(find_g(frames[iei], count)==-1)
                {
                    frames[iei] = "";
                }
            }
        }
/*Set values in frame to "" since pages will no longer show up in the future*/
        for(int iei = 0; iei < num_frames; iei++)
        {
            if(find_g(frames[iei], count)==-1)
            {
                frames[iei] = "";
            }
        }
    }
    cout << "OPT faults: [" << faults << "]" << endl;
    clear_frame();

    delete [] val;
    val = NULL;

    delete [] tmp_frames;
    tmp_frames = NULL;

    delete [] gone;
    gone = NULL;
}


/*
Either enters value into empty slot or refreshes counter to 1 for
slot if the value is still in frame. Decrements all other value counters by 1.
*/
void pagefile::lru(int count)
{
    int fcount[num_frames];
    int where = 0;
    for (int i = 0; i < num_frames; i++)
    {
        fcount[i] = 0;
    }

    create_frame();
    string value;
    int faults = 0;

    for (int i = 0; i < count; i++)
    {
        value = values[i];
        int num1 = find(value);

        if (num1 == -1)
        {
            faults++;
            int j = 1;
            where = 0;
            for (int l = 0; l < num_frames; l++)
            {
                if (fcount[l] < j)
                {
                    where = l;
                    j = fcount[l];
                }
            }

            for (int k = 0; k < num_frames; k++)
            {
                fcount[k] = fcount[k] - 1;
            }

            frames[where] = value;
            fcount[where] = 1;
        }
        else
        {
            for (int k = 0; k < num_frames; k++)
            {
                fcount[k] = fcount[k] - 1;
            }
            fcount[num1] =  1;
        }
    }

    cout << "LRU faults: [" << faults << "]" << endl;
    clear_frame();
}


int pagefile::find_g(string s, int count)
{
    for (int i = 0; i < count; i++)
    {
        if (gone[i] == s)
        {
            return i;
        }
    }
    return -1;
}


void pagefile::fifo(int count)
{
    int num1;
    int faults = 0;
    string value;
    create_frame();

    for (int i = 0; i < count; i++)
    {
        value = values[i];
        num1 = find(value);

        if (num1 == -1)
        {
            insert_first(value);
            faults++;
        }
    }
    cout << "FIFO faults: [" << faults << "]" << endl;
    clear_frame();
}


void pagefile::clock(int count)
{
    create_frame();
    int faults = 0;
    string value;
    int num1;

    int bits[num_frames];
    for (int i = 0; i < num_frames; i++)
    {
        bits[i] = 0;
    }

    int j = 0;
    for (int i = 0; i < count; i++)
    {
        bool search = true;
        value = values[i];

        num1 = find(value);
/*
If page fault occurs find insertion point
else set bit to 1 where value exists
*/
        if (num1 == -1)
        {
            while (search)
            {
                if (j == num_frames)
                {
                    j = 0;
                }

                if (bits[j] == 0)
                {
                    frames[j] = value;
                    bits[j] = 1;
                    faults++;
                    search = false;
                }
                else
                {
                    bits[j] = 0;
                }
                j++;
            }
        }
        else
        {
            bits[num1] = 1;
        }
    }
    cout << "CLOCK faults: [" << faults << "]" << endl;
    clear_frame();
}


void pagefile::insert_first(string s)
{
    string tmp[num_frames];
    for (int i = 0; i < num_frames; i++)
    {
        tmp[i] = frames[i];
    }
    for (int i = 0; i < num_frames; i++)
    {
        frames[0] = s;
        if ((i+1) != num_frames)
        {
            frames[i+1] = tmp[i];
        }
    }
}


void pagefile::print_frame()
{
    for (int i = 0; i < num_frames; i++)
    {
        cout << "Frame Number: " << i << "::" << frames[i] << endl;
    }
}


int pagefile::open_slot()
{
    return find("");
}


string pagefile::getLine()
{
    ifstream page;
    page.open("pages.txt");
    string line;
    getline(page,line);
    page.close();
    return line;
}


void pagefile::print(string s)
{
    cout << s << endl;
}


int pagefile::find(string s)
{
    for (int i = 0; i < num_frames; i++)
    {
        if (frames[i] == s)
        {
            return i;
        }
    }
    return -1;
}


/*Create dynamic array*/
void pagefile::create_frame()
{
    frames = new string[num_frames];
}


/*Clears dynamic array*/
void pagefile::clear_frame()
{
    delete [] frames;
    frames = NULL;
}


void pagefile::create()
{
    string file = "pages.txt";
    ofstream open_f;
    open_f.open(file.c_str(), ios::trunc);
    open_f.close();
}


void pagefile::write_0()
{
    string file = "pages.txt";

    ofstream out;

    out.open(file.c_str());

    out << "1 4 6 3 10 4 55 45 55 21 3 6 9 " <<
        "4 1 2 5 8 7 4 1 2 5 8 9 6 3 2 44 22 11 25 86 99 99 41 25 25 66 99 1 1 1 88";

    out.close();
}


void pagefile::write_1()
{
    string file = "pages.txt";

    ofstream out;

    out.open(file.c_str());

    out << "7 9 1 2 9 3 9 4 2 3 9 3 2 1 2 9 1 7 9 1";

    out.close();
}


string  pagefile::int2str(int n)
{

    ostringstream outstr;

    outstr << n;

    return outstr.str();

}


//Function to convert string to int

int pagefile::str2int(string s)
{

    istringstream instr(s);

    int n;

    instr >> n;

    return n;

}


string pagefile::char2str(char c)
{

    stringstream ss;

    string s;

    ss << c;

    ss >> s;

    return s;

}


void pagefile::check(string line)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < line.length(); i++)
    {
        j = (i+1);
        string val = "";

        if ((j != line.length()) && (line.at(j) != ' '))
        {

            val = char2str(line.at(i));
            string sec = char2str(line.at(j));
            val.append(sec);

            i = i + 2;
        }
        else
        {
            val = char2str(line.at(i));

            i++;
        }

        cout << "'" << val;
    }

    cout << endl;

}


int pagefile::fill(string line)
{

    unsigned int i;
    unsigned int j;

    int k = 0;
    for (i = 0; i < line.length(); i++)
    {
        j = (i+1);
        string val = "";

        if ((j != line.length()) && (line.at(j) != ' '))
        {

            val = char2str(line.at(i));
            string sec = char2str(line.at(j));
            val.append(sec);

            i = i + 2;

            k++;
        }
        else
        {
            val = char2str(line.at(i));

            i++;

            k++;
        }
        values.push_back(val);
    }
    return k;
}


void pagefile::print_line()
{
    string s = getLine();
    cout << s << endl;
}


void pagefile::write_2()
{
    string file = "pages.txt";

    ofstream out;

    out.open(file.c_str());

    out << "1 2 3 4 1 2 5 1 2 3 4 5";

    out.close();
}


void pagefile::custom()
{
    string file = "pages.txt";
    string s = "";
    string line = "";
    int num;
    int running = 1;
    print("To begin enter any number from [1-99] then press enter.");
    print("Enter [done] to write the string to pages.txt.");

    while(running)
    {
        cin >> s;
        num = str2int(s);
        if (num > 0 && num < 100 && s != "done")
        {
            line.append(s);
            line.append(" ");
        }
        else if(s == "done")
        {
            if (line.size () > 0)
            {
                line.resize(line.size() - 1);
            }
            running = 0;
        }
        else
        {
            print("Value entered was invalid.");
            print("Type [done] if finished or any number from [1-99].");
            cout << "You entered [" << s << "]." << endl;
        }
        print("Current string: ");
        cout << line << endl;
    }
    print("You entered:");
    print(line);
    print("Writing to pages.txt now.");

    ofstream out;

    out.open(file.c_str());

    out << line;

    out.close();
    print("Finished writing out to file.");
}


void pagefile::write_c3()
{
    print("Type: [ans] for answers to this number sequence.");
    string file = "pages.txt";

    ofstream out;

    out.open(file.c_str());

    out << "2 3 2 1 5 2 4 5 3 2 5 2";

    out.close();
}


void pagefile::help()
{
    print("Commands: ");
    print("	First:   |Type any number from [1-99] for the main program to start.");
    print("	Second:  |Enter [end] or [exit] to terminate the program.");
    print("	Third:   |Enter [create_(0-2)] to create a pages.txt to test.");
    print("	Example: |[create_0]");
    print("	Fourth:  |Enter [clear] to clear any data in pages.txt.");
    print("	Fifth:   |Enter [custom] to create your own pages.txt.");
    print("	Sixth:   |Enter [c3] to create example from Chapter 3 Slide #42.");
    print("	Seventh: |Enter [current] to print to screen current sequence.");
    print("	Warning: |Creating a file will cause the program to exit.");
    print("	         |Start it up again to test new sequence of numbers.");
}


void pagefile::current()
{
    string ln = getLine();
    print(ln);
}


/*End of File*/
