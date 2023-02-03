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
LIBHARU  = ./libharu

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: spiralPDF

# To create the executable file spiralPDF we need the object files
# HaruPDF.o, Spiral.o, and spiralPDF.o:
#
spiralPDF:  spiralPDF.o HaruPDF.o Spiral.o 
	$(CC) $(CFLAGS) -L$(LIBHARU)/src  -o spiralPDF spiralPDF.o HaruPDF.o Spiral.o -lhpdfs


# To create the object file spiralPDF.o, we need the source files
# HaruPDF.cpp and HaruPDF.h:
spiralPDF.o:  spiralPDF.cpp HaruPDF.h Spiral.h
	$(CC) $(CFLAGS) -I $(LIBHARU)/include -c spiralPDF.cpp

# To create the object file HaruPDF.o, we need the source files
# HaruPDF.cpp and HaruPDF.h:
HaruPDF.o: HaruPDF.cpp HaruPDF.h $(LIBHARU)/include/hpdf.h
	$(CC) $(CFLAGS) -I $(LIBHARU)/include -c HaruPDF.cpp 

# To create the object file Spiral.o, we need the source files
# Spiral.cpp and Spiral.h:
#
Spiral.o:  Spiral.cpp Spiral.h 
	$(CC) $(CFLAGS) -c Spiral.cpp -o Spiral.o

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) spiralPDF *.o *~