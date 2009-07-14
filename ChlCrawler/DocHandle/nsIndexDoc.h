#include "nsIIndexDoc.h"

#include "xpcom-config.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "mozIStorageService.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"

#include "nsIUrlAtt.h"

#include <string>
#include <map>

using namespace std;

#ifndef __NSINDEXDOC_H__
#define __NSINDEXDOC_H__

#define NS_INDEXDOC_CONTRACTID "@nyapc.com/XPCOM/nsIndexDoc;1"
#define NS_INDEXDOC_CLASSNAME "nsIndexDoc"
#define NS_INDEXDOC_CID NS_IINDEXDOC_IID

class nsIndexDoc : public nsIIndexDoc
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIINDEXDOC

  nsIndexDoc();

private:
  ~nsIndexDoc();

protected:
	/* additional members */
	nsCString title;
	nsCString date;
	nsCString source;
	nsCString author;
	nsCString content;
	nsCString fields;

	nsIUrlAtt * url;
};

#endif
