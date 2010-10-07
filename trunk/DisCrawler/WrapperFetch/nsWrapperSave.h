#include "nsIWrapperSave.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsIXpathUtil.h"
#include "mozIStorageService.h"
#ifndef __NS_WRAPPERSAVE_H__
#define __NS_WRAPPERSAVE_H__


#define NS_WRAPPERSAVE_CONTRACTID "@nyapc.com/XPCOM/nsWrapperSave;1"
#define NS_WRAPPERSAVE_CLASSNAME "nsWrapperSave"

#define NS_WRAPPERSAVE_CID NS_IWRAPPERSAVE_IID
class nsWrapperSave : public nsIWrapperSave
{
public:
     NS_DECL_ISUPPORTS
     NS_DECL_NSIWRAPPERSAVE
     
     nsWrapperSave();
     
private:
     ~nsWrapperSave();
protected:
      nsCOMPtr<mozIStorageService> mozSs;
      nsCOMPtr<nsILocalFile> file;
  /* additional members */
};
#endif
