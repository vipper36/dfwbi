SHELL = /bin/bash
SUBDIRS = main soap KMean DOMAttUtil WrapperFetch SoapCom StatCom BrowserListner ContentTrain StatExt
SUBDIRS1 = DOMAttUtil WrapperFetch SoapCom StatCom BrowserListner ContentTrain StatExt

all:
	$(MAKE) soap -C soap 
	@ for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir;\
	done

idl:
	@ for subdir in $(SUBDIRS1); do \
		$(MAKE) idl -C $$subdir; \
	done

install:
	@ for subdir in $(SUBDIRS1); do \
		$(MAKE) install -C $$subdir; \
	done

clean:
	@ for subdir in $(SUBDIRS); do \
		$(MAKE) clean -C $$subdir; \
	done
