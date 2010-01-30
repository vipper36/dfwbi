BOOSTLIB=-L/usr/local/lib -lboost_thread -lboost_system -lboost_program_options -lpthread
TESTLIB=-lboost_unit_test_framework
DLLLIB=-ldl
BOOSTINC= -I./log -I./factory -I/usr/local/include
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
FACLIB=-L./factory -lfactory
CFLAGS= -g -D_XLNX64
CXXFLAGS= -g -D_XLNX64
DESC=httpd boostest

INCLUDE=$(BOOSTINC)
BOOSTOBJ= connection.o mime_types.o posix_main.o reply.o request_handler.o request_parser.o server.o   
TESTOBJ=boostest.o

.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE)  -c $<
all: $(DESC)
	@echo $@ update to date
	@ldconfig
httpd:$(BOOSTOBJ) $(BASELIB)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)
boostest:$(TESTOBJ)
	@echo Linking $@ ...
	$(CXX)  -o $@ $^ ${BOOSTLIB} ${DLLLIB} $(FACLIB)
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#" /usr/local/lib/libmybase.so
