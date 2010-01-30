BOOSTINC= -I../log -I/usr/local/include
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -D_XLNX64 -fPIC 
CXXFLAGS=-g -D_XLNX64 -fPIC
DESC=libfactory.a

INCLUDE=$(BOOSTINC)
BASEOBJ=dllapi.o Logger.o

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
$(DESC):$(BASEOBJ)
	@echo Linking $@ ...
	@ar -r $@ $^ 
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
