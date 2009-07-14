#include "nsIDXCreator.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIParser.h"
#include "nsParserCIID.h"
#include "nsContentCID.h"
#include "nsNetUtil.h"
#include "nsIHTMLToTextSink.h"
#include "nsIContentSink.h"
#include "nsIScriptSecurityManager.h"
#include "nsIPrincipal.h"
#include "nsIVariant.h"
#include <iostream>
#include "property.h"
static NS_DEFINE_CID(kParserCID, NS_PARSER_CID);
static NS_DEFINE_CID(kHTMLToTextSinkCID,NS_PLAINTEXTSERIALIZER_CID);
static NS_DEFINE_CID(kXMLHttpRequestCID,NS_XMLHTTPREQUEST_CID);


NS_IMPL_ISUPPORTS1(nsIDXCreator, nsIIDXCreator)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsIDXCreator)

static nsModuleComponentInfo components[] =
{
     {
	  NS_IDXCREATOR_CLASSNAME, 
	  NS_IDXCREATOR_CID,
	  NS_IDXCREATOR_CONTRACTID,
	  nsIDXCreatorConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsIDXCreatorModule", components)

nsIDXCreator::nsIDXCreator()
{
  /* member initializers and constructor code */
     nsresult rv;
     req=do_CreateInstance(kXMLHttpRequestCID, &rv);
     if (NS_FAILED(rv))
     {
	  std::cout<<"create XMPrequest Error:"<<std::hex<<rv<<std::endl;
	  return;
     }
     nsCOMPtr<nsIScriptSecurityManager> secMan = do_GetService(NS_SCRIPTSECURITYMANAGER_CONTRACTID);
     nsCOMPtr<nsIPrincipal> systemPrincipal;
    rv = secMan->GetSystemPrincipal(getter_AddRefs(systemPrincipal));
    if (NS_FAILED(rv))
    {
        std::cout<<"create nsIPrincipal Error:"<<std::hex<<rv<<std::endl;
	  return;
    }

     req->Init(systemPrincipal,nsnull,nsnull);
}

nsIDXCreator::~nsIDXCreator()
{
  /* destructor code */
}
/*convert html to text*/
void
nsIDXCreator::ConvertBufToPlainText(nsString &aConBuf)
{
     nsresult rv=0;
     nsCOMPtr<nsIParser> parser(do_CreateInstance(kParserCID, &rv));
     if (NS_FAILED(rv))
     {
	  std::cout<<"create parse Error:"<<std::hex<<rv<<std::endl;
	  return;
     }
     nsCOMPtr<nsIContentSink> sink(do_CreateInstance(kHTMLToTextSinkCID,&rv)); 
     if (NS_FAILED(rv))
     {
	  std::cout<<"create parse Error:"<<std::hex<<rv<<std::endl;
	  return;
     }
     if (sink) {
	  nsCOMPtr<nsIHTMLToTextSink> textSink(do_QueryInterface(sink));
	  if (textSink) {
	       nsAutoString convertedText;
	       textSink->Initialize(&convertedText, 0, 72);
	       parser->SetContentSink(sink);
	       parser->Parse(aConBuf, 0, NS_LITERAL_CSTRING("text/html"), PR_TRUE);
	       aConBuf = convertedText;
	  }
     }
}

/* void SetReference (in AUTF8String refer); */
NS_IMETHODIMP nsIDXCreator::SetReference(const nsACString & refer)
{
     mReference=nsCString(refer);
    return NS_OK;
}
/* void SetTitle (in AUTF8String title); */
NS_IMETHODIMP nsIDXCreator::SetTitle(const nsACString & title)
{
     mTitle=nsCString(title);
    return NS_OK;
}

/* void SetDate (in AUTF8String date); */
NS_IMETHODIMP nsIDXCreator::SetDate(const nsACString & date)
{
     mDate=nsCString(date);
    return NS_OK;
}

/* void SetField (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsIDXCreator::SetField(const nsACString & name, const nsACString & value)
{
     nsCString _key(name);
     nsCString _value(value);
     mField.push_back(std::make_pair(_key,_value));
     return NS_OK;
}

/* void SetDB (out AUTF8String db); */
NS_IMETHODIMP nsIDXCreator::SetDB(const nsACString & db)
{
     mDbName=nsCString(db);
     return NS_OK;
}

/* void SetContent (out AUTF8String htmlContent); */
NS_IMETHODIMP nsIDXCreator::SetContent(const nsACString & htmlContent)
{
     nsString inContent=NS_ConvertUTF8toUTF16(htmlContent);
     ConvertBufToPlainText(inContent);
     mContent=NS_ConvertUTF16toUTF8(inContent);
     return NS_OK;
}
/* void GetIDX (out AUTF8String idx); */
NS_IMETHODIMP nsIDXCreator::GetIDX(nsACString & idx)
{
     nsCString _retIdx;
     _retIdx.Append("#DREREFERENCE ");
     _retIdx.Append(mReference);
     _retIdx.Append("\n");
     _retIdx.Append("#DRETITLE ");
     _retIdx.Append(mTitle);
     _retIdx.Append("\n");
     _retIdx.Append("#DREDATE ");
     _retIdx.Append(mDate);
     _retIdx.Append("\n");
     std::list< std::pair<nsCString,nsCString> >::iterator itr=mField.begin();
     for(;itr!=mField.end();++itr)
     {
	  _retIdx.Append("#DREFIELD ");
	  _retIdx.Append(itr->first);
	  _retIdx.Append("=\"");
	  _retIdx.Append(itr->second);
	  _retIdx.Append("\"");
	  _retIdx.Append("\n");
     }
     _retIdx.Append("#DREDBNAME ");
     _retIdx.Append(mDbName);
     _retIdx.Append("\n");
     _retIdx.Append("#DRECONTENT");
     _retIdx.Append("\n");
     _retIdx.Append(mContent);
     _retIdx.Append("\n");
     _retIdx.Append("#DREENDDOC\n");
     _retIdx.Append("#DREENDDATA\n\n");
     idx=_retIdx;
     return NS_OK;
}
/* void SendIDX (in AUTF8String url); */
NS_IMETHODIMP nsIDXCreator::SendIDX(const nsACString & url)
{
      nsresult rv = req->OverrideMimeType(NS_LITERAL_CSTRING("text/xml"));
      if (NS_FAILED(rv)) {
	   return rv;
      }
      const nsAString& empty = EmptyString();
      rv=req->OpenRequest(nsCString("POST"),url,PR_TRUE,empty,empty);
      if (NS_FAILED(rv)) {
	   LOG<<"Open request Error:"<<rv<<"\n";
	   return rv;
      }
      nsCString content;
      GetIDX(content);
      nsCOMPtr<nsIWritableVariant> wv=do_CreateInstance("@mozilla.org/variant;1",&rv);
      if (NS_FAILED(rv))
      {
	   LOG<<"create nsIWritableVariant Error:"<<rv<<"\n";
	   return rv;
      }
      wv->SetAsAUTF8String(content);
      rv=req->Send(wv);
      if (NS_FAILED(rv)) {
	   LOG<<"Send Error:"<<rv<<"\n";
	   return rv;
      }
      //PRUint32 stat=0;
      //req->GetStatus(&stat);
      //LOG<<"stat:"<<stat<<"\n";
      return NS_OK;
}

/* End of implementation class template. */
