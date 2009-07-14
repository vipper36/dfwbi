CC=gcc
AR=ar -r
CXX=g++
CXXFLAG=-fno-rtti -fno-exceptions -fPIC -fshort-wchar
IDL=/usr/local/xulrunner-sdk/bin/xpidl
CPPFLAGS +=-fno-rtti -fno-exceptions -fPIC -shared

# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /usr/local/xulrunner-sdk

# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include $(GECKO_SDK_PATH)/include/mozilla-config.h 

GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR

GECKO_INCLUDES =-I $(GECKO_SDK_PATH)/sdk/include	\
		-I $(GECKO_SDK_PATH)/include/xpcom	\
		-I $(GECKO_SDK_PATH)/include/nspr	\
		-I $(GECKO_SDK_PATH)/include/string	\
		-I $(GECKO_SDK_PATH)/include/necko	\
		-I $(GECKO_SDK_PATH)/include/webbrwsr	\
		-I $(GECKO_SDK_PATH)/include/dom	\
		-I $(GECKO_SDK_PATH)/include/docshell	\
		-I $(GECKO_SDK_PATH)/include/content	\
		-I $(GECKO_SDK_PATH)/include/htmlparser	\
		-I $(GECKO_SDK_PATH)/include/widget	\
		-I $(GECKO_SDK_PATH)/include/storage	\
		-I ../include/			\
		-I $(GECKO_SDK_PATH)/include/layout
GECKO_LDFLAGS = -L $(GECKO_SDK_PATH)/lib 	\
		-L $(GECKO_SDK_PATH)/lib -lplds4 -lplc4 -lnspr4	\
		-L $(GECKO_SDK_PATH)/lib -lxpcomglue_s	
SHALIB= -L ../sha1 -lsha1
DESC=libColFilterFetcher.so
PUBOBJECT= nsColFilterFetcher.o
DESC2=libColNextPageFetcher.so
PUBOBJECT2= nsColNextPageFetcher.o
DESC3=libColBridge.so
PUBOBJECT3= nsColBridge.o
IDLH= nsIColFetcher.idl
IDLI= nsIColBridge.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESC2) $(DESC3)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $(DESC) $^ $(GECKO_LDFLAGS) $(SHALIB)
$(DESC2) :  $(PUBOBJECT2) 
	$(CXX) $(CPPFLAGS) -o $(DESC2) $^ $(GECKO_LDFLAGS) $(SHALIB)
$(DESC3) :  $(PUBOBJECT3) 
	$(CXX) $(CPPFLAGS) -o $(DESC3) $^ $(GECKO_LDFLAGS)
idl:$(IDLH) $(IDLI) 
	$(IDL) -m header -I /usr/local/xulrunner-sdk/idl $(IDLH)
	$(IDL) -m typelib -I /usr/local/xulrunner-sdk/idl $(IDLH)
	$(IDL) -m header -I /usr/local/xulrunner-sdk/idl $(IDLI)
	$(IDL) -m typelib -I /usr/local/xulrunner-sdk/idl $(IDLI)
install:
	@cp *.so *.xpt $(GECKO_SDK_PATH)/bin/components/
clean: 
	@rm $(DESC) $(DESC2) $(DESE) *.o *.o *.a *~ "*#" 2>/dev/null
