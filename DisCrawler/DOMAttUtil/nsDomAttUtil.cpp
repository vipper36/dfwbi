#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMAbstractView.h"
#include "nsIDOMDocumentView.h"
#include "nsIDOMCSSStyleDeclaration.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSDocument.h"
#include "inIDOMUtils.h"
#include "nsIDOMViewCSS.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOM3Node.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIDOMHTMLAreaElement.h"
#include "nsNetUtil.h"
#include "nsDomAttUtil.h"
#include "nsIAttVec.h"
#include "nsIBoxObject.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMElement.h"
#include "nsIDOMHTMLFrameElement.h"
#include "nsIDOMHTMLIFrameElement.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsISupports.h"
#include <iostream>
#include <sstream>
#include <stack>
#include "math.h"
#include "stdlib.h"
#include "distance.h"
#include "property.h"
#include "StyleCompare.h"
#define VISUALAREA 1024*768

NS_IMPL_ISUPPORTS1(nsDomAttUtil, nsIDomAttUtil)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDomAttUtil)

static nsModuleComponentInfo components[] =
{
     {
	  NS_DOMATTUTIL_CLASSNAME,
	  NS_DOMATTUTIL_CID,
	  NS_DOMATTUTIL_CONTRACTID,
	  nsDomAttUtilConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsDomAttUtilModule", components)



nsDomAttUtil::nsDomAttUtil()
{
}

nsDomAttUtil::~nsDomAttUtil()
{
     /* destructor code */
}

/* long CalNodeDepth (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::CalNodeDepth(nsIDOMNode *node, PRInt32 *_retval )
{
     int ret=0;
     nsIDOMNode* pNode=node;
     while(pNode!=nsnull)
     {
	  ret++;
	  pNode->GetParentNode((nsIDOMNode**)(&pNode));
     }
     *_retval=ret;
     return NS_OK;
}

/* long GetDocUrlCount (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDomAttUtil::GetDocUrlCount(nsIDOMDocument *doc, PRInt32 *_retval )
{
     nsresult rv;
     nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     xpathUtil->SetDocument(doc);
     nsCOMPtr<nsISupportsArray> nodeArr(nsnull);
     nsCString xpath("//a[@href]");
     xpathUtil->GetNodes(xpath, getter_AddRefs(nodeArr));
     if(nodeArr!=nsnull)
     {
	  PRUint32 arrlen=0;
	  nodeArr->Count(&arrlen);
	  *_retval=arrlen;
     }else
     {
	  *_retval=0;
     }
     return NS_OK;
}

/* long GetNodeUrlCount (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeUrlCount(nsIDOMNode *node, PRInt32 *_retval )
{
     nsresult rv;
     nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     nsCOMPtr<nsIDOMDocument> oDoc(nsnull);
     node->GetOwnerDocument(getter_AddRefs(oDoc));
     if(oDoc!=nsnull)
     {
	  xpathUtil->SetDocument(oDoc);
	  nsCOMPtr<nsISupportsArray> nodeArr(nsnull);
	  nsCString xpath(".//a[@href]");
	  xpathUtil->GetSubNodes(node,xpath,getter_AddRefs(nodeArr));
	  if(nodeArr!=nsnull)
	  {
	       PRUint32 arrlen=0;
	       nodeArr->Count(&arrlen);
	       *_retval=arrlen;
	  }else
	  {
	       *_retval=0;
	  }
     }else
     {
	  *_retval=0;
     }
     return NS_OK;
}

/* AUTF8String GetDocText (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDomAttUtil::GetDocText(nsIDOMDocument *doc, nsACString & _retval )
{
     nsCOMPtr<nsIDOMElement> dele(nsnull);
     nsCString nsValue;
     doc->GetDocumentElement(getter_AddRefs(dele));
     nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(dele);
     if(nsEle!=nsnull)
     {
	  nsString Value;
	  nsEle->GetTextContent(Value);
	  nsValue=NS_ConvertUTF16toUTF8(Value);
     }else
     {
	  nsValue=nsCString("");
     }
     nsValue.StripChars("\n");
     nsValue.StripWhitespace();
     _retval=nsValue;
     return NS_OK;
}

/* AUTF8String GetNodeText (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeText(nsIDOMNode *node, nsACString & _retval )
{
     nsCString nsValue;
     nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(node);
     if(nsEle!=nsnull)
     {
	  nsString Value;
	  nsEle->GetTextContent(Value);
	  nsValue=NS_ConvertUTF16toUTF8(Value);
     }else
     {
	  nsValue=nsCString("");
     }
     nsValue.StripChars("\n");
     nsValue.StripWhitespace();

     _retval=nsValue;
     return NS_OK;
}

/* AUTF8String GetNodeOwnText (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeOwnText(nsIDOMNode *node, nsACString & _retval)
{
     nsresult rv;
     nsCString nsValue = nsCString("");
     PRBool has_child = false;
     node->HasChildNodes(&has_child);
     if(has_child){
	  nsCOMPtr<nsIDOMNodeList> children;
	  rv = node->GetChildNodes(getter_AddRefs(children));
	  if(!NS_FAILED(rv)){
	       PRUint32 len;
	       children->GetLength(&len);
	       for(int i = 0; i < len; i++)
	       {
		    nsIDOMNode * n;
		    children->Item(i, &n);
		    unsigned short type;
		    n->GetNodeType(&type);
		    if(type == nsIDOMNode::TEXT_NODE)
		    {
			 nsString value;
			 n->GetNodeValue(value);
			 nsValue.Append(NS_ConvertUTF16toUTF8(value).get());
		    }
	       }
	  }
     }

     nsValue.StripChars("\n");
     nsValue.StripWhitespace();

     _retval=nsValue;
     return NS_OK;
}

/* long GetDocUrlDistance (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDomAttUtil::GetDocUrlDistance(nsIDOMDocument *doc, PRInt32 *_retval )
{
     nsresult rv;
     nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     Distance ld;
     PRInt32 distValue=0;
     xpathUtil->SetDocument(doc);
     nsCOMPtr<nsISupportsArray> nodeArr(nsnull);
     nsCString xpath("//a[@href]");
     xpathUtil->GetNodes(xpath, getter_AddRefs(nodeArr));
     if(nodeArr!=nsnull)
     {
	  PRUint32 arrlen=0;
	  nodeArr->Count(&arrlen);
	  std::string lastUrl;
	  bool setinit=false;

	  for(PRUint32 i=0;i<arrlen;i++)
	  {
	       nsCOMPtr<nsISupports> node;
	       nodeArr->GetElementAt(i,getter_AddRefs(node));

	       nsCOMPtr<nsIDOMElement> domele=do_QueryInterface(node);
	       nsString nsName=NS_ConvertUTF8toUTF16("href");
	       nsString nsValue;
	       if(domele!=nsnull)
	       {
		    domele->GetAttribute(nsName,nsValue);


		    if(!setinit)
		    {
			 lastUrl=std::string(NS_ConvertUTF16toUTF8(nsValue).get());
			 setinit=true;
		    }
		    else
		    {
			 std::string curUrl(NS_ConvertUTF16toUTF8(nsValue).get());

			 distValue+=ld.LD(lastUrl,curUrl);
			 lastUrl=curUrl;
		    }
	       }
	  }
	  *_retval=distValue;
     }
     else
     {
	  *_retval=-1;
     }
     return NS_OK;
}

/* long GetNodeUrlDistance (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeUrlDistance(nsIDOMNode *node, PRInt32 *_retval )
{
     nsresult rv;
     nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     nsCOMPtr<nsIDOMDocument> oDoc(nsnull);
     if(node!=nsnull)
	  node->GetOwnerDocument(getter_AddRefs(oDoc));
     if(oDoc!=nsnull)
     {
	  Distance ld;
	  PRInt32 distValue=0;

	  xpathUtil->SetDocument(oDoc);

	  nsCOMPtr<nsISupportsArray> nodeArr(nsnull);
	  nsCString xpath(".//a[@href]");
	  xpathUtil->GetSubNodes(node,xpath,getter_AddRefs(nodeArr));
	  if(nodeArr!=nsnull)
	  {
	       PRUint32 arrlen=0;
	       nodeArr->Count(&arrlen);
	       std::string lastUrl;
	       bool setinit=false;
	       LOG<<"urlcount:"<<arrlen<<"\n";
	       for(PRUint32 i=0;i<arrlen;i++)
	       {
		    nsCOMPtr<nsISupports> node;
		    nodeArr->GetElementAt(i,getter_AddRefs(node));
		    nsCOMPtr<nsIDOMElement> domele=do_QueryInterface(node);
		    nsString nsName=NS_ConvertUTF8toUTF16("href");
		    nsString nsValue;
		    if(domele!=nsnull)
		    {
			 domele->GetAttribute(nsName,nsValue);


			 if(!setinit)
			 {
			      lastUrl=std::string(NS_ConvertUTF16toUTF8(nsValue).get());
			      setinit=true;
			 }
			 else
			 {
			      std::string curUrl(NS_ConvertUTF16toUTF8(nsValue).get());

			      distValue+=ld.LD(lastUrl,curUrl);
			      LOG<<"last:"<<lastUrl<<"cururl:"<<curUrl<<"dist:"<<distValue<<"\n";
			      lastUrl=curUrl;
			 }
		    }
	       }
	       *_retval=distValue;
	  }else
	  {
	       *_retval=-1;
	  }
     }else
     {
	  *_retval=-1;
     }
     return NS_OK;
}

/* void GetALLDocumentArray (in nsIDOMDocument doc, in nsISupportsArray supArr); */
NS_IMETHODIMP nsDomAttUtil::GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray *supArr)
{
     nsresult rv = NS_OK;
     LOG << "Add doc:" << doc <<"\n";
     supArr->AppendElement(doc);
     nsCOMPtr<nsIXpathUtil> xu=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
     if (NS_FAILED(rv))
	  return rv;
     xu->SetDocument(doc);

     PRUint32 frmLen = 0;

     nsCOMPtr<nsISupportsArray> frmArr;
	

     nsCString xPath("//frame | //iframe");
     xu->GetNodes(xPath,getter_AddRefs(frmArr));
     frmArr->Count(&frmLen);
     if(frmLen > 0)
     {
	  for(PRUint32 i = 0; i < frmLen; i++)
	  {
	       nsCOMPtr<nsISupports> frmSup;
	       nsCOMPtr<nsIDOMNode> frmNode(nsnull);
	       nsString tagName;
	       string frmStr = "FRAME";
	       string ifrmStr = "IFRAME";
	       frmArr->GetElementAt(i,getter_AddRefs(frmSup));
	       frmNode = do_QueryInterface(frmSup);
	       frmNode->GetNodeName(tagName);

	       if(frmStr==std::string(NS_ConvertUTF16toUTF8(tagName).get()))
	       {
		    LOG << "frame tag is" << NS_ConvertUTF16toUTF8(tagName).get() <<"\n";
		    nsCOMPtr<nsIDOMHTMLFrameElement> frmEle= do_QueryInterface(frmSup);
		    nsCOMPtr<nsIDOMDocument> frmDoc;
		    frmEle->GetContentDocument(getter_AddRefs(frmDoc));

		    GetALLDocumentArray(frmDoc,supArr);
	       }
	       else if(ifrmStr==std::string(NS_ConvertUTF16toUTF8(tagName).get()))
	       {
		    LOG << "frame tag is" << NS_ConvertUTF16toUTF8(tagName).get() <<"\n";
		    nsCOMPtr<nsIDOMHTMLIFrameElement> ifrmEle = do_QueryInterface(frmSup);
		    nsCOMPtr<nsIDOMDocument> frmDoc;
		    ifrmEle->GetContentDocument(getter_AddRefs(frmDoc));
		    GetALLDocumentArray(frmDoc,supArr);
	       }
	  }
     }

     return rv;
}
/* void CalSibParentDist (in nsIDOMElement node, out double pDist, out double lDist); */
NS_IMETHODIMP nsDomAttUtil::CalSibParentDist(nsIDOMElement *node, double *pDist , double *lDist )
{
     double nsib,psib;
     std::map<std::string,std::string> nodemap;
     std::map<std::string,std::string> nsibmap;
     std::map<std::string,std::string> psibmap;
     std::map<std::string,std::string> parentmap;

     GetComLayoutInfo(node,nodemap);

     nsCOMPtr<nsIDOMNode> pSibNode;
     node->GetPreviousSibling(getter_AddRefs(pSibNode));
     PRUint16 tmptype=0;
     if(pSibNode!=nsnull)
	  pSibNode->GetNodeType(&tmptype);
     while(pSibNode!=nsnull&&tmptype!=nsIDOMNode::ELEMENT_NODE)
     {
	  pSibNode->GetPreviousSibling(getter_AddRefs(pSibNode));
	  if(pSibNode!=nsnull)
	       pSibNode->GetNodeType(&tmptype);
     }
     nsCOMPtr<nsIDOMElement> pSibEle=do_QueryInterface(pSibNode);
     if(pSibEle!=nsnull)
     {
	  GetComLayoutInfo(pSibEle,psibmap);
	  psib=compare_styles(nodemap, psibmap);
     }else
     {
	  psib=0;
     }
     nsCOMPtr<nsIDOMNode> nSibNode;
     node->GetNextSibling(getter_AddRefs(nSibNode));
     if(nSibNode!=nsnull)
	  nSibNode->GetNodeType(&tmptype);
     while(nSibNode!=nsnull&&tmptype!=nsIDOMNode::ELEMENT_NODE)
     {
	  nSibNode->GetNextSibling(getter_AddRefs(nSibNode));
	  if(nSibNode!=nsnull)
	       nSibNode->GetNodeType(&tmptype);
     }
     nsCOMPtr<nsIDOMElement> nSibEle=do_QueryInterface(nSibNode);
     if(nSibEle!=nsnull)
     {
	  GetComLayoutInfo(nSibEle,nsibmap);
	  nsib=compare_styles(nodemap, nsibmap);
     }else
     {
	  nsib=0;
     }
     if(nSibEle!=nsnull&&pSibEle!=nsnull)
     {
	  *lDist=(psib+nsib)/2;
     }else if(nSibEle==nsnull&&pSibEle==nsnull)
     {
	  *lDist=1;
     }
     else
     {
	  *lDist=psib+nsib;
     }
     nsCOMPtr<nsIDOMNode> pNode;
     node->GetParentNode(getter_AddRefs(pNode));
     nsCOMPtr<nsIDOMElement> pSEle=do_QueryInterface(pNode);

     GetComLayoutInfo(pSEle,parentmap);

     *pDist=compare_styles(nodemap, parentmap);
     return NS_OK;
}

/* void GetNodeBox (in nsIDOMElement node, out long x, out long y, out long w, out long h); */
NS_IMETHODIMP nsDomAttUtil::GetEleBox(nsIDOMElement *node, PRInt32 *x , PRInt32 *y , PRInt32 *w , PRInt32 *h )
{
     nsCOMPtr<nsIDOMDocument> oDoc(nsnull);
     if(node!=nsnull)
	  node->GetOwnerDocument(getter_AddRefs(oDoc));
     if(oDoc!=nsnull)
     {
	  nsCOMPtr<nsIDOMNSDocument> nsdoc=do_QueryInterface(oDoc);
	  nsCOMPtr<nsIBoxObject> box;
	  nsresult rv=nsdoc->GetBoxObjectFor(node,getter_AddRefs(box));
	  if (NS_FAILED(rv))
	  {
	       return rv;
	  }
	  PRInt32 m_x,m_y,m_h,m_w;
	  box->GetX(&m_x);
	  box->GetY(&m_y);
	  box->GetHeight(&m_h);
	  box->GetWidth(&m_w);
	  *x=m_x;
	  *y=m_y;
	  *w=m_w;
	  *h=m_h;
	  return NS_OK;
     }else
     {
	  return NS_ERROR_FAILURE;
     }
}
/* boolean IsLink (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::IsLink(nsIDOMNode *node, PRBool *_retval)
{
     nsresult rv;
     nsCString linkUrl;
     rv=GetLinkStr(node,0,linkUrl);
     if(linkUrl.Length()>0&&linkUrl.FindChar('#')<0)
	  *_retval=PR_TRUE;
     else
	  *_retval=PR_FALSE;
     return rv;
}
/* boolean IsLinkNotInCal (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::IsLinkNotInCal(nsIDOMNode *node, PRBool *_retval )
{
     PRBool bisLink=false;
     IsLink(node, &bisLink);
     if(bisLink)
     {
	  nsCString content;
	  GetNodeText(node, content);

	  int date=atoi(content.get());

	  if(content.Length()<3&&date>0&&date<31)
	       *_retval=PR_FALSE;
	  else
	       *_retval=PR_TRUE;
     }else
     {
	  *_retval=PR_FALSE;
     }


     return NS_OK;
}

/* AUTF8String GetLinkStr (in nsIDOMNode node, in short type); */
NS_IMETHODIMP nsDomAttUtil::GetLinkStr(nsIDOMNode *node, PRInt16 type, nsACString & _retval)
{
     nsString linkUrl;
     if(type==0)
     {

	  nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle=do_QueryInterface(node);
	  if(linkEle!=nsnull)
	  {
	       linkEle->GetHref(linkUrl);
	  }else
	  {
	       nsCOMPtr<nsIDOMHTMLLinkElement>  linkEle2=do_QueryInterface(node);
	       if(linkEle2!=nsnull)
	       {
		    linkEle2->GetHref(linkUrl);
	       }else
	       {
		    nsCOMPtr<nsIDOMHTMLAreaElement>  linkEle3=do_QueryInterface(node);

		    if(linkEle3!=nsnull)
		    {
			 PRBool herfdef=PR_FALSE;
			 linkEle3->GetNoHref(&herfdef);
			 if(!herfdef)
			      linkEle3->GetHref(linkUrl);
		    }
	       }
	  }
     }else if(type==1)
     {
	  nsCOMPtr<nsIDOMElement> domele=do_QueryInterface(node);
	  nsString nsName=NS_ConvertUTF8toUTF16("href");
	  if(domele!=nsnull)
	  {
	       domele->GetAttribute(nsName,linkUrl);
	  }
     }
     _retval=NS_ConvertUTF16toUTF8(linkUrl);
     return NS_OK;
}
/* long GetNodeArea (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeArea(nsIDOMNode *node, PRInt32 *_retval)
{
     PRInt32 x=0 ,y=0 ,w=0 ,h=0;
     nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(node);
     if(tmpEle!=nsnull)
	  GetEleBox(tmpEle,&x ,&y ,&w ,&h);
     *_retval=w*h;
     return NS_OK;
}
void nsDomAttUtil::GetComLayoutInfo(nsIDOMElement* node,std::map<std::string,std::string> &lmap)
{
     nsCOMPtr<nsIDOMDocument> oDoc(nsnull);
     if(node!=nsnull)
	  node->GetOwnerDocument(getter_AddRefs(oDoc));
     if(oDoc!=nsnull)
     {
	  nsCOMPtr<nsIDOMViewCSS> viewCSS(nsnull);
	  nsCOMPtr<nsIDOMDocumentView> domView = do_QueryInterface(oDoc);
	  if(domView!=nsnull)
	  {
	       nsCOMPtr<nsIDOMAbstractView> abstractView;
	       domView->GetDefaultView(getter_AddRefs(abstractView));
	       if(abstractView!=nsnull)
	       {
		    viewCSS=do_QueryInterface(abstractView);
	       }
	  }
	  if(viewCSS!=nsnull)
	  {
	       nsCOMPtr<nsIDOMCSSStyleDeclaration> style;
	       viewCSS->GetComputedStyle(node, EmptyString(),getter_AddRefs(style));
	       if(style!=nsnull)
	       {
		    PRUint32 slen;
		    style->GetLength(&slen);
		    nsString csstext;
		    style->GetCssText(csstext);
		    for(int j=0;j<slen;j++)
		    {
			 nsString name;
			 nsString value;
			 nsString prio;
			 style->Item(j,name);
			 style->GetPropertyValue(name,value);

			 std::string strName(NS_ConvertUTF16toUTF8(name).get());

			 std::map<std::string,std::string>::iterator fit=lmap.find(strName);
			 if(fit==lmap.end())
			 {
			      lmap.insert(make_pair(strName,std::string(NS_ConvertUTF16toUTF8(value).get())));
			 }
		    }
	       }
	  }
     }
}
