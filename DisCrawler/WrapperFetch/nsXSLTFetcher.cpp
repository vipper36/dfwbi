#include "nsXSLTFetcher.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMXPathNSResolver.h"
#include "nsIDOMXPathExpression.h"
#include "nsIDOMXPathResult.h"
#include "nsNetUtil.h"
#include "nsIDOMElement.h"
#include "nsParserCIID.h"
#include "nsLayoutCID.h"
#include "nsIDOMParser.h"
#include "nsIXSLTProcessor.h"
#include "nsIDOMSerializer.h"
#include "nsIDOMXPathEvaluator.h"
#include "nsIChannel.h"
#include "nsIURI.h"
#include "nsIInputStream.h"
#include "nsIVariant.h"
#include "property.h"
#include <string>
#include <stack>
#include <set>

NS_IMPL_ISUPPORTS1(nsXSLTFetcher, nsIXSLTFetcher)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsXSLTFetcher)

static nsModuleComponentInfo components[] =
{
  {
    NS_XSLTFETCHER_CLASSNAME,
    NS_XSLTFETCHER_CID,
    NS_XSLTFETCHER_CONTRACTID,
    nsXSLTFetcherConstructor,
  }
};

NS_IMPL_NSGETMODULE("nsXSLTFetcherModule", components)



nsXSLTFetcher::nsXSLTFetcher()
:mXSLT(nsnull)
  ,mDoc(nsnull)
{
  /* member initializers and constructor code */
}

nsXSLTFetcher::~nsXSLTFetcher()
{
  /* destructor code */
}

/* void OpenXsltFile (in AUTF8String name); */
NS_IMETHODIMP nsXSLTFetcher::OpenXsltFile(const nsACString & name)
{
  nsresult rv=NS_OK;
  nsCOMPtr<nsIURI>             pURI;
  nsCOMPtr<nsIChannel>         pChannel;
  nsCOMPtr<nsIInputStream>     pInputStream;
  PRUint32                     xLength;

  rv = NS_NewURI( getter_AddRefs( pURI ),
		  name);
  if (NS_FAILED(rv)) 
    return rv;

  rv = NS_NewChannel( getter_AddRefs( pChannel ),
		      pURI,
		      nsnull,
		      nsnull );
  if (NS_FAILED(rv)) 
    return rv;

  rv = pChannel->Open( getter_AddRefs( pInputStream ) );
  if (NS_FAILED(rv)) 
    return rv;

  rv = pInputStream->Available(&xLength );
  if (NS_FAILED(rv)) 
    return rv;

  nsCOMPtr<nsIDOMParser> parser=do_CreateInstance(NS_DOMPARSER_CONTRACTID,&rv );
  if (NS_FAILED(rv))
    return rv;

  nsCOMPtr<nsIDOMDocument> tmpDoc(nsnull);
  rv = parser->ParseFromStream( pInputStream,
				"UTF-8",
				xLength,
				"application/xml",
				getter_AddRefs(tmpDoc) );
  if (NS_FAILED(rv))
    return rv;

  if(tmpDoc!=nsnull)
    {
      mXSLT=do_QueryInterface(tmpDoc);
      if(mXSLT!=nsnull)
	{
	  mXSLT->SetAsync(false);
	  rv=GetXsltVars(mVarMap);
	}
    }
  return rv;
}

