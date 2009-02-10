BOOSTLIB=-L/usr/local/lib -lboost_thread-gcc43-mt -lboost_system-gcc43-mt -lpthread
BOOSTINC=-I/usr/local/include/boost-1_37
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -DBOOSTEST
DESC=stock
LFLAGS=-shared  -Wl,-soname,$(DESC).1
INCLUDE=$(BOOSTINC)
BOOSTOBJ=async_client.o

.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE)  -c $<
all: $(DESC)
	@echo $@ update to date
$(DESC):$(BOOSTOBJ)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB}
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
