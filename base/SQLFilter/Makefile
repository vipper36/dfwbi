KEYVIEW=/opt/autonomy/FilterSDK
KVINCLUDE=$(KEYVIEW)/include
KVLIB=$(KEYVIEW)/_xlnx64/bin/
INCLUDE=-I$(KVINCLUDE)
LIB=-lm -ldl -lc
CC=gcc
LIBFILTER=libfilter.so
TEST=test
LIBOBJ=dllapi.o filter.o getPStr.o support.o
TESTOBJ=test.o
DEST=$(TEST) 
CFLAGS=-g -c -fPIC -D_XLNX64
LFLAGS=-shared -Wl,-soname,$(LIBFILTER).1
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE) -c $<
all:$(DEST)

$(TEST):$(TESTOBJ) $(LIBFILTER)
	$(CC)  -o $(TEST) $(TESTOBJ) -L . -lfilter
$(LIBFILTER):$(LIBOBJ)
	$(CC) $(LFLAGS) -o $(LIBFILTER) $(LIBOBJ) $(LIB)
	@-rm /usr/lib/$(LIBFILTER).1
	@-ln `pwd`/$(LIBFILTER) /usr/lib/$(LIBFILTER).1 -s
	@-ldconfig
clean: 
	rm -rf *.o *.so $(DEST) *~