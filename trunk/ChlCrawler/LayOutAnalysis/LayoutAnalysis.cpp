#include "LayoutAnalysis.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsXPCOMGlue.h"
#include "nsIWebNavigation.h"
#include "nsIDOMElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIDOMNodeList.h"
#include "nsIBoxObject.h"
#include "nsIDOMCSSStyleDeclaration.h"
#include "nsIDOMElementCSSInlineStyle.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsISupportsArray.h"
#include "nsIDOMCSSStyleRule.h"
#include "nsNetUtil.h"
#include <iconv.h>
#include <iostream>
#include <stack>
#include <utility>
#include "StyleCompare.h"
#include "nsIDOMNamedNodeMap.h"
#include "nsIDOMDocumentView.h"
#include "nsIDOMViewCSS.h"
#include "nsIDOMAbstractView.h"
/* Implementation file */
NS_IMPL_ISUPPORTS1(LayoutAnalysis,
		   ILayoutAnalysis)

NS_GENERIC_FACTORY_CONSTRUCTOR(LayoutAnalysis)

static nsModuleComponentInfo components[] =
{
     {
	  LAYOUTANALYSIS_CLASSNAME, 
	  LAYOUTANALYSIS_CID,
	  LAYOUTANALYSIS_CONTRACTID,
	  LayoutAnalysisConstructor,
     }
};
NS_IMPL_NSGETMODULE("LayoutAnalysisModule", components)

LayoutAnalysis::LayoutAnalysis()
	  :alg("Hybrid"),
	  NeedAly(true),
	  cents(5)
     {
	  
	  term=KMterm(50, 0, 50, 0.5,		// run for 100 stages
		0.01,			// min consec RDL
		0.01,			// min accum RDL
		ATTDIM*20,			// max run stages
		0.3,			// init. prob. of acceptance
		ATTDIM*10,			// temp. run length
		0.75);			// temp. reduction factor
	  ctrs=NULL;
	  dataPts=NULL;
	  
     };
NS_IMETHODIMP LayoutAnalysis::SetDocument(nsIDOMHTMLDocument *doc)
{
     htmldoc=doc;
     nsdoc=do_QueryInterface(doc);
     domdoc=do_QueryInterface(doc);
     nsCOMPtr<nsIDOMDocumentView> domView = do_QueryInterface(domdoc);
     if(domView!=nsnull)
     {
	  nsCOMPtr<nsIDOMAbstractView> abstractView;
	  domView->GetDefaultView(getter_AddRefs(abstractView));
	  if(abstractView!=nsnull)
	  {
	       viewCSS=do_QueryInterface(abstractView);
	  }
     }
     return NS_OK;
}

ScaleFun funArr[ATTDIM]={
     NULL,
     NULL,
     NULL,
     NULL,
     sqrt,
     log
};
typedef std::pair<nsIDOMNode *,nsITreeNode*> DomTree;

