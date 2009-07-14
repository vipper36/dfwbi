/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIUrlIO.idl
 */

#ifndef __gen_nsIUrlIO_h__
#define __gen_nsIUrlIO_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIUrlAtt; /* forward declaration */


/* starting interface:    nsIUrlIO */
#define NS_IURLIO_IID_STR "99424107-692a-4df6-9577-5869311b12b0"

#define NS_IURLIO_IID \
  {0x99424107, 0x692a, 0x4df6, \
    { 0x95, 0x77, 0x58, 0x69, 0x31, 0x1b, 0x12, 0xb0 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIUrlIO : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IURLIO_IID)

  enum { LOCAL_FILE = 1U };

  enum { DATABASE = 2U };

  enum { NETWORK = 3U };

  /* void GetURL (out nsIUrlAtt url, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsIUrlAtt **url, PRUint16 stat) = 0;

  /* void GetURLByLayer (out nsIUrlAtt url, in unsigned short stat, in unsigned short stlay, in unsigned short endlay); */
  NS_SCRIPTABLE NS_IMETHOD GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay) = 0;

  /* void GetURLByCol (out nsIUrlAtt url, in unsigned short stat, in unsigned long colId); */
  NS_SCRIPTABLE NS_IMETHOD GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 colId) = 0;

  /* void SetLocation (in AUTF8String location); */
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) = 0;

  /* void GetType (out unsigned short type); */
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) = 0;

  /* void UpdateStat (in nsIUrlAtt url, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIUrlAtt *url, PRUint16 stat) = 0;

  /* void UpdateALL (in nsIUrlAtt url, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD UpdateALL(nsIUrlAtt *url, PRUint16 stat) = 0;

  /* void UpdateCol (in nsIUrlAtt url, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat) = 0;

  /* void PutURL (in nsIUrlAtt url); */
  NS_SCRIPTABLE NS_IMETHOD PutURL(nsIUrlAtt *url) = 0;

  /* void GetURLID (in AUTF8String url, out unsigned long id); */
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id) = 0;

  /* void GetURLbyID (out nsIUrlAtt url, in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetURLbyID(nsIUrlAtt **url, PRInt32 id) = 0;

  /* void UpdatebyID (in long id, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat) = 0;

  /* void UpdateStatByHash (in AUTF8String hash, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD UpdateStatByHash(const nsACString & hash, PRUint16 stat) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIUrlIO, NS_IURLIO_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIURLIO \
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsIUrlAtt **url, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay); \
  NS_SCRIPTABLE NS_IMETHOD GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 colId); \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location); \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type); \
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIUrlAtt *url, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD UpdateALL(nsIUrlAtt *url, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD PutURL(nsIUrlAtt *url); \
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id); \
  NS_SCRIPTABLE NS_IMETHOD GetURLbyID(nsIUrlAtt **url, PRInt32 id); \
  NS_SCRIPTABLE NS_IMETHOD UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD UpdateStatByHash(const nsACString & hash, PRUint16 stat); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIURLIO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsIUrlAtt **url, PRUint16 stat) { return _to GetURL(url, stat); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay) { return _to GetURLByLayer(url, stat, stlay, endlay); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 colId) { return _to GetURLByCol(url, stat, colId); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return _to SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) { return _to GetType(type); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIUrlAtt *url, PRUint16 stat) { return _to UpdateStat(url, stat); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateALL(nsIUrlAtt *url, PRUint16 stat) { return _to UpdateALL(url, stat); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat) { return _to UpdateCol(url, colName, value, stat); } \
  NS_SCRIPTABLE NS_IMETHOD PutURL(nsIUrlAtt *url) { return _to PutURL(url); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id) { return _to GetURLID(url, id); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLbyID(nsIUrlAtt **url, PRInt32 id) { return _to GetURLbyID(url, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat) { return _to UpdatebyID(id, colName, value, stat); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateStatByHash(const nsACString & hash, PRUint16 stat) { return _to UpdateStatByHash(hash, stat); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIURLIO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetURL(nsIUrlAtt **url, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURL(url, stat); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLByLayer(url, stat, stlay, endlay); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 colId) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLByCol(url, stat, colId); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(type); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIUrlAtt *url, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateStat(url, stat); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateALL(nsIUrlAtt *url, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateALL(url, stat); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateCol(url, colName, value, stat); } \
  NS_SCRIPTABLE NS_IMETHOD PutURL(nsIUrlAtt *url) { return !_to ? NS_ERROR_NULL_POINTER : _to->PutURL(url); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLID(const nsACString & url, PRUint32 *id) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLID(url, id); } \
  NS_SCRIPTABLE NS_IMETHOD GetURLbyID(nsIUrlAtt **url, PRInt32 id) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetURLbyID(url, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdatebyID(id, colName, value, stat); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateStatByHash(const nsACString & hash, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateStatByHash(hash, stat); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsUrlIO : public nsIUrlIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLIO

  nsUrlIO();

private:
  ~nsUrlIO();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsUrlIO, nsIUrlIO)

nsUrlIO::nsUrlIO()
{
  /* member initializers and constructor code */
}

nsUrlIO::~nsUrlIO()
{
  /* destructor code */
}

/* void GetURL (out nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlIO::GetURL(nsIUrlAtt **url, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetURLByLayer (out nsIUrlAtt url, in unsigned short stat, in unsigned short stlay, in unsigned short endlay); */
NS_IMETHODIMP nsUrlIO::GetURLByLayer(nsIUrlAtt **url, PRUint16 stat, PRUint16 stlay, PRUint16 endlay)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetURLByCol (out nsIUrlAtt url, in unsigned short stat, in unsigned long colId); */
NS_IMETHODIMP nsUrlIO::GetURLByCol(nsIUrlAtt **url, PRUint16 stat, PRUint32 colId)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsUrlIO::SetLocation(const nsACString & location)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsUrlIO::GetType(PRUint16 *type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateStat (in nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlIO::UpdateStat(nsIUrlAtt *url, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateALL (in nsIUrlAtt url, in unsigned short stat); */
NS_IMETHODIMP nsUrlIO::UpdateALL(nsIUrlAtt *url, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateCol (in nsIUrlAtt url, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
NS_IMETHODIMP nsUrlIO::UpdateCol(nsIUrlAtt *url, const nsACString & colName, const nsACString & value, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PutURL (in nsIUrlAtt url); */
NS_IMETHODIMP nsUrlIO::PutURL(nsIUrlAtt *url)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetURLID (in AUTF8String url, out unsigned long id); */
NS_IMETHODIMP nsUrlIO::GetURLID(const nsACString & url, PRUint32 *id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetURLbyID (out nsIUrlAtt url, in long id); */
NS_IMETHODIMP nsUrlIO::GetURLbyID(nsIUrlAtt **url, PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdatebyID (in long id, in AUTF8String colName, in AUTF8String value, in unsigned short stat); */
NS_IMETHODIMP nsUrlIO::UpdatebyID(PRInt32 id, const nsACString & colName, const nsACString & value, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateStatByHash (in AUTF8String hash, in unsigned short stat); */
NS_IMETHODIMP nsUrlIO::UpdateStatByHash(const nsACString & hash, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIUrlIO_h__ */
