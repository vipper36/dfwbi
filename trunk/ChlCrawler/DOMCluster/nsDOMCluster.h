#include "nsIDOMCluster.h"

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

#ifndef __NSDOMCLUSTER_H__
#define __NSDOMCLUSTER_H__

#define NS_DOMCLUSTER_CONTRACTID "@nyapc.com/XPCOM/nsDOMCluster;1"
#define NS_DOMCLUSTER_CLASSNAME "nsDOMCluster"
#define NS_DOMCLUSTER_CID NS_IDOMCLUSTER_IID


using namespace std;

class nsDOMCluster : nsIDOMCluster
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDOMCLUSTER
	
	nsDOMCluster();
	~nsDOMCluster();
	
private:
	void load_document(BlockList & bl, int * uid);
	int atom_cluster(BlockList & bn, list<BlockCluster> & bc_set);
	void LoadDBConfig(const nsACString & location);

private:
	//url
	nsIUrlAtt * url_att;
//	string URL;
//	string TITLE;
        string StopTag;

	//Database
	nsCOMPtr<nsIClusterDBHandle> cdb_handle;
	nsCString mLocation;
	
	//Property
	nsIPersistentProperties * property;
	
	//Page clusters
	list<BlockCluster> clusters;
	int cluster_id;

	//wrapper name
	string wrapper_name;

	void serialize();
	void deserialize();

	void save_wrap(int con_type);

	void load_wrap_rules_from_db(int type, BlockCluster & bc);
	void load_wrap_rules(string & rules, BlockCluster & bc);
	void load_wrap_rules();

	//int open_db_file();
	//int init_db();
	void write_con_type_into_db(int uid, int type);

	int get_new_cluster_id();
};

#endif
