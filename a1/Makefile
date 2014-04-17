###########################Makefile########################
# CS570, Spring 2014, a1
# Steven Colburn, masc0974
###########################################################
EXEC = sem
###  or use cc / g++ / gcc   ###
CC = g++  
CCFLAGS = -g -Wall -O3 -Wpointer-arith -Wcast-qual -Wwrite-strings -lposix4

$(EXEC): a1.o functions.o
		$(CC) $(CCFLAGS) -o $(EXEC) a1.o functions.o
		rm -f *.o
	  
driver.o:	a1.cc
		$(CC) $(CCFLAGS) -c a1.cc	  
	  
functions.o: functions.cc functions.h
		$(CC) $(CCFLAGS) -c functions.cc

clean:
		rm -f *.o core a.out $(EXEC)
		
remtxt:
		rm -f PTAB.txt

#######################[ EOF: Makefile ]###################
