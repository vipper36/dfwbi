include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR


SOAPLIB= -L ../soap -l
DESC=libNodeCom.so
PUBOBJECT= nsNodeComJob.o
IDLH= nsINodeCom.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $(DESC) $^ $(GECKO_LDFLAGS)
idl:$(IDLH) $(IDLI) 
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)
install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm -rf $(DESC) $(DESD) $(DESE) *.o *.o *.a *~ "*#" 2>/dev/null
