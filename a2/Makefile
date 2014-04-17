###########################Makefile########################
# CS570, Spring 2014, a2
# Steven Colburn, masc0974
###########################################################
EXEC = a2
###  or use cc / g++ / gcc   ###
CC = g++  
CCFLAGS = -g -Wall -O3 -Wpointer-arith -Wcast-qual -Wwrite-strings

$(EXEC): a2.o pagefile.o
		$(CC) $(CCFLAGS) -o $(EXEC) a2.o pagefile.o
		rm -f *.o
	  
a2.o:	a2.cc
		$(CC) $(CCFLAGS) -c a2.cc	  
	  
pagefile.o: pagefile.cc pagefile.h
		$(CC) $(CCFLAGS) -c pagefile.cc

clean:
		rm -f *.o core a.out $(EXEC)

#######################[ EOF: Makefile ]###################
