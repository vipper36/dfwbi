/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIColFetcher.idl
 */

#ifndef __gen_nsIColFetcher_h__
#define __gen_nsIColFetcher_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIUrlAtt; /* forward declaration */

class nsIColAtt; /* forward declaration */

class nsIDOMDocument; /* forward declaration */

class nsIPersistentProperties; /* forward declaration */


/* starting interface:    nsIColFetcher */
#define NS_ICOLFETCHER_IID_STR "1cefedee-8475-47ff-98e6-3404c8b636ec"

#define NS_ICOLFETCHER_IID \
  {0x1cefedee, 0x8475, 0x47ff, \
    { 0x98, 0xe6, 0x34, 0x04, 0xc8, 0xb6, 0x36, 0xec }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIColFetcher : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICOLFETCHER_IID)

  /* attribute nsIColAtt col; */
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt * *aCol) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetCol(nsIColAtt * aCol) = 0;

  /* void SetDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) = 0;

  /* void SetProperty (in nsIPersistentProperties prop); */
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop) = 0;

  /* long GetUrlLength (); */
  NS_SCRIPTABLE NS_IMETHOD GetUrlLength(PRInt32 *_retval) = 0;

  /* void GetUrlItem (in long index, out nsIUrlAtt url); */
  NS_SCRIPTABLE NS_IMETHOD GetUrlItem(PRInt32 index, nsIUrlAtt **url) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIColFetcher, NS_ICOLFETCHER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICOLFETCHER \
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt * *aCol); \
  NS_SCRIPTABLE NS_IMETHOD SetCol(nsIColAtt * aCol); \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop); \
  NS_SCRIPTABLE NS_IMETHOD GetUrlLength(PRInt32 *_retval); \
  NS_SCRIPTABLE NS_IMETHOD GetUrlItem(PRInt32 index, nsIUrlAtt **url); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICOLFETCHER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt * *aCol) { return _to GetCol(aCol); } \
  NS_SCRIPTABLE NS_IMETHOD SetCol(nsIColAtt * aCol) { return _to SetCol(aCol); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return _to SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop) { return _to SetProperty(prop); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlLength(PRInt32 *_retval) { return _to GetUrlLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlItem(PRInt32 index, nsIUrlAtt **url) { return _to GetUrlItem(index, url); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICOLFETCHER(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt * *aCol) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCol(aCol); } \
  NS_SCRIPTABLE NS_IMETHOD SetCol(nsIColAtt * aCol) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCol(aCol); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetProperty(nsIPersistentProperties *prop) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetProperty(prop); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlLength(PRInt32 *_retval) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrlLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetUrlItem(PRInt32 index, nsIUrlAtt **url) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetUrlItem(index, url); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsColFetcher : public nsIColFetcher
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLFETCHER

  nsColFetcher();

private:
  ~nsColFetcher();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsColFetcher, nsIColFetcher)

nsColFetcher::nsColFetcher()
{
  /* member initializers and constructor code */
}

nsColFetcher::~nsColFetcher()
{
  /* destructor code */
}

/* attribute nsIColAtt col; */
NS_IMETHODIMP nsColFetcher::GetCol(nsIColAtt * *aCol)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsColFetcher::SetCol(nsIColAtt * aCol)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsColFetcher::SetDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetProperty (in nsIPersistentProperties prop); */
NS_IMETHODIMP nsColFetcher::SetProperty(nsIPersistentProperties *prop)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetUrlLength (); */
NS_IMETHODIMP nsColFetcher::GetUrlLength(PRInt32 *_retval)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetUrlItem (in long index, out nsIUrlAtt url); */
NS_IMETHODIMP nsColFetcher::GetUrlItem(PRInt32 index, nsIUrlAtt **url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIColFetcher_h__ */
