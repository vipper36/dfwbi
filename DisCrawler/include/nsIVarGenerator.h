/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIVarGenerator.idl
 */

#ifndef __gen_nsIVarGenerator_h__
#define __gen_nsIVarGenerator_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIClustModel; /* forward declaration */

class nsIAttDim; /* forward declaration */


/* starting interface:    nsIVarGenerator */
#define NS_IVARGENERATOR_IID_STR "25e13b08-c4d9-48d2-8144-e96cef8afae7"

#define NS_IVARGENERATOR_IID \
  {0x25e13b08, 0xc4d9, 0x48d2, \
    { 0x81, 0x44, 0xe9, 0x6c, 0xef, 0x8a, 0xfa, 0xe7 }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIVarGenerator : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_IVARGENERATOR_IID)

  /* void SetModel (in nsIClustModel model); */
  NS_SCRIPTABLE NS_IMETHOD SetModel(nsIClustModel *model) = 0;

  /* void SetParam (in AUTF8String name, in AUTF8String value); */
  NS_SCRIPTABLE NS_IMETHOD SetParam(const nsACString & name, const nsACString & value) = 0;

  /* void SetAttDim (in nsIAttDim attdim); */
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) = 0;

  /* void GenVar (); */
  NS_SCRIPTABLE NS_IMETHOD GenVar(void) = 0;

  /* AUTF8String GetVar (in AUTF8String name); */
  NS_SCRIPTABLE NS_IMETHOD GetVar(const nsACString & name, nsACString & _retval NS_OUTPARAM) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIVarGenerator, NS_IVARGENERATOR_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSIVARGENERATOR \
  NS_SCRIPTABLE NS_IMETHOD SetModel(nsIClustModel *model); \
  NS_SCRIPTABLE NS_IMETHOD SetParam(const nsACString & name, const nsACString & value); \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim); \
  NS_SCRIPTABLE NS_IMETHOD GenVar(void); \
  NS_SCRIPTABLE NS_IMETHOD GetVar(const nsACString & name, nsACString & _retval NS_OUTPARAM); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSIVARGENERATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetModel(nsIClustModel *model) { return _to SetModel(model); } \
  NS_SCRIPTABLE NS_IMETHOD SetParam(const nsACString & name, const nsACString & value) { return _to SetParam(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) { return _to SetAttDim(attdim); } \
  NS_SCRIPTABLE NS_IMETHOD GenVar(void) { return _to GenVar(); } \
  NS_SCRIPTABLE NS_IMETHOD GetVar(const nsACString & name, nsACString & _retval NS_OUTPARAM) { return _to GetVar(name, _retval); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSIVARGENERATOR(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetModel(nsIClustModel *model) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetModel(model); } \
  NS_SCRIPTABLE NS_IMETHOD SetParam(const nsACString & name, const nsACString & value) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetParam(name, value); } \
  NS_SCRIPTABLE NS_IMETHOD SetAttDim(nsIAttDim *attdim) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetAttDim(attdim); } \
  NS_SCRIPTABLE NS_IMETHOD GenVar(void) { return !_to ? NS_ERROR_NULL_POINTER : _to->GenVar(); } \
  NS_SCRIPTABLE NS_IMETHOD GetVar(const nsACString & name, nsACString & _retval NS_OUTPARAM) { return !_to ? NS_ERROR_NULL_POINTER : _to->GetVar(name, _retval); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsVarGenerator : public nsIVarGenerator
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIVARGENERATOR

  nsVarGenerator();

private:
  ~nsVarGenerator();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsVarGenerator, nsIVarGenerator)

nsVarGenerator::nsVarGenerator()
{
  /* member initializers and constructor code */
}

nsVarGenerator::~nsVarGenerator()
{
  /* destructor code */
}

/* void SetModel (in nsIClustModel model); */
NS_IMETHODIMP nsVarGenerator::SetModel(nsIClustModel *model)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsVarGenerator::SetParam(const nsACString & name, const nsACString & value)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetAttDim (in nsIAttDim attdim); */
NS_IMETHODIMP nsVarGenerator::SetAttDim(nsIAttDim *attdim)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void GenVar (); */
NS_IMETHODIMP nsVarGenerator::GenVar()
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* AUTF8String GetVar (in AUTF8String name); */
NS_IMETHODIMP nsVarGenerator::GetVar(const nsACString & name, nsACString & _retval NS_OUTPARAM)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIVarGenerator_h__ */
