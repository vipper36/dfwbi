#include "nsTreeNode.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"

#include "nsIDOMDocument.h"
#include "nsIDOMElement.h"
#include "nsIDOMNode.h"
#include "nsIDOM3Node.h"
#include "property.h"
#include <list>
NS_IMPL_ISUPPORTS1(nsTreeNode, nsITreeNode)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsTreeNode)

static nsModuleComponentInfo components[] =
{
     {
	  NS_TREENODE_CLASSNAME,
	  NS_TREENODE_CID,
	  NS_TREENODE_CONTRACTID,
	  nsTreeNodeConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsTreeNodeModule", components)

nsTreeNode::nsTreeNode()
:mX(0),
     mY(0),
     mW(0),
     mH(0),
     index(-1),
     classid(-1)
{
     subTrees = do_CreateInstance(NS_SUPPORTSARRAY_CONTRACTID);
  /* member initializers and constructor code */
}

nsTreeNode::~nsTreeNode()
{
     LOG<<"Clear subtree\n";
     ClearSub();
  /* destructor code */
}

/* attribute long mX; */
NS_IMETHODIMP nsTreeNode::GetMX(PRInt32 *aMX)
{
     *aMX=mX;
     return NS_OK;
}
NS_IMETHODIMP nsTreeNode::SetMX(PRInt32 aMX)
{
     mX=aMX;
     return NS_OK;
}

/* attribute long mY; */
NS_IMETHODIMP nsTreeNode::GetMY(PRInt32 *aMY)
{
     *aMY=mY;
     return NS_OK;
}
NS_IMETHODIMP nsTreeNode::SetMY(PRInt32 aMY)
{
     mY=aMY;
     return NS_OK;
}

/* attribute long mW; */
NS_IMETHODIMP nsTreeNode::GetMW(PRInt32 *aMW)
{
     *aMW=mW;
     return NS_OK;
}
NS_IMETHODIMP nsTreeNode::SetMW(PRInt32 aMW)
{
     mW=aMW;
     return NS_OK;
}

/* attribute long mH; */
NS_IMETHODIMP nsTreeNode::GetMH(PRInt32 *aMH)
{
     *aMH=mH;
     return NS_OK;
}
NS_IMETHODIMP nsTreeNode::SetMH(PRInt32 aMH)
{
     mH=aMH;
     return NS_OK;
}

/* attribute long index; */
NS_IMETHODIMP nsTreeNode::GetIndex(PRInt32 *aIndex)
{
     *aIndex=index;
     return NS_OK;
}
NS_IMETHODIMP nsTreeNode::SetIndex(PRInt32 aIndex)
{

     index=aIndex;
     return NS_OK;
}

/* attribute nsIDOMNode node; */
NS_IMETHODIMP nsTreeNode::GetNode(nsIDOMNode * *aNode)
{
     *aNode=node;
     return NS_OK;
}
NS_IMETHODIMP nsTreeNode::SetNode(nsIDOMNode * aNode)
{
     node=aNode;
     return NS_OK;
}

/* void AddSubTree (in nsITreeNode tree); */
NS_IMETHODIMP nsTreeNode::AddSubTree(nsITreeNode *tree)
{
     nsISupports *tmp;
     CallQueryInterface(tree,&tmp);
     subTrees->AppendElement(tmp);
     return NS_OK;
}

/* void PrintTree (); */
NS_IMETHODIMP nsTreeNode::PrintTree()
{
     LOG<<std::dec<<mX<<","<<mY<<","<<mW<<","<<mH<<"\n";
     LOG<<"class:"<<classid<<"\n";
     PRUint32 len;
     subTrees->Count(&len);
     for(PRUint32 i=0;i<len;i++)
     {
	  nsITreeNode *tree; 
	  nsISupports *tmp;
	  tmp=subTrees->ElementAt(i);

	  CallQueryInterface(tmp,&tree);
	  if(tree!=nsnull)
	       tree->PrintTree();
     }
     return NS_OK;
}

/* void GetSubTree (out nsISupportsArray array); */
NS_IMETHODIMP nsTreeNode::GetSubTree(nsISupportsArray **array)
{
     NS_ENSURE_ARG_POINTER(array);
     *array = nsnull;
     *array=subTrees;
     NS_ADDREF(*array);
     return NS_OK;
}


/* long GetArea (); */
NS_IMETHODIMP nsTreeNode::GetArea(PRInt32 *_retval)
{
     *_retval=mW*mH;
     return NS_OK;
}

/* void SetTreeBox (in long x, in long y, in long w, in long h); */
NS_IMETHODIMP nsTreeNode::SetTreeBox(PRInt32 x, PRInt32 y, PRInt32 w, PRInt32 h)
{
     mX=x;
     mY=y;
     mW=w;
     mH=h;
    return NS_OK;
}

/* void ClearSub (); */
NS_IMETHODIMP nsTreeNode::ClearSub()
{
     PRUint32 slen=0;
     subTrees->Count(&slen);
     LOG<<"sub len:"<<slen<<"\n";     
     for(PRUint32 j=0;j<slen;j++)
     {
	   nsISupports *stmp;
	   stmp=subTrees->ElementAt(j);
	   NS_IF_RELEASE(stmp);
     }
     subTrees->Clear();
     return NS_OK;
}


NS_IMETHODIMP nsTreeNode::GetWHRate(double *_retval)
{
     *_retval=((double)mW)/mH;
     return NS_OK;
}
/* void SetClass ([array, size_is (cv_size)] in long cv, in unsigned long cv_size); */
NS_IMETHODIMP nsTreeNode::SetClass(PRInt32 *cv, PRUint32 cv_size)
{
     PRUint32 len=0;
     if(index<0)
	  classid=-1;
     else
	  classid=cv[index];
     subTrees->Count(&len);
     for(PRUint32 i=0;i<len;i++)
     {
	  nsITreeNode *tree; 
	  nsISupports *tmp;
	  tmp=subTrees->ElementAt(i);
	  CallQueryInterface(tmp,&tree);
	  
	  if(tree!=nsnull)
	  {
	       tree->SetClass(cv,cv_size);
	  }
     }
     return NS_OK;
}

/* void CutTree ([array, size_is (id_size)] in long id, in unsigned long id_size); */
NS_IMETHODIMP nsTreeNode::CutTree(PRInt32 *id, PRUint32 id_size)
{
     PRUint32 len;
     std::list<nsITreeNode*> target;

     std::set<PRInt32> ids;
     for(PRInt32 i=0;i<id_size;i++)
     {
	  ids.insert(id[i]);
     }

     subTrees->Count(&len);
     for(PRUint32 i=0;i<len;i++)
     {
	  nsITreeNode *tree;
	  nsISupports *tmp;
	  tmp=subTrees->ElementAt(i);
	  CallQueryInterface(tmp,&tree);
	  if(tree!=nsnull)
	  {
	       PRInt32 subId;
	       tree->CutTree(id,id_size);
	       tree->GetClassId(&subId);
	       if(ids.find(subId)==ids.end())
	       {
 		    target.push_back(tree);
	       }
	       else
	       {
		    nsCOMPtr<nsISupportsArray> array;

		    tree->GetSubTree(getter_AddRefs(array));
		    
		    PRUint32 slen;
		    array->Count(&slen);
		    for(PRUint32 j=0;j<slen;j++)
		    {
			 nsITreeNode *stree;
			 nsISupports *stmp;
			 stmp=array->ElementAt(j);

			 CallQueryInterface(stmp,&stree);

			 target.push_back(stree);
		    }

		    NS_IF_RELEASE(tree);
	       }
	       
	  }
     }
     subTrees->Clear();

     std::list<nsITreeNode*>::iterator tit=target.begin();
     for(;tit!=target.end();++tit)
     {
	  AddSubTree(*tit);
     }

     return NS_OK;
}

/* void CutTreeForChl ([array, size_is (id_size)] in long id, in unsigned long id_size); */
NS_IMETHODIMP nsTreeNode::CutTreeForChl(PRInt32 *id, PRUint32 id_size)
{
     PRUint32 len;
     std::list<nsITreeNode*> target;
     if(!ids.empty())
     {
	  ids.clear();
     }
     for(PRInt32 i=0;i<id_size;i++)
     {
	  ids.insert(id[i]);
     }

     int sindCount=0;
     subTrees->Count(&len);
     for(PRUint32 i=0;i<len;i++)
     {
	  nsITreeNode *tree; 
	  nsISupports *tmp;
	  tmp=subTrees->ElementAt(i);
	  CallQueryInterface(tmp,&tree);

	  if(tree!=nsnull)
	  {
	       PRInt32 subId;
	       tree->CutTreeForChl(id,id_size);
	       tree->GetClassId(&subId);
	       if(ids.find(subId)==ids.end())
	       {
		    nsCString text;
		    tree->GetTreeText(text);
		    text.StripChars(" ");
		    text.StripChars("\n");
		    if(sindCount==0&&text.Length()>0)
		    {
			 target.push_back(tree); 
		    }else
		    {
			 NS_IF_RELEASE(tree); 
		    }
		    if(text.Length()>0)
			 sindCount++;
		    
	       }else
	       {
		    target.push_back(tree);
	       }
	  }
     }
     subTrees->Clear();

     std::list<nsITreeNode*>::iterator tit=target.begin();
     for(;tit!=target.end();++tit)
     {
	  AddSubTree(*tit);
     }
    return NS_OK;
}
/* long GetClassId (); */
NS_IMETHODIMP nsTreeNode::GetClassId(PRInt32 *_retval)
{
     *_retval=classid;
     return NS_OK;
}
/* boolean IsBigBox (); */
NS_IMETHODIMP nsTreeNode::IsBigBox(PRBool *_retval)
{
     if(classid<0)
     {
	  *_retval=PR_TRUE;
     }else
     {
	  PRBool ret=ids.find(classid)!=ids.end();
	  *_retval=ret;
     }
     return NS_OK;
}
/* void GetTreeText (out AUTF8String text); */
NS_IMETHODIMP nsTreeNode::GetTreeText(nsACString & text)
{
     if(node!=nsnull)
     {
	  nsString tmpText;
	  nsCOMPtr<nsIDOM3Node> tmpnsEle=do_QueryInterface(node);
	  tmpnsEle->GetTextContent(tmpText);
	  text=NS_ConvertUTF16toUTF8(tmpText);
     }
     return NS_OK;
}
