#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMHTMLDocument.h"
#include "nsNetUtil.h"
#include "nsChlVarGenerator_1.h"
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
#include "distance.h"
#include "StyleCompare.h"
#define VISUALAREA 1024*768

NS_IMPL_ISUPPORTS1(nsChlVarGenerator_1, nsIVarGenerator)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlVarGenerator_1)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLVARGENERATOR_1_CLASSNAME,
	  NS_CHLVARGENERATOR_1_CID,
	  NS_CHLVARGENERATOR_1_CONTRACTID,
	  nsChlVarGenerator_1Constructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlVarGenerator_1Module", components)



nsChlVarGenerator_1::nsChlVarGenerator_1()
{
     nsresult rv;
     dUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"Init nsDomAttUtil error!!";
     }
}

nsChlVarGenerator_1::~nsChlVarGenerator_1()
{
  /* destructor code */
}

/* void SetModel (in nsIClustModel model); */
NS_IMETHODIMP nsChlVarGenerator_1::SetModel(nsIClustModel *model)
{
     m_model=model;
     return NS_OK;
}

/* void GenVar (); */
NS_IMETHODIMP nsChlVarGenerator_1::GenVar()
{
     //Get the target class
     PRInt32 len=0;
     m_model->GetClassCount(&len);
     double minValue=INT_MAX;
     Distance ld;
     std::list<int> classids;
     for(int i=0;i<len;i++)
     {
	  nsCOMPtr<nsIAttVec> vec(nsnull);
	  m_model->GetClassAtt(i, getter_AddRefs(vec) );
	  nsCOMPtr<nsIDOMNode> node(nsnull);
	  vec->GetNode(getter_AddRefs(node));
	  nsCOMPtr<nsIDOMDocument> doc;
	  vec->GetDoc(getter_AddRefs(doc));
	  nsCOMPtr<nsIDOMHTMLDocument> html=do_QueryInterface(doc);
	  nsString docurl;
	  html->GetURL(docurl);
	  
	  nsCString url;
	  dUtil->GetLinkStr(node,0,url);
	 
	std::string urlStr(url.get());
	std::string docurlStr(NS_ConvertUTF16toUTF8(docurl).get());
	LOG<<"url:"<<urlStr<<"\n";
	LOG<<"docurl:"<<docurlStr<<"\n";
	  double tmp=ld.LD(urlStr,docurlStr);
	  LOG<<"START Value:"<<tmp<<"\n";
	  double attValue;
	  vec->GetValueByDim(0,&attValue);
	  tmp+=attValue;

	  LOG<<i<<"Second value:"<<tmp<<" Plus:"<<attValue<<"\n";
	  if(attValue==0)
	       continue;
	  vec->GetValueByDim(1,&attValue);
	  tmp-=log(attValue)/log(2);

	  LOG<<i<<"Third value:"<<tmp<<" SUB:"<<attValue<<"\n";
	  LOG<<i<<" minValue:"<<minValue<<"\n";
	  if(minValue>tmp)
	  {
	       classids.clear();
	       minValue=tmp;
	       classids.push_back(i);
	  }else if(fabs(minValue-tmp)<0.1)
	  {
	       classids.push_back(i);
	  }
	  
     }
     
     LOG<<"classid size:"<<classids.size()<<":"<<minValue<<"\n";
     if(!classids.empty())
     {
	  int MaxCount=INT_MIN;
	  int classid;
	  for(std::list<int>::iterator it=classids.begin();it!=classids.end();++it)
	  {
	       nsCOMPtr<nsIAttSet> cset(nsnull);
	       m_model->GetClassSet(*it, getter_AddRefs(cset));
	       PRInt32 tmplen=0;
	       cset->GetLength(&tmplen);
	       if(tmplen>MaxCount)
	       {
		    MaxCount=tmplen;
		    classid=*it;
	       }
	  }
	  LOG<<"classid"<<classid<<"\n";
	  nsCOMPtr<nsIAttSet> cset(nsnull);
	  m_model->GetClassSet(classid, getter_AddRefs(cset));
	  PRInt32 vlen=0;
	  cset->GetLength(&vlen);
	  int chose=-1;
	  double minatt=INT_MAX;
	  
	  string attnames=m_parm["PATH_ATTS"];
	  LOG<<"--------------------names:"<<attnames<<"\n";
	  std::vector<std::string> nameVec;
	  if(attnames.length()>0)
	       split(attnames, ";",nameVec);
	  
	  std::set<std::string> xpaths;
	  for(int i=0;i<vlen;i++)
	  {
	       nsCOMPtr<nsIAttVec> vec(nsnull);
	       cset->GetVectorByIndex(i, getter_AddRefs(vec));
	       nsresult rv;
	       nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	       if (NS_FAILED(rv))
	       {
		    continue;
	       }
	       for( std::vector<std::string>::iterator it=nameVec.begin();it!=nameVec.end();++it)
	       {
		    LOG<<"-----------------"<<*it<<"\n";
		    xpathUtil->AddAttName(nsCString(it->c_str()));
	       }
	       nsCOMPtr<nsIDOMDocument> doc;
	       nsCOMPtr<nsIDOMNode> node;
	       vec->GetDoc(getter_AddRefs(doc));
	       vec->GetNode(getter_AddRefs(node));
	       xpathUtil->SetDocument(doc);
	       nsCString xpath;
	       xpathUtil->GetXpath(node, 1,xpath);
	       xpaths.insert(std::string(xpath.get()));
	  }
	  std::string name("box");
	  std::string value;
	  for(std::set<std::string>::iterator it=xpaths.begin();it!=xpaths.end();++it)
	  {
	       value+=*it;
	       std::set<std::string>::iterator tit=it;
	       ++tit;
	       if(tit!=xpaths.end())
		    value+="|";
	  }
		    
	  m_vars.insert(make_pair(name,value));
     }
     return NS_OK;
}
/* void GenVar (); */
// NS_IMETHODIMP nsChlVarGenerator_1::GenVar()
// {
//      //Get the target class
//      PRInt32 len=0;
//      m_model->GetClassCount(&len);
//      double minValue=INT_MAX;
//      Distance ld;
//      std::list<int> classids;
//      for(int i=0;i<len;i++)
//      {
// 	  nsCOMPtr<nsIAttVec> vec(nsnull);
// 	  m_model->GetClassAtt(i, getter_AddRefs(vec) );
// 	  nsCOMPtr<nsIDOMNode> node(nsnull);
// 	  vec->GetNode(getter_AddRefs(node));
// 	  nsCOMPtr<nsIDOMDocument> doc;
// 	  vec->GetDoc(getter_AddRefs(doc));
// 	  nsCOMPtr<nsIDOMHTMLDocument> html=do_QueryInterface(doc);
// 	  nsString docurl;
// 	  html->GetURL(docurl);
	  
