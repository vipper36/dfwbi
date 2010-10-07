include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR
KLIB =	-L ../KMean/ -lkml 		
DOMLIB= -L ../DOMAttUtil -ldomutil

DESL=libNDDocAtt.so
PUBOBJECT= nsNDDocAtt.o 
DESL1=libUrlCluster.so
PUBOBJECT1= nsUrlCluster.o
DESL2=libChlVarGenerator_1.so
PUBOBJECT2= nsChlVarGenerator_1.o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESL) $(DESL1) $(DESL2) 
	@echo $@ update to date
$(DESL) :  $(PUBOBJECT)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(GECKO_LDFLAGS)
$(DESL1) :  $(PUBOBJECT1)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(GECKO_LDFLAGS) $(DOMLIB)
$(DESL2) :  $(PUBOBJECT2)
	$(CXX) $(CPPFLAGS) -o $@ $^ $(GECKO_LDFLAGS) $(DOMLIB)

idl:
	@echo "do nothing"
install:
	@cp *.so $(GECKO_COM)
clean: 
	@-rm -rf $(DESL) $(DESL1) $(DESL2) *.o *.o *.a *~ "*#" 2>/dev/null
