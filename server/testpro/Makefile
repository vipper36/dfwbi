INCLUDE=
LIB=-ldl
CC=g++
LIBTAR=testpro.so
LIBOBJ=testpro.o
DEST=$(LIBTAR) 
CFLAGS=-g -c -fPIC -D_XLNX64
LFLAGS=-shared -Wl,-soname,$(LIBTAR).1
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE) $<
all:$(DEST)

$(LIBTAR):$(LIBOBJ)
	$(CC) $(LFLAGS) -o $(LIBTAR) $(LIBOBJ) $(LIB)
clean: 
	rm -rf *.o *.so $(DEST) *~