/*
Steven Colburn
masc0974
CS570
Assignment#3
functions.cc
*/
#include "functions.h"

sem_t locker;
sem_t queue;

functions::functions()
{

}


void functions::run_clock(variables a)
{
	var = a;
	if(var.getCounter() == -1)
	{
		print("Invalid input resetting to default value.");
		var.setCounter(DEFAULT);
	}
	while(1)
	{
		ask();
		make_children();
	}

}


void functions::ask()
{
	int counter;
	int num = 0;
	bool running = true;	
	while (running)
	{
		counter = var.getCounter();
		string s;
		print("If you need help enter [help] or [?] for more commands.");
		cout << "Current: [" << counter << "]" << endl;
		cout << "Enter how long would you like the program to run for [" << counter <<"]: ";
		cin >> s;

		num = con.str2int(s);

		if (s == "end" || s == "exit")
		{
			print("Exiting out of the Program a3");
			exit(1);
		}
		else if(num > 0)
		{
			var.setCounter(num);
		}
		else if(s == "default")
		{
			var.setCounter(DEFAULT);
		}
		else if(s == "help" || s == "?")
		{
			help();
		}
		else if(s == "begin" || s == "start" || s == "run")
		{
			running = false;
		}
		else
		{
			cout << "Invalid Entry [" << s << "]." << endl;
		}
	}
}


void functions::print(string s)
{
	cout << s << endl;
}


void functions::print(int s)
{
	cout << s << endl;
}


void functions::help()
{
	print("Commands available: ");
	print("Type [exit] or [end] if you want to stop the program.");
	print("Type [begin], [start] or [run] to start the program.");
	print("Type [default] to reset the number back to default [6].");
	print("Type any number greater than [0] for the time in seconds the program should run for.");
}


void functions::make_children()
{
	int total = var.getCounter();
	int time[3] = {0,0,0};
	string curr;

	pid_t king = -50;
	pid_t assassin = -50;

	void *shared_memory = (void *)0;
	shared_use *shared_val;
	int shmid;
	shmid = shmget((key_t)1234,MEM_SZ,0666 | IPC_CREAT);
	shared_memory = shmat(shmid, (void *)0,0);
	shared_val = (struct shared_use *)shared_memory;
	shared_val -> kill = 0;

	sem_init(&locker, 0, 1);
	sem_init(&queue, 0, 1);

	king = logger(king,curr,total,time);
	assassin = keeper(assassin,curr,total,time);

	int king_status;
	int ass_status;
	waitpid(king, &king_status, 0);
	waitpid(assassin, &ass_status, 0);	
	
	sem_destroy(&locker);
	sem_destroy(&queue);
	
	print("The children have stopped printing the time.");
}


int functions::logger(pid_t king,string curr, int total,int* time)
{
	king = fork();
	if(king == 0)
	{
		sem_wait(&queue);

		void *shared_memory = (void *)0;
		shared_use *shared_val;
		int shmid;
		shmid = shmget((key_t)1234,MEM_SZ,0666 | IPC_CREAT);
		shared_memory = shmat(shmid, (void *)0,0);
		shared_val = (struct shared_use *)shared_memory;

		sem_post(&queue);

		while(shared_val -> kill != 1)
		{
			sem_wait(&locker);
			print(getTime(time));
			sem_post(&locker);
			sleep(1);
		}
		exit(1);
	}
	return king;

}


int functions::keeper(pid_t assassin, string curr, int total,int* time)
{
	assassin = fork();
	if(assassin == 0)
	{
		void *shared_memory = (void *)0;
		shared_use *shared_val;
		int shmid;
		shmid = shmget((key_t)1234,MEM_SZ,0666 | IPC_CREAT);
		shared_memory = shmat(shmid, (void *)0,0);
		shared_val = (struct shared_use *)shared_memory;

		sem_wait(&queue);

		while(total > 0)
		{
			sem_wait(&locker);
			string s = "";
			curr = getTime(time);
			s.append(prop_len(time[1]));
			s.append(":");
			s.append(prop_len(time[2]));
			print(s);
			total = total - 1;
			if(total != 0)
			{
				sleep(1);
			}
			else
			{
				shared_val -> kill = 1;
			}
			sem_post(&locker);
		}
		exit(1);
	}
	return assassin;
}


string functions::prop_len(int a)
{
	string s = con.int2str(a);
	string t = "";
	if(s.length() == 1)
	{
		t.append("0");
		t.append(s);
		return t;
	}
	return s;
}


string functions::getTime(int* arr)
{
	time_t timer;
	time(&timer);
	string time = asctime(localtime(&timer));
	time.erase(time.size() - 1);
/*[11,12] is the hour, [14,15] are minutes, [17,18] are seconds*/
	int hour = 0;
	int min = 0;
	int sec = 0;

	sec = 10 * con.str2int(con.char2str(time.at(17)));

	sec = sec + con.str2int(con.char2str(time.at(18)));

	min = 10 * con.str2int(con.char2str(time.at(14)));

	min = min + con.str2int(con.char2str(time.at(15)));

	hour = 10 * con.str2int(con.char2str(time.at(11)));

	hour = hour + con.str2int(con.char2str(time.at(12)));

	arr[0] = hour;
	arr[1] = min;
	arr[2] = sec;

	return time;
}


/*EOF*/
