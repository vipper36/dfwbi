#include "nsIDocHandle.h"

#include "xpcom-config.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "mozIStorageService.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"

#include <string>
#include <map>

using namespace std;

#ifndef __NSDOCHANDLE_H__
#define __NSDOCHANDLE_H__

#define NS_DOCHANDLE_CONTRACTID "@nyapc.com/XPCOM/nsDocHandle;1"
#define NS_DOCHANDLE_CLASSNAME "nsDocHandle"
#define NS_DOCHANDLE_CID NS_IDOCHANDLE_IID

class nsDocHandle : public nsIDocHandle
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCHANDLE

  nsDocHandle();

private:
  ~nsDocHandle();

	//Database
  	nsCString mLocation;
	nsCOMPtr<nsILocalFile> file;
	nsCOMPtr<mozIStorageService> mozSs;
protected:
  /* additional members */
	int open_db_file();
	int init_db();
};

#endif
