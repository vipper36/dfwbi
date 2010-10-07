include ../config.mk

GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR


CHPATHLIB=-L ../Wrapper -lWrapper
DESD=libLoginCookieFetch.so
PUBOBJECT2= nsLoginCookieFetch.o
IDLH= nsILoginCookieFetch.idl

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESD)
	@echo $@ update to date
$(DESD) :  $(PUBOBJECT2)
	$(CXX) $(CPPFLAGS) -o $(DESD) $^ $(GECKO_LDFLAGS)

idl:$(IDLI) $(IDLH) $(IDLJ)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)

install:
	@cp *.so *.xpt $(GECKO_COM)
clean:
	@rm  $(DESD) *.o *.o *.a *~ "*#" 2>/dev/null
