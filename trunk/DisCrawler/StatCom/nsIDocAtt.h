/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDocAtt.idl
 */

#ifndef __gen_nsIDocAtt_h__
#define __gen_nsIDocAtt_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */

class nsIDocSet; /* forward declaration */

class nsIAttVec; /* forward declaration */

class nsIAttSet; /* forward declaration */

class nsIAttDim; /* forward declaration */


/* starting interface:    nsIDocAtt */
#define NS_IDOCATT_IID_STR "c010210e-6081-498b-a481-0b10d59535bf"

#define NS_IDOCATT_IID \
  {0xc010210e, 0x6081, 0x498b, \
    { 0xa4, 0x81, 0x0b, 0x10, 0xd5, 0x95, 0x35, 0xbf }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDocAtt : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDOCATT_IID)

  /* attribute nsIAttDim dim; */
  NS_SCRIPTABLE NS_IMETHOD GetDim(nsIAttDim * *aDim) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetDim(nsIAttDim * aDim) = 0;

  /* void AddDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc) = 0;

  /* long GetVectorCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetVectorCount(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* nsIAttVec GetVectorByIndex (in long index); */
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM) = 0;

  /* nsIAttSet GetResult (); */
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsIAttSet **_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDocAtt, NS_IDOCATT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDOCATT \
  NS_SCRIPTABLE NS_IMETHOD GetDim(nsIAttDim * *aDim); \
  NS_SCRIPTABLE NS_IMETHOD SetDim(nsIAttDim * aDim); \
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD GetVectorCount(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsIAttSet **_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDOCATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetDim(nsIAttDim * *aDim) { return _to GetDim(aDim); } \
  NS_SCRIPTABLE NS_IMETHOD SetDim(nsIAttDim * aDim) { return _to SetDim(aDim); } \
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc) { return _to AddDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD GetVectorCount(PRInt32 *_retval NS_OUTPARAM) { return _to GetVectorCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM) { return _to GetVectorByIndex(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsIAttSet **_retval NS_OUTPARAM) { return _to GetResult(_retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDOCATT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetDim(nsIAttDim * *aDim) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDim(aDim); } \
  NS_SCRIPTABLE NS_IMETHOD SetDim(nsIAttDim * aDim) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDim(aDim); } \
  NS_SCRIPTABLE NS_IMETHOD AddDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD GetVectorCount(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVectorCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVectorByIndex(index, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetResult(nsIAttSet **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetResult(_retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDocAtt : public nsIDocAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCATT

  nsDocAtt();

private:
  ~nsDocAtt();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDocAtt, nsIDocAtt)

nsDocAtt::nsDocAtt()
{
  /* member initializers and constructor code */
}

nsDocAtt::~nsDocAtt()
{
  /* destructor code */
}

/* attribute nsIAttDim dim; */
NS_IMETHODIMP nsDocAtt::GetDim(nsIAttDim * *aDim)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsDocAtt::SetDim(nsIAttDim * aDim)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDocAtt::AddDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetVectorCount (); */
NS_IMETHODIMP nsDocAtt::GetVectorCount(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAttVec GetVectorByIndex (in long index); */
NS_IMETHODIMP nsDocAtt::GetVectorByIndex(PRInt32 index, nsIAttVec **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAttSet GetResult (); */
NS_IMETHODIMP nsDocAtt::GetResult(nsIAttSet **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDocAtt_h__ */
