BOOSTLIB=-L/usr/local/lib -lboost_thread -lboost_system -lpthread
BOOSTINC=-I/usr/local/include/
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -DBOOSTEST -fPIC -D_XLNX64
LDESC=libclient.a
LFLAGS=-shared  -Wl,-soname,$(DESC).1
INCLUDE=$(BOOSTINC)
LIBOBJ=HttpClient.o AhttpClient.o HttpReqest.o  HttpResponse.o  HttpUrl.o

.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE)  -c $<
all: $(LDESC)
	@echo $@ update to date
$(LDESC):$(LIBOBJ)
	@echo Linking $@ ...
	$(AR) -o $@ $^
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
