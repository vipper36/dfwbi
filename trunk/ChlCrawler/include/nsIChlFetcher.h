/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIChlFetcher.idl
 */

#ifndef __gen_nsIChlFetcher_h__
#define __gen_nsIChlFetcher_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIColAtt; /* forward declaration */

class nsIChlAtt; /* forward declaration */

class nsIDOMDocument; /* forward declaration */

class nsIPersistentProperties; /* forward declaration */


/* starting interface:    nsIChlFetcher */
#define NS_ICHLFETCHER_IID_STR "8024a42d-2bc3-4bb5-9cc5-55c7309d217b"

#define NS_ICHLFETCHER_IID \
  {0x8024a42d, 0x2bc3, 0x4bb5, \
    { 0x9c, 0xc5, 0x55, 0xc7, 0x30, 0x9d, 0x21, 0x7b }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIChlFetcher : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICHLFETCHER_IID)

  /* void SetChl (in nsIChlAtt chl); */
  NS_SCRIPTABLE NS_IMETHOD SetChl(nsIChlAtt *chl) = 0;

  /* void SetDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) = 0;

  /* void SetProperty (in nsIPersistentProperties prop); */
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop) = 0;

  /* long GetColLength (); */
  NS_SCRIPTABLE NS_IMETHOD GetColLength(PRInt32 *_retval) = 0;

  /* void GetColItem (in long index, out nsIColAtt col); */
  NS_SCRIPTABLE NS_IMETHOD GetColItem(PRInt32 index, nsIColAtt **col) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIChlFetcher, NS_ICHLFETCHER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICHLFETCHER \
  NS_SCRIPTABLE NS_IMETHOD SetChl(nsIChlAtt *chl); \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop); \
  NS_SCRIPTABLE NS_IMETHOD GetColLength(PRInt32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetColItem(PRInt32 index, nsIColAtt **col); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICHLFETCHER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetChl(nsIChlAtt *chl) { return _to SetChl(chl); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return _to SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop) { return _to SetProperty(prop); } \
  NS_SCRIPTABLE NS_IMETHOD GetColLength(PRInt32 *_retval) { return _to GetColLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetColItem(PRInt32 index, nsIColAtt **col) { return _to GetColItem(index, col); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICHLFETCHER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetChl(nsIChlAtt *chl) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetChl(chl); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProperty(prop); } \
  NS_SCRIPTABLE NS_IMETHOD GetColLength(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetColLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetColItem(PRInt32 index, nsIColAtt **col) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetColItem(index, col); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsChlFetcher : public nsIChlFetcher
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLFETCHER

  nsChlFetcher();

private:
  ~nsChlFetcher();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsChlFetcher, nsIChlFetcher)

nsChlFetcher::nsChlFetcher()
{
  /* member initializers and constructor code */
}

nsChlFetcher::~nsChlFetcher()
{
  /* destructor code */
}

/* void SetChl (in nsIChlAtt chl); */
NS_IMETHODIMP nsChlFetcher::SetChl(nsIChlAtt *chl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsChlFetcher::SetDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetProperty (in nsIPersistentProperties prop); */
NS_IMETHODIMP nsChlFetcher::SetProperty(nsIPersistentProperties *prop)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetColLength (); */
NS_IMETHODIMP nsChlFetcher::GetColLength(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetColItem (in long index, out nsIColAtt col); */
NS_IMETHODIMP nsChlFetcher::GetColItem(PRInt32 index, nsIColAtt **col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIChlFetcher_h__ */
