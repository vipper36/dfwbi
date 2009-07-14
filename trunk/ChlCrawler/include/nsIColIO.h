/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIColIO.idl
 */

#ifndef __gen_nsIColIO_h__
#define __gen_nsIColIO_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIColAtt; /* forward declaration */


/* starting interface:    nsIColIO */
#define NS_ICOLIO_IID_STR "d046d058-af28-4f47-8c9b-7707b2d34b27"

#define NS_ICOLIO_IID \
  {0xd046d058, 0xaf28, 0x4f47, \
    { 0x8c, 0x9b, 0x77, 0x07, 0xb2, 0xd3, 0x4b, 0x27 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIColIO : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICOLIO_IID)

  enum { LOCAL_FILE = 1U };

  enum { DATABASE = 2U };

  enum { NETWORK = 3U };

  /* void GetCol (out nsIColAtt col); */
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt **col) = 0;

  /* void SetLocation (in AUTF8String location); */
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) = 0;

  /* void GetType (out unsigned short type); */
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) = 0;

  /* void PutCol (in nsIColAtt col); */
  NS_SCRIPTABLE NS_IMETHOD PutCol(nsIColAtt *col) = 0;

  /* void GetColByID (out nsIColAtt col, in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetColByID(nsIColAtt **col, PRInt32 id) = 0;

  /* void UpdateByID (in long id, in AUTF8String colName, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value) = 0;

  /* void UpdateStat (in nsIColAtt col, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIColAtt *col, PRUint16 stat) = 0;

  /* void GetColByStat (in unsigned short stat, out nsIColAtt col); */
  NS_SCRIPTABLE NS_IMETHOD GetColByStat(PRUint16 stat, nsIColAtt **col) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIColIO, NS_ICOLIO_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICOLIO \
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt **col); \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location); \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type); \
  NS_SCRIPTABLE NS_IMETHOD PutCol(nsIColAtt *col); \
  NS_SCRIPTABLE NS_IMETHOD GetColByID(nsIColAtt **col, PRInt32 id); \
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value); \
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIColAtt *col, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD GetColByStat(PRUint16 stat, nsIColAtt **col); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICOLIO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt **col) { return _to GetCol(col); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return _to SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) { return _to GetType(type); } \
  NS_SCRIPTABLE NS_IMETHOD PutCol(nsIColAtt *col) { return _to PutCol(col); } \
  NS_SCRIPTABLE NS_IMETHOD GetColByID(nsIColAtt **col, PRInt32 id) { return _to GetColByID(col, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value) { return _to UpdateByID(id, colName, value); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIColAtt *col, PRUint16 stat) { return _to UpdateStat(col, stat); } \
  NS_SCRIPTABLE NS_IMETHOD GetColByStat(PRUint16 stat, nsIColAtt **col) { return _to GetColByStat(stat, col); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICOLIO(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetCol(nsIColAtt **col) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetCol(col); } \
  NS_SCRIPTABLE NS_IMETHOD SetLocation(const nsACString & location) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetLocation(location); } \
  NS_SCRIPTABLE NS_IMETHOD GetType(PRUint16 *type) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetType(type); } \
  NS_SCRIPTABLE NS_IMETHOD PutCol(nsIColAtt *col) { return !_to ? NS_ERROR_NULL_POINTER : _to->PutCol(col); } \
  NS_SCRIPTABLE NS_IMETHOD GetColByID(nsIColAtt **col, PRInt32 id) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetColByID(col, id); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateByID(id, colName, value); } \
  NS_SCRIPTABLE NS_IMETHOD UpdateStat(nsIColAtt *col, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->UpdateStat(col, stat); } \
  NS_SCRIPTABLE NS_IMETHOD GetColByStat(PRUint16 stat, nsIColAtt **col) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetColByStat(stat, col); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsColIO : public nsIColIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLIO

  nsColIO();

private:
  ~nsColIO();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsColIO, nsIColIO)

nsColIO::nsColIO()
{
  /* member initializers and constructor code */
}

nsColIO::~nsColIO()
{
  /* destructor code */
}

/* void GetCol (out nsIColAtt col); */
NS_IMETHODIMP nsColIO::GetCol(nsIColAtt **col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetLocation (in AUTF8String location); */
NS_IMETHODIMP nsColIO::SetLocation(const nsACString & location)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetType (out unsigned short type); */
NS_IMETHODIMP nsColIO::GetType(PRUint16 *type)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void PutCol (in nsIColAtt col); */
NS_IMETHODIMP nsColIO::PutCol(nsIColAtt *col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetColByID (out nsIColAtt col, in long id); */
NS_IMETHODIMP nsColIO::GetColByID(nsIColAtt **col, PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateByID (in long id, in AUTF8String colName, in AUTF8String value); */
NS_IMETHODIMP nsColIO::UpdateByID(PRInt32 id, const nsACString & colName, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void UpdateStat (in nsIColAtt col, in unsigned short stat); */
NS_IMETHODIMP nsColIO::UpdateStat(nsIColAtt *col, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetColByStat (in unsigned short stat, out nsIColAtt col); */
NS_IMETHODIMP nsColIO::GetColByStat(PRUint16 stat, nsIColAtt **col)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIColIO_h__ */