bool LayoutAnalysis::BlockCluster(nsITreeNode *tn)
{
     nsresult rv=0;
     PRBool hsc=false ;
     nsIDOMNode *node;
     
     nsCOMPtr<nsIBoxObject> docbox;
     nsCOMPtr<nsIDOMElement> docele;
     domdoc->GetDocumentElement(getter_AddRefs(docele));
     rv=nsdoc->GetBoxObjectFor(docele,getter_AddRefs(docbox));
     if (NS_FAILED(rv))
     {
	  return rv;
     }
     PRInt32 doch,docw;
     docbox->GetHeight(&doch);
     docbox->GetWidth(&docw);
     PRInt32 docArea=docw*doch;
     if(docArea==0)
	  docArea=VISUALAREA;
     nsCOMPtr<nsIDOMHTMLElement> ele;
     rv=htmldoc->GetBody(getter_AddRefs(ele));
     if (NS_FAILED(rv))
     {
	  LOG<<"Get Body Error:"<<rv<<"\n";
	  return false;
     }
	  
     rv=CallQueryInterface(ele,&node); 
     if (NS_FAILED(rv)) 
     {
	  LOG<<"Body Trance to DOMNODE Error:"<<rv<<"\n";
	  return false;
     }
     std::vector<AttributeVector> NodeArray;
     std::stack<DomTree> nodestack;
     tn->SetIndex(-1);

     tn->SetNode(node);

     tn->ClearSub();

     nodestack.push(make_pair(node,tn));
     int index=0;
     while(!nodestack.empty())
     {

	  DomTree dt=nodestack.top();
	  nsIDOMNode* domnode=dt.first;
	  nsITreeNode* tree=dt.second;
	  nodestack.pop();
	  domnode->HasChildNodes(&hsc);
	  if(hsc)
	  {
	       
	       for(domnode->GetFirstChild(&domnode);domnode!=nsnull;domnode->GetNextSibling(&domnode))
	       {
		    
		    nsCOMPtr<nsIBoxObject> box;
		    nsIDOMElement* tele;
		    CallQueryInterface(domnode,&tele); 
		    if(tele!=nsnull)
		    {
			 rv=nsdoc->GetBoxObjectFor(tele,getter_AddRefs(box));
			 if (NS_FAILED(rv))
			 {
			      continue;
			 }
			 PRInt32 x,y,h,w;
			 box->GetX(&x);
			 box->GetY(&y);
			 box->GetHeight(&h);
			 box->GetWidth(&w);
			 bool inbody=true;
			 if(doch*docw>0)
			 {
			      if(y+h>doch)
				   inbody=false;
			 }
			 if(h+w>0&&x>=0&&y>=0&&inbody)
			 {
			      nsCOMPtr<nsIDOMNodeList> childList;
			      rv=tele->GetChildNodes(getter_AddRefs(childList));
			      PRUint32 length;
			      childList->GetLength(&length);
			      if(length>0)
			      {
				   double parent=0;
				   double ldist=0;

				   CalSibParentDist(tele,parent,ldist);

				   int depth=CalNodeDepth(domnode);
				   
				   AttributeVector tmpV;
				   tmpV.push_back(parent);

				   tmpV.push_back(ldist);

				   tmpV.push_back(depth);

				   tmpV.push_back((double)w/double(h+w));

				   tmpV.push_back((double(w*h))/docArea);

				   tmpV.push_back(fabs(h-30)+1);
				   NodeArray.push_back(tmpV);
				   nsITreeNode *stn;
				   CallCreateInstance("@nyapc.com/XPCOM/nsTreeNode;1",&stn);
				   if(stn!=nsnull)
				   {
					stn->SetIndex(index);
					stn->SetTreeBox(x,y,w,h);
					stn->SetNode(domnode);
					tree->AddSubTree(stn);
					nodestack.push(make_pair(domnode,stn));
				   }
				   index++;
			      }
			 }
		    }
	       }
	  }
     }
     LOG<<"size:"<<NodeArray.size()<<"\n";
     if(NodeArray.size()>=100)
     {
	  if(NodeArray.size()<400)
	       cents=6;
	  else if(NodeArray.size()<1400)
	       cents=7;
	  else if(NodeArray.size()<2400)
	       cents=8;
	  else if(NodeArray.size()<3400)
	       cents=9;
	  else
	       cents=10;
	  term.setTempRunLength(ATTDIM+cents);
	  ScaleData(NodeArray);
	  KMeanCluster(NodeArray,int(cents),alg.get());
	  return true;
     }else
     {
	  return false;
     }
}
bool LayoutAnalysis::ScaleData(std::vector<AttributeVector> &Array)
{
     double maxdepth=1,maxchild=1;
     std::vector<AttributeVector>::iterator vit=Array.begin();
     std::vector<double*> att[ATTDIM];
     for(;vit!=Array.end();++vit)
     {
	  for(int i=0;i<ATTDIM;i++)
	  {
	       att[i].push_back(&((*vit)[i]));
	  }
     }
     for(int i=0;i<ATTDIM;i++)
     {
	  ScaleVector(att[i],funArr[i]);
     }
     return true;
}
bool LayoutAnalysis::ScaleVector(std::vector<double*> &Array,ScaleFun fun)
{
     double maxdepth=1,maxchild=1;
     std::vector<double*>::iterator vit=Array.begin();
     double mean=0;
     for(;vit!=Array.end();++vit)
     {
	  if(fun!=NULL)
	       **vit=(*fun)(**vit);
	  mean+=**vit;
     }
     mean=mean/Array.size();
     double sVar=0;
     for(vit=Array.begin();vit!=Array.end();++vit)
     {
//	  sVar+=(**vit-mean)*(**vit-mean);
	  sVar+=fabs(**vit-mean);
     }
//     sVar=sqrt(sVar/(Array.size()-1));
     sVar=sVar/(Array.size()-1);
     LOG<<"mean:"<<mean<<"Var:"<<sVar<<"\n";
     if(sVar!=0)
     {
	  for(vit=Array.begin();vit!=Array.end();++vit)
	  {
	  **vit=(**vit-mean)/sVar;
	  }
     }
     return true;
}
bool LayoutAnalysis::KMeanCluster(std::vector<AttributeVector> &Array,int k,std::string alg)
{

     if(dataPts!=NULL)
	  delete dataPts;
     dataPts=new KMdata(ATTDIM, Array.size());		// allocate data storage
     // generate points
     std::vector<AttributeVector>::iterator vit=Array.begin();
     int nPts=0;
     for(;vit!=Array.end();++vit,nPts++)
     {
	  for(int i=0;i<ATTDIM;i++)
	       (*dataPts)[nPts][i]=(*vit)[i];
     }
     dataPts->setNPts(nPts);			// set actual number of pts
     dataPts->buildKcTree();			// build filtering structure

     if(ctrs!=NULL)
	  delete ctrs;
     ctrs=new KMfilterCenters(k, *dataPts);		// allocate centers

     if(alg=="Lloyd")
     {
	  KMlocalLloyds kmLloyds(*ctrs, term);		// repeated Lloyd's
	  *ctrs = kmLloyds.execute();			// execute
     }else if(alg=="Swap")
     { 
	  KMlocalSwap kmSwap(*ctrs, term);		// Swap heuristic
	  *ctrs = kmSwap.execute();
     }else if(alg=="EZ-Hybrid")
     {
	  KMlocalEZ_Hybrid kmEZ_Hybrid(*ctrs, term);	// EZ-Hybrid heuristic
	  *ctrs = kmEZ_Hybrid.execute();
     }else if(alg=="Hybrid")
     {
	  KMlocalHybrid kmHybrid(*ctrs, term);		// Hybrid heuristic
	  *ctrs = kmHybrid.execute();
     }
     return true;
}
int LayoutAnalysis::CalNodeDepth(nsIDOMNode *node)
{
     int ret=1;
     nsIDOMElement* pNode;
     node->GetParentNode((nsIDOMNode**)(&pNode));
     nsString tag;
     pNode->GetTagName(tag);
     std::string stag(NS_ConvertUTF16toUTF8(tag).get());
     while(stag!="BODY")
     {
	  ret++;
	  pNode->GetParentNode((nsIDOMNode**)(&pNode));
	  pNode->GetTagName(tag);

	  stag=std::string(NS_ConvertUTF16toUTF8(tag).get());

     }
     return ret;
}

