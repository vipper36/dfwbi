BOOSTLIB=-L/home/fly/usr/lib -lboost_thread -lboost_system -lboost_program_options -lpthread
TESTLIB=-lboost_unit_test_framework
DLLLIB=-ldl
BOOSTINC= -I../log -I../factory -I../commands -I/home/fly/usr/include
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
FACLIB=-L./factory -lfactory
CFLAGS= -g -fPIC -D_XLNX64
CXXFLAGS= -g -fPIC -D_XLNX64
DESC=libserver.a

INCLUDE=$(BOOSTINC)
BOOSTOBJ= connection.o mime_types.o reply.o request_handler.o request_parser.o server.o   

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
$(DESC):$(BOOSTOBJ)
	@echo Linking $@ ...
	@ar -r $@ $^
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
