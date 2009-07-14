#include "nsDOMCollector.h"
#include "BlockUtils.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "nsIFileStreams.h"
#include "nsNetUtil.h"
#include "nsILineInputStream.h"
#include <iostream>
#include <math.h>

#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMElement.h"
#include "nsIDOMNodeList.h"

NS_IMPL_ISUPPORTS1(nsDOMCollector, nsIDOMAnalysis)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDOMCollector)

static nsModuleComponentInfo components[] =
{
     {
          NS_NSDOMCOLLECTOR_CLASSNAME,
          NS_NSDOMCOLLECTOR_CID,
          NS_NSDOMCOLLECTOR_CONTRACTID,
          nsDOMCollectorConstructor,
     }
};

NS_IMPL_NSGETMODULE("nsDOMCollectorModule", components)

nsDOMCollector::nsDOMCollector()
{
	nsresult rv;
	cdb_handle = do_CreateInstance("@nyapc.com/XPCOM/nsClusterDBHandle;1", &rv);
	if (NS_FAILED(rv))
	{
		ERROR<<"Get  mozIStorageService  Error:"<<rv<<"\n";
		cdb_handle = NULL;
	}

	url_att		= NULL;
	doc		= NULL;
}

nsDOMCollector::~nsDOMCollector()
{
}

NS_IMETHODIMP nsDOMCollector::Analysis(nsIDOMDocument *doc, PRUint32 *_retval)
{
	LOG << "          startup... "<< "\n";
	nsCOMPtr<nsIDOMHTMLDocument> html = do_QueryInterface(doc);
	nsString t,u;
	html->GetTitle(t);
	html->GetURL(u);
	string title(NS_ConvertUTF16toUTF8(t).get());
	string url(NS_ConvertUTF16toUTF8(u).get());

	LOG<<"title: "<<title<<" url: "<<url<<"\n";

	BlockList bl;
	convert_html_to_bl(html,bl);
	bl.SetTitle(title);
	bl.SetUrl(url);
	LOG<<"convert ok"<< "\n";

	write_page_into_db(bl);

	url_att	= NULL;
	doc	= NULL;
	*_retval = 0;
}

NS_IMETHODIMP nsDOMCollector::SetCurUrl(nsIUrlAtt *url_attr)
{
	this->url_att = url_attr;
	return NS_OK;
}

NS_IMETHODIMP nsDOMCollector::SaveWrapper()
{
    return NS_OK;
}

NS_IMETHODIMP nsDOMCollector::SetProperty(nsIPersistentProperties *p)
{
	this->property = p;
	return NS_OK;
}

NS_IMETHODIMP nsDOMCollector::SetIdxCreator(nsIIDXCreator * creator)
{
	return NS_OK;
}

NS_IMETHODIMP nsDOMCollector::LoadConfig()
{
	if(property!=NULL)
	{
		nsString n1;
		property->GetStringProperty(URL_SOURCE, n1);
		mLocation = NS_ConvertUTF16toUTF8(n1);
		LOG << "target database: " << mLocation.get() << "\n";
		
		if(cdb_handle != NULL)
			cdb_handle->SetLocation(mLocation);

	}
	return NS_OK;
}

/* void GetClusterAttr (in PRUint32 cid, out PRUint32 attr); */
NS_IMETHODIMP nsDOMCollector::GetClusterAttr(PRUint32 cid, PRUint32 *attr)
{
	*attr = 0;
	return NS_OK;
}

/* void SetClusterType (in PRUint32 type); */
NS_IMETHODIMP nsDOMCollector::SetClusterType(PRUint32 cid, PRUint32 type)
{
	return NS_OK;
}

void nsDOMCollector::write_page_into_db(BlockList & bl)
{
	LOG<<"start saving...\n";
	stringstream ss;
	bl.serialize(ss);
        LOG<<"serialization OK...\n";
	nsCString page(ss.str().c_str());
	nsCString target("'");
	nsCString nv("''");
	Replace(page,target,nv);
	
	PRInt32 id;
        if(url_att != NULL){
            url_att->GetId(&id);
            LOG<<"page id : "<<id<<endl;
            cdb_handle->SavePage(id, page);
        }
}

void nsDOMCollector::Replace(nsCString & str, const nsCString & target, const nsCString & nv)
{
	int ps = 0;
	int cut_len = target.Length();
	int insert_len = nv.Length();

	ps = str.Find(target,ps);
	while(ps >= 0)
	{
		str.Cut(ps,cut_len);
		str.Insert(nv,ps);
		ps = str.Find(target,ps+insert_len);
	}
}
