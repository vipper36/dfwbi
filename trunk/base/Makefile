ORA_INC=/opt/oracle/111/rdbms/public
ORA_LIB=/opt/oracle/111/lib
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -c -fPIC -D_XLNX64
DESC=libbase.so
LFLAGS=-shared -Wl,-soname,$(DESC).1
INCLUDE= -I$(ORA_INC)
PUBOBJECT= FileOperator.o  Tocci.o 
.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE) -c $<
all: $(DESC)
	@echo $@ update to date
$(DESC):$(PUBOBJECT)
	@echo Linking $@ ...
	$(CXX) $(LFLAGS) -o libCaxLib.so ${PUBOBJECT} -L$(ORA_LIB) -locci11
	$(AR) libCaxLib.a libCaxLib.so
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
