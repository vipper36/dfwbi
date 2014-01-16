include ../config.mk
IDLH= nsIJsCom
all: idl
	@echo $@ update to date
idl:$(IDLH).idl
	$(typelib) $(IDL_INCLUDE) $(IDLH).idl -o $(IDLH).xpt
install:
	@cp *.js *.xpt ../JsUi/components
clean:
	@-rm -rf *.xpt  *.o *.o *.a *~ "*#" 2>/dev/null
