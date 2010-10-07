#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsIDOMAbstractView.h"
#include "nsIDOMDocumentView.h"
#include "nsIDOMDocument.h"
#include "nsIDOMCSSStyleDeclaration.h"
#include "nsIDOMHTMLElement.h"
#include "nsNetUtil.h"
#include "ContentDocAtt.h"
#include "nsIAttVec.h"
#include "nsIBoxObject.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMElement.h"
#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsISupports.h"
#include <iostream>
#include <sstream>
#include <stack>
#include "math.h"
#include "property.h"
#include "StyleCompare.h"
#define VISUALAREA 1024*768

NS_IMPL_ISUPPORTS1(ContentDocAtt, nsIDocAtt)

NS_GENERIC_FACTORY_CONSTRUCTOR(ContentDocAtt)

static nsModuleComponentInfo components[] =
{
     {
	  CONTENTDOCATT_CLASSNAME,
	  CONTENTDOCATT_CID,
	  CONTENTDOCATT_CONTRACTID,
	  ContentDocAttConstructor,
     }
};
NS_IMPL_NSGETMODULE("ContentDocAttModule", components)



ContentDocAtt::ContentDocAtt()
{
     nsresult rv;
     p_attset = do_CreateInstance("@nyapc.com/XPCOM/nsAttSet;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"[ContentDocAtt] Constructor:nsAttSet initialize error!\n";;
     }

     p_dimstat = do_CreateInstance("@nyapc.com/XPCOM/nsDimStat;1");
     if (NS_FAILED(rv))
     {
	 LOG<<"[ContentDocAtt] Constructor:nsDimStat initialize error!\n";;
     }
     p_xpathutil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
     if (NS_FAILED(rv))
     {
	 LOG << "[ContentDocAtt] Constructor:Get nsIXpathUtil Error" << rv << "\n";
     }
     p_docset = do_CreateInstance("@nyapc.com/XPCOM/nsDocSet;1", &rv);
     if (NS_FAILED(rv))
     {
	 LOG << "[ContentDocAtt] Constructor:Get nsIDocSet Error" << rv << "\n";
     }
}

ContentDocAtt::~ContentDocAtt()
{
  /* destructor code */
}
/* attribute nsIAttDim dim; */
NS_IMETHODIMP ContentDocAtt::GetDim(nsIAttDim * *aDim)
{
     *aDim=p_attdim;
     NS_ADDREF(*aDim);
     return NS_OK;
}
NS_IMETHODIMP ContentDocAtt::SetDim(nsIAttDim * aDim)
{
     p_attdim=aDim;
     p_dimstat->SetAttDim(aDim);
     return NS_OK;
}
/* 
NS_IMETHODIMP ContentDocAtt::SetDocSet(nsIDocSet *docs)
{
    LOG<<"[ContentDocAtt] SetDocSet:set docs here\n";
    if(nsnull == docs)
    {
	return NS_OK;
    }
    PRInt32 doc_counts = 0;
    docs->GetDocCount(&doc_counts);

    //Statistic the dimension attributes of xpath.
    DoStatistic(docs, doc_counts);

    //Generate the AttSet(Vector Space).
    GenerateAttSet(docs, doc_counts);

    return NS_OK;
}
*/
/* long GetVectorCount (); */
NS_IMETHODIMP ContentDocAtt::GetVectorCount(PRInt32 *_retval )
{
    p_attset->GetLength(_retval);
    return NS_OK;
}

/* nsIAttVec GetVectorByIndex (in long index); */
NS_IMETHODIMP ContentDocAtt::GetVectorByIndex(PRInt32 index, nsIAttVec **_retval )
{
    p_attset->GetVectorByIndex(index,_retval);
    return NS_OK;
}

/* nsIAttSet GetResult (); */
NS_IMETHODIMP ContentDocAtt::GetResult(nsIAttSet **_retval)
{
    if(nsnull == p_docset)
    {
	return NS_OK;
    }

    PRInt32 doc_counts = 0;
    p_docset->GetDocCount(&doc_counts);

    //Statistic the dimension attributes of xpath.
    DoStatistic(p_docset, doc_counts);

    //Generate the AttSet(Vector Space).
    GenerateAttSet(p_docset, doc_counts);

    *_retval = p_attset;
    NS_ADDREF(*_retval);
    return NS_OK;
}

