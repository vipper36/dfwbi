#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include "gtkmozembed_glue.cpp"
#include "xpcom-config.h"
#include "nsXPCOMGlue.h"
#include "nsDebug.h"
#include "nsCOMPtr.h"
#include "nsWeakPtr.h"
#include "nsWeakReference.h"
#include "nsIBaseWindow.h"
#include "nsILocalFile.h"
#include "nsIWebBrowser.h"
#include "nsIWebNavigation.h"
#include "nsEmbedCID.h"
#include "nsEmbedString.h"
#include "nsXULAppAPI.h"
#include "nsComponentManagerUtils.h"
#include "nsIDOMDocumentCSS.h"
#include "nsIDOMElementCSSInlineStyle.h"
#include "nsIDOMCSSStyleDeclaration.h"
#include "nsIDOMElement.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMNSDocument.h"
#include "nsIBoxObject.h"
#include "nsIDOMXULElement.h"
#include "nsIServiceManager.h"
#include "nsIDOMWindow.h"
#include "nsIWebBrowserPersist.h"
#include "nsIWebBrowserSetup.h"
#include "nsIBrowserConnector.h"
#include "nsIWebProgressListener.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIComponentRegistrar.h"
#include "nsIPrefService.h"
#include "nsISoapInter.h"
#include "nsISoapTask.h"
//#include "nsITimer.h"
#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include <list>
#include <unistd.h>
#include "gtkBrowser.h"
#ifndef XUL_BIN
#define XUL_BIN "/usr/local/xulrunner-sdk/bin"
#endif

#ifndef XUL_PATH
#define XUL_PATH "/usr/local/xulrunner-sdk/bin/libxpcom.so"
#endif

void usage()
{
     std::cout<<"usage:mulMain <-c crawlerID> "
	      <<"[-n url number] "
	      <<"<-l listener> "
	      <<"[-r <mozSetup run level>] "
	      <<"[-s <libxul.so path>] "
	      <<"[-b <xulrunner bin path>]"
	      <<"<[-C|-G]>"
	      <<"[-S soap server]"
	      <<std::endl;
     exit(0);
}
bool mozilla_prefs_set_string(nsIServiceManager *servMan,const char *preference_name, const char *new_value)
{
     if(preference_name == NULL ||servMan==nsnull) 
	  return false;

     // It is legitimate to pass in a NULL value sometimes. So let's not
     // assert and just check and return.
     if (!new_value) return false;

     nsCOMPtr<nsIPrefService> prefService;
     servMan->GetServiceByContractID(NS_PREFSERVICE_CONTRACTID,NS_GET_IID(nsIPrefService),getter_AddRefs(prefService));
     nsCOMPtr<nsIPrefBranch> pref;
     prefService->GetBranch("", getter_AddRefs(pref));

     if (pref)
     {
	  nsresult rv = pref->SetCharPref(preference_name, new_value);
	  return NS_SUCCEEDED(rv) ? true : false;
     }

     return false;
}



