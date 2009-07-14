#include "nsChlWrapper.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsISupportsArray.h"
#include "nsITreeNode.h"
#include "nsIDOMElement.h"
#include "nsIDOMNamedNodeMap.h"
#include "nsIDOM3Node.h"
#include "nsIDOMNodeList.h"
#include <iostream>
#include <stack>
#include <set>
#include <vector>
#include <algorithm>
#include <regex.h>
NS_IMPL_ISUPPORTS1(nsChlWrapper, nsIChlWrapper)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsChlWrapper)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CHLWRAPPER_CLASSNAME,
	  NS_CHLWRAPPER_CID,
	  NS_CHLWRAPPER_CONTRACTID,
	  nsChlWrapperConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsChlWrapperModule", components)

nsChlWrapper::nsChlWrapper()
:mType(REL)
{
     /* member initializers and constructor code */
}

nsChlWrapper::~nsChlWrapper()
{
     /* destructor code */
}

/* void SetTree (in nsITreeNode tree); */
NS_IMETHODIMP nsChlWrapper::SetTree(nsITreeNode *tree)
{
     mTree=tree;
     return NS_OK;
}

/* void GetWrapper (out AUTF8String xpath); */

NS_IMETHODIMP nsChlWrapper::GetWrapper(nsACString & xpath)
{
     std::map<std::string,NodeAtt> pathmap;
     GetXpath(pathmap,mTree);
     ChlXpath chlp;
     for(std::map<std::string,NodeAtt>::iterator it=pathmap.begin();it!=pathmap.end();++it)
     {
	  if(mType==ABS)
	  {
	       for(std::set<std::string>::iterator sit=it->second.tpSet.begin();sit!=it->second.tpSet.end();++sit)
	       {
		    chlp.AddPath(it->second.xpath,*sit);
	       }
	  }else
	  {
	       if(it->second.count>1)
	       {
		    for(std::set<std::string>::iterator sit=it->second.tpSet.begin();sit!=it->second.tpSet.end();++sit)
		    {
			 chlp.AddPath(it->second.xpath,*sit);
		    }
	       }
	  }
     }
     std::string wrap=chlp.GetWrapper();
     nsCString ret(wrap.c_str());
     xpath=ret;
     return NS_OK;
}
/* void SetXType (in unsigned short type); */
NS_IMETHODIMP nsChlWrapper::SetXType(PRUint16 type)
{
     mType=type;
     return NS_OK;
}

/* void SetDocument (in nsIDOMDocument tree); */
NS_IMETHODIMP nsChlWrapper::SetDocument(nsIDOMDocument *tree)
{
     doc=tree;
     return NS_OK;
}

