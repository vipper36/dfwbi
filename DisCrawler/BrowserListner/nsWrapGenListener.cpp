#include "nsWrapGenListener.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMNode.h"
#include "nsXPCOMGlue.h"
#include "nsIDOMDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsNetUtil.h"
#include "nsIDOMDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIAttDim.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include "nsICluster.h"
#include "property.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
/* Implementation file */

NS_GENERIC_FACTORY_CONSTRUCTOR(nsWrapGenListener)

static nsModuleComponentInfo components[] =
{
     {
	  NS_WRAPGENLISTENER_CLASSNAME, 
	  NS_WRAPGENLISTENER_CID,
	  NS_WRAPGENLISTENER_CONTRACTID,
	  nsWrapGenListenerConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsWrapGenListenerModule", components)

nsWrapGenListener::nsWrapGenListener()
:nsBrowserListener(),
     bodyCheckCount(0),
     task(nsnull),
     curIndex(0),
     Uid(0),
     MaxDoc(0),
     curCount(0)
{
     nsresult rv;
     
     inter=do_CreateInstance("@nyapc.com/XPCOM/nsSoapInter;1",&rv);
     if (NS_FAILED(rv)) 
     {

	  LOG<<"Init Soap Inter error\n";
     }
}

NS_IMETHODIMP nsWrapGenListener::GetUrl(nsACString &url)
{
     if(task==nsnull)
     {
	  LOG<<"Crawler id:"<<cid<<"\n";
	  inter->GetWrapTask(cid,MaxAccCount,getter_AddRefs(task));
	  if(task!=nsnull)
	  {
	       PRInt32 wrapid;
	       task->GetWrapid(&wrapid);
	       
	       
	       if(wrapid>0)
	       {
		    nsresult rv;
		    
		    nsCString wrapgen;
		    inter->GetWrapGen(wrapid,wrapgen);
		    LOG<<"wrapgen:"<<wrapgen.get();
		    std::string wrapgenStr(wrapgen.get());
		    
		    std::map<std::string,std::string> parMap;
		    GetParam(wrapgenStr, parMap);
		    std::map<std::string,std::string>::iterator fit=parMap.find("docatt");
		    if(fit!=parMap.end())
		    {
			 nsresult rv;
			 LOG<<"docatt:"<<fit->second<<"\n";
			 docAtt=do_CreateInstance(fit->second.c_str(),&rv);
			 if (NS_FAILED(rv)) 
			 {
			      LOG<<"Create docAtt error\n";
			      return rv;
			 }
		    }else
		    {
			 return NS_ERROR_FAILURE;
		    }
		    parMap.erase(fit);
		    
		    
		    fit=parMap.find("cluster");
		    if(fit!=parMap.end())
		    {
			 LOG<<"cluster:"<<fit->second<<"\n";
			 cluster=do_CreateInstance(fit->second.c_str(),&rv);
			 if (NS_FAILED(rv)) 
			 {
			      LOG<<"Create cluster error\n";
			      return rv;
			 }
		    }else
		    {
			 return NS_ERROR_FAILURE;
		    }
		    parMap.erase(fit);
		    
		    fit=parMap.find("generator");
		    if(fit!=parMap.end())
		    {
			 LOG<<"generator:"<<fit->second<<"\n";
			 generator=do_CreateInstance(fit->second.c_str(),&rv);
			 if (NS_FAILED(rv)) 
			 {
			      LOG<<"Create generator error\n";
			      return rv;
			 }
		    }else
		    {
			 return NS_ERROR_FAILURE;
		    }
		    parMap.erase(fit);

		    nsCOMPtr<nsIAttDim>  attdim=do_CreateInstance("@nyapc.com/XPCOM/nsAttDim;1",&rv);
		    if (NS_FAILED(rv)) 
		    {
			 LOG<<"Create AttDim error\n";
			 return rv;
		    }
		    

		    for(std::map<std::string,std::string>::iterator it=parMap.begin();it!=parMap.end();++it)
		    {
			 if(it->first=="doccount")
			      MaxDoc=atoi(it->second.c_str());
			 else if(it->first=="dim")
			 {
			      std::vector<std::string> dimvec;
			      split(it->second,";",dimvec);
			      PRInt32 i=0;
			      for(std::vector<std::string>::iterator it=dimvec.begin();it!=dimvec.end();++it,i++)
			      {
				   attdim->AddDim(i,nsCString(it->c_str()));
			      }
			      
			 }
			 else if(it->first=="classcount")
			 {
			      cluster->SetDoubleParam(nsCString("CLASS_COUNT"),atoi(it->second.c_str()));
			 }
			 else if(it->first=="similar_node_th")
			 {
			      cluster->SetDoubleParam(nsCString("similar_node_th"),atof(it->second.c_str()));
			 }
			 else if(it->first=="path_atts")
			 {
			      cluster->SetStringParam(nsCString("PATH_ATTS"),nsCString(it->second.c_str()));
			 }
			 else if(it->first=="res_path_atts")
			 {
			      generator->SetParam(nsCString("PATH_ATTS"),nsCString(it->second.c_str()));
			 }
			 
		    }
		    docAtt->SetDim(attdim);
		    PRInt32 dimlen=0;
		    attdim->GetCount(&dimlen);
		    cluster->SetDoubleParam(nsCString("ATTDIM"),dimlen);
		    generator->SetAttDim(attdim);
	       }
	       
	  }
	  
     }
     if(task!=nsnull)
     {
	  PRInt32 len;
	  task->GetUrlCount(&len);
	  LOG<<"urlcount:"<<len<<"curIndex:"<<curIndex<<"\n";
	  if(curIndex<len)
	  {
	       nsCString aurl;
	       
	       task->GetUrlByIndex(curIndex,&Uid,aurl);
	       LOG<<"cur UID:"<<Uid<<"url:"<<aurl.get()<<"\n";
	       url=aurl;
	       curIndex++;
	  }else
	  {
	       PRInt32 wrapid;
	       task->GetWrapid(&wrapid);
	       PRInt32 taskid;
	       task->GetTaskId(&taskid);
	       PRBool ret;
	       inter->UpdateWrapper(newWrapper,wrapid,taskid,&ret);
	  }
	  
     }
     
     return NS_OK;
}


NS_IMETHODIMP nsWrapGenListener::Excute(nsIWebNavigation *nav)
{
     nsresult rv=NS_OK;
     nsCOMPtr<nsIDOMDocument> domdoc;
     rv=nav->GetDocument(getter_AddRefs(domdoc));
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get domnode Error:"<<std::hex<<rv<<std::endl;
	  return rv;
     }
     domdoc->Normalize();
     nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(domdoc);
     nsString nsUrl;
     domhtml->GetURL(nsUrl);
     
     bool hasb=HasBody(domhtml);
     if(!hasb&&bodyCheckCount<3)
     {
	  bodyCheckCount++;
	  return NS_ERROR_FAILURE;
     }
     else if(hasb)
     {
	  LOG<<"Start Fetch.....\n";
	  LOG<<"current count:"<<curCount<<"\n";
	  LOG<<"max count:"<<MaxDoc<<"\n";
	  if(curCount<MaxDoc)
	  {
	       docAtt->AddDocument(domdoc);
	       curCount++;
	  }
	  if(curCount>=MaxDoc)
	  {
	       nsCOMPtr<nsIAttSet> attSet;
	       docAtt->GetResult(getter_AddRefs(attSet));
	       cluster->SetAtt(attSet);
	       cluster->CaculModel();
	       nsCOMPtr<nsIClustModel> model;
	       cluster->GetResultModel(getter_AddRefs(model));
	       
	       generator->SetModel(model);

	       generator->GenVar();

	       nsCOMPtr<nsIXSLTFetcher> fetcher=do_CreateInstance("@nyapc.com/XPCOM/nsXSLTFetcher;1",&rv);
	       if (NS_FAILED(rv)) 
	       {
		    LOG<<"Init Fetcher error!\n";
		    return rv;
	       }
	       PRInt32 wrapid;
	       task->GetWrapid(&wrapid);
	       
	       LOG<<"wrapid:"<<wrapid<<"\n";
	       nsCString Wrapper;
	       inter->GetWrapper(wrapid,Wrapper);
	       if(Wrapper.Length()>0)
	       {
		    
		    rv=fetcher->SetXsltDocStr(Wrapper);
		    if (NS_FAILED(rv)) 
		    {
			 LOG<<"Set Wrapper error!\n";
			 return rv;
		    }
		    PRUint32 varCount=0;
	       
		    fetcher->GetVarCount(&varCount);
		    for(int i=0;i<varCount;i++)
		    {
			 nsCString name;
			 nsCString value;
			 fetcher->GetVarByIndex(i,name,value);
		    
			 generator->GetVar(name,value);
		    
			 LOG<<"name:"<<name.get()<<"value:"<<value.get()<<"\n";
			 fetcher->SetXsltVar(name,value);
		    }
	       
		    fetcher->GetXsltDocStr(newWrapper);
		    LOG<<"wrapper:"<<newWrapper.get()<<"\n";
		    curIndex=20;
	       }
	       
	  }
	       
	  return NS_OK;
     }else
     {
	  bodyCheckCount=0;
	  return NS_ERROR_FAILURE;
	  
     }
}
bool nsWrapGenListener::GetParam(const std::string& s, std::map<std::string,std::string>& map)
{
     std::vector<std::string> params;
     split(s, "###",params);
     for(std::vector<std::string>::iterator it=params.begin();it!=params.end();++it)
     {
	  std::vector<std::string> pair;
	  split(*it, "=",pair);
	  map.insert(make_pair(pair[0],pair[1]));
     }
     return true;
}
bool nsWrapGenListener::split(const std::string& s, std::string c,std::vector<std::string>& v)
{
     std::string::size_type i = 0;
     std::string::size_type j = s.find(c);
     while (j != std::string::npos) {
	  v.push_back(s.substr(i, j-i));
	  i = j+c.length();
	  j = s.find(c, i);
	  if (j == std::string::npos)
	       v.push_back(s.substr(i, s.length( )));
     }
     return true;
}
