#include "nsLoginCookieFetch.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsIDOMElement.h"
#include "nsIDOMHTMLFrameElement.h"
#include "nsIDOMHTMLIFrameElement.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMXPathEvaluator.h"
#include "nsIURI.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsISupports.h"
#include "nsIDOMNode.h"
#include "nsIDOMDocumentEvent.h"
#include "nsIDOMEvent.h"
#include "nsIDOMEventTarget.h"
#include "nsICookieManager.h"
#include "nsICookie.h"
#include "nsICookie2.h"
#include "nsICookieService.h"
#include "nsISimpleEnumerator.h"
#include "property.h"
#include "nsIIOService.h"

using namespace std;

NS_IMPL_ISUPPORTS1(nsLoginCookieFetch, nsILoginCookieFetch)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsLoginCookieFetch)

static nsModuleComponentInfo components[] =
{
     {
	  NS_LOGINCOOKIEFETCH_CLASSNAME,
	  NS_LOGINCOOKIEFETCH_CID,
	  NS_LOGINCOOKIEFETCH_CONTRACTID,
	  nsLoginCookieFetchConstructor,
     }
};

NS_IMPL_NSGETMODULE("nsLoginCookieFetchModule", components)



nsLoginCookieFetch::nsLoginCookieFetch()
:mDoc(nsnull)
{
     /* member initializers and constructor code */
}

