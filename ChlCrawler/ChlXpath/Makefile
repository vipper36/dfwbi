LIB = libchlpath.a

TESTSOURCES = ChlXpath.cpp 

TESTOBJECTS = $(TESTSOURCES:.cpp=.o)


C++ = g++
CFLAGS = -O3 -fPIC

#-----------------------------------------------------------------------------
# Make the program
#-----------------------------------------------------------------------------


all: $(LIB)


$(LIB): $(TESTOBJECTS)
	ar -r $@ $(TESTOBJECTS)


#-----------------------------------------------------------------------------
# Object files
#-----------------------------------------------------------------------------

ChlXpath.o: ChlXpath.cpp ChlXpath.h
	$(C++) -c $(CFLAGS) ChlXpath.cpp

clean:
	-rm -f *.o *.obj *.fig *.bak *.dmp *.~cpp *.~h core

realclean: clean
	-rm -f $(LIB)
