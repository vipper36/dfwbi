include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR



SHALIB= -L ../sha1 -lsha1
DESC= libMultiDocListener.so
PUBOBJECT= BrowserListener.o nsMultiDocListener.o
DESC1= libWrapGenListener.so
PUBOBJECT1= BrowserListener.o nsWrapGenListener.o
DESC2= libSimpleListener.so
PUBOBJECT2= SimpleListener.o
DESC3= libCrawStatMan.so
PUBOBJECT3= nsCrawStatMan.o nsStatManager.o
DESC4= libWrapStatMan.so
PUBOBJECT4= nsWrapStatMan.o nsStatManager.o
IDLH= nsIBrowserConnector.idl
IDLH1= nsIStatManager.idl
IDLH2= nsIListenerSetter.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESC1) $(DESC2) $(DESC3) $(DESC4)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC1) :  $(PUBOBJECT1) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC2) :  $(PUBOBJECT2) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC3) :  $(PUBOBJECT3) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC4) :  $(PUBOBJECT4) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
idl:
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH1)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH1)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH2)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH2)
install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm -rf $(DESC) $(DESC1) $(DESC2) $(DESC3) $(DESC4) $(DESC5) *.o *.o *.a *~ "*#" 2>/dev/null
