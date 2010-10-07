CC=gcc
AR=ar -r
CXX=g++
CXXFLAG=-g -g -fno-rtti -fno-exceptions -fPIC -fshort-wchar
IDL=/usr/local/xulrunner-sdk/bin/xpidl
CPPFLAGS +=-g -g -fno-rtti -fno-exceptions  -fPIC -shared

# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /usr/local/xulrunner-sdk
GECKO_COM = $(GECKO_SDK_PATH)/bin/components/
# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include $(GECKO_SDK_PATH)/include/mozilla-config.h 

IDL_INCLUDE=-I /usr/local/xulrunner-sdk/idl
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
		-I $(GECKO_SDK_PATH)/include/webbrowserpersist	\
		-I $(GECKO_SDK_PATH)/include/uriloader	\
		-I $(GECKO_SDK_PATH)/include/storage    \
		-I $(GECKO_SDK_PATH)/include/caps	\
		-I $(GECKO_SDK_PATH)/include/xpconnect	\
		-I $(GECKO_SDK_PATH)/include/js		\
		-I $(GECKO_SDK_PATH)/include/inspector/	\
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

MAIN_INCLUDES =-I $(GECKO_SDK_PATH)/sdk/include	\
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
MAIN_LDFLAGS =	-L $(GECKO_SDK_PATH)/lib -lplds4 -lplc4	\
		-L $(GECKO_SDK_PATH)/lib -lxpcomglue -lxpcom -lnspr4 -lmozjs -lxul
