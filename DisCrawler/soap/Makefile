LIB = libmysoap.a
SOAPTOOL=soaptool
SOAPSOURCES = soapC.cpp  soapCrawlerCtrlSoapBindingProxy.cpp

SOAPOBJECTS = $(SOAPSOURCES:.cpp=.o)

TESTSOURCES = main.cpp 

SOAPTOOLSOURCES = soaptool.cpp 

SOAPTOOLOBJECTS = $(SOAPTOOLSOURCES:.cpp=.o)

TESTOBJECTS = $(TESTSOURCES:.cpp=.o)


C++ = g++
CFLAGS = -fPIC -g

#-----------------------------------------------------------------------------
# Make the program
#-----------------------------------------------------------------------------


all: $(LIB) $(SOAPTOOL)


$(LIB): $(SOAPOBJECTS)
	ar -r $@ $(SOAPOBJECTS)

$(SOAPTOOL):$(SOAPTOOLOBJECTS)
	$(C++) -g -o $@ $^ $(LIB) -lgsoap++
test:$(LIB) $(TESTOBJECTS)
	$(C++) -g -o $@ $^ $(LIB) -lgsoap++

#-----------------------------------------------------------------------------
# Object files
#-----------------------------------------------------------------------------
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(C++) $(CFLAGS) -c $<
soap:
	wsdl2h -nnyapc -o CrawlerCtrl.h http://10.8.0.55:8081/WebServiceCrawler/services/CrawlerCtrl?wsdl
	soapcpp2  -s -t -x -i -I/usr/local/share/gsoap/import/ -C CrawlerCtrl.h
	cp *.h ../include
	cp *.nsmap ../include	
clean:
	@-rm -f *.o *.obj *.fig *.bak *.dmp *.~cpp *.~h core $(LIB) test $(TASKTEST)
