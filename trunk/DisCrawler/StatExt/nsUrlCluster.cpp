#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsUrlCluster.h"
#include "nsIAttSet.h"
#include "nsIAttVec.h"
#include "nsIDOMNode.h"
#include "nsIDOMDocument.h"
#include "nsIDOMHTMLDocument.h"
#include <limits.h>
#include <iostream>
#include <sstream>
#include <set>
#include "property.h"
#include "LayerCluster.h"
#include "nsIXpathUtil.h"
#include <KMlocal.h>

NS_IMPL_ISUPPORTS1(nsUrlCluster, nsICluster)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsUrlCluster)

static nsModuleComponentInfo components[] =
{
     {
	  NS_URLCLUSTER_CLASSNAME,
	  NS_URLCLUSTER_CID,
	
  NS_URLCLUSTER_CONTRACTID,
	  nsUrlClusterConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsUrlClusterModule", components)


nsUrlCluster::nsUrlCluster()
{
     nsresult rv;
     m_model=do_CreateInstance("@nyapc.com/XPCOM/nsClustModel;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"Init model error!\n";
     }
     domUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"nsDomAttUtil inti erroe!\n";;
     }
}

nsUrlCluster::~nsUrlCluster()
{
     /* destructor code */
}

/* void SetAtt (in nsIAttSet set); */
NS_IMETHODIMP nsUrlCluster::SetAtt(nsIAttSet *set)
{
    
     m_atts=set;
     return NS_OK;
}
/* void SetDoubleParam (in AUTF8String name, in double value); */
NS_IMETHODIMP nsUrlCluster::SetDoubleParam(const nsACString & name, double value)
{
     nsCString nsName(name);
     std::string nameStr(nsName.get());
     dParams.insert(make_pair(nameStr,value));
     return NS_OK;
}


/* void SetStringParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsUrlCluster::SetStringParam(const nsACString & name, const nsACString & value)
{
     nsCString nsName(name);
     nsCString nsValue(value);
     std::string nameStr(nsName.get());
     std::string valueStr(nsValue.get());
     sParams.insert(make_pair(nameStr,valueStr));
     return NS_OK;
}

/* void CaculModel (); */
NS_IMETHODIMP nsUrlCluster::CaculModel()
{
     int th_HIGH=int(dParams["THRESHOLD_HIGH"]);
     int th_LOW=int(dParams["THRESHOLD_LOW"]);
     string attnames=sParams["PATH_ATTS"];
     LOG<<"--------------------names:"<<attnames<<"\n";
     std::vector<std::string> nameVec;
     split(attnames, ";",nameVec);
     
     if(th_LOW==0)
	  th_LOW=3;
     if(th_HIGH==0)
	  th_HIGH=8;
     m_model->ClearModel();
     
     LayerCluster lc;
     PRInt32 attlen=0;     
     m_atts->GetLength(&attlen);
     std::set<std::string> duList;
     for(int i=0;i<attlen;i++)
     {
	  nsCOMPtr<nsIAttVec> vec(nsnull);
	  m_atts->GetVectorByIndex(i,getter_AddRefs(vec));
	  if(vec!=nsnull)
	  {
	       nsCOMPtr<nsIDOMNode> node(nsnull);
	       vec->GetNode(getter_AddRefs(node));
	       nsCOMPtr<nsIDOMDocument> doc;
               vec->GetDoc(getter_AddRefs(doc));
	       nsCOMPtr<nsIDOMHTMLDocument> html=do_QueryInterface(doc);
	       nsString docurl;
	       html->GetURL(docurl);
	       duList.insert(std::string(NS_ConvertUTF16toUTF8(docurl).get()));
	       if(node!=nsnull)
	       {
		    nsCString url;
		    domUtil->GetLinkStr(node,1,url);
		    if(url.Length()>0)
		    {
			 std::string urlStr(url.get());
			 lc.AddString(urlStr,i);
			 nsresult rv;
			 nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
			 if (NS_FAILED(rv))
			 {
			      continue;
			 }
			 for( std::vector<std::string>::iterator it=nameVec.begin();it!=nameVec.end();++it)
			 {
			      xpathUtil->AddAttName(nsCString(it->c_str()));
			 }
			 xpathUtil->SetDocument(doc);
			 nsCString xpath;
			 xpathUtil->GetXpath(node, 1,xpath);
			 std::string value(xpath.get());
			 lc.AddString(value,i);
		    }
	       }
	  }
     }
     lc.Cluster(th_HIGH,th_LOW);
     lc.printClass();
     for(std::set<std::string>::iterator it=duList.begin();it!=duList.end();++it)
       {
	 lc.ChangeCenter(*it);
       }
     lc.printClass();
     std::list<int> classid=lc.GetClassID();
     for (std::list<int>::iterator it=classid.begin(); it!=classid.end(); ++it) {

	  nsCOMPtr<nsIAttSet> classSet=do_CreateInstance("@nyapc.com/XPCOM/nsAttSet;1");

	  nsCOMPtr<nsIAttVec> cenVec=do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1");
	  std::list<int> classcon=lc.GetClassByID(*it);
	  if(cenVec!=nsnull)
	  {
	       nsCOMPtr<nsIAttVec> tmp(nsnull);
	       m_atts->GetVectorByIndex(*it,getter_AddRefs(tmp));
	       cenVec->SetVector(tmp);
	       cenVec->AddValue(0, lc.GetClassDist(*it));
	       cenVec->AddValue(1, classcon.size());
	  }
	  if(classSet!=nsnull)
	  {
	       for(std::list<int>::iterator cit=classcon.begin(); cit!=classcon.end(); ++cit)
	       {
		    nsCOMPtr<nsIAttVec> classVec(nsnull);
		    m_atts->GetVectorByIndex(*cit,getter_AddRefs(classVec));
		    nsCOMPtr<nsIAttVec> newVec=do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1");
		    if(newVec!=nsnull)
		    {
			 PRInt32 len=0;
			 classVec->GetLength(&len);
			 newVec->SetVector(classVec);
			 newVec->AddValue(len,lc.AttDist(*it,*cit));
			 classSet->AppendVector(newVec);
		    }
	       }
	  }
	  m_model->AppendClass(classSet, cenVec);
	  
     }
     return NS_OK;
}


/* nsIClustModel GetResultModel (); */
NS_IMETHODIMP nsUrlCluster::GetResultModel(nsIClustModel **_retval )
{
     *_retval=m_model;
     NS_ADDREF(*_retval);
     return NS_OK;
}

bool nsUrlCluster::split(const std::string& s, std::string c,std::vector<std::string>& v)
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
