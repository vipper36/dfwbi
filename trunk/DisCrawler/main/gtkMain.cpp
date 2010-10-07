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
//#include "nsITimer.h"
#include <pthread.h>
#include <sys/time.h>
#include <iostream>
#include <unistd.h>
#ifndef XUL_BIN
#define XUL_BIN "/usr/local/xulrunner-sdk/bin"
#endif

#ifndef XUL_PATH
#define XUL_PATH "/usr/local/xulrunner-sdk/bin/libxpcom.so"
#endif

void usage()
{
     std::cout<<"usage:gtkMain <-c crawlerID> "
	      <<"[-n url number] "
	      <<"[-i interrupt time] "
	      <<"<-l listener> "
	      <<"[-r <mozSetup run level>] "
	      <<"[-s <libxul.so path>] "
	      <<"[-b <xulrunner bin path>]"
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
     GtkWidget *mozembed;
     GtkWidget *container;
     nsCOMPtr<nsIServiceManager> servMan;
     nsCOMPtr<nsIBaseWindow> baseWindow;
     nsCOMPtr<nsIWebBrowser> webBrowser;
     nsCOMPtr<nsILocalFile> libxul;
     nsIWebNavigation *webNavigation;
     int cid=0;
     std::string lstStr("");
     int mozSet=0;
     std::string xulPath(XUL_PATH);
     std::string xulrunPath(XUL_BIN);
     double interTime=0.3;
     int maxDoc=20;
     if(argc<2)
     {
	  usage();
	  return 0;
     }
     int opt;
     while((opt = getopt(argc, argv, "n:i:c:l:r:t:s:b:")) != -1) {
	  switch(opt) {
	
	  case 'c':
	       cid=atoi(optarg);
	       break;
	  case 'n':
	       maxDoc=atoi(optarg);
	       break;
	  case 'i':
	       interTime=atof(optarg);
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

     mozembed = gtk_moz_embed_new();

     gtk_container_add(GTK_CONTAINER(window), mozembed);

     gtk_widget_set_usize(window, 1280,1024);

     gtk_widget_show(mozembed);

     gtk_widget_show(window);

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

     gtk_moz_embed_get_nsIWebBrowser(GTK_MOZ_EMBED(mozembed), getter_AddRefs(webBrowser));
     if( webBrowser == nsnull )
     {
	  std::cout<<"webBrowser load error "<<std::endl;
	  return 0;
     }
     gtk_widget_hide(mozembed);
     gtk_widget_hide(window);
     /**********set listener***********/

     nsCOMPtr<nsIWebProgressListener> webl;
     rv=servMan->GetServiceByContractID(lstStr.c_str(), NS_GET_IID(nsIWebProgressListener), getter_AddRefs(webl));
     if (NS_FAILED(rv))
     {
 	  std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
	  return 0;
	  
     }

     nsCOMPtr<nsIBrowserConnector> webs=do_QueryInterface(webl,&rv);
     if (NS_FAILED(rv))
     {
 	  std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
	  return 0;
     }
     std::cout<<"Crawler ID:"<<cid<<std::endl;
     
     webs->SetID(cid);
     webs->SetInterrupt(interTime);
     webs->SetDefDoc(maxDoc);
     webs->SetBrowser(webBrowser);

     nsCOMPtr<nsIWebBrowserPersist> webPer=do_QueryInterface(webBrowser);
     PRUint32 flag;
     webPer->GetPersistFlags(&flag);
     //webPer->SetPersistFlags(flag|
//			     nsIWebBrowserPersist::PERSIST_FLAGS_FIXUP_LINKS_TO_DESTINATION);
     webPer->SetPersistFlags(flag|
			     nsIWebBrowserPersist::PERSIST_FLAGS_DONT_FIXUP_LINKS);

     nsCOMPtr<nsIWeakReference> thisListener(do_GetWeakReference(webl,&rv));
     if (NS_FAILED(rv))
     {
 	  std::cout<<"Get weak ref  Error:"<<std::hex<<rv<<std::endl;
	  return 0;
     }

     webBrowser->AddWebBrowserListener(thisListener, nsIWebProgressListener::GetIID());
     mozilla_prefs_set_string (servMan,"general.useragent.override", "Mozilla/5.0 (X11; U; Linux x86_64; en-US; rv:1.9.0.8) Gecko/2009032600 SUSE/3.0.8-1.1 Firefox/3.0.8");
     nsCOMPtr<nsIWebBrowserSetup> setup = do_QueryInterface(webBrowser);
     PRBool allow_plug=PR_FALSE,allow_js=PR_FALSE,allow_frame=PR_FALSE,allow_img=PR_FALSE,allow_rd=PR_FALSE,allow_dns=PR_TRUE;
     switch(mozSet)
     {
     case 5:
	  allow_frame=PR_TRUE;
     case 4:
	  allow_plug=PR_TRUE;
     case 3:
	  allow_img=PR_TRUE;
     case 2:
	  allow_rd=PR_TRUE;
     case 1:
	  allow_js=PR_TRUE;
     default:
	  break;
     }     

     rv=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_PLUGINS,allow_plug);
     rv|=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_JAVASCRIPT,allow_js);
     rv|=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_META_REDIRECTS,allow_rd);
     rv|=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_SUBFRAMES,allow_frame);
     rv|=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_IMAGES,allow_img);
     if (NS_FAILED(rv)) {
	  std::cout<<"WebBrowser setup  Error:"<<std::hex<<rv<<std::endl;
     }
     gtk_main();
     
     XRE_TermEmbedding();
     XPCOMGlueShutdown();
     return 0;

}
