include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR
KLIB =	-L ../KMean/ -lkml 		
DOMLIB= -L ../DOMAttUtil -ldomutil

DEST1=libDimStat.so
PUBOBJECT1= nsDimStat.o
DEST2=libContentDocAtt.so
PUBOBJECT2= ContentDocAtt.o
DEST3=libThresholdCluster.so
PUBOBJECT3= ThresholdCluster.o
DEST4=libContentVarGen.so
PUBOBJECT4= ContentVarGen.o
DEST5=libContentTrainUtil.so
PUBOBJECT5= ContentTrainUtil.o



IDL1= nsIDimStat.idl
IDL2= nsIContentTrainUtil.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DEST1) $(DEST2) $(DEST3) $(DEST4) $(DEST5)
	@echo $@ update to date
$(DEST1) :  $(PUBOBJECT1) 
	$(CXX) $(CPPFLAGS) -o $(DEST1) $^ $(GECKO_LDFLAGS)
$(DEST2) :  $(PUBOBJECT2)
	$(CXX) $(CPPFLAGS) -o $(DEST2) $^ $(GECKO_LDFLAGS)
$(DEST3) :  $(PUBOBJECT3)
	$(CXX) $(CPPFLAGS) -o $(DEST3) $^ $(GECKO_LDFLAGS)
$(DEST4) :  $(PUBOBJECT4)
	$(CXX) $(CPPFLAGS) -o $(DEST4) $^ $(GECKO_LDFLAGS)
$(DEST5) :  $(PUBOBJECT5)
	$(CXX) $(CPPFLAGS) -o $(DEST5) $^ $(GECKO_LDFLAGS) $(DOMLIB)

idl:
	$(IDL) -m header $(IDL_INCLUDE) $(IDL1)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDL1)
	$(IDL) -m header $(IDL_INCLUDE) $(IDL2)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDL2)
install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm -f *.o *.a *.so *~ "*#" 2>/dev/null
