include ../config.mk
GECKO_DEFINES  = -DMOZ_GLUE_IN_PROGRAM -D_IMPL_NS_COM -DEXPORT_XPT_API -DEXPORT_XPTC_API -D_IMPL_NS_GFX -D_IMPL_NS_WIDGET -DIMPL_XREAPI -DIMPL_NS_NET -DIMPL_THEBES  -DSTATIC_EXPORTABLE_JS_API -DNO_NSPR_10_SUPPORT -DEXCLUDE_SKIA_DEPENDENCIES -DHAVE_CONFIG_H

JSONINC=-I../include
LIBS=-L ../lib_json -ldl -lcrypt -ljson
DESC=libRCom.so
IDLH= nsIRCom
PUBOBJECT=nsRCom.o nsRModule.o Rconnection.o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) $(JSONINC) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(JSONINC) -c $<

all: $(DESC)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT)
	$(CXX) $(CPPFLAGS) -o $(DESC) $^ $(GECKO_LDFLAGS) $(LIBS)
idl:$(IDLH).idl
	$(header) $(IDL_INCLUDE) $(IDLH).idl -o $(IDLH).h 
	$(typelib) $(IDL_INCLUDE) $(IDLH).idl -o $(IDLH).xpt  
install:
	@cp *.so *.xpt ../JsUi/components
clean: 
	@-rm -rf $(DESC) *.o *.o *.a *~ "*#" 2>/dev/null
