/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM ILayoutAnalysis.idl
 */

#ifndef __gen_ILayoutAnalysis_h__
#define __gen_ILayoutAnalysis_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMHTMLDocument; /* forward declaration */

class nsITreeNode; /* forward declaration */


/* starting interface:    ILayoutAnalysis */
#define ILAYOUTANALYSIS_IID_STR "63fe2585-b14f-442e-8c06-939e87c9902b"

#define ILAYOUTANALYSIS_IID \
  {0x63fe2585, 0xb14f, 0x442e, \
    { 0x8c, 0x06, 0x93, 0x9e, 0x87, 0xc9, 0x90, 0x2b }}

class NS_NO_VTABLE NS_SCRIPTABLE ILayoutAnalysis : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(ILAYOUTANALYSIS_IID)

  /* void SetDocument (in nsIDOMHTMLDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMHTMLDocument *doc) = 0;

  /* void SetKMeanAlg (in AUTF8String alg); */
  NS_SCRIPTABLE NS_IMETHOD SetKMeanAlg(const nsACString & alg) = 0;

  /* void GetResult (out nsITreeNode tree); */
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsITreeNode **tree) = 0;

  /* void SetClassCount (in unsigned long n); */
  NS_SCRIPTABLE NS_IMETHOD SetClassCount(PRUint32 n) = 0;

  /* void SetFilterPath (in DOMString path); */
  NS_SCRIPTABLE NS_IMETHOD SetFilterPath(const nsAString & path) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(ILayoutAnalysis, ILAYOUTANALYSIS_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_ILAYOUTANALYSIS \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMHTMLDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD SetKMeanAlg(const nsACString & alg); \
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsITreeNode **tree); \
  NS_SCRIPTABLE NS_IMETHOD SetClassCount(PRUint32 n); \
  NS_SCRIPTABLE NS_IMETHOD SetFilterPath(const nsAString & path); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_ILAYOUTANALYSIS(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMHTMLDocument *doc) { return _to SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetKMeanAlg(const nsACString & alg) { return _to SetKMeanAlg(alg); } \
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsITreeNode **tree) { return _to GetResult(tree); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassCount(PRUint32 n) { return _to SetClassCount(n); } \
  NS_SCRIPTABLE NS_IMETHOD SetFilterPath(const nsAString & path) { return _to SetFilterPath(path); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_ILAYOUTANALYSIS(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMHTMLDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetKMeanAlg(const nsACString & alg) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetKMeanAlg(alg); } \
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsITreeNode **tree) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetResult(tree); } \
  NS_SCRIPTABLE NS_IMETHOD SetClassCount(PRUint32 n) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetClassCount(n); } \
  NS_SCRIPTABLE NS_IMETHOD SetFilterPath(const nsAString & path) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetFilterPath(path); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class _MYCLASS_ : public ILayoutAnalysis
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_ILAYOUTANALYSIS

  _MYCLASS_();

private:
  ~_MYCLASS_();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(_MYCLASS_, ILayoutAnalysis)

_MYCLASS_::_MYCLASS_()
{
  /* member initializers and constructor code */
}

_MYCLASS_::~_MYCLASS_()
{
  /* destructor code */
}

/* void SetDocument (in nsIDOMHTMLDocument doc); */
NS_IMETHODIMP _MYCLASS_::SetDocument(nsIDOMHTMLDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetKMeanAlg (in AUTF8String alg); */
NS_IMETHODIMP _MYCLASS_::SetKMeanAlg(const nsACString & alg)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetResult (out nsITreeNode tree); */
NS_IMETHODIMP _MYCLASS_::GetResult(nsITreeNode **tree)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetClassCount (in unsigned long n); */
NS_IMETHODIMP _MYCLASS_::SetClassCount(PRUint32 n)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetFilterPath (in DOMString path); */
NS_IMETHODIMP _MYCLASS_::SetFilterPath(const nsAString & path)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_ILayoutAnalysis_h__ */
