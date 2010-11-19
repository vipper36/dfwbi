BOOSTLIB=-L/usr/local/lib -lboost_system -lboost_program_options -ltherond -lboost_thread
BOOSTINC= -I/usr/local/include -I/usr/include/libxml++-2.6/ -I/usr/include/glibmm-2.4 -I/usr/include/glib-2.0 -I/usr/lib64/glibmm-2.4/include/ -I/usr/lib64/glib-2.0/include/ -I/usr/lib64/libxml++-2.6/include/
XMLLIB=-lxml++-2.6 -licuuc
LIBCUTL=-lcurl
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS= -g -fPIC -D_XLNX64 -DTHERON_USE_BOOST_THREADS=1 -D_DEBUG
CXXFLAGS= -g -fPIC -D_XLNX64 -DTHERON_USE_BOOST_THREADS=1 -D_DEBUG
DESC=stock
INCLUDE=$(BOOSTINC)
BOOSTOBJ= main.o   
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
stock:$(BOOSTOBJ)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB} ${LIBCUTL}
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