nsLoginCookieFetch::~nsLoginCookieFetch()
{
     /* destructor code */
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsLoginCookieFetch::SetDocument(nsIDOMDocument *doc,const nsACString &url,const nsACString &userName,const nsACString &password)
{
     mDoc=doc;
     this->userName = NS_ConvertUTF8toUTF16(userName);
     this->password = NS_ConvertUTF8toUTF16(password);
     this->url = NS_ConvertUTF8toUTF16(url);
     return NS_OK;

}
/**
*/
NS_IMETHODIMP nsLoginCookieFetch::DoLogin()
{
	cout << "--------------------------------------------begin" <<endl;


		nsString tagName;

		nsCOMPtr<nsIDOMNode> pwdNode(nsnull);
		this->GetPassWordDomNode(getter_AddRefs(pwdNode));

		if(pwdNode == nsnull)
		{
			cout << "pwd Node is null" <<endl;
		}
		SetNodeAttributValue(pwdNode,this->password);

		//call SetUserAttribut
		this->SetUserAttribut(pwdNode);


		nsCOMPtr<nsIDOMNode> formNode(nsnull);
		pwdNode->GetParentNode(getter_AddRefs(formNode));

		string form = "FORM";
		formNode->GetNodeName(tagName);
		if(form.compare(NS_ConvertUTF16toUTF8(tagName).get()) != 0)
		{
			formNode->GetParentNode(getter_AddRefs(formNode));
		}

		formNode->GetNodeName(tagName);
		SendClickEvent(formNode, mDoc);

		cout << "Form Name1 =" <<NS_ConvertUTF16toUTF8(tagName).get() <<endl;


	cout << "--------------------------------------------------end" << endl;
	return NS_OK;
}
NS_IMETHODIMP nsLoginCookieFetch::GetPassWordDomNode(nsIDOMNode **result)
{
	nsresult rv = NS_OK;
	nsCOMPtr<nsIXpathUtil> xu=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	if (NS_FAILED(rv))
		return rv;

	    nsCOMPtr<nsISupportsArray> docArr(nsnull);
    this->GetALLDocumentArray(mDoc,getter_AddRefs(docArr));

    PRUint32 len = 0;
    docArr->Count(&len);
    cout << "len is " << len <<endl;
    nsCString xpath("//form//input[@type='password']");
    for(PRUint32 i = 0; i < len; i++)
    {
    	nsCOMPtr<nsISupports> docSup;
    	docArr->GetElementAt(i,getter_AddRefs(docSup));
    	nsCOMPtr<nsIDOMDocument> pdoc = do_QueryInterface(docSup);

    	xu->SetDocument(pdoc);
    	nsCOMPtr<nsISupportsArray> pwdNodeArr(nsnull);
    	xu->GetNodes(xpath,getter_AddRefs(pwdNodeArr));
		PRUint32 nodeLen = 0;
    	pwdNodeArr->Count(&nodeLen);

		nsCOMPtr<nsIDOMNode> pNode;


    	if(nodeLen == 1)
    	{
    		nsCOMPtr<nsISupports> nodeSup;
    		pwdNodeArr->GetElementAt(0,getter_AddRefs(nodeSup));
    		nsCOMPtr<nsIDOMNode> pNode = do_QueryInterface(nodeSup);

    		*result = pNode;
    		NS_ADDREF(*result);
    	}
    	else
    	{
    		cout << "password node no found" <<endl;
    	}

	}
	return NS_OK;
}

/* AUTF8String GetLoginCookie (); */
NS_IMETHODIMP nsLoginCookieFetch::GetLoginCookie( nsACString & _retval)
{
	nsresult rv=NS_OK;

	//login in
	rv = DoLogin();
	if(NS_FAILED(rv))
		return rv;

	nsCOMPtr<nsICookieManager> cm=do_CreateInstance("@mozilla.org/cookiemanager;1",&rv);
	if (NS_FAILED(rv))
		return rv;

	nsCOMPtr<nsISimpleEnumerator> enu;
	cm->GetEnumerator(getter_AddRefs(enu));

	PRBool bl;
	nsCOMPtr<nsISupports> el;
	nsCString rvStr;
	/*
	while(bl)
	{
		enu->GetNext(getter_AddRefs(el));
		nsCOMPtr<nsICookie> cookie = do_QueryInterface(el);
		nsCOMPtr<nsICookie2> cookie2 = do_QueryInterface(cookie);

		nsCString name;
		nsCString value;
		nsCString host;
		PRUint64 expires;
		nsCString path;
		PRInt64 creationTime;
		PRBool isSession;

		cookie2->GetName(name);
		cookie2->GetValue(value);
		cookie2->GetHost(host);
		cookie2->GetExpires(&expires);
		cookie2->GetPath(path);
		cookie2->GetCreationTime(&creationTime);
		cookie2->GetIsSession(&isSession);

		if(host.Equals("bbs.jrj.com.cn"))
		{
			if(!isSession)
			{
				rvStr.Append(name);
				rvStr.Append("\n");
				rvStr.Append(value);
				rvStr.Append("\n");
				rvStr.Append(host);
				rvStr.Append(path);
				rvStr.Append("\n");
				rvStr.AppendInt(creationTime);
				rvStr.Append("\n");
				rvStr.AppendInt(expires);
				rvStr.Append("\n*\n");
			}
		}

		enu->HasMoreElements(&bl);
	}
*/
	nsCOMPtr<nsIIOService> ios = do_CreateInstance("@mozilla.org/network/io-service;1",&rv);
	if (NS_FAILED(rv))
		return rv;

	nsCOMPtr<nsIURI> uri ;
	ios->NewURI(NS_ConvertUTF16toUTF8(this->url), NULL, NULL,getter_AddRefs(uri));

	nsCOMPtr<nsICookieService> cs = do_CreateInstance("@mozilla.org/cookieService;1",&rv);
	if(NS_FAILED(rv))
		return rv;

	char* strCookie;
	cs->GetCookieString(uri, NULL,&strCookie);
	_retval = strCookie;
	return NS_OK;
}
/**
* get all document ,return document arrary
*/
NS_IMETHODIMP nsLoginCookieFetch::GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray **supArr)
{
	nsresult rv = NS_OK;

	nsCOMPtr<nsIXpathUtil> xu=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	if (NS_FAILED(rv))
		return rv;
	xu->SetDocument(doc);

	nsCOMPtr<nsISupportsArray> result = do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);

	result->AppendElement(doc);

	PRUint32 frmLen = 0;
	PRUint32 ifrmLen = 0;
	nsCOMPtr<nsISupportsArray> frmArr;
	nsCOMPtr<nsISupportsArray> ifrmArr;

	nsCString frmPath("//frame");
	nsCString ifrmPath("//iframe");
	xu->GetNodes(frmPath,getter_AddRefs(frmArr));
	frmArr->Count(&frmLen);

	if(frmLen > 0)
	{
		for(PRUint32 i = 0; i < frmLen; i++)
		{
			nsCOMPtr<nsISupports> frmSup;
			nsCOMPtr<nsIDOMHTMLFrameElement> frmEle;
			nsCOMPtr<nsIDOMDocument> frmDoc;

			frmArr->GetElementAt(i,getter_AddRefs(frmSup));
			frmEle = do_QueryInterface(frmSup);
			frmEle->GetContentDocument(getter_AddRefs(frmDoc));
			result->AppendElement(frmDoc);

			xu->SetDocument(frmDoc);

			xu->GetNodes(ifrmPath,getter_AddRefs(ifrmArr));
			ifrmArr->Count(&ifrmLen);

			cout << "ifrm len = " << ifrmLen <<endl;

			if(ifrmLen > 0)
			{
				for(PRUint32 j = 0; j < ifrmLen; j++)
				{
					nsCOMPtr<nsISupports> ifrmSup;
					nsCOMPtr<nsIDOMHTMLIFrameElement> ifrmEle;
					nsCOMPtr<nsIDOMDocument> ifrmDoc;

					ifrmArr->GetElementAt(j,getter_AddRefs(ifrmSup));
					ifrmEle = do_QueryInterface(ifrmSup);
					ifrmEle->GetContentDocument(getter_AddRefs(ifrmDoc));
					result->AppendElement(ifrmDoc);
				}
			}
			ifrmArr->Clear();
		}
	}

	*supArr = result;
	NS_ADDREF(*supArr);
	return rv;
}
/**
*set attribut value
*/
NS_IMETHODIMP nsLoginCookieFetch::SetNodeAttributValue(nsCOMPtr<nsIDOMNode> &node,const nsString value)
{
	nsresult rv=NS_OK;

	nsCOMPtr<nsIDOMElement>domEle = do_QueryInterface(node);
	nsString att = NS_ConvertUTF8toUTF16("value");

	domEle->SetAttribute(att,value);

	return rv;
}
/**
*set user node value
*/
NS_IMETHODIMP nsLoginCookieFetch::SetUserAttribut(nsCOMPtr<nsIDOMNode>&node)
{
	nsresult rv=NS_OK;

	string label = "LABEL";
	string input = "INPUT";
	string text = "#text";

	nsString tagName;

	nsCOMPtr<nsIDOMNode> usrNode(nsnull);

	node->GetPreviousSibling(getter_AddRefs(usrNode));

	usrNode->GetNodeName(tagName);
	if(label.compare(NS_ConvertUTF16toUTF8(tagName).get()) == 0)
	{
		usrNode->GetPreviousSibling(getter_AddRefs(usrNode));
		if(usrNode != nsnull)
		{
			usrNode->GetNodeName(tagName);
			if(input.compare(NS_ConvertUTF16toUTF8(tagName).get()) == 0)
			{
				SetNodeAttributValue(usrNode,this->userName);
			}
		}
		cout <<"node is null" <<endl;
	}
	else if(input.compare(NS_ConvertUTF16toUTF8(tagName).get()) == 0)
	{
		SetNodeAttributValue(usrNode,this->userName);
	}

	if(text.compare(NS_ConvertUTF16toUTF8(tagName).get()) == 0)
	{
		usrNode->GetPreviousSibling(getter_AddRefs(usrNode));
		SetNodeAttributValue(usrNode,this->userName);
	}
	else if(input.compare(NS_ConvertUTF16toUTF8(tagName).get()) == -1)
	{
		node->GetParentNode(getter_AddRefs(usrNode));
		usrNode->GetPreviousSibling(getter_AddRefs(usrNode));
		usrNode->GetLastChild(getter_AddRefs(usrNode));

		SetNodeAttributValue(usrNode,this->userName);
	}

	usrNode->GetNodeName(tagName);

	cout << "tagName =" <<NS_ConvertUTF16toUTF8(tagName).get() <<endl;

	return rv;
}
/**
*sent mouse click event
*/
NS_IMETHODIMP nsLoginCookieFetch::SendClickEvent(nsCOMPtr<nsIDOMNode> &node, nsCOMPtr<nsIDOMDocument> &doc)
{
	nsresult rv = NS_OK;

	nsCOMPtr<nsIDOMElement>domEle = do_QueryInterface(node);

    nsCOMPtr<nsIDOMDocumentEvent> docEvent = do_QueryInterface(doc);
    nsCOMPtr<nsIDOMEvent> event;
	docEvent->CreateEvent(NS_LITERAL_STRING("HTMLEvents"),getter_AddRefs(event));

	NS_SUCCEEDED(event->InitEvent(NS_LITERAL_STRING("submit"),PR_TRUE,PR_TRUE));
    nsCOMPtr<nsIDOMEventTarget> evtTarget=do_QueryInterface(domEle);
    PRBool clickStatus;
    evtTarget->DispatchEvent(event,&clickStatus);

    return rv;
}
