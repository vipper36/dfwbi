BOOSTLIB=-lboost_thread -lboost_system -lboost_program_options -lpthread
TESTLIB=-lboost_unit_test_framework
DLLLIB=-ldl
BOOSTINC= -I./log
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-DBOOSTEST -fPIC -D_XLNX64
CXXFLAGS=-DBOOSTEST -fPIC -D_XLNX64
DESC=httpd boostest

INCLUDE=$(BOOSTINC)
BOOSTOBJ= connection.o mime_types.o posix_main.o reply.o request_handler.o request_parser.o server.o   
BASELIB=libmybase.so
BASEOBJ=Logger.o config_file.o dllapi.o
TESTOBJ=boostest.o dllapi.o Logger.o config_file.o

LFLAGS=-shared -O2 -Wl,-soname,$(BASELIB)
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
	$(CXX) -O3 -o $@ $^ ${BOOSTLIB} ${DLLLIB} -L. -lmybase
$(BASELIB):$(BASEOBJ)
	@echo Linking $@ ...
	$(CXX) -O3 $(LFLAGS) -o $@ $^ ${BOOSTLIB} ${DLLLIB}
	@ln -s `pwd`/libmybase.so /usr/local/lib/libmybase.so
boostest:$(TESTOBJ) $(BASELIB)
	@echo Linking $@ ...
	$(CXX)  -o $@ $^ ${BOOSTLIB} ${TESTLIB} ${DLLLIB} -L. -lmybase
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#" /usr/local/lib/libmybase.so
