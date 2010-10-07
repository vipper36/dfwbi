include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR


SOAPLIB= -L ../soap -lmysoap -lgsoap++
DESC=libSoapJob.so
PUBOBJECT= nsSoapJob.o
DESD=libSoapTask.so
PUBOBJECT2= nsSoapTask.o
DESE=libSoapInter.so
PUBOBJECT3= nsSoapInter.o
IDLH= nsISoapTask.idl
IDLI= nsISoapJob.idl
IDLJ= nsISoapInter.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESD) $(DESE)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $(DESC) $^ $(GECKO_LDFLAGS)
$(DESD) :  $(PUBOBJECT2) 
	$(CXX) $(CPPFLAGS) -o $(DESD) $^ $(GECKO_LDFLAGS)
$(DESE) :  $(PUBOBJECT3) 
	$(CXX) $(CPPFLAGS) -o $(DESE) $^ $(GECKO_LDFLAGS) $(SOAPLIB)
idl:$(IDLH) $(IDLI) 
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLI)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLI)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLJ)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLJ)
install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm -rf $(DESC) $(DESD) $(DESE) *.o *.o *.a *~ "*#" 2>/dev/null
