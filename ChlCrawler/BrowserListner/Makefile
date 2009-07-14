CC=gcc
AR=ar -r
CXX=g++
CXXFLAG=-fno-rtti -fno-exceptions -fPIC -fshort-wchar
IDL=/usr/local/xulrunner-sdk/bin/xpidl
CPPFLAGS +=-fno-rtti -fno-exceptions  -fPIC -shared

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
		-I $(GECKO_SDK_PATH)/include/layout	\
		-I /usr/include/gtk-2.0/		\
		-I /usr/include/glib-2.0/		\
		-I /usr/lib64/glib-2.0/include		\
		-I /usr/lib64/gtk-2.0/include		\
		-I /usr/include/pango-1.0/		\
		-I /usr/include/atk-1.0/		\
		-I /usr/include/cairo/			\
		-I ../include/
GECKO_LDFLAGS = -L $(GECKO_SDK_PATH)/lib 	\
		-L $(GECKO_SDK_PATH)/lib -lplds4 -lplc4 -lnspr4	\
		-L $(GECKO_SDK_PATH)/lib -lxpcomglue_s
SHALIB= -L ../sha1 -lsha1
DESC= libChlCrawListener.so
PUBOBJECT= BrowserListener.o nsChlCrawListener.o
DESC2= libColCrawListener.so
PUBOBJECT2= BrowserListener.o nsColCrawListener.o
DESC3= libLinkCollectListener.so
PUBOBJECT3= BrowserListener.o nsLinkCollectListener.o
DESC4= libPageCrawListener.so
PUBOBJECT4= BrowserListener.o nsPageCrawListener.o
IDLH= nsIBrowserConnector.idl
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC) $(DESC2) $(DESC3) $(DESC4)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC2) :  $(PUBOBJECT2) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC3) :  $(PUBOBJECT3) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
$(DESC4) :  $(PUBOBJECT4) 
	$(CXX) $(CPPFLAGS) -o $@  $^ $(GECKO_LDFLAGS)
idl:$(IDLH)
	$(IDL) -m header -I /usr/local/xulrunner-sdk/idl $^
	$(IDL) -m typelib -I /usr/local/xulrunner-sdk/idl $^
install:
	@cp *.so *.xpt $(GECKO_SDK_PATH)/bin/components/
clean: 
	@rm $(DESC) $(DESC2) $(DESC3) $(DESC4) $(DESC5) *.o *.o *.a *~ "*#" 2>/dev/null
