#ifndef __GTK_BROWSER_H__
#define __GTK_BROWSER_H__
#include "nsIWebBrowser.h"
#include "nsIBrowserConnector.h"
#include "nsIWebProgressListener.h"
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include "nsEmbedCID.h"
#include "nsEmbedString.h"
#include "nsIIOService.h"
#include "nsICookieService.h"
#include "nsIURI.h"
#include "nsIStatManager.h"
#include "nsIListenerSetter.h"
class gtkBrowser
{
private:
     nsCOMPtr<nsIWebBrowser> webBrowser;
     nsCOMPtr<nsIBrowserConnector> webs;
     nsCOMPtr<nsIWebProgressListener> webl;
     GtkWidget *mozembed;
     nsCString m_url;
     int m_bid;
public:
     gtkBrowser(GtkWidget *window,int bid)
	  :m_bid(bid)
	  {
	       if(window!=NULL)
	       {
		    mozembed = gtk_moz_embed_new();

		    gtk_container_add(GTK_CONTAINER(window), mozembed);
		    gtk_widget_show(mozembed);
		    gtk_moz_embed_get_nsIWebBrowser(GTK_MOZ_EMBED(mozembed), getter_AddRefs(webBrowser));
		    if( webBrowser == nsnull )
		    {
			 std::cout<<"webBrowser load error "<<std::endl;
		    }
		    gtk_widget_hide(mozembed);
	       }
	  }
     bool SetListener(nsIStatManager *man)
	  {
	       nsresult rv;
	       webl=do_CreateInstance("@nyapc.com/XPCOM/nsSimpleListener;1",&rv);
	       if (NS_FAILED(rv))
	       {
		    std::cout<<"Get listener  Error:"<<std::hex<<rv<<std::endl;
		    return false;    
	       }
	       nsCOMPtr<nsIListenerSetter> ls=do_QueryInterface(webl,&rv);
	       if (NS_FAILED(rv))
	       {
		    std::cout<<"Get listener  setter Error:"<<std::hex<<rv<<std::endl;
		    return false;    
	       }
	       man->SetBrowser(webBrowser,m_bid);
	       ls->SetStatManager(man);
	       ls->SetId(m_bid);
	       nsCOMPtr<nsIWeakReference> thisListener(do_GetWeakReference(webl,&rv));
	       if (NS_FAILED(rv))
	       {
		    std::cout<<"Get weak ref  Error:"<<std::hex<<rv<<std::endl;
		    return false;
	       }
	       webBrowser->AddWebBrowserListener(thisListener, nsIWebProgressListener::GetIID());
	  }
     void SetRunlevel(int mozSet)
	  {
	       nsresult rv;
	       nsCOMPtr<nsIWebBrowserSetup> setup = do_QueryInterface(webBrowser);
	       PRBool allow_plug=PR_FALSE,allow_js=PR_FALSE,allow_frame=PR_FALSE,allow_img=PR_FALSE,allow_rd=PR_FALSE,allow_dns=PR_TRUE;
	       switch(mozSet)
	       {
	       case 5:
		    allow_plug=PR_TRUE;
	       case 4:
		    allow_img=PR_TRUE;
	       case 3:
		    allow_frame=PR_TRUE;
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
	  }
     bool SetCookie(std::string cookie,nsIServiceManager *servMan)
	  {
	       nsresult rv;
	       nsCOMPtr<nsIIOService> iio;
	       rv=servMan->GetServiceByContractID("@mozilla.org/network/io-service;1", NS_GET_IID(nsIIOService), getter_AddRefs(iio));
     
	       if (NS_FAILED(rv))
	       {
		    std::cout<<"Get ioservice  Error:"<<std::hex<<rv<<std::endl;
		    return false;
	       }
	       nsCOMPtr<nsICookieService> cookServ;
	       rv=servMan->GetServiceByContractID("@mozilla.org/cookieService;1",  NS_GET_IID(nsICookieService),getter_AddRefs(cookServ));
	       if (NS_FAILED(rv)) 
	       {
		    std::cout<<"Get nsicookieservice Error:"<<rv<<std::endl;
		    return false;
	       }
	       nsCOMPtr<nsIURI> cookieUri(nsnull);
	       iio->NewURI(m_url,nsnull,nsnull,getter_AddRefs(cookieUri));
	       if (cookieUri==nsnull)
	       {
		    return false;
	       }
	       size_t index=0;
	       do
	       {
		    size_t curr=index;
		    index=cookie.find(";",curr);
		    if(index!=std::string::npos)
		    {
			 index++;
			 std::string tmpCook=cookie.substr(curr,index-curr);
			 std::cout<<"tmpcook:"<<tmpCook<<"\n";
			 cookServ->SetCookieString(cookieUri, nsnull, tmpCook.c_str(), nsnull);
		    }
	       }while(index!=std::string::npos);
	       return true;
	       
	  }
     void SetUrl(nsCString aurl)
	  {
	       m_url=aurl;
	  }
     nsresult Start()
	  {
	       
	       nsresult rv;
	       nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(webBrowser);
	       std::cout<<"acess:"<<m_url.get()<<"\n";
	       if(m_url.Length()>0)
	       {		     
		    rv = nav->LoadURI(NS_ConvertUTF8toUTF16(m_url).get(),nsIWebNavigation::LOAD_FLAGS_STOP_CONTENT, nsnull, nsnull, nsnull);
		    if (NS_FAILED(rv)) {
			 return rv;
		    }
	       }
	       return NS_OK;
	  }
     nsresult Stop()
	  {
	  
	       nsresult rv;
	       nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(webBrowser);
	       return nav->Stop(nsIWebNavigation::STOP_ALL);
	  }
};
#endif
