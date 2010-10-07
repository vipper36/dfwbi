include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR

DESC=libdomutil.a
PUBOBJECT= StyleCompare.o BlockCluster.o  BlockNode.o BlockUtils.o analysis.o date.o stringutil.o distance.o LayerCluster.o

DESD=libDomAttUtil.so
PUBOBJECT1= nsDomAttUtil.o


IDLH= nsIDomAttUtil.idl

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
$(DESC) :  $(PUBOBJECT) 
	ar -r $@ $(PUBOBJECT)
$(DESD) :  $(PUBOBJECT1) 
	$(CXX) $(CPPFLAGS) -o $(DESD) $^ $(GECKO_LDFLAGS) -L. -ldomutil

idl:$(IDLH) $(IDLI)
	$(IDL) -m header $(IDL_INCLUDE) $(IDLH)
	$(IDL) -m typelib $(IDL_INCLUDE) $(IDLH)
install:
	@cp *.so *.xpt $(GECKO_COM)
clean: 
	@-rm -rf $(DESC) $(DESD)  *.o *.o *.a *~ "*#" 2>/dev/null
