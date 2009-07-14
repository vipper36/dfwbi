#include "nsIUrlIO.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsStringAPI.h"
#include "mozIStorageService.h"
#include "nsILocalFile.h"
#include "nsIUrlAtt.h"
#ifndef __NSURLFILEIO_H__
#define __NSURLFILEIO_H__
#define NS_URLFILEIO_CONTRACTID "@nyapc.com/XPCOM/nsUrlFileIO;1"
#define NS_URLFILEIO_CLASSNAME "nsUrlFileIO"

#define NS_URLFILEIO_CID {0xb96290fa,0x0998,0x41ed,{0x89,0x5e,0xaf,0x53,0xc5,0x0f,0xcd,0x64}}
class nsUrlFileIO : public nsIUrlIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLIO

  nsUrlFileIO();

private:
  ~nsUrlFileIO();
  nsCOMArray<nsIUrlAtt> urls;
protected:
  nsCOMPtr<nsILocalFile> file;
  int ReadUrls(PRInt32 stat);
  PRInt32 curr;
  /* additional members */
};
#endif
