include ../config.mk
GECKO_DEFINES  = -DXPCOM_GLUE
DEPBASE=300
DEPCOUNT=2

CXXFLAG=-g -fshort-wchar
CPPFLAGS =-g
DESC=gtkMain
PUBOBJECT= gtkMain.o
DESC2=keyPress
PUBOBJECT2= keyPress.o
DESC3=mulMain
PUBOBJECT3= mulMain.o
DESC4=WinPro
PUBOBJECT4= WinPro.o
.cpp.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CXX) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(MAIN_INCLUDES) $(CXXFLAG) $(DEF) -c $<
.c.o:
	@echo Compiling cc program $< ......
	@echo c to o
	$(CC) $(GECKO_CONFIG_INCLUDE) $(GECKO_DEFINES) $(MAIN_INCLUDES) $(DEF) -c $<

all: $(DESC) $(DESC2) $(DESC3) $(DESC4)
	@echo $@ update to date
$(DESC) :  $(PUBOBJECT) 
	$(CXX) $(CPPFLAGS) -o $@ $^ $(MAIN_LDFLAGS)
$(DESC2) :  $(PUBOBJECT2) 
	$(CXX) -o $(DESC2) $^ -lX11
$(DESC3) :  $(PUBOBJECT3) 
	$(CXX) $(CPPFLAGS) -o $@ $^ $(MAIN_LDFLAGS)
$(DESC4) :  $(PUBOBJECT4) 
	$(CXX) $(CPPFLAGS) -o $@ $^ $(MAIN_LDFLAGS)
clean: 
	@-rm -f $(DESC) $(DESC2) *.o *.o *.a *~ "*#" 2>/dev/null
deploy:
	./deploy.sh $(DEPBASE) $(DEPCOUNT)
cleandeploy:
	./depclean.sh $(DEPBASE) $(DEPCOUNT)

