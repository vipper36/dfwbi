include ../config.mk
IDLH= nsIJsCom.idl
all: idl
	@echo $@ update to date
idl:$(IDLH) 
	$(typelib) $(IDL_INCLUDE) $(IDLH).idl -o $(IDLH).xpt
install:
	@cp *.js *.xpt ../SetGUI/components
clean:
	@-rm -rf $(DESC) $(DESD) $(DESE) *.o *.o *.a *~ "*#" 2>/dev/null
