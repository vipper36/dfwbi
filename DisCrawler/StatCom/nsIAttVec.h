/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIAttVec.idl
 */

#ifndef __gen_nsIAttVec_h__
#define __gen_nsIAttVec_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIDOMDocument; /* forward declaration */

class nsIDOMNode; /* forward declaration */


/* starting interface:    nsIAttVec */
#define NS_IATTVEC_IID_STR "cbe1afb1-8057-4500-a325-5aa407b0ade6"

#define NS_IATTVEC_IID \
  {0xcbe1afb1, 0x8057, 0x4500, \
    { 0xa3, 0x25, 0x5a, 0xa4, 0x07, 0xb0, 0xad, 0xe6 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIAttVec : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IATTVEC_IID)

  /* attribute nsIDOMDocument doc; */
  NS_SCRIPTABLE NS_IMETHOD GetDoc(nsIDOMDocument * *aDoc) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetDoc(nsIDOMDocument * aDoc) = 0;

  /* attribute nsIDOMNode node; */
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode) = 0;
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode) = 0;

  /* long GetLength (); */
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* void SetValue (in long dim, in double value); */
  NS_SCRIPTABLE NS_IMETHOD SetValue(PRInt32 dim, double value) = 0;

  /* void AddValue (in long dim, in double value); */
  NS_SCRIPTABLE NS_IMETHOD AddValue(PRInt32 dim, double value) = 0;

  /* boolean Contains (in long dim); */
  NS_SCRIPTABLE NS_IMETHOD Contains(PRInt32 dim, PRBool *_retval NS_OUTPARAM) = 0;

  /* void AppendVector (in nsIAttVec vec); */
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *vec) = 0;

  /* void SetVector (in nsIAttVec vec); */
  NS_SCRIPTABLE NS_IMETHOD SetVector(nsIAttVec *vec) = 0;

  /* double GetValueByDim (in long dim); */
  NS_SCRIPTABLE NS_IMETHOD GetValueByDim(PRInt32 dim, double *_retval NS_OUTPARAM) = 0;

  /* void GetDims ([array, size_is (cv_size)] out long dims, out unsigned long cv_size); */
  NS_SCRIPTABLE NS_IMETHOD GetDims(PRInt32 **dims NS_OUTPARAM, PRUint32 *cv_size NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIAttVec, NS_IATTVEC_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIATTVEC \
  NS_SCRIPTABLE NS_IMETHOD GetDoc(nsIDOMDocument * *aDoc); \
  NS_SCRIPTABLE NS_IMETHOD SetDoc(nsIDOMDocument * aDoc); \
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode); \
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode); \
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD SetValue(PRInt32 dim, double value); \
  NS_SCRIPTABLE NS_IMETHOD AddValue(PRInt32 dim, double value); \
  NS_SCRIPTABLE NS_IMETHOD Contains(PRInt32 dim, PRBool *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *vec); \
  NS_SCRIPTABLE NS_IMETHOD SetVector(nsIAttVec *vec); \
  NS_SCRIPTABLE NS_IMETHOD GetValueByDim(PRInt32 dim, double *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetDims(PRInt32 **dims NS_OUTPARAM, PRUint32 *cv_size NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIATTVEC(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetDoc(nsIDOMDocument * *aDoc) { return _to GetDoc(aDoc); } \
  NS_SCRIPTABLE NS_IMETHOD SetDoc(nsIDOMDocument * aDoc) { return _to SetDoc(aDoc); } \
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode) { return _to GetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode) { return _to SetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM) { return _to GetLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetValue(PRInt32 dim, double value) { return _to SetValue(dim, value); } \
  NS_SCRIPTABLE NS_IMETHOD AddValue(PRInt32 dim, double value) { return _to AddValue(dim, value); } \
  NS_SCRIPTABLE NS_IMETHOD Contains(PRInt32 dim, PRBool *_retval NS_OUTPARAM) { return _to Contains(dim, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *vec) { return _to AppendVector(vec); } \
  NS_SCRIPTABLE NS_IMETHOD SetVector(nsIAttVec *vec) { return _to SetVector(vec); } \
  NS_SCRIPTABLE NS_IMETHOD GetValueByDim(PRInt32 dim, double *_retval NS_OUTPARAM) { return _to GetValueByDim(dim, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDims(PRInt32 **dims NS_OUTPARAM, PRUint32 *cv_size NS_OUTPARAM) { return _to GetDims(dims, cv_size); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIATTVEC(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetDoc(nsIDOMDocument * *aDoc) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDoc(aDoc); } \
  NS_SCRIPTABLE NS_IMETHOD SetDoc(nsIDOMDocument * aDoc) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetDoc(aDoc); } \
  NS_SCRIPTABLE NS_IMETHOD GetNode(nsIDOMNode * *aNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD SetNode(nsIDOMNode * aNode) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetNode(aNode); } \
  NS_SCRIPTABLE NS_IMETHOD GetLength(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetLength(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD SetValue(PRInt32 dim, double value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetValue(dim, value); } \
  NS_SCRIPTABLE NS_IMETHOD AddValue(PRInt32 dim, double value) { return !_to ? NS_ERROR_NULL_POINTER : _to->AddValue(dim, value); } \
  NS_SCRIPTABLE NS_IMETHOD Contains(PRInt32 dim, PRBool *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->Contains(dim, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AppendVector(nsIAttVec *vec) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendVector(vec); } \
  NS_SCRIPTABLE NS_IMETHOD SetVector(nsIAttVec *vec) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetVector(vec); } \
  NS_SCRIPTABLE NS_IMETHOD GetValueByDim(PRInt32 dim, double *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetValueByDim(dim, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetDims(PRInt32 **dims NS_OUTPARAM, PRUint32 *cv_size NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetDims(dims, cv_size); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsAttVec : public nsIAttVec
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIATTVEC

  nsAttVec();

private:
  ~nsAttVec();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsAttVec, nsIAttVec)

nsAttVec::nsAttVec()
{
  /* member initializers and constructor code */
}

nsAttVec::~nsAttVec()
{
  /* destructor code */
}

/* attribute nsIDOMDocument doc; */
NS_IMETHODIMP nsAttVec::GetDoc(nsIDOMDocument * *aDoc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsAttVec::SetDoc(nsIDOMDocument * aDoc)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* attribute nsIDOMNode node; */
NS_IMETHODIMP nsAttVec::GetNode(nsIDOMNode * *aNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}
NS_IMETHODIMP nsAttVec::SetNode(nsIDOMNode * aNode)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* long GetLength (); */
NS_IMETHODIMP nsAttVec::GetLength(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetValue (in long dim, in double value); */
NS_IMETHODIMP nsAttVec::SetValue(PRInt32 dim, double value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AddValue (in long dim, in double value); */
NS_IMETHODIMP nsAttVec::AddValue(PRInt32 dim, double value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* boolean Contains (in long dim); */
NS_IMETHODIMP nsAttVec::Contains(PRInt32 dim, PRBool *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AppendVector (in nsIAttVec vec); */
NS_IMETHODIMP nsAttVec::AppendVector(nsIAttVec *vec)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetVector (in nsIAttVec vec); */
NS_IMETHODIMP nsAttVec::SetVector(nsIAttVec *vec)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* double GetValueByDim (in long dim); */
NS_IMETHODIMP nsAttVec::GetValueByDim(PRInt32 dim, double *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GetDims ([array, size_is (cv_size)] out long dims, out unsigned long cv_size); */
NS_IMETHODIMP nsAttVec::GetDims(PRInt32 **dims NS_OUTPARAM, PRUint32 *cv_size NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIAttVec_h__ */