// 	  nsCString url;
// 	  dUtil->GetLinkStr(node,0,url);
	  
// 	  double docUrlDist=ld.LD(url.get(),NS_ConvertUTF16toUTF8(docurl).get());


// 	  nsCOMPtr<nsIAttSet> cset(nsnull);
// 	  m_model->GetClassSet(i, getter_AddRefs(cset));
	  
// 	  PRInt32 vlen=0;
// 	  cset->GetLength(&vlen);
// 	  std::set<nsIDOMNode*> nodeSet;

// 	  for(int j=0;j<vlen;j++)
// 	  {
// 	       nsCOMPtr<nsIAttVec> cvec(nsnull);
// 	       cset->GetVectorByIndex(j, getter_AddRefs(cvec));
// 	       nsIDOMNode *cnode;
// 	       cvec->GetNode(&cnode);
// 	       nodeSet.insert(cnode);
// 	  }

// 	  nsIDOMNode *ancest=GetParent(nodeSet);
// 	  LOG<<i<<" ancest:"<<ancest<<"\n";
// 	  PRInt32 anLen;
// 	  double AreaRate=0;

// 	  dUtil->GetNodeUrlCount(ancest, &anLen);
// 	  if(anLen!=nodeSet.size())
// 	       continue;
// 	  else
// 	  {
// 	       PRInt32 x ,y ,w ,h;
// 	       nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(ancest);
// 	       dUtil->GetEleBox(tmpEle,&x ,&y ,&w ,&h);
// 	       double eleArea=w*h;
// 	       nsCOMPtr<nsIDOMDocument> tmpDoc;
// 	       ancest->GetOwnerDocument(getter_AddRefs(tmpDoc));
// 	       nsCOMPtr<nsIDOMElement> docEle;
// 	       tmpDoc->GetDocumentElement(getter_AddRefs(docEle));
// 	       dUtil->GetEleBox(docEle,&x ,&y ,&w ,&h);
// 	       double docArea=w*h;
// 	       AreaRate=pow(10,eleArea/docArea);
// 	  }
	  
// 	  LOG<<i<<" value:"<<docUrlDist<<":"<<AreaRate<<"\n";
// 	  if(minValue>docUrlDist+AreaRate)
// 	  {
// 	       classids.clear();
// 	       minValue=docUrlDist+AreaRate;
// 	       classids.push_back(i);
// 	  }else if(fabs(minValue-(docUrlDist+AreaRate))<0.1)
// 	  {
// 	       classids.push_back(i);
// 	  }
	  
//      }
     
