CC=gcc
AR=ar -r
CXX=g++
CXXFLAG=-fno-rtti -fno-exceptions -fPIC -fshort-wchar
CPPFLAGS +=-fno-rtti -fno-exceptions -fPIC

# Change this to point at your Gecko SDK directory. 
GECKO_SDK_PATH = /usr/local/xulrunner-sdk

# GCC only define which allows us to not have to #include mozilla-config 
# in every .cpp file.  If your not using GCC remove this line and add 
# #include "mozilla-config.h" to each of your .cpp files. 
GECKO_CONFIG_INCLUDE = -include $(GECKO_SDK_PATH)/include/mozilla-config.h 

GECKO_DEFINES  = -DXPCOM_GLUE_USE_NSPR -DLEVEL=3

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
		-I $(GECKO_SDK_PATH)/include/storage    \
		-I ../include	
DESC=libblockcluster.a

PUBOBJECT= BlockCluster.o BlockNode.o BlockUtils.o date.o analysis.o

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
	ar -r $@  $(PUBOBJECT)
clean: 
	@rm *.so *.o *.a *~ "*#" 2>/dev/null