XRE_InitEmbeddingType XRE_InitEmbedding;
XRE_TermEmbeddingType XRE_TermEmbedding;
int main(int argc, char** argv) {
     GtkWidget *window=NULL;
     GtkWidget *vbox=NULL;
     nsCOMPtr<nsIServiceManager> servMan;
    
     nsCOMPtr<nsILocalFile> libxul;
     nsIWebNavigation *webNavigation;
     int cid=0;
     std::string lstStr("");
     int mozSet=0;
     std::string xulPath(XUL_PATH);
     std::string xulrunPath(XUL_BIN);
     std::string soapServer;
     int maxDoc=20;
     if(argc<2)
     {
	  usage();
	  return 0;
     }
     bool isCraw=true;
     int opt;
     while((opt = getopt(argc, argv, "n:i:c:l:r:t:s:b:S:CG")) != -1) {
	  switch(opt) {
	  case 'C':
	       isCraw=true;
	       break;
	  case 'G':
	       isCraw=false;
	       break;
	  case 'c':
	       cid=atoi(optarg);
	       break;
	  case 'n':
	       maxDoc=atoi(optarg);
	       break;
	  case 'l':
	       
	       lstStr=std::string(optarg);
	       break;
	  case 'r':
	       mozSet=atoi(optarg);
	       break;
	  case 's':
	       xulPath=std::string(optarg);
	       break;
	  case 'S':
	       soapServer=std::string(optarg);
	       break;
	  case 'b':
	       xulrunPath=std::string(optarg);
	       break;
	  default:
	       usage();
	  }
     }
     if(lstStr.length()==0||lstStr.length()==0)
     {
	  usage();
     }
     nsDynamicFunctionLoad nsFuncs[] = {
	  {"XRE_InitEmbedding", (NSFuncPtr*)&XRE_InitEmbedding},
	  {"XRE_TermEmbedding", (NSFuncPtr*)
	   &XRE_TermEmbedding},
	  {0, 0}
     };
     nsresult rv;
     //create native window
     gtk_init (&argc, &argv);
     window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
     GTKEmbedGlueStartup();
     GTKEmbedGlueStartupInternal();

     gtk_widget_set_usize(window, 1280,1024);
     vbox = gtk_vbox_new(TRUE, 0);
     gtk_container_add(GTK_CONTAINER(window), vbox);
     gtk_widget_show(window);
     gtk_widget_show(vbox);
     //init standalone env
     rv = XPCOMGlueStartup(xulPath.c_str());
     if (NS_FAILED(rv)) {
	  printf("XPCOMGlueStartup\n");
     }
     rv = XPCOMGlueLoadXULFunctions(nsFuncs);
     if (NS_FAILED(rv)) {
	  printf("XPCOMGlueLoadXULFunctions\n");
     }
     rv = NS_NewNativeLocalFile(nsEmbedCString(xulrunPath.c_str()),
				PR_FALSE, getter_AddRefs(libxul));
     if (NS_FAILED(rv)) {
	  printf("NS_NewNativeLocalFile\n");
     }
     rv = XRE_InitEmbedding(libxul, 0, 0, 0, 0);
     if (NS_FAILED(rv)) {
	  printf("XRE_InitEmbedding\n");
     }

     rv = NS_GetServiceManager(getter_AddRefs(servMan)); 
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Get manager Error:"<<rv<<std::endl;
     }
     nsCOMPtr<nsIComponentRegistrar> registrar = do_QueryInterface(servMan);
     rv=registrar->AutoRegister(nsnull); 
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Get manager Error:"<<rv<<std::endl;
     }
     mozilla_prefs_set_string (servMan,"general.useragent.override", "Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.0.8) Gecko/2009032600 SUSE/3.0.8-1.1 Firefox/3.0.8");
     nsCOMPtr<nsIStatManager> sm=do_CreateInstance(lstStr.c_str(),&rv);
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get stat manager Error:"<<std::hex<<rv<<std::endl;
	  return 0;    
     }
     nsCOMPtr<nsISoapInter> inter=do_CreateInstance("@nyapc.com/XPCOM/nsSoapInter;1",&rv);
     if (NS_FAILED(rv)) 
     {
	  std::cout<<"Init Soap Inter error\n";
	  return 0;    
     }
     if(soapServer.length()>0)
	  inter->SetAddress(nsCString(soapServer.c_str()));
     nsCOMPtr<nsISoapTask> task;
     if(isCraw)
	  inter->GetTask(cid,maxDoc,getter_AddRefs(task));
     else
	  inter->GetWrapTask(cid,maxDoc,getter_AddRefs(task));
     sm->SetInter(inter);
     std::list<gtkBrowser> bList;
     if(task!=nsnull)
     {
 	  sm->SetTask(task);
 	  PRInt32 len;
 	  task->GetUrlCount(&len);
 	  for(PRInt32 index=0;index<len;index++)
 	  {
 	       int Uid;
 	       nsCString aurl;
 	       task->GetUrlByIndex(index,&Uid,aurl);
	       gtkBrowser gb(vbox,Uid);

	       gb.SetListener(sm);
	       gb.SetRunlevel(mozSet);
	       gb.SetUrl(aurl);
 	       bList.push_back(gb);
 	  }
     
 	  for(std::list<gtkBrowser>::iterator it=bList.begin();it!=bList.end();++it)
 	       it->Start();
     }else
     {
	  sleep(60);
	  exit(0);
     }
     gtk_widget_hide(vbox);
     gtk_widget_hide(window);
     /**********set listener***********/

     
     std::cout<<"Crawler ID:"<<cid<<std::endl;
     
     
     
     
     
     gtk_main();
     
     XRE_TermEmbedding();
     XPCOMGlueShutdown();
     return 0;

}