bool LayoutAnalysis::CalSibParentDist(nsIDOMElement *node,double &pDist,double &lDist)
{
     double nsib,psib;
     std::map<std::string,std::string> nodemap;
     std::map<std::string,std::string> nsibmap;
     std::map<std::string,std::string> psibmap;
     std::map<std::string,std::string> parentmap;
     
     GetComLayoutInfo(node,nodemap);
     
     nsCOMPtr<nsIDOMNode> pSibNode;
     node->GetPreviousSibling(getter_AddRefs(pSibNode));
     PRUint16 tmptype=0;
     if(pSibNode!=nsnull)
	  pSibNode->GetNodeType(&tmptype);
     while(pSibNode!=nsnull&&tmptype!=nsIDOMNode::ELEMENT_NODE)
     {
	  pSibNode->GetPreviousSibling(getter_AddRefs(pSibNode));
	  if(pSibNode!=nsnull)
	       pSibNode->GetNodeType(&tmptype);
     }
     nsCOMPtr<nsIDOMElement> pSibEle=do_QueryInterface(pSibNode);
     if(pSibEle!=nsnull)
     {
	  GetComLayoutInfo(pSibEle,psibmap);
	  psib=compare_styles(nodemap, psibmap);
     }else
     {
	  psib=0;
     }
     nsCOMPtr<nsIDOMNode> nSibNode;
     node->GetNextSibling(getter_AddRefs(nSibNode));
     if(nSibNode!=nsnull)
	  nSibNode->GetNodeType(&tmptype);
     while(nSibNode!=nsnull&&tmptype!=nsIDOMNode::ELEMENT_NODE)
     {
	  nSibNode->GetNextSibling(getter_AddRefs(nSibNode));
	  if(nSibNode!=nsnull)
	       nSibNode->GetNodeType(&tmptype);
     }
     nsCOMPtr<nsIDOMElement> nSibEle=do_QueryInterface(nSibNode);
     if(nSibEle!=nsnull)
     {
	  GetComLayoutInfo(nSibEle,nsibmap);
	  nsib=compare_styles(nodemap, nsibmap);
     }else
     {
	  nsib=0;
     }
     if(nSibEle!=nsnull&&pSibEle!=nsnull)
     {
	  lDist=(psib+nsib)/2;
     }else if(nSibEle==nsnull&&pSibEle==nsnull)
     {
	  lDist=1;
     }
     else
     {
	  lDist=psib+nsib;
     }
     nsCOMPtr<nsIDOMNode> pNode;
     node->GetParentNode(getter_AddRefs(pNode));
     nsCOMPtr<nsIDOMElement> pSEle=do_QueryInterface(pNode);
     
     GetComLayoutInfo(pSEle,parentmap);

     pDist=compare_styles(nodemap, parentmap);
     return true;
     
}

