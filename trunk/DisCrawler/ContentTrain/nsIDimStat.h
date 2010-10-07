/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIDimStat.idl
 */

#ifndef __gen_nsIDimStat_h__
#define __gen_nsIDimStat_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */

class nsIAttDim; /* forward declaration */


/* starting interface:    nsIDimStat */
#define NS_IDIMSTAT_IID_STR "b4cf915f-72a9-440c-9b9b-cff0ddf4dbfd"

#define NS_IDIMSTAT_IID \
  {0xb4cf915f, 0x72a9, 0x440c, \
    { 0x9b, 0x9b, 0xcf, 0xf0, 0xdd, 0xf4, 0xdb, 0xfd }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIDimStat : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IDIMSTAT_IID)

  /* double GetTotalWeightByDim (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetTotalWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM) = 0;

  /* double GetAvrgWeightByDim (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetAvrgWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM) = 0;

  /* double GetWeightVarianceByDim (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetWeightVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM) = 0;

  /* double GetInverseDocCountByDim (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetInverseDocCountByDim(PRInt32 id, double *_retval NS_OUTPARAM) = 0;

  /* double GetAvrgShowCountByDim (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetAvrgShowCountByDim(PRInt32 id, double *_retval NS_OUTPARAM) = 0;

  /* double GetShowCountVarianceByDim (in long id); */
  NS_SCRIPTABLE NS_IMETHOD GetShowCountVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM) = 0;

  /* long GetDocCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void SetDocument (in nsIDOMDocument doc); */
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) = 0;

  /* void SetAttDim (in nsIAttDim attdim); */
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIDimStat, NS_IDIMSTAT_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIDIMSTAT \
  NS_SCRIPTABLE NS_IMETHOD GetTotalWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetAvrgWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetWeightVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetInverseDocCountByDim(PRInt32 id, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetAvrgShowCountByDim(PRInt32 id, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetShowCountVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc); \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIDIMSTAT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetTotalWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return _to GetTotalWeightByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAvrgWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return _to GetAvrgWeightByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWeightVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return _to GetWeightVarianceByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetInverseDocCountByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return _to GetInverseDocCountByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAvrgShowCountByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return _to GetAvrgShowCountByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowCountVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return _to GetShowCountVarianceByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM) { return _to GetDocCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return _to SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) { return _to SetAttDim(attdim); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIDIMSTAT(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetTotalWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetTotalWeightByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAvrgWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAvrgWeightByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetWeightVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetWeightVarianceByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetInverseDocCountByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetInverseDocCountByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetAvrgShowCountByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetAvrgShowCountByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetShowCountVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetShowCountVarianceByDim(id, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDocCount(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDocCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetDocument(nsIDOMDocument *doc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDocument(doc); } \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAttDim(attdim); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsDimStat : public nsIDimStat
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDIMSTAT

  nsDimStat();

private:
  ~nsDimStat();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsDimStat, nsIDimStat)

nsDimStat::nsDimStat()
{
  /* member initializers and constructor code */
}

nsDimStat::~nsDimStat()
{
  /* destructor code */
}

/* double GetTotalWeightByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetTotalWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetAvrgWeightByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetAvrgWeightByDim(PRInt32 id, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetWeightVarianceByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetWeightVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetInverseDocCountByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetInverseDocCountByDim(PRInt32 id, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetAvrgShowCountByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetAvrgShowCountByDim(PRInt32 id, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetShowCountVarianceByDim (in long id); */
NS_IMETHODIMP nsDimStat::GetShowCountVarianceByDim(PRInt32 id, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetDocCount (); */
NS_IMETHODIMP nsDimStat::GetDocCount(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetDocument (in nsIDOMDocument doc); */
NS_IMETHODIMP nsDimStat::SetDocument(nsIDOMDocument *doc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsDimStat::SetAttDim(nsIAttDim *attdim)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIDimStat_h__ */
