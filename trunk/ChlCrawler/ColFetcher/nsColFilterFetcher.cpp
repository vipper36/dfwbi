#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsIUrlAtt.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMHTMLCollection.h"
#include "nsColFilterFetcher.h"
#include <iostream>
#include <sstream>
#include <map>
#include <list>
#include <vector>
#include "nsIDOM3Node.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLLinkElement.h"
#include "nsIColAtt.h"
#include "sha1.h"
#include "property.h"
#include <regex.h>
#include <stdlib.h>
static NS_DEFINE_CID(kIOServiceCID, NS_IOSERVICE_CID);
NS_IMPL_ISUPPORTS1(nsColFilterFetcher, nsIColFetcher)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsColFilterFetcher)

static nsModuleComponentInfo components[] =
{
  {
    NS_COLFILTERFETCHER_CLASSNAME,
    NS_COLFILTERFETCHER_CID,
    NS_COLFILTERFETCHER_CONTRACTID,
    nsColFilterFetcherConstructor,
  }
};
NS_IMPL_NSGETMODULE("nsColFilterFetcherModule", components)


/* Implementation file */


nsColFilterFetcher::nsColFilterFetcher()
     :editDis(5),
     classCount(10),
     replaceType(0)
{
  /* member initializers and constructor code */
}

nsColFilterFetcher::~nsColFilterFetcher()
{
  /* destructor code */
}

