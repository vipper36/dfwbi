#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsColVarGenerator.h"
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
#include "distance.h"
#include "LayerCluster.h"
#include "NodeTree.h"

NS_IMPL_ISUPPORTS1(nsColVarGenerator, nsIVarGenerator)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsColVarGenerator)

static nsModuleComponentInfo components[] =
{
     {
	  NS_COLVARGENERATOR_CLASSNAME,
	  NS_COLVARGENERATOR_CID,
	  NS_COLVARGENERATOR_CONTRACTID,
	  nsColVarGeneratorConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsColVarGeneratorModule", components)



nsColVarGenerator::nsColVarGenerator():m_attDim(nsnull)
{
     nsresult rv;
     dUtil=do_CreateInstance("@nyapc.com/XPCOM/nsDomAttUtil;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"Init nsDomAttUtil error!!";
     }
}

nsColVarGenerator::~nsColVarGenerator()
{
  /* destructor code */
}

/* void SetModel (in nsIClustModel model); */
NS_IMETHODIMP nsColVarGenerator::SetModel(nsIClustModel *model)
{
     m_model=model;
     return NS_OK;
}
/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsColVarGenerator::SetAttDim(nsIAttDim *attdim)
{
     m_attDim=attdim;
     return NS_OK;
}
/* void GenVar (); */
NS_IMETHODIMP nsColVarGenerator::GenVar()
{
     //Get the target class
     LOG<<"start gen!\n";
     string attnames=m_parm["PATH_ATTS"];
     LOG<<"--------------------names:"<<attnames<<"\n";
     std::vector<std::string> nameVec;
     if(attnames.length()>0)
	  split(attnames, ";",nameVec);

     PRInt32 len=0;
     m_model->GetClassCount(&len);
     double minValue=INT_MAX;
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
	  }
	  vec->GetValueByDim(0,&attValue);
	  if(minValue>attValue)
	  {
	       minValue=attValue;
	       classid=i;
	  }
	  LOG<<"classid:"<<i<<"att:"<<attValue<<"\n";
     }
     if(classid>=0)
     {
	  PRInt32 dim=0;
	  m_attDim->GetDimId(nsCString("AREA_RATE"),&dim);
	  nsCOMPtr<nsIAttSet> cset(nsnull);
	  m_model->GetClassSet(classid, getter_AddRefs(cset));
	  std::map<nsIDOMDocument*,NodeTree > blockMap;
	  
	  PRInt32 vlen=0;
	  cset->GetLength(&vlen);
	  for(int i=0;i<vlen;i++)
	  {
	       nsCOMPtr<nsIAttVec> cvec(nsnull);
	       cset->GetVectorByIndex(i, getter_AddRefs(cvec));
	       nsIDOMDocument* doc;
	       nsIDOMNode* node;
	       cvec->GetDoc(&doc);
	       cvec->GetNode(&node);
	       double area;
	       cvec->GetValueByDim(dim,&area);
	       std::map<nsIDOMDocument*,NodeTree >::iterator it=blockMap.find(doc);
	       if(it!=blockMap.end())
	       {
		    NodeTree tmp(node,area);
		    it->second.AddSub(tmp);
	       }else
	       {
		    NodeTree tmp;
		    NodeTree tmpsub(node,area);
		    tmp.AddSub(tmpsub);
		    blockMap.insert(make_pair(doc,tmp));
	       }
	  }

	  nsIDOMNode* boxnode=CaculAtt(blockMap);
	  if(boxnode!=nsnull)
	  {
	       nsresult rv;
	       
	       nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	       if (NS_FAILED(rv))
	       {
		    return rv;
	       }
	       for( std::vector<std::string>::iterator it=nameVec.begin();it!=nameVec.end();++it)
	       {
		    LOG<<"-----------------"<<*it<<"\n";
		    xpathUtil->AddAttName(nsCString(it->c_str()));
	       }

	       nsCOMPtr<nsIDOMDocument> domdoc;
	       boxnode->GetOwnerDocument(getter_AddRefs(domdoc));
	       xpathUtil->SetDocument(domdoc);

	       nsCString xpath;
	       xpathUtil->GetXpath(boxnode, 1,xpath);
	       std::string xpathStr(xpath.get());

	       std::string name("box");
	       m_vars.insert(make_pair(name,xpathStr));


	       LOG<<"start url cluster..."<<xpathStr<<"\n";
	       LayerCluster lc;
		    
	       nsCOMPtr<nsISupportsArray> urls(nsnull);
	       
	       nsCString hrefpath(".//a[@href]");
	       std::map<int,std::string> textMap;
	       int curIndex=0;
	       xpathUtil->GetSubNodes(boxnode,hrefpath,getter_AddRefs(urls));
	       if(urls!=nsnull)
	       {
		    PRUint32 urllen=0;
		    urls->Count(&urllen);
		    for(int j=0;j<urllen;j++)
		    {
			 nsCOMPtr<nsISupports> urlnode;
			 urls->GetElementAt(j,getter_AddRefs(urlnode));
			 nsCOMPtr<nsIDOMNode> domurlnode=do_QueryInterface(urlnode);
			 nsCString url;
			 dUtil->GetLinkStr(domurlnode,1,url);
			 if(url.Length()>0)
			 {
			      std::string urlStr(url.get());
			      lc.AddString(urlStr,curIndex);
			      
			      nsCString urlxpath;
			      xpathUtil->GetSubpath(boxnode,domurlnode,urlxpath);
			      std::string urlpathStr(urlxpath.get());
			      lc.AddString(urlpathStr,curIndex);
			      
			      nsCString textTitle;
			      dUtil->GetNodeText(domurlnode,textTitle);
			      textMap.insert(std::make_pair(curIndex,std::string(textTitle.get())));
			      
			      curIndex++;
			 }
		    }
		    
	       }
		    
	       lc.Cluster(3,5);
	       lc.printClass();
	  
	       std::list<int> classid=lc.GetClassID();
	       double maxAvr=INT_MIN;
	       int classindex=-1;
	       for (std::list<int>::iterator it=classid.begin(); it!=classid.end(); ++it) 
	       {
		    std::list<int> tmpclass=lc.GetClassByID(*it);

		    int classCount=tmpclass.size();
		    int sumCount=0;
		    
		    for(std::list<int>::iterator lit=tmpclass.begin();lit!=tmpclass.end();++lit)
		    {
			 sumCount+=textMap[*lit].length();
		    }
		    
		    if(maxAvr < double(sumCount)/double(classCount))
		    {
			 
			 maxAvr=double(sumCount)/double(classCount);
			 classindex=*it;
		    }
		    LOG<<"id:"<<*it<<":"<<classCount<<"max:"<<maxAvr<<"\n";
	       }
	       LOG<<"classid:"<<classindex<<"\n";
	       if(classindex>=0)
	       {
		    std::set<std::string> pathSet;
		    
		    std::list<int> classcon=lc.GetClassByID(classindex);
		    for (std::list<int>::iterator it=classcon.begin(); it!=classcon.end(); ++it) 
		    {
			 LOG<<"path:"<<*(lc.GetAtt(*it).rbegin())<<"\n";
			 pathSet.insert(*(lc.GetAtt(*it).rbegin()));
		    }
		    std::string subpath;
		    for(std::set<std::string>::iterator it=pathSet.begin();it!=pathSet.end();++it)
		    {
			 subpath+=*it;
			 std::set<std::string>::iterator tit=it;
			 ++tit;
			 if(tit!=pathSet.end())
			      subpath+="|";
		    }
		    LOG<<"sub:"<<subpath<<"\n";
		    if(subpath.length()>0)
		    {
			 std::string name("sub");
			 m_vars.insert(make_pair(name,subpath));
		    }
	       }
	  }
     }
     return NS_OK;
}
/* void SetParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsColVarGenerator::SetParam(const nsACString & name, const nsACString & value)
{
     nsCString nsName(name);
     nsCString nsValue(value);
     m_parm.insert(make_pair(std::string(nsName.get()),std::string(nsValue.get())));
     return NS_OK;
}

/* AUTF8String GetVar (in AUTF8String name); */
NS_IMETHODIMP nsColVarGenerator::GetVar(const nsACString & name, nsACString & _retval)
{
     nsCString nsName(name);
     std::string nameStr(nsName.get());
     std::string valueStr=m_vars[nameStr];
     nsCString nsValue(valueStr.c_str());
     _retval=nsValue;
     return NS_OK;
}
nsIDOMNode* nsColVarGenerator::CaculAtt(std::map<nsIDOMDocument*,NodeTree > &map)
{
     std::map<nsIDOMDocument*,std::list<nsIDOMNode*> > resmap;
     for(std::map<nsIDOMDocument*,NodeTree >::iterator it=map.begin();it!=map.end();++it)
     {
	  nsresult rv;
	  nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	  if (NS_FAILED(rv))
	  {
	       return nsnull;
	  }
	  
	  xpathUtil->SetDocument(it->first);
	  it->second.PrintTree(xpathUtil);
	  
	  LOG<<"-------------------------\n";
	  
	  it->second.ArrangeTree();

	  it->second.PrintTree(xpathUtil);
	  std::list<nsIDOMNode*> tmpList;
	  it->second.GetAll(tmpList);
	  resmap.insert(std::make_pair(it->first,tmpList));
     }
     std::list< std::map<std::string,nsIDOMNode*> > mapList;
     for(std::map<nsIDOMDocument*,std::list<nsIDOMNode*> >::iterator it=resmap.begin();it!=resmap.end();++it)
     {
	  std::map<std::string,nsIDOMNode*> nodemap;
	  nsresult rv;
	  nsCOMPtr<nsIXpathUtil> xpathUtil=do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1",&rv);
	  if (NS_FAILED(rv))
	  {
	       return nsnull;
	  }
	  
	  xpathUtil->SetDocument(it->first);
	  
	  for(std::list<nsIDOMNode*>::iterator jit=it->second.begin();jit!=it->second.end();++jit)
	  {
	       nsCString xpath;
	       xpathUtil->GetXpath(*jit, 1,xpath);
	       std::string xpathStr(xpath.get());
	       
	       nodemap.insert(make_pair(xpathStr,*jit));

	  }
	  mapList.push_back(nodemap);
     }

     Distance ld;
     std::list< std::map<std::string,nsIDOMNode*> >::iterator tit=mapList.begin();
     std::list< std::map<std::string,nsIDOMNode*> >::iterator mit=mapList.begin();
     ++mit;
     int maxDist=INT_MIN;
     std::map<std::string,nsIDOMNode*>::iterator rit=tit->end();
     for(;mit!=mapList.end();++mit)
     {
	  for(std::map<std::string,nsIDOMNode*>::iterator it=mit->begin();it!=mit->end();++it)
	  {
	       std::map<std::string,nsIDOMNode*>::iterator fit= tit->find(it->first);
	       LOG<<"path:"<<it->first<<"\n";
	       
	       if(fit!=tit->end())
	       {
		    nsCString text1;
		    dUtil->GetNodeText(it->second,text1);
		    std::string textStr1(text1.get());

		    nsCString text2;
		    dUtil->GetNodeText(fit->second,text2);
		    std::string textStr2(text2.get());

		    LOG<<"text1:"<<textStr1<<"\n";
		    LOG<<"text2:"<<textStr2<<"\n";
		    int tmp=0;
		    if((textStr2.length()+textStr1.length())>0)
		    {
			 tmp=ld.LD(textStr1,textStr2)*it->first.size();
			 LOG<<"dist:"<<tmp<<"\n";
			 double numRate=double(StrNumCount(textStr1)+StrNumCount(textStr2))/double(textStr1.length()+textStr2.length());
			 tmp=tmp*(1.0-numRate)*(1.0-numRate);
		    }
		    LOG<<"dist:"<<tmp<<"\n";
		    if(maxDist<tmp)
		    {
			 maxDist=tmp;
			 rit=fit;
		    }
	       }
	  }
     }
     if(rit!=tit->end())
     {
	  return rit->second;
     }else
     {
	  return nsnull;
     }
     
}
bool nsColVarGenerator::split(const std::string& s, std::string c,std::vector<std::string>& v)
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
int nsColVarGenerator::StrNumCount(std::string str)
{
     int ret=0;
     for(std::string::iterator it=str.begin();it!=str.end();++it)
     {
	  switch(*it)
	  {
	  case '0':
	  case '1':
	  case '2':
	  case '3':
	  case '4':
	  case '5':	  
	  case '6':
     	  case '7':
	  case '8':
	  case '9':
	       ret++;
	       break;
	  default:
	       break;
	  }
     }
     return ret;
}



