BOOSTLIB=-L/usr/local/lib -lboost_thread-gcc43-mt -lboost_system-gcc43-mt -lpthread
BOOSTINC=-I/usr/local/include/boost-1_37
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -DBOOSTEST
LDESC=libhttp.a
SDESC=Stock
LFLAGS=-shared  -Wl,-soname,$(DESC).1
INCLUDE=$(BOOSTINC)
LIBOBJ=HttpClient.o  HttpReqest.o  HttpResponse.o  HttpUrl.o
STOCKOBJ=Yahoo.o Stock.o StockDataAdaptor.o
.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE)  -c $<
all: $(LDESC) $(SDESC)
	@echo $@ update to date
$(LDESC):$(LIBOBJ)
	@echo Linking $@ ...
	$(AR) -o $@ $^
$(SDESC):main.o $(STOCKOBJ) $(LDESC)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ $(BOOSTLIB)

clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
