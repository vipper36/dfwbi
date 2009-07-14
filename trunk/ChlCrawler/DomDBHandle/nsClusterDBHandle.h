#include "nsIClusterDBHandle.h"

#include "xpcom-config.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsNetUtil.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "mozIStorageService.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"

#include "nsIUrlIO.h"
#include "nsIUrlAtt.h"

#ifndef __NSCLUSTERDBHANDLE_H__
#define	__NSCLUSTERDBHANDLE_H__

#define NS_NSCLUSTERDBHANDLE_CONTRACTID "@nyapc.com/XPCOM/nsClusterDBHandle;1"
#define NS_NSCLUSTERDBHANDLE_CLASSNAME "nsClusterDBHandle"
#define NS_NSCLUSTERDBHANDLE_CID NS_ICLUSTERDBHANDLE_IID

class nsClusterDBHandle : public nsIClusterDBHandle
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSICLUSTERDBHANDLE

  nsClusterDBHandle();

private:
  ~nsClusterDBHandle();

protected:
  /* additional members */

	//Database
	nsCOMPtr<nsIUrlIO> url_handle;
	nsCString mLocation;
	nsCOMPtr<nsILocalFile> file;
	nsCOMPtr<mozIStorageService> mozSs;
	
	int open_db_file();
	int init_db();
};

#endif
