###########################Makefile########################
# CS570, Spring 2014, a3
# Steven Colburn, masc0974
###########################################################
EXEC = a3
###  or use cc / g++ / gcc   ###
CC = g++
CCFLAGS = -g -Wall -O3 -Wpointer-arith -Wcast-qual -Wwrite-strings -lposix4

$(EXEC):	a3.o functions.o variables.o convert.o import.h error_exception.h
	$(CC) $(CCFLAGS) -o $(EXEC) a3.o functions.o variables.o convert.o import.h error_exception.h

a3.o:	a3.cc
	$(CC) $(CCFLAGS) -c a3.cc

functions.o:	functions.cc functions.h
	$(CC) $(CCFLAGS) -c functions.cc

variables.o:	variables.cc variables.h
	$(CC) $(CCFLAGS) -c variables.cc
	
convert.o:	convert.cc convert.h
	$(CC) $(CCFLAGS) -c convert.cc

clean:
	rm -f *.o $(EXEC)

#######################[ EOF: Makefile ]###################
