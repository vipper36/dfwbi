#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <gtk/gtk.h>
#include "xpcom-config.h"
#include "nsXPCOMGlue.h"
#include "nsDebug.h"
#include "nsCOMPtr.h"
#include "nsWeakPtr.h"
#include "nsWeakReference.h"
#include "widget/nsIBaseWindow.h"
#include "nsILocalFile.h"
#include "nsIWebBrowser.h"
#include "docshell/nsIWebNavigation.h"
#include "nsEmbedCID.h"
#include "nsEmbedString.h"
#include "xulapp/nsXULAppAPI.h"
#include "nsComponentManagerUtils.h"
#include "nsIDOMDocumentCSS.h"
#include "nsIDOMElementCSSInlineStyle.h"
#include "nsIDOMCSSStyleDeclaration.h"
#include "dom/nsIDOMElement.h"
#include "dom/nsIDOMDocument.h"
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
#include "nsIUrlCollector.h"
#include <iostream>
#include <unistd.h>



XRE_InitEmbeddingType XRE_InitEmbedding;
XRE_TermEmbeddingType XRE_TermEmbedding;
int main(int argc, char** argv) {
     GtkWidget *window=NULL;
     nsCOMPtr<nsIServiceManager> servMan;
     nsCOMPtr<nsIBaseWindow> baseWindow;
     nsCOMPtr<nsIWebBrowser> webBrowser;
     nsCOMPtr<nsILocalFile> libxul;
     nsIWebNavigation *webNavigation;
//      if(argc<2)
//      {
// 	  std::cout<<"usage:gtkMain url"<<std::endl;
// 	return 0;
//      }
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
     //init standalone env
     rv = XPCOMGlueStartup("/usr/local/xulrunner-sdk/bin/libxpcom.so");
     if (NS_FAILED(rv)) {
	  printf("XPCOMGlueStartup\n");
     }
     rv = XPCOMGlueLoadXULFunctions(nsFuncs);
     if (NS_FAILED(rv)) {
	  printf("XPCOMGlueLoadXULFunctions\n");
     }
     rv = NS_NewNativeLocalFile(nsEmbedCString("/usr/local/xulrunner-sdk/bin"),
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
     rv = servMan->GetServiceByContractID("@mozilla.org/embedding/browser/nsWebBrowser;1", NS_GET_IID(nsIWebBrowser), getter_AddRefs(webBrowser)); 
      if (NS_FAILED(rv))
      {
 	  std::cout<<"Get docshell  Error:"<<std::hex<<rv<<std::endl;
      }
      /**********set listener***********/
      nsCOMPtr<nsIWebProgressListener> webl;
      rv = servMan->GetServiceByContractID("@nyapc.com/XPCOM/nsBrowserListener;1", NS_GET_IID(nsIWebProgressListener), getter_AddRefs(webl)); 
      if (NS_FAILED(rv))
      {
 	  std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
      }


      nsCOMPtr<nsIBrowserConnector> webs=do_QueryInterface(webl,&rv);
      if (NS_FAILED(rv))
      {
 	  std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
	  return 0;
      }
      webs->SetBrowser(webBrowser);

//      nsCOMPtr<nsIWebBrowserSetup> setup = do_QueryInterface(webBrowser);
//      rv=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_PLUGINS,false);
//      rv=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_JAVASCRIPT,true);
//      rv=setup->SetProperty(nsIWebBrowserSetup::SETUP_ALLOW_SUBFRAMES,true);
//      if (NS_FAILED(rv)) {
// 	  printf("setup\n");
//      }
     //set base windows
     baseWindow = do_QueryInterface(webBrowser);
      rv = baseWindow->InitWindow(window, 0, 0, 0, 768, 1024);
     if (NS_FAILED(rv)) {
	  printf("InitWindow\n");
        }
     rv = baseWindow->Create();
     if (NS_FAILED(rv)) {
	  printf("Create\n");
     }

     nsCOMPtr<nsIWeakReference> thisListener(do_GetWeakReference(webl,&rv));
     if (NS_FAILED(rv))
      {
 	  std::cout<<"Get weak ref  Error:"<<std::hex<<rv<<std::endl;
	  return 0;
      }

     webBrowser->AddWebBrowserListener(thisListener, nsIWebProgressListener::GetIID());

     CallQueryInterface(webBrowser,&webNavigation);
     //get the crawl url
     nsCOMPtr<nsIUrlCollector> urls;
      rv = servMan->GetServiceByContractID("@nyapc.com/XPCOM/nsUrlCollector;1", NS_GET_IID(nsIUrlCollector), getter_AddRefs(urls)); 
      if (NS_FAILED(rv))
      {
 	  std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
      }
//      PRBool urla;
//      urls->IsEmpty(&urla);
      nsCString aurl;
      urls->GetURL(aurl);
      std::cout<<ToNewCString(aurl)<<std::endl;
      if(aurl.Length()>0)
      {
	   rv = webNavigation->LoadURI(NS_ConvertUTF8toUTF16(aurl).get(),nsIWebNavigation::LOAD_FLAGS_NONE, nsnull, nsnull, nsnull);
	   if (NS_FAILED(rv)) {
		printf("LoadURI\n");
	   }
      }
     //navigate the urls
     
     
     gtk_main();

     
     XRE_TermEmbedding();
     XPCOMGlueShutdown();
     return 0;

}
