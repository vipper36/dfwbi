#include "nsIDOMAnalysis.h"
#include "xpcom-config.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMDocument.h"
#include "nsIPersistentProperties2.h"
#include "nsIURI.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "nsIInputStream.h"
#include "nsIFileStreams.h"
#include "mozIStorageService.h"
#include "mozIStorageConnection.h"
#include "mozIStorageStatement.h"

#include "nsIUrlIO.h"
#include "nsIUrlAtt.h"
#include "nsIClusterDBHandle.h"

#include "BlockUtils.h"
#include "BlockNode.h"

#include <string>
#include <map>
#include <list>
#include <set>

#ifndef __NSDOMCOLLECTOR_H__
#define __NSDOMCOLLECTOR_H__

#define NS_NSDOMCOLLECTOR_CONTRACTID "@nyapc.com/XPCOM/nsDOMCollector;1"
#define NS_NSDOMCOLLECTOR_CLASSNAME "nsDOMCollector"
#define NS_NSDOMCOLLECTOR_CID {0xdcc8ac44, 0x2d69, 0x4e60, { 0xb3, 0x24, 0x9c, 0x94, 0x26, 0x26, 0x89, 0x58}}


using namespace std;

class nsDOMCollector : nsIDOMAnalysis
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDOMANALYSIS
	
	nsDOMCollector();
	~nsDOMCollector();
	
private:
	//DOM
	nsIDOMDocument * doc;

	//url
	nsIUrlAtt * url_att;
	string URL;
	string TITLE;

	//Database
	nsCOMPtr<nsIClusterDBHandle> cdb_handle;
	nsCString mLocation;
	
	//Property
	nsIPersistentProperties * property;
	
	void write_page_into_db(BlockList & bl);
	void Replace(nsCString & str, const nsCString & target, const nsCString & nv);
};

#endif
