BOOSTLIB=-L/usr/local/lib -lboost_system -lboost_program_options -ltherond -lboost_thread -lboost_date_time -lboost_serialization -lboost_regex
BOOSTINC= -I/usr/local/include -I/usr/include/libxml++-2.6/ -I/usr/include/glibmm-2.4 -I/usr/include/glib-2.0 -I/usr/lib64/glibmm-2.4/include/ -I/usr/lib64/glib-2.0/include/ -I/usr/lib64/libxml++-2.6/include/
LOCALINC=-I./stock -I./frame -I./fetch -I./search -I./grammer -I./search/ictclas
XMLLIB=-lxml++-2.6 -licuuc -lxslt
#WTLIB=-lwt -lwthttp
WTLIB=-lwt -lwtfcgi
FCGILIB=-lfastcgipp -lmysqlclient
LIBCUTL=-lcurl -ltidy
LIBMQ=-lrabbitmq
LIBXAPIAN=-L./search/ictclas/Source -lxapian -lictclas
CC=gcc
AR=ar -r
CXX=g++
LINK=ld
CFLAGS= -g -fPIC -D_XLNX64 -DTHERON_USE_BOOST_THREADS=1 -D_DEBUG
CXXFLAGS= -g -fPIC -D_XLNX64 -DTHERON_USE_BOOST_THREADS=1 -D_DEBUG
DESC=stockserver
DESC2=stockonce
DESC3=tools.fcgi
DESC4=index.fcgi
DESC5=query.fcgi
INCLUDE=$(BOOSTINC) $(LOCALINC)
BOOSTOBJ= main.o   
BOOSTOBJ2= mainonce.o   
BOOSTOBJ3= fcgiMain.o   
BOOSTOBJ4= index.o   
BOOSTOBJ5= query.o
.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo cpp to o
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE)  -c $<
all: $(DESC) $(DESC2) $(DESC3)
	@echo $@ update to date
$(DESC):$(BOOSTOBJ)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB} ${LIBCUTL} ${LIBMQ} ${LIBXAPIAN}
$(DESC2):$(BOOSTOBJ2)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB} ${LIBCUTL} ${LIBMQ} ${LIBXAPIAN}
$(DESC3):$(BOOSTOBJ3)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB} ${LIBMQ} ${WTLIB}
$(DESC4):$(BOOSTOBJ4)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB} ${FCGILIB} ${LIBXAPIAN}
$(DESC5):$(BOOSTOBJ5)
	@echo Linking $@ ...
	$(CXX) -o $@ $^ ${BOOSTLIB} ${XMLLIB} ${FCGILIB} ${LIBXAPIAN}
clean:
	@-rm $(DESC) $(DESC2)
	@-rm -fr *.o *.a *~ "*#"
