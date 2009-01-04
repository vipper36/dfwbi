ORA_INC=/opt/oracle/111/rdbms/public
ORA_LIB=/opt/oracle/111/lib
SOCI_INC=/root/workspace/dfwbi/include
SOCI_LIB=/root/workspace/dfwbi/lib
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS=-g -c -fPIC -D_XLNX64
DESC=dbtest
LFLAGS=
INCLUDE= -I$(SOCI_INC) -I$(ORA_INC)
PUBOBJECT= dbtest.o
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
	$(CXX) $(LFLAGS) -o $(DESC) ${PUBOBJECT} -L$(SOCI_LIB) -L$(ORA_LIB) -lsoci_core -lsoci_oracle -lclntsh -lnnz11
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
