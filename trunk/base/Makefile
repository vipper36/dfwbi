#Directory Define
include ../config.mk
include $(EPT_INCLUDE)/makefile_include_pub
#Compliers and their flags
CC=cc
AR=ar -r
CXX=xlC_r
LINK=ld
CFLAGS=-g -DLOG4CPP_HAVE_SSTREAM -DAIXSYS $(CFLAGS_PUB) $(APPCFLAGS) -I/usr/include -qcpluscmt
AMQLIBS=-L$(AMQOPTDIR)/lib -lmqm -lmqmxa
INCLUDE= -I$(AixMailBox)/include -I$(AixMailBox)/pub/include
LOGXMLLIB=-L$(AixMailBox)/lib/ -llog4cpp -lxerces-c -liconv
VPATH=
CIPHERLIB=$(EPT_LIB)/cacipher.a
RSAADDLIB=$(EPT_LIB)/librsa_add.a
DESC=libCaxLib.so
PUBOBJECT=CACipher.o FileOperator.o  MQManager.o OptManager.o XMLConfiger.o CaxMessage.o DirOperator.o Logger.o XMLStringTranslate.o clob.o 
.SUFFIXES: .h .cpp .o

.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(CFLAGS) $(INCLUDE) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(CFLAGS) $(INCLUDE) -c $<
all: $(DESC)
	@echo $@ update to date
libCaxLib.so:$(PUBOBJECT)
	@echo Linking $@ ...
	makeC++SharedLib_r -p -100 -bglink:/lib/glink.o -bM:SRE -o libCaxLib.so ${PUBOBJECT} $(LIBS) $(CIPHERLIB) $(RSAADDLIB) $(LOGXMLLIB) $(EPTLIBS)
	$(AR) libCaxLib.a libCaxLib.so
	@cp libCaxLib.so $(AixMailBox)/bin 
	@cp $@ $(AixMailBox)/lib
	@cp libCaxLib.a $(AixMailBox)/lib
	@cp *.h $(AixMailBox)/include
clob.o:clob.pc
	proc $(PCFLAGS) clob.pc
	$(CXX) $(CFLAGS) $(INCLUDE) -o clob.o -c clob.c
clean:
	@-rm $(DESC)
	@-rm -fr *.o *.a *~ "*#"
