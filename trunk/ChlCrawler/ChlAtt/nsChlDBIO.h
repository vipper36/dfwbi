#include "nsIChlIO.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsStringAPI.h"
#include "mozIStorageService.h"
#include "mozIStorageStatement.h"
#include "nsILocalFile.h"
#include "nsIChlAtt.h"
#ifndef __NSCHLDBIO_H__
#define __NSCHLDBIO_H__
#define NS_CHLDBIO_CONTRACTID "@nyapc.com/XPCOM/nsChlDBIO;1"
#define NS_CHLDBIO_CLASSNAME "nsChlDBIO"

#define NS_CHLDBIO_CID {0x050ffa89,0xe9a6,0x4d14,{0xb9,0x26,0x48,0x49,0x01,0xea,0x66,0x08}}
class nsChlDBIO : public nsIChlIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICHLIO

  nsChlDBIO();

private:
  ~nsChlDBIO();
  nsCOMArray<nsIChlAtt> chls; 
protected:
  nsCOMPtr<mozIStorageService> mozSs;
  nsCOMPtr<nsILocalFile> file;
  int ReadChls(mozIStorageStatement *state);
  int ReadAllChls();
  PRInt32 curr;
  /* additional members */
};
#endif