/* void SetXsltDocStr (in AUTF8String content); */
NS_IMETHODIMP nsXSLTFetcher::SetXsltDocStr(const nsACString & content)
{
  nsresult rv=NS_OK;
  nsCOMPtr<nsIDOMParser> parser=do_CreateInstance(NS_DOMPARSER_CONTRACTID,&rv );
  if (NS_FAILED(rv))
    return rv;
  nsString str=NS_ConvertUTF8toUTF16(content);
  nsCOMPtr<nsIDOMDocument> tmpDoc(nsnull);
  rv = parser->ParseFromString(str.get(), "application/xml",getter_AddRefs(tmpDoc ) );
  if (NS_FAILED(rv))
    return rv;
  if(tmpDoc!=nsnull)
    {
      mXSLT=do_QueryInterface(tmpDoc);
      if(mXSLT!=nsnull)
	{
	  mXSLT->SetAsync(false);
	  rv=GetXsltVars(mVarMap);
	}
    }
  return rv;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsXSLTFetcher::SetDocument(nsIDOMDocument *doc)
{
  mDoc=doc;
  return NS_OK;
}

/* AUTF8String GetResultXML (); */
NS_IMETHODIMP nsXSLTFetcher::GetResultXML(nsACString & _retval )
{
  nsresult rv=NS_OK;
  nsCOMPtr<nsIXSLTProcessor> transformer =do_CreateInstance("@mozilla.org/document-transformer;1?type=xslt", &rv);
  if (NS_FAILED(rv))
    return rv;
  rv = transformer->ImportStylesheet(mXSLT);
  if (NS_FAILED(rv))
    return rv;
  for(std::map<std::string,std::string>::iterator it=mParMap.begin();it!=mParMap.end();++it)
    {
      //	  LOG<<"key:"<<it->first<<" value:"<<it->second<<"\n";
      nsCOMPtr<nsIWritableVariant> strData = do_CreateInstance("@mozilla.org/variant;1", &rv);
      nsString value=NS_ConvertUTF8toUTF16(it->second.c_str());
      nsString name=NS_ConvertUTF8toUTF16(it->first.c_str());
      nsString space=NS_ConvertUTF8toUTF16("");
      strData->SetAsAString(value);
	  
      transformer->SetParameter(space,name, strData);
	  
    }
  nsCOMPtr<nsIDOMDocument> resultDoc;
  rv = transformer->TransformToDocument(mDoc,getter_AddRefs(resultDoc));
  if (NS_FAILED(rv))
    return rv;
  nsCOMPtr<nsIDOMSerializer> ds =
    do_CreateInstance("@mozilla.org/xmlextras/xmlserializer;1",&rv);
  if (NS_FAILED(rv))
    return rv;
  nsCOMPtr<nsIDOMNode> docnode=do_QueryInterface(resultDoc);
  nsString retStr;
  ds->SerializeToString(docnode,retStr);
  _retval=NS_ConvertUTF16toUTF8(retStr);
  return NS_OK;
}
/* AUTF8String GetXsltVar (in AUTF8String name); */
NS_IMETHODIMP nsXSLTFetcher::GetXsltVar(const nsACString & name, nsACString & _retval )
{
  std::string nameStr(nsCString(name).get());
  std::map<std::string,nsIDOMNode*>::iterator fit=mVarMap.find(nameStr);
  if(fit!=mVarMap.end())
    {
      nsCOMPtr<nsIDOMElement> tmpele=do_QueryInterface(fit->second);
      nsString namevalue;
      nsString tmpname=NS_ConvertUTF8toUTF16("select"); 
      tmpele->GetAttribute(tmpname,namevalue);
      _retval=NS_ConvertUTF16toUTF8(namevalue);
    }
  return NS_OK;
}

/* void SetXsltVar (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsXSLTFetcher::SetXsltVar(const nsACString & name, const nsACString & value)
{
  std::string nameStr(nsCString(name).get());
  std::map<std::string,nsIDOMNode*>::iterator fit=mVarMap.find(nameStr);
  if(fit!=mVarMap.end())
    {
      nsCOMPtr<nsIDOMElement> tmpele=do_QueryInterface(fit->second);
      nsString tmpvalue=NS_ConvertUTF8toUTF16(value);
      nsString tmpname=NS_ConvertUTF8toUTF16("select");
      tmpele->SetAttribute(tmpname,tmpvalue);
    }
  return NS_OK;
}

/* AUTF8String GetXsltDocStr (); */
NS_IMETHODIMP nsXSLTFetcher::GetXsltDocStr(nsACString & _retval )
{
  nsresult rv=NS_OK;
  nsCOMPtr<nsIDOMSerializer> ds =
    do_CreateInstance(NS_XMLSERIALIZER_CONTRACTID,&rv);
  if (NS_FAILED(rv))
    return rv;
  nsCOMPtr<nsIDOMNode> docnode=do_QueryInterface(mXSLT);
  nsString retStr;
  ds->SerializeToString(docnode,retStr);
  _retval=NS_ConvertUTF16toUTF8(retStr);
  return NS_OK;
}
/* long GetVarCount (); */
NS_IMETHODIMP nsXSLTFetcher::GetVarCount(PRUint32 *_retval )
{
  *_retval=mVarMap.size();
  return NS_OK;
}

/* void GetVarByIndex (in long index, out AUTF8String name, out AUTF8String value); */
NS_IMETHODIMP nsXSLTFetcher::GetVarByIndex(PRInt32 index, nsACString & name , nsACString & value )
{
  std::map<std::string,nsIDOMNode*>::iterator it=mVarMap.begin();
  PRInt32 i=0;
  for(;i<index&&it!=mVarMap.end();i++,++it);
  if(i==index&&it!=mVarMap.end())
    {
      nsCOMPtr<nsIDOMElement> tmpele=do_QueryInterface(it->second);
      nsString selvalue;
      nsString namevalue;
      nsString namename=NS_ConvertUTF8toUTF16("name");
      nsString selname=NS_ConvertUTF8toUTF16("select");
      tmpele->GetAttribute(namename,namevalue);
      tmpele->GetAttribute(selname,selvalue);
      name=NS_ConvertUTF16toUTF8(namevalue);
      value=NS_ConvertUTF16toUTF8(selvalue);
    }
  return NS_OK;
}
NS_IMETHODIMP nsXSLTFetcher::GetXsltVars(std::map<std::string,nsIDOMNode*> &varMap)
{
  nsCString xpath("//xsl:variable");
  nsresult rv;
  nsCOMPtr<nsIDOMXPathEvaluator> xpathEV=do_QueryInterface(mXSLT,&rv);
  if (NS_FAILED(rv))
    {
      return rv;
    }

  nsCOMPtr<nsIDOMXPathNSResolver> resov;
	  
  nsCOMPtr<nsIDOMElement> docele;

  mXSLT->GetDocumentElement(getter_AddRefs(docele));
  nsCOMPtr<nsIDOMNode> elenode=do_QueryInterface(docele);

  
  xpathEV->CreateNSResolver(elenode,getter_AddRefs(resov));
	  
  nsCOMPtr<nsIDOMXPathExpression> expr;
     

  xpathEV->CreateExpression(NS_ConvertUTF8toUTF16(xpath),resov,getter_AddRefs(expr));

  nsCOMPtr<nsISupports> ret;
  LOG<<"expr:"<<expr<<" ele:"<<elenode<<"\n";
  if(expr!=nsnull)
    {
	  
      expr->Evaluate(elenode,0,nsnull,getter_AddRefs(ret));

      nsCOMPtr<nsIDOMXPathResult> exprresults=do_QueryInterface(ret);
      nsIDOMNode* anode=NULL;
      if(exprresults!=nsnull)
	{
	  do
	    {
	      exprresults->IterateNext(&anode);
	      if(anode!=NULL)
		{

		  nsCOMPtr<nsIDOMElement> tmpele=do_QueryInterface(anode);
		  nsString namevalue;
		  nsString tmpname=NS_ConvertUTF8toUTF16("name"); 
		  tmpele->GetAttribute(tmpname,namevalue);
		  std::string nameStr(NS_ConvertUTF16toUTF8(namevalue).get());
		  if(nameStr.length()>0)
		    {
		      varMap.insert(make_pair(nameStr,anode));
		    }
		}
	    }while(anode!=NULL);
	}
     }
     return NS_OK;
}
/* void SetXsltParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsXSLTFetcher::SetXsltParam(const nsACString & name, const nsACString & value)
{
     std::string keyStr(nsCString(name).get());
     std::string valueStr(nsCString(value).get());
//     LOG<<"key:"<<keyStr<<" value:"<<valueStr<<"\n";
     mParMap.insert(make_pair(keyStr,valueStr));
     return NS_OK;
}
