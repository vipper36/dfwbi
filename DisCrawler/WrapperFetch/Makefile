include ../config.mk

GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR


CHPATHLIB=-L ../Wrapper -lWrapper
DESD=libXpathUtil.so
PUBOBJECT2= nsXpathUtil.o
DESF=libXSLTFetcher.so
PUBOBJECT4= nsXSLTFetcher.o
DESG=libWrapperSave.so
PUBOBJECT5= nsWrapperSave.o
IDLH= nsIXpathUtil.idl
IDLK= nsIXSLTFetcher.idl
IDLL= nsIWrapperSave.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESD) $(DESE) $(DESF) $(DESG)
	@echo $@ update to date
$(DESD) :  $(PUBOBJECT2) 
	$(CXX) $(CPPFLAGS) -o $(DESD) $^ $(GECKO_LDFLAGS)
$(DESF) :  $(PUBOBJECT4) 
	$(CXX) $(CPPFLAGS) -o $(DESF) $^ $(GECKO_LDFLAGS)
$(DESG) :  $(PUBOBJECT5) 
	$(CXX) $(CPPFLAGS) -o $(DESG) $^ $(GECKO_LDFLAGS)

idl:$(IDLI) $(IDLH) $(IDLJ)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLK)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLK)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLL)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLL)

install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm  -rf $(DESD) $(DESG) $(DESF) *.o *.o *.a *~ "*#" 2>/dev/null
