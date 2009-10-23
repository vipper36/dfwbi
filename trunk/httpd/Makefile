BOOSTLIB=-lboost_thread-mt -lboost_system-mt -lboost_program_options-mt -lpthread
TESTLIB=-lboost_unit_test_framework-mt
DLLLIB=-ldl
BOOSTINC= -I./log
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-DBOOSTEST -fPIC -D_XLNX64
CXXFLAGS=-DBOOSTEST -fPIC -D_XLNX64
DESC=httpd boostest
LFLAGS=-shared -O2 -Wl,-soname,$(DESC).1
INCLUDE=$(BOOSTINC)
BOOSTOBJ=Logger.o connection.o mime_types.o posix_main.o reply.o request_handler.o request_parser.o server.o config_file.o  dllapi.o
TESTOBJ=boostest.o dllapi.o Logger.o config_file.o
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
httpd:$(BOOSTOBJ)
	@echo Linking $@ ...
	$(CXX) -O3 -o $@ $^ ${BOOSTLIB} ${DLLLIB}
boostest:$(TESTOBJ)
	@echo Linking $@ ...
	$(CXX)  -o $@ $^ ${BOOSTLIB} ${TESTLIB} ${DLLLIB}
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
