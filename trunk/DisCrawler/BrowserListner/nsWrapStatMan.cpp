#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsXPCOMGlue.h"
#include "nsIWebBrowser.h"
#include "nsWrapStatMan.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIWebNavigation.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMElement.h"
#include "nsISoapTask.h"
#include "nsISoapInter.h"
#include "nsIXSLTFetcher.h"
#include "nsIDocAtt.h"
#include "nsICluster.h"
#include "nsIVarGenerator.h"
#include "nsIAttDim.h"
#include "nsIAttSet.h"
#include "nsIClustModel.h"
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include "property.h"

NS_GENERIC_FACTORY_CONSTRUCTOR(nsWrapStatMan)

static nsModuleComponentInfo components[] =
{
     {
	  NS_WRAPSTATMAN_CLASSNAME,
	  NS_WRAPSTATMAN_CID,
	  NS_WRAPSTATMAN_CONTRACTID,
	  nsWrapStatManConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsWrapStatManModule", components)

nsWrapStatMan::nsWrapStatMan()
{
     /* member initializers and constructor code */
     nsresult rv;
     domUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
          LOG<<"nsDomAttUtil inti erroe!\n";;
     }
}

nsWrapStatMan::~nsWrapStatMan()
{
     /* destructor code */
}
NS_IMETHODIMP nsWrapStatMan::Excute()
{
     nsresult rv;
     PRInt32 wrapid;
     PRInt32 taskid;
     int MaxDoc;
     
     m_task->GetWrapid(&wrapid);

     m_task->GetTaskId(&taskid);
     nsCString wrapgen;
     m_inter->GetWrapGen(wrapid,wrapgen);
     LOG<<"wrapgen:"<<wrapgen.get();
     std::string wrapgenStr(wrapgen.get());	    
     std::map<std::string,std::string> parMap;
     GetParam(wrapgenStr, parMap);
     
     nsCOMPtr<nsIDocAtt> docAtt=nsnull;
     nsCOMPtr<nsICluster> cluster=nsnull;
     nsCOMPtr<nsIVarGenerator> generator=nsnull;
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
     std::map<int,nsIDOMDocument*> docMap;
     
     for(std::map<int,nsIWebBrowser *>::iterator it=bMap.begin();it!=bMap.end();++it)
     {
	  if(sMap[it->first]==FIN_DOC||sMap[it->first]==FINISH)
	  {
	       
	       nsCOMPtr<nsIWebNavigation> nav = do_QueryInterface(it->second);
	       nsIDOMDocument* domdoc;
	       rv=nav->GetDocument(&domdoc);
	       if (NS_FAILED(rv))
	       {
		    LOG<<"Get domnode Error:"<<std::hex<<rv<<std::endl;
		    continue;
	       }
	       nsCString DocText;
	       domUtil->GetDocText(domdoc,DocText);
	       
	       docMap.insert(std::make_pair(DocText.Length(),domdoc));
	       
	      
	  }
	 
     }
     int docCount=0;
     for(std::map<int,nsIDOMDocument*>::reverse_iterator it=docMap.rbegin();it!=docMap.rend();++it)
     {
	  LOG<<"Text length:"<<it->first;
	  docAtt->AddDocument(it->second);
	  docCount++;
	  if(docCount>=MaxDoc)
	       break;
     }
     
     if(docCount==0)
     {
	  nsCString tmpWrapper;
	  PRBool ret;
	  m_inter->UpdateWrapper(tmpWrapper,wrapid,taskid,&ret);
	  return NS_OK;
     }
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

     nsCString Wrapper;
     nsCString newWrapper;
     m_inter->GetWrapper(wrapid,Wrapper);
     if(Wrapper.Length()>0)
     {
		    
	  rv=fetcher->SetXsltDocStr(Wrapper);
	  if (NS_FAILED(rv)) 
	  {
	       LOG<<"Set Wrapper error!\n";
	       return rv;
	  }
	  PRUint32 varCount=0;
	  bool varChang=false;
	  fetcher->GetVarCount(&varCount);
	  for(int i=0;i<varCount;i++)
	  {
	       nsCString name;
	       nsCString value;
	       fetcher->GetVarByIndex(i,name,value);
		    
	       generator->GetVar(name,value);
		    
	       LOG<<"name:"<<name.get()<<"value:"<<value.get()<<"\n";
	       if(value.Length()>0)
	       {
		    varChang=true;
		    fetcher->SetXsltVar(name,value);
	       }
	  }
	  if(varChang)
	  {
	       fetcher->GetXsltDocStr(newWrapper);
	       LOG<<"wrapper:"<<newWrapper.get()<<"\n";
	  }
     }
     PRBool ret;
     m_inter->UpdateWrapper(newWrapper,wrapid,taskid,&ret);
     return NS_OK;
}
bool nsWrapStatMan::GetParam(const std::string& s, std::map<std::string,std::string>& map)
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
bool nsWrapStatMan::split(const std::string& s, std::string c,std::vector<std::string>& v)
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