//Get all the xpath from the tree and store it in a map
void nsChlWrapper::GetXpath(std::map<std::string,NodeAtt> &pathmap,nsITreeNode *ptree)
{
     PRUint32 len;
     nsCOMPtr<nsISupportsArray> subTrees;
     ptree->GetSubTree(getter_AddRefs(subTrees));
     nsCOMPtr<nsIDOMNode> par;

     ptree->GetNode(getter_AddRefs(par));
     nsCOMPtr<nsIDOMElement> ptmpEle=do_QueryInterface(par);
     nsString ptag;
     ptmpEle->GetTagName(ptag);

     PRBool ptisBig;
     ptree->IsBigBox(&ptisBig);
     if(subTrees!=nsnull)
     {
	  subTrees->Count(&len);
	  LOG<<"sublen:"<<len<<"\n";
	  for(PRUint32 i=0;i<len;i++)
	  {
	       nsITreeNode *tree; 
	       nsISupports *tmp;
	       tmp=subTrees->ElementAt(i);
		
	       CallQueryInterface(tmp,&tree);
	       if(tree!=nsnull)
	       {
		    double pwh,wh;
		    ptree->GetWHRate(&pwh);
		    tree->GetWHRate(&wh);

		    PRInt32 area;
		    tree->GetArea(&area);
		    PRInt32 classid;
		    tree->GetClassId(&classid);
		    PRBool isBig;
		    tree->IsBigBox(&isBig);
		    LOG<<"par tag:"<<NS_ConvertUTF16toUTF8(ptag).get()<<"  id:"<<classid<<"  isBig:"<<isBig<<"  ptisBig:"<<ptisBig<<"  area:"<<area<<"\n";
		    if(ptisBig&&!isBig&&wh>1&&3*pwh<wh&&area>0)
		    {
			 nsIDOMNode *node;
			 tree->GetNode(&node);
			 
			 nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(node);
			 nsString tag;
			 tmpEle->GetTagName(tag);

			 std::string tmp;
			 if(mType==REL)
			      tmp=CalXpath(node, par);
			 else if(mType==ABS)
			      tmp=CalXpathABS(node,par);
			 else
			      tmp=CalXpathDUL(node,par);
			 LOG<<"xpath:"<<tmp<<"\n";
			 if(tmp.length()>0)
			 {
			      std::string tpath=GetTitlePath1(node);
			      LOG<<"tpath+++++++++++:"<<tpath<<"\n";
			      if(pathmap.find(tmp)==pathmap.end())
			      {
				   NodeAtt tmpatt;
				   tmpatt.xpath=tmp;
				   tmpatt.count=1;
				   if(tpath.length()>0)
				   {
					tmpatt.tpSet.insert(tpath);
					pathmap.insert(make_pair(tmp,tmpatt));
				   }
			      }
			      else
			      {
				   if(tpath.length()>0)
				   {
					pathmap[tmp].tpSet.insert(tpath);
					pathmap[tmp].count++;
				   }
			      }
			 }
		    }
		    GetXpath(pathmap,tree);
	       }
	  }
     }
}
//if the element tag is the filter tag return true.
bool nsChlWrapper::IsFilterTag(std::string &tag)
{
     for(int i=0;i<sizeof(non_tag)/sizeof(std::string);i++)
     {
	  if(tag==non_tag[i])
	       return true;
     }
     return false;
}
//caculate the ralative xpath with parent of the node the par.
std::string nsChlWrapper::CalXpath(nsIDOMNode * node, nsIDOMNode * par)
{
     nsresult rv;
     nsIDOMNode * parent;
     std::string xpath;
     node->GetParentNode(&parent);
     if(parent==par)
     {
	  nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(node);
	  nsString tag;
	  ele->GetTagName(tag);
	  
	  if(tag.Length()>0)
	  {
	       std::string strtag(NS_ConvertUTF16toUTF8(tag).get());
	       if(!IsFilterTag(strtag))
	       {
		    xpath.append("//");
		    xpath.append(strtag);
		    std::string atts=GetXpathAtt(ele);
		    if(atts.length()>0)
		    {
			 xpath.append("[");
			 xpath.append(atts);
			 xpath.append("]");
		    }
	       }
	  }
     }
     return xpath;
}
std::string nsChlWrapper::CalXpathAnc(nsIDOMNode * node, nsIDOMNode * anc)
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
//caculate the ralative xpath of the node the par.
std::string nsChlWrapper::CalXpathDUL(nsIDOMNode * node, nsIDOMNode * par)
{
     nsresult rv;
     nsIDOMNode * parent;
     std::string xpath;
     node->GetParentNode(&parent);
     if(parent==par)
     {
	  nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(par);
	  nsString tag;
	  ele->GetTagName(tag);
	  if(tag.Length()>0)
	  {
	       std::string strtag(NS_ConvertUTF16toUTF8(tag).get());
	       {
		    xpath.append("//");
		    xpath.append(strtag);
		    std::string atts=GetXpathAtt(ele);
		    if(atts.length()>0)
		    {
			 xpath.append("[");
			 xpath.append(atts);
			 xpath.append("]");
		    }
	       }
	  }
	  ele=do_QueryInterface(node);
	  ele->GetTagName(tag);
	  
	  if(tag.Length()>0)
	  {
	       std::string strtag(NS_ConvertUTF16toUTF8(tag).get());
	       if(!IsFilterTag(strtag))
	       {
		    
		    xpath.append("/");
		    std::string atts=GetXpathAtt(ele);
		    if(atts.length()>0)
		    {
			 xpath.append("[");
			 xpath.append(atts);
			 xpath.append("]");
		    }
	       }
	  }
     }
     return xpath;
}
//caculate the absolute xpath of the node.
std::string nsChlWrapper::CalXpathABS(nsIDOMNode * node,nsIDOMNode * par)
{
     nsresult rv;
     std::string ret;
     nsIDOMNode * parent = node;
     // nsIDOMNode * tmpPar;
//      node->GetParentNode(&tmpPar);
//      if(tmpPar!=par)
//      {
// 	  LOG<<"--------------------------\n";
// 	  return ret;
//      }
     std::stack<std::string> ps;
     nsString tmptag;
     nsCOMPtr<nsIDOMElement> tmpele=do_QueryInterface(node);
     tmpele->GetTagName(tmptag);
     std::string strtag(NS_ConvertUTF16toUTF8(tmptag).get());
     if(!IsFilterTag(strtag))
     {
	  while(parent!=nsnull)
	  {
	       nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(parent);
	       if(ele!=nsnull)
	       {
		    nsString tag;
		    ele->GetTagName(tag);
		    std::string tmp(NS_ConvertUTF16toUTF8(tag).get());
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
std::string nsChlWrapper::GetXpathAtt(nsIDOMElement *ele)
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
	       for(int i=0;i<sizeof(AttNames)/sizeof(std::string);i++)
	       {
		    nsString tmpAtt;
		    ele->GetAttribute(NS_ConvertUTF8toUTF16(AttNames[i].c_str()),tmpAtt);
		    if(tmpAtt.Length()>0)
		    {
			 if(ret.length()>0)
			      ret.append(" and ");
			 ret.append("@");
			 ret.append(AttNames[i]);
			 ret.append("=\"");
			 ret.append(NS_ConvertUTF16toUTF8(tmpAtt).get());
			 ret.append("\"");
		    }
	       }
	  }
     }
     return ret;
}
int nsChlWrapper::distance(const std::string source, const std::string target) 
{

     // Step 1

     const int n = source.length();
     const int m = target.length();
     if (n == 0) {
	  return m;
     }
     if (m == 0) {
	  return n;
     }

     // Good form to declare a TYPEDEF

     typedef std::vector< std::vector<int> > Tmatrix; 

     Tmatrix matrix(n+1);

     // Size the vectors in the 2.nd dimension. Unfortunately C++ doesn't
     // allow for allocation on declaration of 2.nd dimension of vec of vec

     for (int i = 0; i <= n; i++) {
	  matrix[i].resize(m+1);
     }

     // Step 2

     for (int i = 0; i <= n; i++) {
	  matrix[i][0]=i;
     }

     for (int j = 0; j <= m; j++) {
	  matrix[0][j]=j;
     }

     // Step 3

     for (int i = 1; i <= n; i++) {

	  const char s_i = source[i-1];

	  // Step 4

	  for (int j = 1; j <= m; j++) {

	       const char t_j = target[j-1];

	       // Step 5

	       int cost;
	       if (s_i == t_j) {
		    cost = 0;
	       }
	       else {
		    cost = 1;
	       }

	       // Step 6

	       const int above = matrix[i-1][j];
	       const int left = matrix[i][j-1];
	       const int diag = matrix[i-1][j-1];
	       int cell = std::min( above + 1, std::min(left + 1, diag + cost));

	       // Step 6A: Cover transposition, in addition to deletion,
	       // insertion and substitution. This step is taken from:
	       // Berghel, Hal ; Roach, David : "An Extension of Ukkonen's 
	       // Enhanced Dynamic Programming ASM Algorithm"
	       // (http://www.acm.org/~hlb/publications/asm/asm.html)

	       if (i>2 && j>2) {
		    int trans=matrix[i-2][j-2]+1;
		    if (source[i-2]!=t_j) trans++;
		    if (s_i!=target[j-2]) trans++;
		    if (cell>trans) cell=trans;
	       }

	       matrix[i][j]=cell;
	  }
     }

     // Step 7

     return matrix[n][m];
}
std::string nsChlWrapper::GetTitlePath(nsIDOMNode *node)
{
     std::string ret;
     nsString tmpText;
     nsCOMPtr<nsIDOM3Node> tmpnsEle=do_QueryInterface(node);
     tmpnsEle->GetTextContent(tmpText);
      LOG<<NS_ConvertUTF16toUTF8(tmpText).get()<<"\n";
     //Get the text of the first leaf element node
     nsIDOMNode *domnode=node;
     nsString nodetext;
     for(domnode->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
     {
          PRUint16 type;
          domnode->GetNodeType(&type);
          if(type==nsIDOMNode::TEXT_NODE)
          {
               nsString tmp;
               domnode->GetNodeValue(tmp);
               nodetext.Append(tmp);
          }
     }
     nodetext.StripChars("\t");
     nodetext.StripWhitespace();
     nodetext.StripChars("\n");
     if(nodetext.Length()>10)
     {
	  return ret;
     }
     domnode=nsnull;
//     LOG<<"----------------\n";
     nsIDOMNode *domele=node;
     do
     {
	  bool isImg=false;
	  LOG<<"ele:"<<domele<<"\n";
	  for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	  {
	       LOG<<"node:"<<domnode<<"\n";
	       PRUint16 type;
	       domnode->GetNodeType(&type);
	       if(type==nsIDOMNode::ELEMENT_NODE)
	       {
		    nsCOMPtr<nsIDOMElement> ele=do_QueryInterface(domnode);
		    nsString tag;
		    ele->GetTagName(tag);
		    LOG<<"tag:"<<NS_ConvertUTF16toUTF8(tag).get()<<"\n";
		    if(std::string(NS_ConvertUTF16toUTF8(tag).get())=="IMG")
		    {
			 isImg=true;
		    }else
		    {
			 isImg=false;
			 domele=domnode;
			 break;
		    }
	       }
	  }
	  LOG<<"isimg:"<<isImg<<"\n";
	  if(isImg)
	  {
	       for(domele->GetNextSibling(&domele);domele!=nsnull;domele->GetNextSibling(&domele))
	       {
		    PRUint16 type;
		    domele->GetNodeType(&type);
		    if(type==nsIDOMNode::ELEMENT_NODE)
		    {
			 break;
		    }
	       }
	       domnode=domele;
	  }
	       
     }while(domnode!=nsnull);
     bool notFistEle=true;
     if(domele!=nsnull)
     {
	  nsString Text;
	  nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(domele);
	  nsEle->GetTextContent(Text);
	  std::string tmpStr(NS_ConvertUTF16toUTF8(Text).get());
	  if(domele!=node&&IsTitle(tmpStr))
	  {
	       notFistEle=false;
	       ret=CalXpathAnc(domele,node);
	  }
     }
     if(notFistEle)
     {
	  //get the "alt" attribute of the first "IMG" node
	  nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(node);
	  nsCOMPtr<nsIDOMNodeList> EleList;
	  tmpEle->GetElementsByTagName(NS_ConvertUTF8toUTF16("IMG"),getter_AddRefs(EleList));
	  nsCOMPtr<nsIDOMNode> tmpNode;
	  if(EleList!=nsnull)
	  {
	       EleList->Item(0,getter_AddRefs(tmpNode));
	       if(tmpNode!=nsnull)
	       {
		    nsString Text;
		    nsString attText;
		    nsCOMPtr<nsIDOMElement> firEle=do_QueryInterface(tmpNode);
		    firEle->GetAttribute(NS_ConvertUTF8toUTF16("alt"),attText);
		    
		    nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(tmpNode);
		    nsEle->GetTextContent(Text);
		    std::string tmpStr1(NS_ConvertUTF16toUTF8(Text).get());
		    std::string tmpStr2(NS_ConvertUTF16toUTF8(attText).get());
		    if(IsTitle(tmpStr1)||IsTitle(tmpStr2))
		    {
			 ret=CalXpathAnc(tmpNode,node);			 
		    }
	       }

	  }
     }
     return ret;
}
std::string nsChlWrapper::GetTitlePath1(nsIDOMNode *node)
{
     std::string ret;
     nsString tmpText;
     nsCOMPtr<nsIDOM3Node> tmpnsEle=do_QueryInterface(node);
     tmpnsEle->GetTextContent(tmpText);
     LOG<<NS_ConvertUTF16toUTF8(tmpText).get()<<"\n";
     //Get the text of current element node
     nsIDOMNode *domnode=node;
     nsString nodetext;
     for(domnode->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
     {
          PRUint16 type;
          domnode->GetNodeType(&type);
          if(type==nsIDOMNode::TEXT_NODE)
          {
               nsString tmp;
               domnode->GetNodeValue(tmp);
               nodetext.Append(tmp);
          }
     }
     nsCString tmpNodetext=NS_ConvertUTF16toUTF8(nodetext);
     tmpNodetext.StripWhitespace();
     tmpNodetext.StripChars("\n");
     std::string nodeStr(tmpNodetext.get());
     string_filter(nodeStr);
//     LOG<<nodeStr<<":--------"<<IsTitle(nodeStr)<<":----------"<<nodeStr.length()<<"\n";
     if(IsTitle(nodeStr))
     {
	  ret=".";
	  return ret;
     }else if(nodeStr.length()>20)
     {
	  return ret;
     }
     //Get the text of the first leaf element node
     std::list<nsIDOMNode*> leafList;
     std::stack<nsIDOMNode*> eleStack;
     eleStack.push(node);
     while(!eleStack.empty())
     {
	  nsIDOMNode *domele=eleStack.top();
	  eleStack.pop();
	  nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(domele);
	  nsString tag;
	  tmpEle->GetTagName(tag);
//	  LOG<<"tag:"<<NS_ConvertUTF16toUTF8(tag).get()<<"\n";
	  bool isLeaf=true;
	  domnode=nsnull;
	  for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	  {
	       PRUint16 type;
	       domnode->GetNodeType(&type);
	       if(type==nsIDOMNode::ELEMENT_NODE)
	       {
		    isLeaf=false;
		    break;
	       }
	  }
//	  LOG<<"isLeaf:"<<isLeaf<<"\n";
	  if(isLeaf)
	       leafList.push_back(domele);
	  else
	  {
	       domnode=nsnull;
	       for(domele->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	       {
		    PRUint16 type;
		    domnode->GetNodeType(&type);
		    if(type==nsIDOMNode::ELEMENT_NODE)
		    {
			 eleStack.push(domnode);
		    }
	       }
	  }
     }
     int count=0;
     domnode=nsnull;
     for(std::list<nsIDOMNode*>::reverse_iterator it=leafList.rbegin();it!=leafList.rend();++it)
     {
	  nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(*it);
	  nsString tag;
	  tmpEle->GetTagName(tag);
//	  LOG<<"tag:"<<NS_ConvertUTF16toUTF8(tag).get()<<"\n";
	  
	  nsString Text;
	  nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(tmpEle);
	  nsEle->GetTextContent(Text);
	  Text.StripChars("\n");
	  Text.StripChars("\t");
	  Text.StripWhitespace();
//	  LOG<<"text:"<<NS_ConvertUTF16toUTF8(Text).get()<<"\n";
	  if(Text.Length()>0)
	  {
	       std::string tmpTextStr(NS_ConvertUTF16toUTF8(tag).get());
	       if(std::string(NS_ConvertUTF16toUTF8(tag).get())!="IMG"&&tmpTextStr.find("更多")==std::string::npos)
	       {
		    count++;
	       }
	       std::string tmpStr(NS_ConvertUTF16toUTF8(Text).get());
	       if(IsTitle(tmpStr))
	       {
		    domnode=*it;
	       }
	       break;
	  }
     }
     if(domnode!=nsnull&&count<2)
     {
	  ret=CalXpathAnc(domnode,node);
     }else
     {
	  //get the "alt" attribute of the first "IMG" node
	  nsCOMPtr<nsIDOMElement> tmpEle=do_QueryInterface(node);
	  nsCOMPtr<nsIDOMNodeList> EleList;
	  tmpEle->GetElementsByTagName(NS_ConvertUTF8toUTF16("IMG"),getter_AddRefs(EleList));
	  nsCOMPtr<nsIDOMNode> tmpNode;
	  if(EleList!=nsnull)
	  {
	       EleList->Item(0,getter_AddRefs(tmpNode));
	       if(tmpNode!=nsnull)
	       {
		    nsString Text;
		    nsString attText;
		    nsCOMPtr<nsIDOMElement> firEle=do_QueryInterface(tmpNode);
		    firEle->GetAttribute(NS_ConvertUTF8toUTF16("alt"),attText);
		    
		    nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(tmpNode);
		    nsEle->GetTextContent(Text);
		    std::string tmpStr1(NS_ConvertUTF16toUTF8(Text).get());
		    std::string tmpStr2(NS_ConvertUTF16toUTF8(attText).get());

		    if(IsTitle(tmpStr1)||IsTitle(tmpStr2))
		    {
			 ret=CalXpathAnc(tmpNode,node);			 
		    }
	       }

	  }
     }
     return ret;
}
bool nsChlWrapper::IsTitle(const std::string &str)
{
     int len=str.length();
     if(str.find("\n")!=std::string::npos)
     {
	  return false;
     }
     if(str.find("更多")!=std::string::npos)
     {
	  return false;
     }
     if(len>21||len<4)
     {
	  return false;
     }
     return true;
}

void nsChlWrapper::string_filter(std::string & s)
{
	int flag = 0;
	regex_t reg;
	int r = regcomp(&reg, "\\(#\\|\n\\| \\|　\\|\\s\\|\r\\|，\\|。\\|：\\|·\\|“\\|[,.:\"|]\\)\\+", flag);
	if(r != 0)
	{
		char ebuf[128];
		regerror(r, &reg, ebuf, sizeof(ebuf));
		LOG<<"regexp pattern error: "<<ebuf<<"\n";
	}
	else
	{
		size_t nmatch = 1;
		regmatch_t pm;
		int r = regexec(&reg, s.c_str(), nmatch, &pm, 0);
		if(!r)
		{
			int pos = 0;
			if(pm.rm_so != -1)
			{
				int len = pm.rm_eo - pm.rm_so;
				s.erase(pm.rm_so, len);
				string_filter(s);
			}
		}
	}
	regfree(&reg);
}
