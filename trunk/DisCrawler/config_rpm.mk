CC=gcc
AR=ar -r
CXX=g++


DEF=-DXUL_BIN=\"/usr/lib64/xulrunner-1.9.1.5/\" -DXUL_PATH=\"/usr/lib64/xulrunner-devel-1.9.1.5/lib/libxpcom.so\"

CXXFLAG=-g -fno-rtti -fno-exceptions -fPIC -fshort-wchar

CPPFLAGS += -g -fno-rtti -fno-exceptions  -fPIC -shared

# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /usr/lib64/xulrunner-devel-1.9.1.5/
GECKO_COM = $(GECKO_SDK_PATH)/bin/components/
IDL=$(GECKO_SDK_PATH)/bin/xpidl
# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include $(GECKO_SDK_PATH)/include/mozilla-config.h 

IDL_INCLUDE= -I $(GECKO_SDK_PATH)/include -I $(GECKO_SDK_PATH)/sdk/include
GECKO_INCLUDES =-I $(GECKO_SDK_PATH)/include	\
		-I $(GECKO_SDK_PATH)/sdk/include	\
		-I /usr/include/nspr4/			\
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

MAIN_INCLUDES =	-I /usr/include/gtk-2.0/		\
		-I /usr/include/glib-2.0/		\
		-I /usr/lib64/glib-2.0/include		\
		-I /usr/lib64/gtk-2.0/include		\
		-I /usr/include/pango-1.0/		\
		-I /usr/include/atk-1.0/		\
		-I $(GECKO_SDK_PATH)/include	\
		-I $(GECKO_SDK_PATH)/sdk/include	\
		-I /usr/include/nspr4/			\
		-I /usr/include/cairo/			\
		-I ../include/
MAIN_LDFLAGS =	-L $(GECKO_SDK_PATH)/lib -lplds4 -lplc4	\
		-L $(GECKO_SDK_PATH)/lib -lxpcomglue -lxpcom -lnspr4 -lmozjs -lxul 
