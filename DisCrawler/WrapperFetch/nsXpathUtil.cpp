#include "nsXpathUtil.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsIDOMXPathNSResolver.h"
#include "nsIDOMXPathExpression.h"
#include "nsIDOMXPathResult.h"
#include "nsIDOMElement.h"
#include "nsIDOMNamedNodeMap.h"
#include "property.h"
#include <string>
#include <stack>
NS_IMPL_ISUPPORTS1(nsXpathUtil, nsIXpathUtil)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsXpathUtil)

static nsModuleComponentInfo components[] =
{
  {
    NS_XPATHUTIL_CLASSNAME,
    NS_XPATHUTIL_CID,
    NS_XPATHUTIL_CONTRACTID,
    nsXpathUtilConstructor,
  }
};
NS_IMPL_NSGETMODULE("nsXpathUtilModule", components)
void toLower(std::basic_string<char>& s) {
  for (std::basic_string<char>::iterator p = s.begin( );p != s.end( ); ++p) 
    {
      *p = tolower(*p);
    }
}
nsXpathUtil::nsXpathUtil()
{
  /* member initializers and constructor code */
}

nsXpathUtil::~nsXpathUtil()
{
  /* destructor code */
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsXpathUtil::SetDocument(nsIDOMDocument *doc)
{
  nsresult rv=NS_OK;
  mDoc=doc;
  if(mDoc!=nsnull)
    {
      xpathEV=do_QueryInterface(mDoc,&rv);
      if (NS_FAILED(rv))
	{
	  LOG<<"Get evaluator Error:"<<rv<<std::endl;
	}
    }
  return rv;
}

/* AUTF8String GetXpath (in nsIDOMNode node); */
NS_IMETHODIMP nsXpathUtil::GetXpath(nsIDOMNode *node, PRInt16 type,nsACString & _retval)
{
  std::string xpath;
  if(type==0)
    xpath=CalXpath(node);
  else if(type==1)
    xpath=CalXpathABS(node);
  _retval=nsCString(xpath.c_str());
  return NS_OK;
}

/* void GetNodes (in AUTF8String xpath, out nsISupportsArray nodes); */
NS_IMETHODIMP nsXpathUtil::GetNodes(const nsACString & xpath, nsISupportsArray **nodes)
{
  nsresult rv;
  nsCOMPtr<nsISupportsArray> result = do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
  if (NS_FAILED(rv))
    return rv;
  nsCOMPtr<nsIDOMXPathNSResolver> resov;
	  
  nsCOMPtr<nsIDOMElement> docele;
     
  mDoc->GetDocumentElement(getter_AddRefs(docele));

  nsCOMPtr<nsIDOMNode> elenode=do_QueryInterface(docele);

  
  xpathEV->CreateNSResolver(elenode,getter_AddRefs(resov));
	  
  nsCOMPtr<nsIDOMXPathExpression> expr(nsnull);
     
  xpathEV->CreateExpression(NS_ConvertUTF8toUTF16(xpath),resov,getter_AddRefs(expr));
  if(expr!=nsnull)
    {
      nsCOMPtr<nsISupports> ret;
      expr->Evaluate(elenode,0,nsnull,getter_AddRefs(ret));
     
      nsCOMPtr<nsIDOMXPathResult> exprresults=do_QueryInterface(ret);
	  
      if(exprresults!=nsnull)
	{
	  nsIDOMNode* anode=nsnull;
	  do
	    {
	      exprresults->IterateNext(&anode);
	      if(anode!=nsnull)
		{
		  nsISupports *tmp;
		  CallQueryInterface(anode,&tmp);
		  result->AppendElement(anode);
		}
	    }while(anode!=nsnull);
	}
    }
  *nodes = nsnull;
  *nodes=result;
  NS_ADDREF(*nodes);
  return NS_OK;
}

/* void GetSubNodes (in nsIDOMNode node, in AUTF8String xpath, out nsISupportsArray nodes); */
NS_IMETHODIMP nsXpathUtil::GetSubNodes(nsIDOMNode *node, const nsACString & xpath, nsISupportsArray **nodes)
{
  nsresult rv;
  nsCOMPtr<nsISupportsArray> result = do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID,&rv);
  if (NS_FAILED(rv))
    return rv;
  nsCOMPtr<nsIDOMXPathNSResolver> resov;
	  
  xpathEV->CreateNSResolver(node,getter_AddRefs(resov));
	  
  nsCOMPtr<nsIDOMXPathExpression> expr;
     
     
  xpathEV->CreateExpression(NS_ConvertUTF8toUTF16(xpath),resov,getter_AddRefs(expr));
     
  if(expr!=nsnull)
    {
      nsCOMPtr<nsISupports> ret;
      expr->Evaluate(node,0,nsnull,getter_AddRefs(ret));
     
     

      nsCOMPtr<nsIDOMXPathResult> exprresults=do_QueryInterface(ret);
     
      if(exprresults!=nsnull)
	{
	  nsIDOMNode* anode=nsnull;
	  do
	    {
	      exprresults->IterateNext(&anode);
	      if(anode!=nsnull)
		{
		  nsISupports *tmp;
		  CallQueryInterface(anode,&tmp);
		  result->AppendElement(anode);
		}
	    }while(anode!=nsnull);
	}
     }
     
     *nodes = nsnull;
     *nodes=result;
     NS_ADDREF(*nodes);
     return NS_OK;
}