/* attribute nsIColAtt col; */
NS_IMETHODIMP nsColFilterFetcher::GetCol(nsIColAtt * *aCol)
{
     if(mCol!=nsnull)
     {
	  *aCol=mCol;
	  NS_ADDREF(*aCol);
     }
     return NS_OK;
}
NS_IMETHODIMP nsColFilterFetcher::SetCol(nsIColAtt * aCol)
{
     mCol=aCol;
     return NS_OK;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsColFilterFetcher::SetDocument(nsIDOMDocument *doc)
{
     mDoc=doc;
     urls.Clear();
     FillUrls();
     return NS_OK;
}

/* void SetProperty (in nsIPersistentProperties prop); */
NS_IMETHODIMP nsColFilterFetcher::SetProperty(nsIPersistentProperties *prop)
{
     nsString tmpExp;
     nsString tmpInc;
     property=prop;
     property->GetStringProperty(EXCEPT_REG,tmpExp);
     property->GetStringProperty(INCLUDE_REG,tmpInc);
     expStr=NS_ConvertUTF16toUTF8(tmpExp);
     incStr=NS_ConvertUTF16toUTF8(tmpInc);

     nsString strCount;
     nsString strDis;
     property->GetStringProperty(URL_CLASS_COUNT,strCount);
     classCount=atol(NS_ConvertUTF16toUTF8(strCount).get());
     property->GetStringProperty(URL_EDIT_DIS,strDis);
     editDis=atol(NS_ConvertUTF16toUTF8(strDis).get());

     nsString rplType;
     nsString strFrom;
     nsString strTo;
     property->GetStringProperty(URL_REPLACE_TYPE,rplType);
     replaceType=atol(NS_ConvertUTF16toUTF8(rplType).get());

     property->GetStringProperty(URL_REPLACE_FROM,strFrom);
     RepFrom=std::string(NS_ConvertUTF16toUTF8(strFrom).get());

     property->GetStringProperty(URL_REPLACE_TO,strTo);
     RepTo=std::string(NS_ConvertUTF16toUTF8(strTo).get());
     return NS_OK;
}

/* long GetColLength (); */
NS_IMETHODIMP nsColFilterFetcher::GetUrlLength(PRInt32 *_retval)
{
     *_retval=urls.Count();
     return NS_OK;
}

/* void GetColItem (in long index, out nsIColAtt col); */
NS_IMETHODIMP nsColFilterFetcher::GetUrlItem(PRInt32 index, nsIUrlAtt **url)
{
     if(index<urls.Count())
     {
	  *url = urls[index];
	  NS_ADDREF(*url);
     }
     else
     {
	  *url=nsnull;
     }
     return NS_OK;
}
NS_IMETHODIMP nsColFilterFetcher::FillUrls()
{
     nsCOMPtr<nsIDOMHTMLDocument> domhtml=do_QueryInterface(mDoc);
     nsCOMPtr<nsIDOMHTMLCollection> links;
     domhtml->GetLinks(getter_AddRefs(links));
     PRUint32 len;
     links->GetLength(&len);
     std::list< std::list<URLDesc> > UrlClass;
     for(int i=0;i<len;i++)
     {
	  nsCOMPtr<nsIDOMNode> aLink(nsnull);
	  links->Item(i,getter_AddRefs(aLink));
	  if(aLink!=nsnull)
	  {
	       nsString Value;
	       nsString linkUrl;
	       nsCOMPtr<nsIDOM3Node> nsEle=do_QueryInterface(aLink);
	       nsEle->GetTextContent(Value);
					
	       nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle=do_QueryInterface(aLink);
	       if(linkEle!=nsnull)
	       {
		    linkEle->GetHref(linkUrl);
	       }else
	       {
		    nsCOMPtr<nsIDOMHTMLLinkElement>  linkEle2=do_QueryInterface(aLink);
		    if(linkEle2!=nsnull)
		    {
			 linkEle2->GetHref(linkUrl);
		    }
	       }

//	       LOG<<"link:"<<NS_ConvertUTF16toUTF8(linkUrl).get()<<"\n";
	       std::string strurl(NS_ConvertUTF16toUTF8(linkUrl).get());
	       std::string strname(NS_ConvertUTF16toUTF8(Value).get());

	       
	       std::string tmpExp(expStr.get());
	       std::string tmpInc(incStr.get());

	       bool matchExp=StrMatch(strurl,tmpExp);
	       bool matchInc=StrMatch(strurl,tmpInc);
	       if(matchInc&&!matchExp)
	       {
		    
		    URLDesc tmpDesc;
		    tmpDesc.url=strurl;
		    tmpDesc.title=strname;
		    if(UrlClass.empty())
		    {
			 std::list<URLDesc> tmpList;
			 tmpList.push_back(tmpDesc);
			 UrlClass.push_back(tmpList);
		    }else
		    {
			 bool inClass=false;
			 for(std::list< std::list<URLDesc> >::iterator it=UrlClass.begin();it!=UrlClass.end();++it)
			 {
			      URLDesc tmpIn=it->front();
			      if(distance(tmpDesc.url,tmpIn.url)<editDis)
			      {
				   it->push_back(tmpDesc);
				   inClass=true;
			      }
			 }
			 if(!inClass)
			 {
			      std::list<URLDesc> tmpList;
			      tmpList.push_back(tmpDesc);
			      UrlClass.push_back(tmpList);
			 }
		    }
	       }
	  }
				   
     }
     std::map<std::string,URLDesc> urlMap;
     for(std::list< std::list<URLDesc> >::iterator it=UrlClass.begin();it!=UrlClass.end();++it)
     {
	  LOG<<"class:"<<it->size()<<"\n";
	  if(it->size()>classCount)
	  {
	       for(std::list<URLDesc>::iterator lit=it->begin();lit!=it->end();++lit)
	       {
		    if(urlMap.find(lit->url)==urlMap.end())
		    {
			 urlMap.insert(make_pair(lit->url,*lit));
		    }
	       }
	  }
     }
     
     PRInt32 colId;
     mCol->GetId(&colId);
      
     for(std::map<std::string,URLDesc>::iterator it=urlMap.begin();it!=urlMap.end();++it)
     {
	  nsresult rv;
	  nsCOMPtr<nsIUrlAtt> url=do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1", &rv);
	  if (NS_FAILED(rv))
	  {
	       LOG<<"Get nsWebChannel Error:"<<rv<<"\n";
	  }else
	  {
	       ReplaceString(it->second.url,RepFrom,RepTo,replaceType);
	       nsCString strName(it->second.title.c_str());
	       nsCString strUrl(it->second.url.c_str());
//	       LOG<<"name:"<<strName.get()<<" url:"<<strUrl.get()<<" chl id:"<<colId<<"\n";
	       url->SetURL(strName, strUrl,colId);
	       urls.AppendObject(url);
	  }
     }

     return NS_OK;
}

bool nsColFilterFetcher::StrMatch(const std::string &src,const std::string &match)
{
     bool b = false;
     int flag = 0;
     regex_t reg;
     int r = regcomp(&reg, match.c_str(), flag);
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
	  int r = regexec(&reg, src.c_str(), nmatch, &pm, 0);
	  if(r==0)
	  {
	       b = true;
	  }
     }
     regfree(&reg);
     return b;
}
int nsColFilterFetcher::distance(const std::string source, const std::string target) 
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
/** 
 * @brief Mapping the url to the right one 
 * 
 * @param s the url
 * @param from replace this string
 * @param to   the target substring
 * @param type  mapping type.
 */
void nsColFilterFetcher::ReplaceString(std::string & s,const std::string &from,const std::string &to,int type)
{
     std::size_t index;
     if(type==1)
     {
	  index=s.find(from);
     }else if(type==2)
     {
	  index=s.rfind(from);
     }else if(type==3)
     {
	  index=s.find(from);
     }
     else if(type==4)
     {
	  index=s.rfind(from);
     }
     else
     {
	  return;
     }
     if(index!=std::string::npos)
     {
	  s.replace(index,from.length(),to);
	  if(type>2)
	  {
	       std::string ret=TranHost(s);
	       s=ret;
	  }
     }
}
std::string nsColFilterFetcher::TranHost(const std::string &from)
{
     std::string ret;
     std::size_t index,index1=7;
     index=from.rfind("/");
     std::string blogname=from.substr(index);
     blogname.append(".blog");
     ret.append("http:/");
     ret.append(blogname);
     std::string host=from.substr(index1,index-index1);
     ret.append(host);
     return ret;
     
}
void nsColFilterFetcher::string_filter(std::string & s)
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
