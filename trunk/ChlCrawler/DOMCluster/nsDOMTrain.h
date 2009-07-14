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

#include "nsIClusterDBHandle.h"

#include "BlockUtils.h"
#include "BlockNode.h"

#include <string>
#include <map>
#include <list>
#include <set>

#ifndef __NSDOMTRAIN_H__
#define __NSDOMTRAIN_H__

#define NS_DOMTRAIN_CONTRACTID "@nyapc.com/XPCOM/nsDOMTrain;1"
#define NS_DOMTRAIN_CLASSNAME "nsDOMTrain"
#define NS_DOMTRAIN_CID {0x2fca384e, 0x9fb0, 0x4862, \
    { 0x8c, 0x40, 0x7b, 0x33, 0x4b, 0x3d, 0x7e, 0xf8 }}


using namespace std;

class nsDOMTrain : nsIDOMCluster
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDOMCLUSTER
	
	nsDOMTrain();
	~nsDOMTrain();
	
private:
	void load_document(BlockList & bl, int * uid);
	void load_cluster();
	void LoadDBConfig(const nsACString & location);

	void analyze_clusters(list<BlockCluster> & bc_set);
	void analyze_cluster_type(BlockCluster & bc);

private:
	//url
	nsIUrlAtt * url_att;
	string URL;
	string TITLE;

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

        void save_wrapper();
	void save_wrap_rules(int con_type,int con_att, string & rules);

	void load_wrap_rules_from_db(int type, BlockCluster & bc);
	void load_wrap_rules(string & rules, BlockCluster & bc);
	void load_wrap_rules();

	//int open_db_file();
	//int init_db();
	void write_con_type_into_db(int uid, int type);

	int get_new_cluster_id();
	int get_num_of_cluster();
};

#endif
