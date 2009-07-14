SHALIB = libsha1.a

TESTSOURCES = sha1.cpp 

TESTOBJECTS = $(TESTSOURCES:.cpp=.o)


C++ = g++
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

sha1.o: sha1.h sha1.cpp
	$(C++) -c $(CFLAGS) sha1.cpp

clean:
	-rm -f *.o *.obj *.fig *.bak *.dmp *.~cpp *.~h core

realclean: clean
	-rm -f $(SHALIB)
