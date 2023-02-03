# George Benyeogor
# CS3505
# A2: Classes, Facades, and Makefiles
#
# This is a Makefile for a spiralPDF program.  This
# program uses both the Spiral class and HaruPDF class.
# Typing 'make spiralPDF' will create the executable file.
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

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: tryOut

# To create the executable file spiralPDF we need the object files
# HaruPDF.o, Spiral.o, and spiralPDF.o:
#
tryOut:  tryOut.o Node.o Trie.o 
	$(CC) $(CFLAGS) -o tryOut tryOut.o Node.o Trie.o 


# To create the object file spiralPDF.o, we need the source files
# HaruPDF.cpp and HaruPDF.h:
tryOut.o:  tryOut.cpp Node.h Trie.h
	$(CC) $(CFLAGS)  -c tryOut.cpp

# To create the object file HaruPDF.o, we need the source files
# HaruPDF.cpp and HaruPDF.h:
Trie.o: Trie.cpp Trie.h Node.h
	$(CC) $(CFLAGS) -c Trie.cpp 

# To create the object file Spiral.o, we need the source files
# Spiral.cpp and Spiral.h:
#
Node.o:  Node.cpp Node.h 
	$(CC) $(CFLAGS) -c Node.cpp -o Node.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) tryOut *.o *~