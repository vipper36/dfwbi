BOOSTLIB=-L/usr/local/lib -lboost_thread -lboost_system -lpthread
BOOSTINC=-I/usr/local/include/boost
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -DBOOSTEST
LDESC=libhttp.a
SDESC=Stock
GDESC=Google
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
all: $(LDESC) $(SDESC) $(GDESC)
	@echo $@ update to date
$(LDESC):$(LIBOBJ)
	@echo Linking $@ ...
	$(AR) -o $@ $^
$(SDESC):main.o $(STOCKOBJ) $(LDESC)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ $(BOOSTLIB)
$(GDESC):Google.o $(LDESC)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ $(BOOSTLIB)

clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
