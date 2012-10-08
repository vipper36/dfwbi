include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR


IDLH= nsIJsCom.idl
all: idl
	@echo $@ update to date
idl:$(IDLH) $(IDLI) 
	$(IDL) -m typelib -w -v $(IDL_INCLUDE) $(IDLH)
install:
	@cp *.js *.xpt $(GECKO_COM)
clean:
	@-rm -rf $(DESC) $(DESD) $(DESE) *.o *.o *.a *~ "*#" 2>/dev/null
