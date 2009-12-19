INCLUDE=-I../ -I./libscws -I../log
LIB=-ldl -L./libscws -lscws -L../ -lmybase -lboost_iostreams
CC=g++
LIBTAR=status.so
LIBOBJ=status.o
LIBTAR1=Segment.so
LIBOBJ1=Segment.o
DEST=$(LIBTAR) $(LIBTAR1) 
CFLAGS=-g -c -fPIC -D_XLNX64
LFLAGS=-shared -Wl,-soname,$(LIBTAR).1
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE) $<
all:$(DEST)

$(LIBTAR):$(LIBOBJ)
	$(CC) $(LFLAGS) -o $(LIBTAR) $(LIBOBJ) $(LIB)
$(LIBTAR1):$(LIBOBJ1)
	$(CC) $(LFLAGS) -o $(LIBTAR1) $(LIBOBJ1) $(LIB)
clean: 
	rm -rf *.o *.so $(DEST) *~
