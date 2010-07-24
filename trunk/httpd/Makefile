BOOSTLIB=-L/home/fly/usr/lib -lboost_thread -lboost_system -lboost_program_options -lpthread -ldlib
TESTLIB=-lboost_unit_test_framework
DLLLIB=-ldl
BOOSTINC= -I./log -I./factory -I./server -I./stock -I./commands -I/home/fly/usr/include -I./da -I./svm
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
FACLIB=-L./factory -lfactory
CGILIB=-lfastcgipp
SRVLIB=-L./server -lserver
CFLAGS= -g -fPIC -D_XLNX64
CXXFLAGS= -g -fPIC -D_XLNX64
DESC=httpd boostest stockclient stockday stockprice stocknn
CGI=cmd.fcgi
INCLUDE=$(BOOSTINC)
BOOSTOBJ= posix_main.o   
TESTOBJ=boostest.o
.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo cpp to o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE)  -c $<
all: $(DESC)
	@echo $@ update to date
httpd:$(BOOSTOBJ) $(BASELIB)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB}  $(SRVLIB) $(FACLIB)

stockclient:stock.o
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)

stockday:stockday.o
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)

stocknn:stocknn.o
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)

stockprice:stockprice.o
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)

$(CGI):fcgiMain.o
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB) $(CGILIB)

boostest:$(TESTOBJ)
	@echo Linking $@ ...
	$(CXX)  -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)

clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
