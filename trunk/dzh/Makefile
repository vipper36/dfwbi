BOOSTLIB=-L/usr/local/lib -lboost_program_options -lboost_date_time
BOOSTINC= -I/usr/local/include
LOCALINC=-I.
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS= -g
CXXFLAGS= -g
DESC=dzhDay
INCLUDE=$(BOOSTINC) $(LOCALINC)
BOOSTOBJ= Day.o   
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
$(DESC):$(BOOSTOBJ)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB}
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
