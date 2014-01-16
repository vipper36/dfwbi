JSONLIB = libjson.a

SOURCES = json_reader.cpp  json_value.cpp  json_writer.cpp

OBJECTS = $(SOURCES:.cpp=.o)

C++ = g++
CFLAGS = -O3 -Wall -DASSERT -fPIC

all: $(JSONLIB)


$(JSONLIB): $(OBJECTS)
	ar -r $@ $(OBJECTS)


#-----------------------------------------------------------------------------
# Object files
#-----------------------------------------------------------------------------
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) -c $< -I../include
clean:
	@-rm -f *.o *.obj *.fig *.bak *.dmp *.~cpp *.~h core

realclean: clean
	@-rm -f $(JSONLIB)
