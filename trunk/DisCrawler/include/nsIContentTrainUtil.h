/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIContentTrainUtil.idl
 */

#ifndef __gen_nsIContentTrainUtil_h__
#define __gen_nsIContentTrainUtil_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAttDim; /* forward declaration */

class nsIDimStat; /* forward declaration */

class nsIAttSet; /* forward declaration */

class nsIXpathUtil; /* forward declaration */

class nsISupportsArray; /* forward declaration */


/* starting interface:    nsIContentTrainUtil */
#define NS_ICONTENTTRAINUTIL_IID_STR "db0aff49-f158-42b6-ae37-f52593361f28"

#define NS_ICONTENTTRAINUTIL_IID \
  {0xdb0aff49, 0xf158, 0x42b6, \
    { 0xae, 0x37, 0xf5, 0x25, 0x93, 0x36, 0x1f, 0x28 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIContentTrainUtil : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICONTENTTRAINUTIL_IID)

  /* void FindCommonDim ([array, size_is (id_size)] out long dims, out PRUint32 id_size); */
  NS_SCRIPTABLE NS_IMETHOD FindCommonDim(PRInt32 **dims NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM) = 0;

  /* void SetVectorSet (in nsIAttSet attset); */
  NS_SCRIPTABLE NS_IMETHOD SetVectorSet(nsIAttSet *attset) = 0;

  /* void SetAttDim (in nsIAttDim attdim); */
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) = 0;

  /* double GetSimilarityByDim (in long dimid); */
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityByDim(PRInt32 dimid, double *_retval NS_OUTPARAM) = 0;

  /* double GetSimilarityBetweenStrings (in AUTF8String s1, in AUTF8String s2); */
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenStrings(const nsACString & s1, const nsACString & s2, double *_retval NS_OUTPARAM) = 0;

  /* double GetSimilarityBetweenDims (in PRInt32 dim1, in PRInt32 dim2); */
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenDims(PRInt32 dim1, PRInt32 dim2, double *_retval NS_OUTPARAM) = 0;

  /* AUTF8String GetNodesTextByXpath (in nsIXpathUtil xpathutil, in AUTF8String xpath); */
  NS_SCRIPTABLE NS_IMETHOD GetNodesTextByXpath(nsIXpathUtil *xpathutil, const nsACString & xpath, nsACString & _retval NS_OUTPARAM) = 0;

  /* double IsDateDim (in long dimid, in nsIDimStat dimstat); */
  NS_SCRIPTABLE NS_IMETHOD IsDateDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) = 0;

  /* double IsSourceDim (in long dimid, in nsIDimStat dimstat); */
  NS_SCRIPTABLE NS_IMETHOD IsSourceDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) = 0;

  /* double isAuthorDim (in long dimid, in nsIDimStat dimstat); */
  NS_SCRIPTABLE NS_IMETHOD IsAuthorDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIContentTrainUtil, NS_ICONTENTTRAINUTIL_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICONTENTTRAINUTIL \
  NS_SCRIPTABLE NS_IMETHOD FindCommonDim(PRInt32 **dims NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetVectorSet(nsIAttSet *attset); \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim); \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityByDim(PRInt32 dimid, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenStrings(const nsACString & s1, const nsACString & s2, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenDims(PRInt32 dim1, PRInt32 dim2, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetNodesTextByXpath(nsIXpathUtil *xpathutil, const nsACString & xpath, nsACString & _retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsDateDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsSourceDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD IsAuthorDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICONTENTTRAINUTIL(_to) \
  NS_SCRIPTABLE NS_IMETHOD FindCommonDim(PRInt32 **dims NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM) { return _to FindCommonDim(dims, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD SetVectorSet(nsIAttSet *attset) { return _to SetVectorSet(attset); } \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) { return _to SetAttDim(attdim); } \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityByDim(PRInt32 dimid, double *_retval NS_OUTPARAM) { return _to GetSimilarityByDim(dimid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenStrings(const nsACString & s1, const nsACString & s2, double *_retval NS_OUTPARAM) { return _to GetSimilarityBetweenStrings(s1, s2, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenDims(PRInt32 dim1, PRInt32 dim2, double *_retval NS_OUTPARAM) { return _to GetSimilarityBetweenDims(dim1, dim2, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodesTextByXpath(nsIXpathUtil *xpathutil, const nsACString & xpath, nsACString & _retval NS_OUTPARAM) { return _to GetNodesTextByXpath(xpathutil, xpath, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsDateDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) { return _to IsDateDim(dimid, dimstat, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsSourceDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) { return _to IsSourceDim(dimid, dimstat, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsAuthorDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) { return _to IsAuthorDim(dimid, dimstat, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICONTENTTRAINUTIL(_to) \
  NS_SCRIPTABLE NS_IMETHOD FindCommonDim(PRInt32 **dims NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->FindCommonDim(dims, id_size); } \
  NS_SCRIPTABLE NS_IMETHOD SetVectorSet(nsIAttSet *attset) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVectorSet(attset); } \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAttDim(attdim); } \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityByDim(PRInt32 dimid, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSimilarityByDim(dimid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenStrings(const nsACString & s1, const nsACString & s2, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSimilarityBetweenStrings(s1, s2, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetSimilarityBetweenDims(PRInt32 dim1, PRInt32 dim2, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetSimilarityBetweenDims(dim1, dim2, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetNodesTextByXpath(nsIXpathUtil *xpathutil, const nsACString & xpath, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNodesTextByXpath(xpathutil, xpath, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsDateDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsDateDim(dimid, dimstat, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsSourceDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsSourceDim(dimid, dimstat, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD IsAuthorDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->IsAuthorDim(dimid, dimstat, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsContentTrainUtil : public nsIContentTrainUtil
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICONTENTTRAINUTIL

  nsContentTrainUtil();

private:
  ~nsContentTrainUtil();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsContentTrainUtil, nsIContentTrainUtil)

nsContentTrainUtil::nsContentTrainUtil()
{
  /* member initializers and constructor code */
}

nsContentTrainUtil::~nsContentTrainUtil()
{
  /* destructor code */
}

/* void FindCommonDim ([array, size_is (id_size)] out long dims, out PRUint32 id_size); */
NS_IMETHODIMP nsContentTrainUtil::FindCommonDim(PRInt32 **dims NS_OUTPARAM, PRUint32 *id_size NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetVectorSet (in nsIAttSet attset); */
NS_IMETHODIMP nsContentTrainUtil::SetVectorSet(nsIAttSet *attset)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsContentTrainUtil::SetAttDim(nsIAttDim *attdim)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetSimilarityByDim (in long dimid); */
NS_IMETHODIMP nsContentTrainUtil::GetSimilarityByDim(PRInt32 dimid, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetSimilarityBetweenStrings (in AUTF8String s1, in AUTF8String s2); */
NS_IMETHODIMP nsContentTrainUtil::GetSimilarityBetweenStrings(const nsACString & s1, const nsACString & s2, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetSimilarityBetweenDims (in PRInt32 dim1, in PRInt32 dim2); */
NS_IMETHODIMP nsContentTrainUtil::GetSimilarityBetweenDims(PRInt32 dim1, PRInt32 dim2, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetNodesTextByXpath (in nsIXpathUtil xpathutil, in AUTF8String xpath); */
NS_IMETHODIMP nsContentTrainUtil::GetNodesTextByXpath(nsIXpathUtil *xpathutil, const nsACString & xpath, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double IsDateDim (in long dimid, in nsIDimStat dimstat); */
NS_IMETHODIMP nsContentTrainUtil::IsDateDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double IsSourceDim (in long dimid, in nsIDimStat dimstat); */
NS_IMETHODIMP nsContentTrainUtil::IsSourceDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double isAuthorDim (in long dimid, in nsIDimStat dimstat); */
NS_IMETHODIMP nsContentTrainUtil::IsAuthorDim(PRInt32 dimid, nsIDimStat *dimstat, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIContentTrainUtil_h__ */
