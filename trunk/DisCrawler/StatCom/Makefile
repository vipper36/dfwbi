include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR
KLIB =	-L ../KMean/ -lkml 		
DOMLIB= -L ../DOMAttUtil -ldomutil

DESC=libAttSet.so
PUBOBJECT= nsAttSet.o
DESD=libAttVec.so
PUBOBJECT1= nsAttVec.o
DESE=libDocAtt.so
PUBOBJECT2= nsDocAtt.o
DESF=libDocSet.so
PUBOBJECT3= nsDocSet.o
DESG=libCluster.so
PUBOBJECT4= nsCluster.o
DESH=libClustModel.so
PUBOBJECT5= nsClustModel.o
DESI=libChlVarGenerator.so
PUBOBJECT6= nsChlVarGenerator.o
DESJ=libAttDim.so
PUBOBJECT7= nsAttDim.o
DESK=libColVarGenerator.so
PUBOBJECT8= nsColVarGenerator.o


IDLH= nsICluster.idl
IDLI= nsIClustModel.idl
IDLJ= nsIAttSet.idl
IDLK= nsIAttVec.idl
IDLL= nsIDocAtt.idl
IDLM= nsIDocSet.idl
IDLO= nsIVarGenerator.idl
IDLP= nsIAttDim.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESD) $(DESE) $(DESF)  $(DESH) $(DESG) $(DESI) $(DESI) $(DESJ) $(DESK) $(DESL)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $(DESC) $^ $(GECKO_LDFLAGS)
$(DESD) :  $(PUBOBJECT1) 
	$(CXX) $(CPPFLAGS) -o $(DESD) $^ $(GECKO_LDFLAGS)
$(DESE) :  $(PUBOBJECT2) 
	$(CXX) $(CPPFLAGS) -o $(DESE) $^ $(GECKO_LDFLAGS) $(DOMLIB)
$(DESF) :  $(PUBOBJECT3) 
	$(CXX) $(CPPFLAGS) -o $(DESF) $^ $(GECKO_LDFLAGS)
$(DESG) :  $(PUBOBJECT4) 
	$(CXX) $(CPPFLAGS) -o $(DESG) $^ $(GECKO_LDFLAGS) $(KLIB)
$(DESH) :  $(PUBOBJECT5)
	$(CXX) $(CPPFLAGS) -o $(DESH) $^ $(GECKO_LDFLAGS)
$(DESI) :  $(PUBOBJECT6)
	$(CXX) $(CPPFLAGS) -o $(DESI) $^ $(GECKO_LDFLAGS)
$(DESJ) :  $(PUBOBJECT7)
	$(CXX) $(CPPFLAGS) -o $(DESJ) $^ $(GECKO_LDFLAGS)
$(DESK) :  $(PUBOBJECT8)
	$(CXX) $(CPPFLAGS) -o $(DESK) $^ $(GECKO_LDFLAGS) $(DOMLIB)

idl:$(IDLH) $(IDLI) $(IDLH) $(IDLJ) $(IDLK) $(IDLL) $(IDLM) $(IDLN) $(IDLO) $(IDLP)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLI)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLI)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLJ)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLJ)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLK)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLK)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLL)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLL)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLM)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLM)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLO)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLO)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLP)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLP)
install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm -rf $(DESC) $(DESD) $(DESE) $(DESF) $(DESG) $(DESH)  $(DESI) $(DESJ) $(DESK) *.o *.o *.a *~ "*#" 2>/dev/null