void ContentDocAtt::DoStatistic(nsIDocSet * docs, PRInt32 doc_counts)
{
    for(int i = 0; i < doc_counts; i++)
    {
	nsIDOMDocument * doc = nsnull;
	docs->GetDocByIndex(i, &doc);
	if(nsnull != doc)
	{
	    p_dimstat->SetDocument(doc);
	}

    }

    LOG<<"[ContentDocAtt] DoStatistic:print statistic results.\n";
    PrintStatisticResults();
    LOG<<"[ContentDocAtt] DoStatistic:print ok.\n";
}

void ContentDocAtt::PrintStatisticResults()
{
    PRInt32 dim_count = 0;
    p_attdim->GetCount(&dim_count);
    for(int id = 0; id < dim_count; id++)
    {
	nsCString xpath;
	p_attdim->GetDesc(id, xpath);
	double weight = 0.0;
	p_dimstat->GetAvrgWeightByDim(id, &weight);

	LOG<<"[ContentDocAtt] id: "<<id<<" weight: "<<weight<<" xpath: "<<xpath.get()<<"\n";
    }
}

void ContentDocAtt::GenerateAttSet(nsIDocSet * docs, PRInt32 doc_counts)
{
    //
    for(int i = 0; i < doc_counts; i++)
    {
	nsCOMPtr<nsIDOMDocument> doc = nsnull;
	docs->GetDocByIndex(i, getter_AddRefs(doc));
	if(nsnull != doc)
	{
	    nsresult rv;
	    nsCOMPtr<nsIAttVec> vector = do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1",&rv);
	    if (NS_FAILED(rv))
	    {
		LOG<<"[ContentDocAtt] GenerateAttSet:nsAttVec initialize error!\n";;
	    }
	    vector->SetDoc(doc);
	    nsCOMPtr<nsIDOMNode> node = do_QueryInterface(doc);
	    LOG<<"[ContentDocAtt] GenerateAttSet: init vector.\n";;
	    WalkTree(node,doc,vector);
	    p_attset->AppendVector(vector);
	}

    }
}

void ContentDocAtt::WalkTree(nsIDOMNode * node, nsIDOMDocument * doc, nsIAttVec * attvec)
{
	if(nsnull == node){
		LOG << "[ContentDocAtt] WalkTree:node is null";
		return;
	}

	nsresult rv;
	PRBool has_child = false;
	node->HasChildNodes(&has_child);
	if(has_child){
		nsCOMPtr<nsIDOMNodeList> children;
		rv = node->GetChildNodes(getter_AddRefs(children));
		if(!NS_FAILED(rv)){
			PRUint32 len;
			children->GetLength(&len);
			for(int i = 0; i < len; i++)
			{
				nsIDOMNode * n;
				children->Item(i, &n);

				nsString name;
				n->GetNodeName(name);
				unsigned short type;
				n->GetNodeType(&type);

				if(type == nsIDOMNode::ELEMENT_NODE)
				{
					//Get statistic weight here
					//LOG << "[ContentDocAtt] WalkTree: get statistic weight.\n";
					nsCString xpath;
					p_xpathutil->SetDocument(doc);
					p_xpathutil->GetXpath(n, 1, xpath);
					PRInt32 id = -1;
					p_attdim->GetDimId(xpath,&id);
					double weight = 0.0;
					if(id >= 0)
					{
					    p_dimstat->GetAvrgWeightByDim(id, &weight);
					    //LOG << "[ContentDocAtt] WalkTree:dimid "<<id<< " weight " << weight <<" xpath "<<xpath.get()<<"\n";
					    attvec->AddValue(id, weight);
					}

					//Recursive walk
					WalkTree(n, doc, attvec);
				}
			}
		}
	}
}
/* void AddDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP ContentDocAtt::AddDocument(nsIDOMDocument *doc)
{
    p_docset->AddDocument(doc);
    
    //PRInt32 doc_counts = 0;
    //p_docset->GetDocCount(&doc_counts);
    //LOG<< "[ContentDocAtt] AddDocument: document count is " << doc_counts <<"\n";
    return NS_OK;
}
