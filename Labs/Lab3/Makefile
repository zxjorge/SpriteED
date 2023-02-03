#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = g++
CFLAGS  = -g -Wall
CARDIR = /root/cs3505/Labs/Lab3/Carlib


# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
car3: main.o 
	$(CC) $(CFLAGS) -L$(CARDIR)/lib -lCar -o car4 main.o 

# To create the object file counter.o, we need the source files
# counter.c and counter.h:
#
main.o:  main.cpp $(CARDIR)/include/Car.h
	$(CC) $(CFLAGS) -I $(CARDIR)/include -c main.cpp

# To create the object file Car.o, we need the source files
# Car.cpp and Car.h:
#
Car.o:  Car.cpp $(CARDIR)/include/Car.h 
	$(CC) $(CFLAGS) -I $(CARDIR)/include -c Car.cpp 

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) car3 *.o *~