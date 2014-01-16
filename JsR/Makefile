SHELL = /bin/bash
SUBDIRS = RCom

all:
	@ for subdir in $(SUBDIRS); do \
		$(MAKE) -C $$subdir;\
	done

idl:
	@ for subdir in $(SUBDIRS); do \
		$(MAKE) idl -C $$subdir; \
	done

install:
	@ for subdir in $(SUBDIRS); do \
		$(MAKE) install -C $$subdir; \
	done

clean:
	@ for subdir in $(SUBDIRS); do \
		$(MAKE) clean -C $$subdir; \
	done
