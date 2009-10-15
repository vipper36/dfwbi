BOOSTLIB=-L/usr/local/lib -lboost_thread-gcc43-mt -lboost_system-gcc43-mt -lboost_program_options-gcc43-mt -lpthread
TESTLIB=-L/usr/local/lib -lboost_unit_test_framework-gcc43-mt-s
DLLLIB=-ldl
BOOSTINC=-I/usr/local/include/boost-1_37 -I./log
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -DBOOSTEST -fPIC -D_XLNX64
CXXFLAGS=-g -DBOOSTEST -fPIC -D_XLNX64
DESC=httpd boostest
LFLAGS=-shared -O2 -Wl,-soname,$(DESC).1
INCLUDE=$(BOOSTINC)
BOOSTOBJ=Logger.o connection.o mime_types.o posix_main.o reply.o request_handler.o request_parser.o server.o config_file.o
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
	$(CXX) -g -o $@ $^ ${BOOSTLIB}
boostest:$(TESTOBJ)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${TESTLIB} ${DLLLIB}
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
