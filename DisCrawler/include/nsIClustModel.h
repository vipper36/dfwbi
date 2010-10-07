/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIClustModel.idl
 */

#ifndef __gen_nsIClustModel_h__
#define __gen_nsIClustModel_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIAttSet; /* forward declaration */

class nsIAttVec; /* forward declaration */


/* starting interface:    nsIClustModel */
#define NS_ICLUSTMODEL_IID_STR "be94ca29-5d0f-43ca-b724-ca2b5a029f53"

#define NS_ICLUSTMODEL_IID \
  {0xbe94ca29, 0x5d0f, 0x43ca, \
    { 0xb7, 0x24, 0xca, 0x2b, 0x5a, 0x02, 0x9f, 0x53 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIClustModel : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ICLUSTMODEL_IID)

  /* long GetClassCount (); */
  NS_SCRIPTABLE NS_IMETHOD GetClassCount(PRInt32 *_retval NS_OUTPARAM) = 0;

  /* nsIAttVec GetClassAtt (in long classid); */
  NS_SCRIPTABLE NS_IMETHOD GetClassAtt(PRInt32 classid, nsIAttVec **_retval NS_OUTPARAM) = 0;

  /* nsIAttSet GetClassSet (in long classid); */
  NS_SCRIPTABLE NS_IMETHOD GetClassSet(PRInt32 classid, nsIAttSet **_retval NS_OUTPARAM) = 0;

  /* void AppendClass (in nsIAttSet set, in nsIAttVec att); */
  NS_SCRIPTABLE NS_IMETHOD AppendClass(nsIAttSet *set, nsIAttVec *att) = 0;

  /* void ClearModel (); */
  NS_SCRIPTABLE NS_IMETHOD ClearModel(void) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIClustModel, NS_ICLUSTMODEL_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSICLUSTMODEL \
  NS_SCRIPTABLE NS_IMETHOD GetClassCount(PRInt32 *_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetClassAtt(PRInt32 classid, nsIAttVec **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD GetClassSet(PRInt32 classid, nsIAttSet **_retval NS_OUTPARAM); \
  NS_SCRIPTABLE NS_IMETHOD AppendClass(nsIAttSet *set, nsIAttVec *att); \
  NS_SCRIPTABLE NS_IMETHOD ClearModel(void); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSICLUSTMODEL(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetClassCount(PRInt32 *_retval NS_OUTPARAM) { return _to GetClassCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassAtt(PRInt32 classid, nsIAttVec **_retval NS_OUTPARAM) { return _to GetClassAtt(classid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassSet(PRInt32 classid, nsIAttSet **_retval NS_OUTPARAM) { return _to GetClassSet(classid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AppendClass(nsIAttSet *set, nsIAttVec *att) { return _to AppendClass(set, att); } \
  NS_SCRIPTABLE NS_IMETHOD ClearModel(void) { return _to ClearModel(); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSICLUSTMODEL(_to) \
  NS_SCRIPTABLE NS_IMETHOD GetClassCount(PRInt32 *_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassCount(_retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassAtt(PRInt32 classid, nsIAttVec **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassAtt(classid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD GetClassSet(PRInt32 classid, nsIAttSet **_retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetClassSet(classid, _retval); } \
  NS_SCRIPTABLE NS_IMETHOD AppendClass(nsIAttSet *set, nsIAttVec *att) { return !_to ? NS_ERROR_NULL_POINTER : _to->AppendClass(set, att); } \
  NS_SCRIPTABLE NS_IMETHOD ClearModel(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->ClearModel(); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsClustModel : public nsIClustModel
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTMODEL

  nsClustModel();

private:
  ~nsClustModel();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsClustModel, nsIClustModel)

nsClustModel::nsClustModel()
{
  /* member initializers and constructor code */
}

nsClustModel::~nsClustModel()
{
  /* destructor code */
}

/* long GetClassCount (); */
NS_IMETHODIMP nsClustModel::GetClassCount(PRInt32 *_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAttVec GetClassAtt (in long classid); */
NS_IMETHODIMP nsClustModel::GetClassAtt(PRInt32 classid, nsIAttVec **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* nsIAttSet GetClassSet (in long classid); */
NS_IMETHODIMP nsClustModel::GetClassSet(PRInt32 classid, nsIAttSet **_retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void AppendClass (in nsIAttSet set, in nsIAttVec att); */
NS_IMETHODIMP nsClustModel::AppendClass(nsIAttSet *set, nsIAttVec *att)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ClearModel (); */
NS_IMETHODIMP nsClustModel::ClearModel()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIClustModel_h__ */
