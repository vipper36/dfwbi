#include "nsIColIO.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsCOMArray.h"
#include "nsStringAPI.h"
#include "mozIStorageService.h"
#include "mozIStorageStatement.h"
#include "nsILocalFile.h"
#include "nsIColAtt.h"
#ifndef __NSCOLDBIO_H__
#define __NSCOLDBIO_H__
#define NS_COLDBIO_CONTRACTID "@nyapc.com/XPCOM/nsColDBIO;1"
#define NS_COLDBIO_CLASSNAME "nsColDBIO"

#define NS_COLDBIO_CID {0x6df9f4ea,0x8328,0x4d4e,{0x8b,0x70,0x0e,0x4c,0x0e,0xf9,0x6e,0x43}}
class nsColDBIO : public nsIColIO
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICOLIO

  nsColDBIO();

private:
  ~nsColDBIO();
  nsCOMArray<nsIColAtt> cols; 
protected:
  nsCOMPtr<mozIStorageService> mozSs;
  nsCOMPtr<nsILocalFile> file;
  int ReadCols(mozIStorageStatement *state);
  int ReadAllCols();
  int ReadColsByStat(PRUint16 stat);
  PRInt32 curr;
  /* additional members */
};
#endif