void LayoutAnalysis::GetComLayoutInfo(nsIDOMElement* node,std::map<std::string,std::string> &lmap)
{

     if(viewCSS!=nsnull)
     {
	  nsCOMPtr<nsIDOMCSSStyleDeclaration> style;
	  viewCSS->GetComputedStyle(node, EmptyString(),getter_AddRefs(style));
	  if(style!=nsnull)
	  {
	       PRUint32 slen;
	       style->GetLength(&slen);
	       nsString csstext;
	       style->GetCssText(csstext);
	       for(int j=0;j<slen;j++)
	       {
		    nsString name;
		    nsString value;
		    nsString prio;
		    style->Item(j,name);
		    style->GetPropertyValue(name,value);
		    
		    std::string strName(NS_ConvertUTF16toUTF8(name).get());
		    
		    std::map<std::string,std::string>::iterator fit=lmap.find(strName);
		    if(fit==lmap.end())
		    {
			 lmap.insert(make_pair(strName,std::string(NS_ConvertUTF16toUTF8(value).get())));
		    }
	       }
	  }
     }
}

/* void SetKMeanAlg (in AUTF8String alg); */
NS_IMETHODIMP LayoutAnalysis::SetKMeanAlg(const nsACString & alg)
{
     this->alg=alg;
     return NS_OK;
}


/* void GetResult (out nsITreeNode tree); */
NS_IMETHODIMP LayoutAnalysis::GetResult(nsITreeNode **tree)
{
     NS_ENSURE_ARG_POINTER(tree);
     *tree = nsnull;
     nsCOMPtr<nsITreeNode> tn=do_CreateInstance("@nyapc.com/XPCOM/nsTreeNode;1");

     nsresult rv;

     if(NeedAly)
     {
	  if(!BlockCluster(tn))
	       return NS_ERROR_FAILURE;
     } 

     KMctrIdxArray closeCtr = new KMctrIdx[dataPts->getNPts()];
     double* sqDist = new double[dataPts->getNPts()];
     ctrs->getAssignments(closeCtr, sqDist);
     double* CenDist = ctrs->getDists();
     int maxIndex=0;
     int secIndex=0;
     double maxpar=0;
     double Secpar=0;
     
     ctrs->print();
     double totalDist=0;
     std::map<double,int> classmap;
     double minH=0;
     double minsH=0;
     for (int j = 0; j < cents; j++) {
	  double atts=0;
	  if(CenDist[j]==0)
	  {
	       atts=-100;
	  }else
	       atts=-((*ctrs)[j][2])+(*ctrs)[j][3]+(*ctrs)[j][4];
	  //Get the minimal two of (h-30)-(w/w+h)
	  if(minH>((*ctrs)[j][5]-(*ctrs)[j][3]))
	  {
	       minsH=minH;
	       minH=((*ctrs)[j][5]-(*ctrs)[j][3]);
	  }else if(minsH>((*ctrs)[j][5]-(*ctrs)[j][3]))
	  {
	       minsH=((*ctrs)[j][5]-(*ctrs)[j][3]);
	  }
	  LOG<<minH<<":"<<minsH<<"\n";
	  totalDist+=CenDist[j];
	  classmap.insert(make_pair(atts,j));
     }
     int *cv=new int[dataPts->getNPts()];
     for(int i=0;i<dataPts->getNPts();i++)
     {
	  cv[i]=closeCtr[i];
     }
     int *cutset=new int[cents];
     int *bigset=new int[cents];
     int bigsetCount=0;
     std::map<double,int>::iterator rit=classmap.begin();
     std::map<double,int>::iterator rend=classmap.end();
     // for(;rit!=rend;++rit)
//      {
// 	  if(CenDist[rit->second]<totalDist/(cents*5))
// 	  {
// 	       bigset[bigsetCount]=rit->second;
// 	       bigsetCount++;
// 	       classmap.erase(rit);
// 	  }
//      }
     rit=classmap.begin();
     rend=classmap.end();
     --rend;
     bigset[bigsetCount]=rend->second;
     bigsetCount++;
     --rend;
     bigset[bigsetCount]=rend->second;
     bigsetCount++;
     int setCount=0;
     for(/*++rit*/;rit!=rend;++rit)
     {
	  if(((*ctrs)[rit->second][5]-(*ctrs)[rit->second][3])>minsH)
	  {
	       cutset[setCount]=rit->second;
	       setCount++;
	       LOG<<rit->first<<":"<<rit->second<<"\n";
	  }
     }
     delete [] sqDist;
     delete [] closeCtr;
     tn->SetClass(cv,dataPts->getNPts());
     tn->CutTree(cutset,setCount);
     tn->CutTreeForChl(bigset,bigsetCount);
     tn->PrintTree();
     delete [] cv;
     delete [] cutset;
     delete [] bigset;
     NeedAly=true;
     *tree=tn;
     NS_ADDREF(*tree);
     return NS_OK;
}

