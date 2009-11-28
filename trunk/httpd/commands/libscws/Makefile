LIB = libscws.a

TESTSOURCES = charset.c  darray.c  lock.c  pool.c  rule.c  scws.c  xdb.c  xdict.c  xtree.c

TESTOBJECTS = $(TESTSOURCES:.c=.o)
TESTHEAD = $(TESTSOURCES:.c=.h)

C++ = g++
CC = gcc
CFLAGS = -fPIC

#-----------------------------------------------------------------------------
# Make the program
#-----------------------------------------------------------------------------


all: $(LIB)


$(LIB): $(TESTOBJECTS)
	ar -r $@ $(TESTOBJECTS)


#-----------------------------------------------------------------------------
# Object files
#-----------------------------------------------------------------------------

$(TESTOBJECTS): $(TESTSOURCES) $(TESTHEAD)
	$(CC) -c $(CFLAGS) $(TESTSOURCES)

clean:
	-rm -f *.o *.obj *.fig *.bak *.dmp *.~cpp *.~h core

realclean: clean
	-rm -f $(LIB)
