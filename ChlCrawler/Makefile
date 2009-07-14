SHELL = /bin/bash
SUBDIRS = main sha1 LD ChlXpath KMean BlockCluster BrowserListner DOMAnalysis DOMCluster DomDBHandle DocHandle LayOutAnalysis ChlAtt ColAtt UrlAtt IDXCreator
SUBDIRS1 = BrowserListner DOMAnalysis DOMCluster DomDBHandle DocHandle LayOutAnalysis ChlAtt ColAtt UrlAtt IDXCreator

all:
	@ for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE)); \
	done

idl:
	@ for subdir in $(SUBDIRS1); do \
		(cd $$subdir && $(MAKE) idl); \
	done

install:
	@ for subdir in $(SUBDIRS1); do \
		(cd $$subdir && $(MAKE) install); \
	done

clean:
	@ for subdir in $(SUBDIRS); do \
		(cd $$subdir && $(MAKE) clean); \
	done