/* AUTF8String GetSubpath (in nsIDOMNode par, in nsIDOMNode sub, in short type); */
NS_IMETHODIMP nsXpathUtil::GetSubpath(nsIDOMNode *par, nsIDOMNode *sub, nsACString & _retval)
{
     std::string xpath=CalXpathAnc(sub,par);
     _retval=nsCString(xpath.c_str());
     return NS_OK;
}
/* void AddAttName (in AUTF8String name); */
NS_IMETHODIMP nsXpathUtil::AddAttName(const nsACString & name)
{
     nsCString nsName(name);
     attlist.insert(std::string(nsName.get()));
     return NS_OK;
}

//caculate the ralative xpath with parent of the node the par.
std::string nsXpathUtil::CalXpath(nsIDOMNode * node)
{
     nsresult rv;
     std::string xpath;
     
     nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(node);
     nsString tag;
     ele->GetTagName(tag);
	  
     if(tag.Length()>0)
     {
	  std::string strtag(NS_ConvertUTF16toUTF8(tag).get());
	  toLower(strtag);
	  xpath.append("//");
	  xpath .append(strtag);
	  std::string atts=GetXpathAtt(ele);
	  if(atts.length()>0)
	  {
	       xpath.append("[");
	       xpath.append(atts);
	       xpath.append("]");
	  }
     }
     return xpath;
}
std::string nsXpathUtil::CalXpathAnc(nsIDOMNode * node, nsIDOMNode * anc)
{
     nsresult rv;
     nsIDOMNode * parent=node;
     std::stack<std::string> ps;
     std::string xpath;
     while(parent!=anc)
     {
//	  LOG<<"node:"<<parent<<"anc:"<<anc<<"\n";
	  nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(parent);
	  nsString tag;
	  ele->GetTagName(tag);
	  if(tag.Length()>0)
	  {

	       std::string tmp(NS_ConvertUTF16toUTF8(tag).get());
	       toLower(tmp);
	       std::string atts=GetXpathAtt(ele);
	       if(atts.length()>0)
	       {
		    tmp.append("[");
		    tmp.append(atts);
		    tmp.append("]");
	       }
	       ps.push(tmp);

	  }
	  parent->GetParentNode(&parent);
     }
     if(ps.empty())
	  return xpath;
     while(!ps.empty())
     {
	  std::string tmp=ps.top();
	  ps.pop();
	  xpath.append(tmp);
	  if(!ps.empty())
	       xpath.append("/");
     }
     return xpath;
}

//caculate the absolute xpath of the node.
std::string nsXpathUtil::CalXpathABS(nsIDOMNode * node)
{
     nsresult rv;
     std::string ret;
     nsIDOMNode * parent = node;

     std::stack<std::string> ps;
     nsString tmptag;
     nsCOMPtr<nsIDOMElement> tmpele=do_QueryInterface(node);
     tmpele->GetTagName(tmptag);
     std::string strtag(NS_ConvertUTF16toUTF8(tmptag).get());
     toLower(strtag);
     while(parent!=nsnull)
     {
	  nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(parent);
	  if(ele!=nsnull)
	  {
	       nsString tag;
	       ele->GetTagName(tag);
	       std::string tmp(NS_ConvertUTF16toUTF8(tag).get());
	       toLower(tmp);
	       std::string atts=GetXpathAtt(ele);
	       if(atts.length()>0)
	       {
		    tmp.append("[");
		    tmp.append(atts);
		    tmp.append("]");
	       }
	       ps.push(tmp);
	  }
	  parent->GetParentNode(&parent);
     }
     if(ps.empty())
	  return ret;
     ret.append("/");
     while(!ps.empty())
     {
	  std::string tmp=ps.top();
	  ps.pop();
	  ret.append(tmp);
	  if(!ps.empty())
	       ret.append("/");
     }
     return ret;
     
}

std::string nsXpathUtil::GetXpathAtt(nsIDOMElement *ele)
{
     std::string ret;
     nsCOMPtr<nsIDOMNamedNodeMap> amap;
     ele->GetAttributes(getter_AddRefs(amap));
     PRUint32 len=0;
     if(amap!=nsnull)
     {
	  amap->GetLength(&len);
	  if(len>0)
	  {
	       if(!attlist.empty())
	       {
		    for(std::set<std::string>::iterator it=attlist.begin();it!=attlist.end();++it)
		    {
			 nsString tmpAtt;
			 ele->GetAttribute(NS_ConvertUTF8toUTF16(it->c_str()),tmpAtt);
			 if(tmpAtt.Length()>0)
			 {
			      if(ret.length()>0)
				   ret.append(" and ");
			      ret.append("@");
			      ret.append(*it);
			      ret.append("=\"");
			      ret.append(NS_ConvertUTF16toUTF8(tmpAtt).get());
			      ret.append("\"");
			 } 
		    }
	       }else
	       {
		    
		    for(int i=0;i<sizeof(Att_Name)/sizeof(std::string);i++)
		    {
			 nsString tmpAtt;
			 ele->GetAttribute(NS_ConvertUTF8toUTF16(Att_Name[i].c_str()),tmpAtt);
			 if(tmpAtt.Length()>0)
			 {
			      if(ret.length()>0)
				   ret.append(" and ");
			      ret.append("@");
			      ret.append(Att_Name[i]);
			      ret.append("=\"");
			      ret.append(NS_ConvertUTF16toUTF8(tmpAtt).get());
			      ret.append("\"");
			 }
		    }
	       }
	       
	  }
     }
     return ret;
}