NS_IMETHODIMP LayoutAnalysis::SetClassCount(PRUint32 n)
{
     cents=n;
     return NS_OK;
}
NS_IMETHODIMP LayoutAnalysis::SetFilterPath(const nsAString & path)
{
     xpath=path;
     return NS_OK;
}
std::string & LayoutAnalysis::get_node_path(nsIDOMNode * node, std::string & path)
{
     std::string stop_pos("BODY");
	return get_node_path(node,path,stop_pos);
}

std::string & LayoutAnalysis::get_node_path(nsIDOMNode * node, std::string & path, std::string & stop_pos)
{
     nsresult rv;
     nsIDOMNode * parent = nsnull;
     if(node == nsnull)
	  return path;
     
     nsString node_name;
     rv = node->GetNodeName(node_name);
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get Node Name Error:"<<std::hex<<rv<<std::endl;
	  return path;
     }

     std::string s(NS_ConvertUTF16toUTF8(node_name).get());

     if(s.compare(stop_pos)==0) return path;
     if(s.at(0)=='#') return path;
     
     path.append(s);
     
     //cout << "get_node_path" <<path<<endl;
     
     rv = node->GetParentNode(&parent);
     if (NS_FAILED(rv))
     {
	  std::cout<<"Get Parent Error:"<<std::hex<<rv<<std::endl;
	  return path;
     }
     else
     {
	  //Get Attrs
	  nsIDOMNamedNodeMap * attrs_map;
	  rv = node->GetAttributes(&attrs_map);
	  std::map<std::string,std::string> attr;
	  if(NS_FAILED(rv))
	  {
	       cout << "Get attributes error" << endl;
	  }
	  else
	  {
	       PRUint32 len;
	       attrs_map->GetLength(&len);
	       for(int i = 0; i<len; i++)
	       {
		    nsIDOMNode * n;
		    attrs_map->Item(i,&n);
		    nsString value;
		    n->GetNodeValue(value);
		    nsString name;
		    n->GetNodeName(name);

		    std::string str_name(NS_ConvertUTF16toUTF8(name).get());
		    std::string str_value(NS_ConvertUTF16toUTF8(value).get());

		    attr.insert(pair<string,string>(str_name,str_value));
	       }
	  }
	  if(attr.size()>0)
	  {
	       path.append(":");
	  }
	  std::map<std::string,std::string>::iterator it;
	  for(it=attr.begin();it!=attr.end();it++)
	  {
	       if(it->first.compare("href")!=0 && it->first.compare("title")!=0)
		    path.append(" ").append(it->first).append("=").append(it->second);
	  }
	  path.append("/");
	  return get_node_path(parent, path);
     }
     
}
