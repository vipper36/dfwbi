/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsITreeNode.idl
 */

#ifndef __gen_nsITreeNode_h__
#define __gen_nsITreeNode_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMNode; /* forward declaration */

class nsISupportsArray; /* forward declaration */


/* starting interface:    nsITreeNode */
#define NS_ITREENODE_IID_STR "f4882709-fc1f-4dab-bd56-91987b91eced"

#define NS_ITREENODE_IID \
  {0xf4882709, 0xfc1f, 0x4dab, \
    { 0xbd, 0x56, 0x91, 0x98, 0x7b, 0x91, 0xec, 0xed }}

class NS_NO_VTABLE NS_SCRIPTABLE nsITreeNode : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ITREENODE_IID)

  /* attribute long mX; */
  NS_SCRIPTABLE NS_IMETHOD GetMX(PRInt32 *aMX) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetMX(PRInt32 aMX) = 0;

  /* attribute long mY; */
  NS_SCRIPTABLE NS_IMETHOD GetMY(PRInt32 *aMY) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetMY(PRInt32 aMY) = 0;

  /* attribute long mW; */
  NS_SCRIPTABLE NS_IMETHOD GetMW(PRInt32 *aMW) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetMW(PRInt32 aMW) = 0;

  /* attribute long mH; */
  NS_SCRIPTABLE NS_IMETHOD GetMH(PRInt32 *aMH) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetMH(PRInt32 aMH) = 0;

  /* attribute long index; */
  NS_SCRIPTABLE NS_IMETHOD GetIndex(PRInt32 *aIndex) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetIndex(PRInt32 aIndex) = 0;

  /* attribute nsIDOMNode node; */
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode) = 0;

  /* void AddSubTree (in nsITreeNode tree); */
  NS_SCRIPTABLE NS_IMETHOD AddSubTree(nsITreeNode *tree) = 0;

  /* void PrintTree (); */
  NS_SCRIPTABLE NS_IMETHOD PrintTree(void) = 0;

  /* void GetSubTree (out nsISupportsArray array); */
  NS_SCRIPTABLE NS_IMETHOD GetSubTree(nsISupportsArray **array) = 0;

  /* long GetArea (); */
  NS_SCRIPTABLE NS_IMETHOD GetArea(PRInt32 *_retval) = 0;

  /* void SetTreeBox (in long x, in long y, in long w, in long h); */
  NS_SCRIPTABLE NS_IMETHOD SetTreeBox(PRInt32 x, PRInt32 y, PRInt32 w, PRInt32 h) = 0;

  /* void ClearSub (); */
  NS_SCRIPTABLE NS_IMETHOD ClearSub(void) = 0;

  /* double GetWHRate (); */
  NS_SCRIPTABLE NS_IMETHOD GetWHRate(double *_retval) = 0;

  /* void SetClass ([array, size_is (cv_size)] in long cv, in unsigned long cv_size); */
  NS_SCRIPTABLE NS_IMETHOD SetClass(PRInt32 *cv, PRUint32 cv_size) = 0;

  /* void CutTree ([array, size_is (id_size)] in long id, in unsigned long id_size); */
  NS_SCRIPTABLE NS_IMETHOD CutTree(PRInt32 *id, PRUint32 id_size) = 0;

  /* void CutTreeForChl ([array, size_is (id_size)] in long id, in unsigned long id_size); */
  NS_SCRIPTABLE NS_IMETHOD CutTreeForChl(PRInt32 *id, PRUint32 id_size) = 0;

  /* long GetClassId (); */
  NS_SCRIPTABLE NS_IMETHOD GetClassId(PRInt32 *_retval) = 0;

  /* boolean IsBigBox (); */
  NS_SCRIPTABLE NS_IMETHOD IsBigBox(PRBool *_retval) = 0;

  /* void GetTreeText (out AUTF8String text); */
  NS_SCRIPTABLE NS_IMETHOD GetTreeText(nsACString & text) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsITreeNode, NS_ITREENODE_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSITREENODE \
  NS_SCRIPTABLE NS_IMETHOD GetMX(PRInt32 *aMX); \
  NS_SCRIPTABLE NS_IMETHOD SetMX(PRInt32 aMX); \
  NS_SCRIPTABLE NS_IMETHOD GetMY(PRInt32 *aMY); \
  NS_SCRIPTABLE NS_IMETHOD SetMY(PRInt32 aMY); \
  NS_SCRIPTABLE NS_IMETHOD GetMW(PRInt32 *aMW); \
  NS_SCRIPTABLE NS_IMETHOD SetMW(PRInt32 aMW); \
  NS_SCRIPTABLE NS_IMETHOD GetMH(PRInt32 *aMH); \
  NS_SCRIPTABLE NS_IMETHOD SetMH(PRInt32 aMH); \
  NS_SCRIPTABLE NS_IMETHOD GetIndex(PRInt32 *aIndex); \
  NS_SCRIPTABLE NS_IMETHOD SetIndex(PRInt32 aIndex); \
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode); \
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode); \
  NS_SCRIPTABLE NS_IMETHOD AddSubTree(nsITreeNode *tree); \
  NS_SCRIPTABLE NS_IMETHOD PrintTree(void); \
  NS_SCRIPTABLE NS_IMETHOD GetSubTree(nsISupportsArray **array); \
  NS_SCRIPTABLE NS_IMETHOD GetArea(PRInt32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetTreeBox(PRInt32 x, PRInt32 y, PRInt32 w, PRInt32 h); \
  NS_SCRIPTABLE NS_IMETHOD ClearSub(void); \
  NS_SCRIPTABLE NS_IMETHOD GetWHRate(double *_retval); \
  NS_SCRIPTABLE NS_IMETHOD SetClass(PRInt32 *cv, PRUint32 cv_size); \
  NS_SCRIPTABLE NS_IMETHOD CutTree(PRInt32 *id, PRUint32 id_size); \
  NS_SCRIPTABLE NS_IMETHOD CutTreeForChl(PRInt32 *id, PRUint32 id_size); \
  NS_SCRIPTABLE NS_IMETHOD GetClassId(PRInt32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD IsBigBox(PRBool *_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetTreeText(nsACString & text); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSITREENODE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetMX(PRInt32 *aMX) { return _to GetMX(aMX); } \
  NS_SCRIPTABLE NS_IMETHOD SetMX(PRInt32 aMX) { return _to SetMX(aMX); } \
  NS_SCRIPTABLE NS_IMETHOD GetMY(PRInt32 *aMY) { return _to GetMY(aMY); } \
  NS_SCRIPTABLE NS_IMETHOD SetMY(PRInt32 aMY) { return _to SetMY(aMY); } \
  NS_SCRIPTABLE NS_IMETHOD GetMW(PRInt32 *aMW) { return _to GetMW(aMW); } \
  NS_SCRIPTABLE NS_IMETHOD SetMW(PRInt32 aMW) { return _to SetMW(aMW); } \
  NS_SCRIPTABLE NS_IMETHOD GetMH(PRInt32 *aMH) { return _to GetMH(aMH); } \
  NS_SCRIPTABLE NS_IMETHOD SetMH(PRInt32 aMH) { return _to SetMH(aMH); } \
  NS_SCRIPTABLE NS_IMETHOD GetIndex(PRInt32 *aIndex) { return _to GetIndex(aIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetIndex(PRInt32 aIndex) { return _to SetIndex(aIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode) { return _to GetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode) { return _to SetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD AddSubTree(nsITreeNode *tree) { return _to AddSubTree(tree); } \
  NS_SCRIPTABLE NS_IMETHOD PrintTree(void) { return _to PrintTree(); } \
  NS_SCRIPTABLE NS_IMETHOD GetSubTree(nsISupportsArray **array) { return _to GetSubTree(array); } \
  NS_SCRIPTABLE NS_IMETHOD GetArea(PRInt32 *_retval) { return _to GetArea(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetTreeBox(PRInt32 x, PRInt32 y, PRInt32 w, PRInt32 h) { return _to SetTreeBox(x, y, w, h); } \
  NS_SCRIPTABLE NS_IMETHOD ClearSub(void) { return _to ClearSub(); } \
  NS_SCRIPTABLE NS_IMETHOD GetWHRate(double *_retval) { return _to GetWHRate(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetClass(PRInt32 *cv, PRUint32 cv_size) { return _to SetClass(cv, cv_size); } \
  NS_SCRIPTABLE NS_IMETHOD CutTree(PRInt32 *id, PRUint32 id_size) { return _to CutTree(id, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD CutTreeForChl(PRInt32 *id, PRUint32 id_size) { return _to CutTreeForChl(id, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassId(PRInt32 *_retval) { return _to GetClassId(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsBigBox(PRBool *_retval) { return _to IsBigBox(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTreeText(nsACString & text) { return _to GetTreeText(text); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSITREENODE(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetMX(PRInt32 *aMX) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMX(aMX); } \
  NS_SCRIPTABLE NS_IMETHOD SetMX(PRInt32 aMX) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMX(aMX); } \
  NS_SCRIPTABLE NS_IMETHOD GetMY(PRInt32 *aMY) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMY(aMY); } \
  NS_SCRIPTABLE NS_IMETHOD SetMY(PRInt32 aMY) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMY(aMY); } \
  NS_SCRIPTABLE NS_IMETHOD GetMW(PRInt32 *aMW) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMW(aMW); } \
  NS_SCRIPTABLE NS_IMETHOD SetMW(PRInt32 aMW) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMW(aMW); } \
  NS_SCRIPTABLE NS_IMETHOD GetMH(PRInt32 *aMH) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetMH(aMH); } \
  NS_SCRIPTABLE NS_IMETHOD SetMH(PRInt32 aMH) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetMH(aMH); } \
  NS_SCRIPTABLE NS_IMETHOD GetIndex(PRInt32 *aIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetIndex(aIndex); } \
  NS_SCRIPTABLE NS_IMETHOD SetIndex(PRInt32 aIndex) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetIndex(aIndex); } \
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD AddSubTree(nsITreeNode *tree) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddSubTree(tree); } \
  NS_SCRIPTABLE NS_IMETHOD PrintTree(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->PrintTree(); } \
  NS_SCRIPTABLE NS_IMETHOD GetSubTree(nsISupportsArray **array) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSubTree(array); } \
  NS_SCRIPTABLE NS_IMETHOD GetArea(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetArea(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetTreeBox(PRInt32 x, PRInt32 y, PRInt32 w, PRInt32 h) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTreeBox(x, y, w, h); } \
  NS_SCRIPTABLE NS_IMETHOD ClearSub(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearSub(); } \
  NS_SCRIPTABLE NS_IMETHOD GetWHRate(double *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWHRate(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetClass(PRInt32 *cv, PRUint32 cv_size) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClass(cv, cv_size); } \
  NS_SCRIPTABLE NS_IMETHOD CutTree(PRInt32 *id, PRUint32 id_size) { return !_to ? NS_ERROR_NULL_POINTER : _to->CutTree(id, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD CutTreeForChl(PRInt32 *id, PRUint32 id_size) { return !_to ? NS_ERROR_NULL_POINTER : _to->CutTreeForChl(id, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassId(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassId(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsBigBox(PRBool *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsBigBox(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetTreeText(nsACString & text) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTreeText(text); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsTreeNode : public nsITreeNode
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSITREENODE

  nsTreeNode();

private:
  ~nsTreeNode();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsTreeNode, nsITreeNode)

nsTreeNode::nsTreeNode()
{
  /* member initializers and constructor code */
}

nsTreeNode::~nsTreeNode()
{
  /* destructor code */
}

/* attribute long mX; */
NS_IMETHODIMP nsTreeNode::GetMX(PRInt32 *aMX)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsTreeNode::SetMX(PRInt32 aMX)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long mY; */
NS_IMETHODIMP nsTreeNode::GetMY(PRInt32 *aMY)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsTreeNode::SetMY(PRInt32 aMY)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long mW; */
NS_IMETHODIMP nsTreeNode::GetMW(PRInt32 *aMW)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsTreeNode::SetMW(PRInt32 aMW)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long mH; */
NS_IMETHODIMP nsTreeNode::GetMH(PRInt32 *aMH)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsTreeNode::SetMH(PRInt32 aMH)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute long index; */
NS_IMETHODIMP nsTreeNode::GetIndex(PRInt32 *aIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsTreeNode::SetIndex(PRInt32 aIndex)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIDOMNode node; */
NS_IMETHODIMP nsTreeNode::GetNode(nsIDOMNode * *aNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsTreeNode::SetNode(nsIDOMNode * aNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddSubTree (in nsITreeNode tree); */
NS_IMETHODIMP nsTreeNode::AddSubTree(nsITreeNode *tree)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PrintTree (); */
NS_IMETHODIMP nsTreeNode::PrintTree()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetSubTree (out nsISupportsArray array); */
NS_IMETHODIMP nsTreeNode::GetSubTree(nsISupportsArray **array)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetArea (); */
NS_IMETHODIMP nsTreeNode::GetArea(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetTreeBox (in long x, in long y, in long w, in long h); */
NS_IMETHODIMP nsTreeNode::SetTreeBox(PRInt32 x, PRInt32 y, PRInt32 w, PRInt32 h)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ClearSub (); */
NS_IMETHODIMP nsTreeNode::ClearSub()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetWHRate (); */
NS_IMETHODIMP nsTreeNode::GetWHRate(double *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetClass ([array, size_is (cv_size)] in long cv, in unsigned long cv_size); */
NS_IMETHODIMP nsTreeNode::SetClass(PRInt32 *cv, PRUint32 cv_size)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void CutTree ([array, size_is (id_size)] in long id, in unsigned long id_size); */
NS_IMETHODIMP nsTreeNode::CutTree(PRInt32 *id, PRUint32 id_size)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void CutTreeForChl ([array, size_is (id_size)] in long id, in unsigned long id_size); */
NS_IMETHODIMP nsTreeNode::CutTreeForChl(PRInt32 *id, PRUint32 id_size)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetClassId (); */
NS_IMETHODIMP nsTreeNode::GetClassId(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean IsBigBox (); */
NS_IMETHODIMP nsTreeNode::IsBigBox(PRBool *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetTreeText (out AUTF8String text); */
NS_IMETHODIMP nsTreeNode::GetTreeText(nsACString & text)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsITreeNode_h__ */
