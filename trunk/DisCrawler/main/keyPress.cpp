#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Intrinsic.h>
#include <X11/Shell.h>
#include <X11/StringDefs.h>
#include <X11/extensions/XShm.h>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sstream>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>

using namespace std;

class WindowsMatchingPid
{
public:
     WindowsMatchingPid(Display *display, unsigned long pid,Window w)
	  : _display(display)
	  , _pid(pid)
	  {
	       // Get the PID property atom.
	       _atomPID = XInternAtom(display, "_NET_WM_PID", True);
	       if(_atomPID == None)
	       {
		    cout << "No such atom" << endl;
		    return;
	       }
	       search(w);
	  }

     const list<Window> &result() const { return _result; }
     
private:
     void search(Window w)
	  {
	       // Get the PID for the current Window.
	       Atom           type;
	       int            format;
	       unsigned long  nItems;
	       unsigned long  bytesAfter;
	       unsigned char *propPID = 0;
	       if(Success == XGetWindowProperty(_display, w, _atomPID, 0, 1, False, XA_CARDINAL,
						&type, &format, &nItems, &bytesAfter, &propPID))
	       {
		    if(propPID != 0)
		    {
			 // If the PID matches, add this window to the result set.
			 if(_pid == *((unsigned long *)propPID))
			      _result.push_back(w);

			 XFree(propPID);
		    }
	       }

	       // Recurse into child windows.
	       Window    wRoot;
	       Window    wParent;
	       Window   *wChild;
	       unsigned  nChildren;
	       if(0 != XQueryTree(_display, w, &wRoot, &wParent, &wChild, &nChildren))
	       {
		    for(unsigned i = 0; i < nChildren; i++)
			 search(wChild[i]);
	       }
	  }
     unsigned long  _pid;
     Atom           _atomPID;
     Display       *_display;
     list<Window>   _result;
    
};

void usage()
{
     std::cout<<"usage:keyPress process args "
	      <<std::endl;
     exit(0);
}

static void xsimulate_key(Display *dis, Window win)
{
     if(dis!=NULL)
     {
	  XKeyEvent xev;
	  memset(&xev, 0, sizeof(xev));
	  xev.serial = 0;
	  xev.send_event = 0;
	  xev.type = KeyPress;
	  xev.display = dis;
	  xev.keycode= XKeysymToKeycode(xev.display, XK_Return);
	  xev.root = None;
//     xev.subwindow = GDK_WINDOW_XWINDOW(widget);
	  xev.window = win;
	  xev.time = 0;
	  xev.same_screen = 1;
	  xev.state = 0;
	  xev.x = 1;
	  xev.y = 1;
	  xev.x_root = 1;
	  xev.y_root = 1;
	  (void) XSendEvent(xev.display, xev.window, True, KeyPressMask,
			    (XEvent *)&xev);
	  XFlush(xev.display);
/* Key release may be needed for some programs */
	  xev.type = KeyRelease;
	  (void) XSendEvent(xev.display, xev.window, True, KeyReleaseMask,
			    (XEvent *)&xev);
	  XFlush(xev.display); 
     }
}
int SendErrorHandler(Display *dis, XErrorEvent *env)
{
	if(env->error_code==BadWindow)
     		std::cout<<"exit.......... "<<std::endl;
     		exit(0);
}
bool split(const std::string& s, std::string c,std::vector<std::string>& v)
{
     std::string::size_type i = 0;
     std::string::size_type j = s.find(c);
     while (j != std::string::npos)
     {
          v.push_back(s.substr(i, j-i));
          i = j+c.length();
          j = s.find(c, i);
     }
     if(j == std::string::npos)
     {
          std::string tmp=s.substr(i, s.length( ));
          if(tmp.length()>0)
               v.push_back(tmp);
     }
     return true;
}
bool IsZombie(int pid)
{
     std::stringstream ss;
     ss<<"/proc/"<<pid<<"/stat";
     struct stat stFileInfo;
     int intStat;

     intStat = stat(ss.str().c_str(),&stFileInfo);
     if(intStat == 0) {
	  std::ifstream ifi(ss.str().c_str());
	  std::string statstr;
	  getline(ifi,statstr);
	  std::vector<std::string> att;
	  split(statstr, " ",att);
	  if(att[2]=="Z")
	       return true;
	  else
	       return false;
     } else {
	  false;
     }
     
}
int main(int argc, char** argv) {
     if(argc<2)
     {
	  usage();
     }
     int pid;
     pid=fork();
     if(pid==0)
     {
	  char **newargv =argv+1;
	  execv(argv[1], newargv);
     }else
     {

	  ofstream ofi("gtkMain.pid");
	  ofi<<pid;
	  ofi.close();
	  
	  XErrorHandler oldXErrorHandler=XSetErrorHandler(SendErrorHandler);
	  while(1)
	  {
	       sleep(1);
	       if(IsZombie(pid))
		    break;
	       std::cout<<"send key press.......... "<<pid<<std::endl;
	       Display *display = XOpenDisplay(0);
	       if(display!=NULL)
		 {
		   WindowsMatchingPid match(display, pid,XDefaultRootWindow(display));
		   const list<Window> &result = match.result();
		   {
		     
		     for(list<Window>::const_iterator it = result.begin(); it != result.end(); it++)
		       
		       xsimulate_key(display, *it);
		   }
		 }
	       else
		 {
		   break;
		 }
	       
	  }
     }
     return 0;
}
