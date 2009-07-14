/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIChlIO.idl
 */

#ifndef __gen_nsIChlIO_h__
#define __gen_nsIChlIO_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIChlAtt; /* forward declaration */


/* starting interface:    nsIChlIO */
#define NS_ICHLIO_IID_STR "d046d058-af28-4f47-8c9b-7707b2d34b27"

#define NS_ICHLIO_IID \
  {0xd046d058, 0xaf28, 0x4f47, \
    { 0x8c, 0x9b, 0x77, 0x07, 0xb2, 0xd3, 0x4b, 0x27 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIChlIO : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICHLIO_IID)

  enum { LOCAL_FILE = 1U };

  enum { DATABASE = 2U };

  enum { NETWORK = 3U };

  /* void GetChl (out nsIChlAtt chl); */
  NS_SCRIPTABLE NS_IMETHOD GetChl(nsIChlAtt **chl) = 0;

  /* void SetLocation (in AUTF8String location); */
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) = 0;

  /* void GetType (out unsigned short type); */
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) = 0;

  /* void PutChl (in nsIChlAtt chl); */
  NS_SCRIPTABLE NS_IMETHOD PutChl(nsIChlAtt *chl) = 0;

  /* void GetChlByID (out nsIChlAtt chl, in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetChlByID(nsIChlAtt **chl, PRInt32 id) = 0;

  /* void UpdateByID (in long id, in AUTF8String colName, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIChlIO, NS_ICHLIO_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICHLIO \
  NS_SCRIPTABLE NS_IMETHOD GetChl(nsIChlAtt **chl); \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location); \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type); \
  NS_SCRIPTABLE NS_IMETHOD PutChl(nsIChlAtt *chl); \
  NS_SCRIPTABLE NS_IMETHOD GetChlByID(nsIChlAtt **chl, PRInt32 id); \
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICHLIO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetChl(nsIChlAtt **chl) { return _to GetChl(chl); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return _to SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) { return _to GetType(type); } \
  NS_SCRIPTABLE NS_IMETHOD PutChl(nsIChlAtt *chl) { return _to PutChl(chl); } \
  NS_SCRIPTABLE NS_IMETHOD GetChlByID(nsIChlAtt **chl, PRInt32 id) { return _to GetChlByID(chl, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value) { return _to UpdateByID(id, colName, value); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICHLIO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetChl(nsIChlAtt **chl) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChl(chl); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(type); } \
  NS_SCRIPTABLE NS_IMETHOD PutChl(nsIChlAtt *chl) { return !_to ? NS_ERROR_NULL_POINTER : _to->PutChl(chl); } \
  NS_SCRIPTABLE NS_IMETHOD GetChlByID(nsIChlAtt **chl, PRInt32 id) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetChlByID(chl, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateByID(id, colName, value); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsChlIO : public nsIChlIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLIO

  nsChlIO();

private:
  ~nsChlIO();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsChlIO, nsIChlIO)

nsChlIO::nsChlIO()
{
  /* member initializers and constructor code */
}

nsChlIO::~nsChlIO()
{
  /* destructor code */
}

/* void GetChl (out nsIChlAtt chl); */
NS_IMETHODIMP nsChlIO::GetChl(nsIChlAtt **chl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsChlIO::SetLocation(const nsACString & location)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsChlIO::GetType(PRUint16 *type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PutChl (in nsIChlAtt chl); */
NS_IMETHODIMP nsChlIO::PutChl(nsIChlAtt *chl)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetChlByID (out nsIChlAtt chl, in long id); */
NS_IMETHODIMP nsChlIO::GetChlByID(nsIChlAtt **chl, PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateByID (in long id, in AUTF8String colName, in AUTF8String value); */
NS_IMETHODIMP nsChlIO::UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIChlIO_h__ */
