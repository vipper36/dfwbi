#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsChlVarGenerator.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsIDOMElement.h"
#include "nsISupports.h"
#include "nsIDOMDocument.h"
#include "nsIAttVec.h"
#include "nsIAttSet.h"
#include <iostream>
#include <sstream>
#include <stack>
#include <limits.h>
#include "math.h"
#include "property.h"
#include "StyleCompare.h"
#define VISUALAREA 1024*768

NS_IMPL_ISUPPORTS1(nsChlVarGenerator, nsIVarGenerator)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlVarGenerator)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLVARGENERATOR_CLASSNAME,
	  NS_CHLVARGENERATOR_CID,
	  NS_CHLVARGENERATOR_CONTRACTID,
	  nsChlVarGeneratorConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlVarGeneratorModule", components)



nsChlVarGenerator::nsChlVarGenerator()
{
     nsresult rv;
     dUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"Init nsDomAttUtil error!!";
     }
}

nsChlVarGenerator::~nsChlVarGenerator()
{
  /* destructor code */
}

/* void SetModel (in nsIClustModel model); */
NS_IMETHODIMP nsChlVarGenerator::SetModel(nsIClustModel *model)
{
     m_model=model;
     return NS_OK;
}

/* void GenVar (); */
NS_IMETHODIMP nsChlVarGenerator::GenVar()
{
     //Get the target class
     PRInt32 len=0;
     m_model->GetClassCount(&len);
     double maxValue=0;
     PRInt32 classid=-1;
     for(int i=0;i<len;i++)
     {
	  nsCOMPtr<nsIAttVec> vec(nsnull);
	  m_model->GetClassAtt(i, getter_AddRefs(vec) );
	  double attValue;
	  PRInt32 vlen=0;
	  vec->GetLength(&vlen);
	  for(int j=0;j<vlen;j++)
	  {
	       vec->GetValueByDim(j,&attValue);
	       LOG<<attValue;
	  }
	  LOG<<"\n";
	  vec->GetValueByDim(0,&attValue);
	  if(maxValue==0)
	  {
	       maxValue=attValue;
	       classid=i;
	  }else if(maxValue>attValue)
	  {
	       maxValue=attValue;
	       classid=i;
	  }
	  LOG<<"classid:"<<i<<"att:"<<attValue<<"\n";
     }
     LOG<<"classid:"<<classid<<"\n";
     if(classid>=0)
     {
	  nsCOMPtr<nsIAttSet> cset(nsnull);
	  m_model->GetClassSet(classid, getter_AddRefs(cset));
	  PRInt32 vlen=0;
	  cset->GetLength(&vlen);
	  int chose=-1;
	  double minatt=INT_MAX;
	  for(int i=0;i<vlen;i++)
	  {
	       nsCOMPtr<nsIAttVec> vec(nsnull);
	       cset->GetVectorByIndex(i, getter_AddRefs(vec));
	       double att;
	       LOG<<"vec:"<<i<<"\n";
	       bool rv=CaculAtt(vec,&att);
	       if(rv)
	       {
		    if(minatt>att)
		    {
			 minatt=att;
			 chose=i;
		    }
	       }else
	       {
		    continue;
	       }
	  }
	  LOG<<"chose:"<<chose<<"\n";
	  if(chose>=0)
	  {
	       nsCOMPtr<nsIAttVec> vec(nsnull);
	       cset->GetVectorByIndex(chose, getter_AddRefs(vec));
	       nsresult rv;
	       nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	       if (NS_FAILED(rv))
	       {
		    return rv;
	       }
	       nsCOMPtr<nsIDOMDocument> doc;
	       nsCOMPtr<nsIDOMNode> node;
	       vec->GetDoc(getter_AddRefs(doc));
	       vec->GetNode(getter_AddRefs(node));
	       xpathUtil->SetDocument(doc);
	       nsCString xpath;
	       xpathUtil->GetXpath(node, 1,xpath);
	       std::string name("box");
	       std::string value(xpath.get());
	       m_vars.insert(make_pair(name,value));
	  }
     }
     return NS_OK;
}
/* void SetParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsChlVarGenerator::SetParam(const nsACString & name, const nsACString & value)
{
     nsCString nsName(name);
     nsCString nsValue(value);
     m_parm.insert(make_pair(std::string(nsName.get()),std::string(nsValue.get())));
     return NS_OK;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsChlVarGenerator::SetAttDim(nsIAttDim *attdim)
{
    return NS_OK;
}

/* AUTF8String GetVar (in AUTF8String name); */
NS_IMETHODIMP nsChlVarGenerator::GetVar(const nsACString & name, nsACString & _retval)
{
     nsCString nsName(name);
     std::string nameStr(nsName.get());
     std::string valueStr=m_vars[nameStr];
     nsCString nsValue(valueStr.c_str());
     _retval=nsValue;
     return NS_OK;
}
bool nsChlVarGenerator::CaculAtt(nsIAttVec *vec,double *ret)
{
     nsCOMPtr<nsIDOMDocument> doc;
     nsCOMPtr<nsIDOMNode> node;
     vec->GetDoc(getter_AddRefs(doc));
     vec->GetNode(getter_AddRefs(node));
     PRInt32 nodeurlcont;
     PRInt32 docurlcont;
     nsCString nodeText;
     nsCString docText;
     PRInt32 urldist;
     PRInt32 docdist;
     dUtil->GetDocUrlCount(doc,&docurlcont);
     dUtil->GetNodeUrlCount(node,&nodeurlcont);
     dUtil->GetDocText(doc,docText);
     dUtil->GetNodeText(node,nodeText);

     dUtil->GetNodeUrlDistance(node,&urldist);
     dUtil->GetDocUrlDistance(doc,&docdist);
     
     PRInt32 x,y,w,h;
     nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(node);
     dUtil->GetEleBox(ele,&x,&y,&w,&h);
     
     nsCOMPtr<nsIDOMElement> docele;
     doc->GetDocumentElement(getter_AddRefs(docele));

     PRInt32 docx,docy,doch,docw;
     dUtil->GetEleBox(docele,&docx,&docy,&docw,&doch);
     

     //Get the element att for display! 
     nsIDOMElement* tele;
     CallQueryInterface(node,&tele);
     nsString nsName=NS_ConvertUTF8toUTF16("id");
     nsString nsValue;
     tele->GetAttribute(nsName,nsValue);
     LOG<<"class:"<<NS_ConvertUTF16toUTF8(nsValue).get()<<"\n";

     
     LOG<<nodeurlcont<<":"<<docurlcont<<":"<<nodeText.Length()<<":"<<docText.Length()<<":"<<urldist<<":"<<docdist<<"\n";
     if(nodeurlcont>0&&nodeText.Length()>0&&urldist>=0)
     {
	  double retValue=(docurlcont/nodeurlcont)*(double(nodeText.Length())/double(docText.Length())+double(urldist)/double(docdist)+double(w*h)/double(docw*doch));
	  LOG<<"retval:"<<retValue<<"\n";
	  *ret=retValue;
	  return true;
     }else 
     {
	  return false;
     }
}
