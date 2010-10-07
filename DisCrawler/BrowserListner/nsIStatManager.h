/*
 * DO NOT EDIT.  THIS FILE IS GENERATED FROM nsIStatManager.idl
 */

#ifndef __gen_nsIStatManager_h__
#define __gen_nsIStatManager_h__


#ifndef __gen_nsISupports_h__
#include "nsISupports.h"
#endif

/* For IDL files that don't want to include root IDL files. */
#ifndef NS_NO_VTABLE
#define NS_NO_VTABLE
#endif
class nsIWebBrowser; /* forward declaration */

class nsISoapTask; /* forward declaration */

class nsISoapInter; /* forward declaration */


/* starting interface:    nsIStatManager */
#define NS_ISTATMANAGER_IID_STR "af490cbe-7a7c-40b1-a4a9-3aa277526eaa"

#define NS_ISTATMANAGER_IID \
  {0xaf490cbe, 0x7a7c, 0x40b1, \
    { 0xa4, 0xa9, 0x3a, 0xa2, 0x77, 0x52, 0x6e, 0xaa }}

class NS_NO_VTABLE NS_SCRIPTABLE nsIStatManager : public nsISupports {
 public: 

  NS_DECLARE_STATIC_IID_ACCESSOR(NS_ISTATMANAGER_IID)

  enum { NOT_START = 0U };

  enum { RUNNING = 1U };

  enum { FIN_DOC = 2U };

  enum { FINISH = 3U };

  enum { TIME_OUT_ERROR = 4U };

  enum { NETWORK_ERROR = 5U };

  /* void SetBrowser (in nsIWebBrowser browser, in long id); */
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser, PRInt32 id) = 0;

  /* void ChangeStat (in long id, in unsigned short stat); */
  NS_SCRIPTABLE NS_IMETHOD ChangeStat(PRInt32 id, PRUint16 stat) = 0;

  /* void SetTask (in nsISoapTask task); */
  NS_SCRIPTABLE NS_IMETHOD SetTask(nsISoapTask *task) = 0;

  /* void SetInter (in nsISoapInter inter); */
  NS_SCRIPTABLE NS_IMETHOD SetInter(nsISoapInter *inter) = 0;

  /* void SetCid (in long id); */
  NS_SCRIPTABLE NS_IMETHOD SetCid(PRInt32 id) = 0;

};

  NS_DEFINE_STATIC_IID_ACCESSOR(nsIStatManager, NS_ISTATMANAGER_IID)

/* Use this macro when declaring classes that implement this interface. */
#define NS_DECL_NSISTATMANAGER \
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser, PRInt32 id); \
  NS_SCRIPTABLE NS_IMETHOD ChangeStat(PRInt32 id, PRUint16 stat); \
  NS_SCRIPTABLE NS_IMETHOD SetTask(nsISoapTask *task); \
  NS_SCRIPTABLE NS_IMETHOD SetInter(nsISoapInter *inter); \
  NS_SCRIPTABLE NS_IMETHOD SetCid(PRInt32 id); 

/* Use this macro to declare functions that forward the behavior of this interface to another object. */
#define NS_FORWARD_NSISTATMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser, PRInt32 id) { return _to SetBrowser(browser, id); } \
  NS_SCRIPTABLE NS_IMETHOD ChangeStat(PRInt32 id, PRUint16 stat) { return _to ChangeStat(id, stat); } \
  NS_SCRIPTABLE NS_IMETHOD SetTask(nsISoapTask *task) { return _to SetTask(task); } \
  NS_SCRIPTABLE NS_IMETHOD SetInter(nsISoapInter *inter) { return _to SetInter(inter); } \
  NS_SCRIPTABLE NS_IMETHOD SetCid(PRInt32 id) { return _to SetCid(id); } 

/* Use this macro to declare functions that forward the behavior of this interface to another object in a safe way. */
#define NS_FORWARD_SAFE_NSISTATMANAGER(_to) \
  NS_SCRIPTABLE NS_IMETHOD SetBrowser(nsIWebBrowser *browser, PRInt32 id) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetBrowser(browser, id); } \
  NS_SCRIPTABLE NS_IMETHOD ChangeStat(PRInt32 id, PRUint16 stat) { return !_to ? NS_ERROR_NULL_POINTER : _to->ChangeStat(id, stat); } \
  NS_SCRIPTABLE NS_IMETHOD SetTask(nsISoapTask *task) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetTask(task); } \
  NS_SCRIPTABLE NS_IMETHOD SetInter(nsISoapInter *inter) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetInter(inter); } \
  NS_SCRIPTABLE NS_IMETHOD SetCid(PRInt32 id) { return !_to ? NS_ERROR_NULL_POINTER : _to->SetCid(id); } 

#if 0
/* Use the code below as a template for the implementation class for this interface. */

/* Header file */
class nsStatManager : public nsIStatManager
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISTATMANAGER

  nsStatManager();

private:
  ~nsStatManager();

protected:
  /* additional members */
};

/* Implementation file */
NS_IMPL_ISUPPORTS1(nsStatManager, nsIStatManager)

nsStatManager::nsStatManager()
{
  /* member initializers and constructor code */
}

nsStatManager::~nsStatManager()
{
  /* destructor code */
}

/* void SetBrowser (in nsIWebBrowser browser, in long id); */
NS_IMETHODIMP nsStatManager::SetBrowser(nsIWebBrowser *browser, PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void ChangeStat (in long id, in unsigned short stat); */
NS_IMETHODIMP nsStatManager::ChangeStat(PRInt32 id, PRUint16 stat)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetTask (in nsISoapTask task); */
NS_IMETHODIMP nsStatManager::SetTask(nsISoapTask *task)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetInter (in nsISoapInter inter); */
NS_IMETHODIMP nsStatManager::SetInter(nsISoapInter *inter)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* void SetCid (in long id); */
NS_IMETHODIMP nsStatManager::SetCid(PRInt32 id)
{
    return NS_ERROR_NOT_IMPLEMENTED;
}

/* End of implementation class template. */
#endif


#endif /* __gen_nsIStatManager_h__ */
