SHALIB = libeditdistance.a

TESTSOURCES = distance.cpp 

TESTOBJECTS = $(TESTSOURCES:.cpp=.o)

#-----------------------------------------------------------------------------
# Compiler and compilation options:
#
#	C++		your C++ compiler
#	CFLAGS (for g++)
#		-O[1-3]        	Optimization
#		-Wall		Be noisy about warnings
#		-traditional	Flag nontraditional C++ usage
#		-g          	Debugging
#                               (may slow execution slightly)
#		-DASSERT	Enable assertion checking
#                               (may slow execution slightly)
#	WAIT_FOR_COMFIRM	Force user to confirm program termination
#				(Useful in some PC versions, which create a
#				temporary command terminal in which to run
#				the program.)
#-----------------------------------------------------------------------------
C++ = g++
#CFLAGS = -O3 
#CFLAGS = -g -Wall -DASSERT -traditional
CFLAGS = -O3 -fPIC

#-----------------------------------------------------------------------------
# Make the program
#-----------------------------------------------------------------------------


all: $(SHALIB)


$(SHALIB): $(TESTOBJECTS)
	ar -r $@ $(TESTOBJECTS)


#-----------------------------------------------------------------------------
# Object files
#-----------------------------------------------------------------------------

distance.o: distance.h distance.cpp
	$(C++) -c $(CFLAGS) distance.cpp

clean:
	-rm -f *.o *.obj *.fig *.bak *.dmp *.~cpp *.~h core

realclean: clean
	-rm -f $(SHALIB)
