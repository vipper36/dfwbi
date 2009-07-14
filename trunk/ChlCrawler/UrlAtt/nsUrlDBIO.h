#include "nsIUrlIO.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsStringAPI.h"
#include "mozIStorageService.h"
#include "mozIStorageStatement.h"
#include "nsILocalFile.h"
#include "nsIUrlAtt.h"
#ifndef __NSURLDBIO_H__
#define __NSURLDBIO_H__
#define NS_URLDBIO_CONTRACTID "@nyapc.com/XPCOM/nsUrlDBIO;1"
#define NS_URLDBIO_CLASSNAME "nsUrlDBIO"

#define NS_URLDBIO_CID {0x1e0eefb3,0xb2d3,0x4ff8,{0x8a,0x33,0x57,0x96,0xa4,0x16,0x25,0xff}}
class nsUrlDBIO : public nsIUrlIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIURLIO

  nsUrlDBIO();

private:
  ~nsUrlDBIO();
  nsCOMArray<nsIUrlAtt> urls; 
protected:
  nsCOMPtr<mozIStorageService> mozSs;
  nsCOMPtr<nsILocalFile> file;
  int ReadUrls(mozIStorageStatement *state);
  int ReadbyStat(PRInt16 stat);
  int ReadbyLayer(PRInt16 stat,PRUint16 stlay, PRUint16 endlay);
  int ReadbyCol(PRInt16 stat,PRUint16 colId);
  PRInt32 curr;
  PRInt32 currStat;
  /* additional members */
};
#endif
