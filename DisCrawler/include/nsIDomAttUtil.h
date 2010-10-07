/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDomAttUtil.idl
 */

#ifndef __gen_nsIDomAttUtil_h__
#define __gen_nsIDomAttUtil_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */

class nsIDOMNode; /* forward declaration */

class nsIDOMElement; /* forward declaration */

class nsISupportsArray; /* forward declaration */


/* starting interface:    nsIDomAttUtil */
#define NS_IDOMATTUTIL_IID_STR "04d0d5e6-a3bf-4968-a4da-07478a562c0f"

#define NS_IDOMATTUTIL_IID \
  {0x04d0d5e6, 0xa3bf, 0x4968, \
    { 0xa4, 0xda, 0x07, 0x47, 0x8a, 0x56, 0x2c, 0x0f }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDomAttUtil : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOMATTUTIL_IID)

  /* long CalNodeDepth (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD CalNodeDepth(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long GetDocUrlCount (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlCount(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long GetNodeUrlCount (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlCount(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* AUTF8String GetDocText (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD GetDocText(nsIDOMDocument *doc, nsACString & _retval NS_OUTPARAM) = 0;

  /* AUTF8String GetNodeText (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD GetNodeText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM) = 0;

  /* AUTF8String GetNodeOwnText (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD GetNodeOwnText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM) = 0;

  /* long GetDocUrlDistance (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlDistance(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* long GetNodeUrlDistance (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlDistance(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void CalSibParentDist (in nsIDOMElement node, out double pDist, out double lDist); */
  NS_SCRIPTABLE NS_IMETHOD CalSibParentDist(nsIDOMElement *node, double *pDist NS_OUTPARAM, double *lDist NS_OUTPARAM) = 0;

  /* void GetEleBox (in nsIDOMElement node, out long x, out long y, out long w, out long h); */
  NS_SCRIPTABLE NS_IMETHOD GetEleBox(nsIDOMElement *node, PRInt32 *x NS_OUTPARAM, PRInt32 *y NS_OUTPARAM, PRInt32 *w NS_OUTPARAM, PRInt32 *h NS_OUTPARAM) = 0;

  /* boolean IsLink (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD IsLink(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM) = 0;

  /* boolean IsLinkNotInCal (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD IsLinkNotInCal(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM) = 0;

  /* AUTF8String GetLinkStr (in nsIDOMNode node, in short type); */
  NS_SCRIPTABLE NS_IMETHOD GetLinkStr(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM) = 0;

  /* void GetALLDocumentArray (in nsIDOMDocument doc, in nsISupportsArray supArr); */
  NS_SCRIPTABLE NS_IMETHOD GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray *supArr) = 0;

  /* long GetNodeArea (in nsIDOMNode node); */
  NS_SCRIPTABLE NS_IMETHOD GetNodeArea(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDomAttUtil, NS_IDOMATTUTIL_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOMATTUTIL \
  NS_SCRIPTABLE NS_IMETHOD CalNodeDepth(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlCount(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlCount(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDocText(nsIDOMDocument *doc, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetNodeText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetNodeOwnText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlDistance(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlDistance(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD CalSibParentDist(nsIDOMElement *node, double *pDist NS_OUTPARAM, double *lDist NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetEleBox(nsIDOMElement *node, PRInt32 *x NS_OUTPARAM, PRInt32 *y NS_OUTPARAM, PRInt32 *w NS_OUTPARAM, PRInt32 *h NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsLink(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsLinkNotInCal(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetLinkStr(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray *supArr); \
  NS_SCRIPTABLE NS_IMETHOD GetNodeArea(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOMATTUTIL(_to) \
  NS_SCRIPTABLE NS_IMETHOD CalNodeDepth(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return _to CalNodeDepth(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlCount(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM) { return _to GetDocUrlCount(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlCount(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return _to GetNodeUrlCount(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocText(nsIDOMDocument *doc, nsACString & _retval NS_OUTPARAM) { return _to GetDocText(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM) { return _to GetNodeText(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeOwnText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM) { return _to GetNodeOwnText(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlDistance(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM) { return _to GetDocUrlDistance(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlDistance(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return _to GetNodeUrlDistance(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD CalSibParentDist(nsIDOMElement *node, double *pDist NS_OUTPARAM, double *lDist NS_OUTPARAM) { return _to CalSibParentDist(node, pDist, lDist); } \
  NS_SCRIPTABLE NS_IMETHOD GetEleBox(nsIDOMElement *node, PRInt32 *x NS_OUTPARAM, PRInt32 *y NS_OUTPARAM, PRInt32 *w NS_OUTPARAM, PRInt32 *h NS_OUTPARAM) { return _to GetEleBox(node, x, y, w, h); } \
  NS_SCRIPTABLE NS_IMETHOD IsLink(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM) { return _to IsLink(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsLinkNotInCal(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM) { return _to IsLinkNotInCal(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetLinkStr(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM) { return _to GetLinkStr(node, type, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray *supArr) { return _to GetALLDocumentArray(doc, supArr); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeArea(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return _to GetNodeArea(node, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOMATTUTIL(_to) \
  NS_SCRIPTABLE NS_IMETHOD CalNodeDepth(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->CalNodeDepth(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlCount(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocUrlCount(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlCount(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodeUrlCount(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocText(nsIDOMDocument *doc, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocText(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodeText(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeOwnText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodeOwnText(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocUrlDistance(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocUrlDistance(doc, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeUrlDistance(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodeUrlDistance(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD CalSibParentDist(nsIDOMElement *node, double *pDist NS_OUTPARAM, double *lDist NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->CalSibParentDist(node, pDist, lDist); } \
  NS_SCRIPTABLE NS_IMETHOD GetEleBox(nsIDOMElement *node, PRInt32 *x NS_OUTPARAM, PRInt32 *y NS_OUTPARAM, PRInt32 *w NS_OUTPARAM, PRInt32 *h NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetEleBox(node, x, y, w, h); } \
  NS_SCRIPTABLE NS_IMETHOD IsLink(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsLink(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsLinkNotInCal(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsLinkNotInCal(node, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetLinkStr(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLinkStr(node, type, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray *supArr) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetALLDocumentArray(doc, supArr); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodeArea(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodeArea(node, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDomAttUtil : public nsIDomAttUtil
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOMATTUTIL

  nsDomAttUtil();

private:
  ~nsDomAttUtil();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDomAttUtil, nsIDomAttUtil)

nsDomAttUtil::nsDomAttUtil()
{
  /* member initializers and constructor code */
}

nsDomAttUtil::~nsDomAttUtil()
{
  /* destructor code */
}

/* long CalNodeDepth (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::CalNodeDepth(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetDocUrlCount (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDomAttUtil::GetDocUrlCount(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetNodeUrlCount (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeUrlCount(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetDocText (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDomAttUtil::GetDocText(nsIDOMDocument *doc, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetNodeText (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetNodeOwnText (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeOwnText(nsIDOMNode *node, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetDocUrlDistance (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDomAttUtil::GetDocUrlDistance(nsIDOMDocument *doc, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetNodeUrlDistance (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeUrlDistance(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void CalSibParentDist (in nsIDOMElement node, out double pDist, out double lDist); */
NS_IMETHODIMP nsDomAttUtil::CalSibParentDist(nsIDOMElement *node, double *pDist NS_OUTPARAM, double *lDist NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetEleBox (in nsIDOMElement node, out long x, out long y, out long w, out long h); */
NS_IMETHODIMP nsDomAttUtil::GetEleBox(nsIDOMElement *node, PRInt32 *x NS_OUTPARAM, PRInt32 *y NS_OUTPARAM, PRInt32 *w NS_OUTPARAM, PRInt32 *h NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean IsLink (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::IsLink(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean IsLinkNotInCal (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::IsLinkNotInCal(nsIDOMNode *node, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetLinkStr (in nsIDOMNode node, in short type); */
NS_IMETHODIMP nsDomAttUtil::GetLinkStr(nsIDOMNode *node, PRInt16 type, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetALLDocumentArray (in nsIDOMDocument doc, in nsISupportsArray supArr); */
NS_IMETHODIMP nsDomAttUtil::GetALLDocumentArray(nsIDOMDocument *doc, nsISupportsArray *supArr)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetNodeArea (in nsIDOMNode node); */
NS_IMETHODIMP nsDomAttUtil::GetNodeArea(nsIDOMNode *node, PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDomAttUtil_h__ */
