CC=gcc
AR=ar -r
CXX=g++
CXXFLAG=-g -fshort-wchar
CPPFLAGS +=-g 

# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /usr/local/xulrunner-sdk

# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include $(GECKO_SDK_PATH)/include/mozilla-config.h 

GECKO_DEFINES  = -DXPCOM_GLUE

GECKO_INCLUDES =-I $(GECKO_SDK_PATH)/sdk/include	\
		-I $(GECKO_SDK_PATH)/include		\
		-I /usr/include/gtk-2.0/		\
		-I /usr/include/glib-2.0/		\
		-I /usr/lib64/glib-2.0/include		\
		-I /usr/lib64/gtk-2.0/include		\
		-I /usr/include/pango-1.0/		\
		-I /usr/include/atk-1.0/		\
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
		-I $(GECKO_SDK_PATH)/include/xulapp	\
		-I $(GECKO_SDK_PATH)/include/webbrowserpersist	\
		-I $(GECKO_SDK_PATH)/include/gtkembedmoz	\
		-I /usr/include/cairo/			\
		-I ../include/
GECKO_LDFLAGS =	-L $(GECKO_SDK_PATH)/lib -lplds4 -lplc4	\
		-L $(GECKO_SDK_PATH)/lib -lxpcomglue -lxpcom -lnspr4 -lmozjs -lxul
DESC=gtkMain
PUBOBJECT= gtkMain.o
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) $(CXXFLAG) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(GECKO_INCLUDES) -c $<

all: $(DESC)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $(DESC) $^ $(GECKO_LDFLAGS)
clean: 
	@rm $(DESC) $(EDESC) *.o *.o *.a *~ "*#" 2>/dev/null