//      LOG<<"classid size:"<<classids.size()<<":"<<minValue<<"\n";
//      if(!classids.empty())
//      {
// 	  int MaxCount=INT_MIN;
// 	  int classid;
// 	  for(std::list<int>::iterator it=classids.begin();it!=classids.end();++it)
// 	  {
// 	       nsCOMPtr<nsIAttSet> cset(nsnull);
// 	       m_model->GetClassSet(*it, getter_AddRefs(cset));
// 	       PRInt32 tmplen=0;
// 	       cset->GetLength(&tmplen);
// 	       if(tmplen>MaxCount)
// 	       {
// 		    MaxCount=tmplen;
// 		    classid=*it;
// 	       }
// 	  }
// 	  LOG<<"classid"<<classid<<"\n";
// 	  nsCOMPtr<nsIAttSet> cset(nsnull);
// 	  m_model->GetClassSet(classid, getter_AddRefs(cset));
// 	  PRInt32 vlen=0;
// 	  cset->GetLength(&vlen);
// 	  int chose=-1;
// 	  double minatt=INT_MAX;
// 	  std::set<std::string> xpaths;
// 	  for(int i=0;i<vlen;i++)
// 	  {
// 	       nsCOMPtr<nsIAttVec> vec(nsnull);
// 	       cset->GetVectorByIndex(i, getter_AddRefs(vec));
// 	       nsresult rv;
// 	       nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
// 	       if (NS_FAILED(rv))
// 	       {
// 		    continue;
// 	       }
// 	       nsCOMPtr<nsIDOMDocument> doc;
// 	       nsCOMPtr<nsIDOMNode> node;
// 	       vec->GetDoc(getter_AddRefs(doc));
// 	       vec->GetNode(getter_AddRefs(node));
// 	       xpathUtil->SetDocument(doc);
// 	       nsCString xpath;
// 	       xpathUtil->GetXpath(node, 1,xpath);
// 	       xpaths.insert(std::string(xpath.get()));
// 	  }
// 	  std::string name("box");
// 	  std::string value;
// 	  for(std::set<std::string>::iterator it=xpaths.begin();it!=xpaths.end();++it)
// 	  {
// 	       value+=*it;
// 	       std::set<std::string>::iterator tit=it;
// 	       ++tit;
// 	       if(tit!=xpaths.end())
// 		    value+="|";
// 	  }
		    
// 	  m_vars.insert(make_pair(name,value));
//      }
//      return NS_OK;
// }
/* void SetParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsChlVarGenerator_1::SetParam(const nsACString & name, const nsACString & value)
{
     nsCString nsName(name);
     nsCString nsValue(value);
     m_parm.insert(make_pair(std::string(nsName.get()),std::string(nsValue.get())));
     return NS_OK;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsChlVarGenerator_1::SetAttDim(nsIAttDim *attdim)
{
    return NS_OK;
}

/* AUTF8String GetVar (in AUTF8String name); */
NS_IMETHODIMP nsChlVarGenerator_1::GetVar(const nsACString & name, nsACString & _retval)
{
     nsCString nsName(name);
     std::string nameStr(nsName.get());
     std::string valueStr=m_vars[nameStr];
     nsCString nsValue(valueStr.c_str());
     _retval=nsValue;
     return NS_OK;
}
nsIDOMNode *nsChlVarGenerator_1::GetParent(std::set<nsIDOMNode*> nodeSet)
{
     
     PRInt32 depth;
     std::set<nsIDOMNode*> trgSet;
     std::set<nsIDOMNode*>::iterator it=nodeSet.begin();
     dUtil->CalNodeDepth(*it, &depth );
     trgSet.insert(*it);
     ++it;
     for(;it!=nodeSet.end();++it)
     {
	  PRInt32 tmpdep;
	  dUtil->CalNodeDepth(*it, &tmpdep );
	  nsIDOMNode* par=*it;
	  for(int i=0;i<tmpdep-depth;i++)
	       par->GetParentNode(&par);
	  trgSet.insert(par);
     }
     while(trgSet.size()>1&&*(trgSet.begin())!=nsnull)
     {
	  std::set<nsIDOMNode*> trgSet1;
	  for(std::set<nsIDOMNode*>::iterator tit=trgSet.begin();tit!=trgSet.end();++tit)
	  {
	       nsIDOMNode* par;
	       (*tit)->GetParentNode(&par);
	       trgSet1.insert(par);
	  }
	  trgSet=trgSet1;
     }
     it=trgSet.begin();
     return (*it);
}

bool nsChlVarGenerator_1::split(const std::string& s, std::string c,std::vector<std::string>& v)
{
     std::string::size_type i = 0;
     std::string::size_type j = s.find(c);
     while (j != std::string::npos) 
     {
	  v.push_back(s.substr(i, j-i));
	  i = j+c.length();
	  j = s.find(c, i);
     }
     if(j == std::string::npos)
     {
	  std::string tmp=s.substr(i, s.length( ));
	  if(tmp.length()>0)
	       v.push_back(tmp);
     }
     return true;
}
