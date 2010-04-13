INCLUDE=-I../log -I/home/fly/usr/include -I ../factory -I ../client
LIB=-ldl -L/home/fly/usr/lib -lboost_date_time -L../factory -lfactory -L ../client -lclient -lboost_thread -lboost_system -lpthread
CC=g++
LIBTAR=yahoo.so
LIBOBJ=yahoo.o
LIBTAR1=file_list.so
LIBOBJ1=file_list.o
DEST=$(LIBTAR) $(LIBTAR1)
CFLAGS=-g -c -fPIC -D_XLNX64
LFLAGS=-shared -Wl,-soname,$(LIBTAR).1
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE) $<
all:$(DEST)

$(LIBTAR):$(LIBOBJ)
	$(CC) $(LFLAGS) -o $@ $^ $(LIB)
$(LIBTAR1):$(LIBOBJ1)
	$(CC) $(LFLAGS) -o $@ $^ $(LIB)

clean: 
	rm -rf *.o *.so $(DEST) *~
