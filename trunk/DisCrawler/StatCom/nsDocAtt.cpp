#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMDocument.h"
#include "nsNetUtil.h"
#include "nsDocAtt.h"
#include "nsIAttVec.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMElement.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsISupports.h"
#include <iostream>
#include <sstream>
#include <stack>
#include "math.h"
#include "property.h"
#include "StyleCompare.h"
#define VISUALAREA 2000*2000

NS_IMPL_ISUPPORTS1(nsDocAtt, nsIDocAtt)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDocAtt)

static nsModuleComponentInfo components[] =
{
     {
	  NS_DOCATT_CLASSNAME,
	  NS_DOCATT_CID,
	  NS_DOCATT_CONTRACTID,
	  nsDocAttConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsDocAttModule", components)



nsDocAtt::nsDocAtt()
:m_docs(nsnull)
{
     nsresult rv;
     vset=do_CreateInstance("@nyapc.com/XPCOM/nsAttSet;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"nsAttSet inti erroe!\n";;
     }
     domUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"nsDomAttUtil inti erroe!\n";;
     }
}

nsDocAtt::~nsDocAtt()
{
     /* destructor code */
}
/* attribute nsIAttDim dim; */
NS_IMETHODIMP nsDocAtt::GetDim(nsIAttDim * *aDim)
{
     *aDim=vdim;
     NS_ADDREF(*aDim);
     return NS_OK;
}
NS_IMETHODIMP nsDocAtt::SetDim(nsIAttDim * aDim)
{
     vdim=aDim;
     return NS_OK;
}

/* void AddDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDocAtt::AddDocument(nsIDOMDocument *doc)
{
     if(doc!=nsnull)
     {
	  if(m_docs==nsnull)
	  {
	       nsresult rv;
	       m_docs=do_CreateInstance("@nyapc.com/XPCOM/nsDocSet;1",&rv);
	       if (NS_FAILED(rv))
	       {
		    return rv;
	       }
	  }
	  m_docs->AddDocument(doc);
	  GetBoxAtt(doc);
     }
     
     return NS_OK;
}
/* long GetVectorCount (); */
NS_IMETHODIMP nsDocAtt::GetVectorCount(PRInt32 *_retval )
{
     PRInt32 len=0;
     vset->GetLength(&len);
     *_retval=len;
     return NS_OK;
}

/* nsIAttVec GetVectorByIndex (in long index); */
NS_IMETHODIMP nsDocAtt::GetVectorByIndex(PRInt32 index, nsIAttVec **_retval )
{
     nsCOMPtr<nsIAttVec> res;
     vset->GetVectorByIndex(index,getter_AddRefs(res));
     *_retval=res;
     NS_ADDREF(*_retval);
     return NS_OK;
}

/* nsIAttSet GetResult (); */
NS_IMETHODIMP nsDocAtt::GetResult(nsIAttSet **_retval)
{
     int attlen;
     vset->GetLength(&attlen);
     for(int nPts=0;nPts<attlen;nPts++)
     {
	  nsCOMPtr<nsIAttVec> vec(nsnull);
	  vset->GetVectorByIndex(nPts,getter_AddRefs(vec));
	  nsIDOMDocument* doc;
	  nsIDOMNode* node;
	  vec->GetDoc(&doc);
	  vec->GetNode(&node);
	  LOG<<"doc:"<<doc<<"node:"<<node<<"\n";
     }
     *_retval=vset;
     NS_ADDREF(*_retval);
     return NS_OK;
}
bool nsDocAtt::GetBoxAtt(nsIDOMDocument *domdoc)
{
     nsresult rv=0;
     PRBool hsc=false ;
     
     nsCOMPtr<nsIDOMElement> docele;
     domdoc->GetDocumentElement(getter_AddRefs(docele));

     PRInt32 docx,docy,doch=0,docw=0;
     domUtil->GetEleBox(docele,&docx,&docy,&docw,&doch);
     if(docw < 1280)
	  docw=1280;
     if(doch<1024)
	  doch=1024;
     PRInt32 docArea=docw*doch;
     LOG<<"doc area:"<<docArea<<"docw:"<<docw<<"doch"<<doch<<"\n";
     nsCOMPtr<nsIXpathUtil> xu=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     xu->SetDocument(domdoc);
     nsCOMPtr<nsISupportsArray> nodeArr(nsnull);
     nsCString xpath("//*");
     xu->GetNodes(xpath, getter_AddRefs(nodeArr));
     if(nodeArr!=nsnull)
     {
	  PRUint32 arrlen=0;
	  nodeArr->Count(&arrlen);
	  LOG<<"node count:"<<arrlen<<"\n";
	  for(PRUint32 i=0;i<arrlen;i++)
	  {
	       nsCOMPtr<nsISupports> node;
	       nodeArr->GetElementAt(i,getter_AddRefs(node));
	       nsCOMPtr<nsIDOMNode> domnode=do_QueryInterface(node); 

	       nsIDOMElement* tele;
	       CallQueryInterface(domnode,&tele);
	       nsString nsName=NS_ConvertUTF8toUTF16("style");
	       nsString nsValue;
	       tele->GetAttribute(nsName,nsValue);
	       std::string valueStr(NS_ConvertUTF16toUTF8(nsValue).get());
	       if(valueStr=="display: none;")
	       {
		    tele->SetAttribute(nsName,NS_ConvertUTF8toUTF16(""));
	       }
	       if(tele!=nsnull)
	       {
		    
		    PRInt32 x,y,h,w;
		    domUtil->GetEleBox(tele,&x,&y,&w,&h);
		    if(h*w>0&&x>=0&&y>=0)
		    {
			 nsCOMPtr<nsIDOMNodeList> childList;
			 rv=tele->GetChildNodes(getter_AddRefs(childList));
			 PRUint32 length;
			 childList->GetLength(&length);
			 if(length>0)
			 {
			      double parent=0;
			      double ldist=0;
		    
			      domUtil->CalSibParentDist(tele,&parent,&ldist);
		    
			      int depth=-1;
			      domUtil->CalNodeDepth(domnode,&depth);
		    
			      nsCOMPtr<nsIAttVec> tmpV=do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1");
			      if(tmpV!=nsnull)
			      {
				   tmpV->SetDoc(domdoc);
				   tmpV->SetNode(domnode);
				   PRInt32 dimid=-1;
				   nsCString dimName("AREA_RATE");
				   LOG<<"Area rate:"<<(-log((double(w*h))/docArea)/5)<<"w:"<<w<<"h:"<<h<<"\n";
				   vdim->GetDimId(dimName,&dimid);
				   if(dimid>=0)
					tmpV->AddValue(dimid,-log((double(w*h))/docArea)/5);
				   dimid=-1;
				   dimName=nsCString("STYLE_PAR");
				   vdim->GetDimId(dimName,&dimid);
				   if(dimid>=0)
					tmpV->AddValue(dimid,parent);
				   dimid=-1;
				   dimName=nsCString("STYLE_SIB");
				   vdim->GetDimId(dimName,&dimid);
				   if(dimid>=0)
					tmpV->AddValue(dimid,ldist);
				   dimid=-1;
				   dimName=nsCString("DEPTH");
				   vdim->GetDimId(dimName,&dimid);
				   if(dimid>=0)
					tmpV->AddValue(dimid,log(depth)/2);
				   dimid=-1;
				   dimName=nsCString("WH_RATE");
				   vdim->GetDimId(dimName,&dimid);
				   if(dimid>=0)
					tmpV->AddValue(dimid,(double)w/double(h+w));
				   vset->AppendVector(tmpV);
				   
			      }
			 }
		    }
	       }
	  }
     }
     return true;
}





