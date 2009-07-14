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

#ifndef __NSDOMANALYSIS_H__
#define __NSDOMANALYSIS_H__

#define NS_NSDOMANALYSIS_CONTRACTID "@nyapc.com/XPCOM/nsDOMAnalysis;1"
#define NS_NSDOMANALYSIS_CLASSNAME "nsDOMAnalysis"
#define NS_NSDOMANALYSIS_CID NS_IDOMANALYSIS_IID


using namespace std;

class nsDOMAnalysis : nsIDOMAnalysis
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDOMANALYSIS
	
	nsDOMAnalysis();
	~nsDOMAnalysis();
	
	int atom_cluster(BlockList & bn, list<BlockCluster> & bc_set);
	void analyze_clusters(list<BlockCluster> & bc_set);
	void analyze_cluster_type(BlockCluster & bc);

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
	
	//Page clusters
	list<BlockCluster> clusters;
	int cluster_id;

	//wrapper name
	string wrapper_name;

	void serialize();
	void deserialize();

	void save_wrap_rules();
	void save_wrap_rules(int con_type, int con_attr, string & rules);

	void load_wrap_rules_from_db(int type, BlockCluster & bc);
	void load_wrap_rules(string & rules, BlockCluster & bc);
	void load_wrap_rules();

	//int open_db_file();
	//int init_db();
	void write_page_type_into_db(int type);

	int get_new_cluster_id();
};

#endif
