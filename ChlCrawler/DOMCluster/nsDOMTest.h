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
#include "nsIDocHandle.h"
#include "nsIIndexDoc.h"

#include "BlockUtils.h"
#include "BlockNode.h"
#include "BlockCluster.h"

#include <string>
#include <map>
#include <list>
#include <set>

#ifndef __NSDOMTEST_H__
#define __NSDOMTEST_H__

#define NS_DOMTEST_CONTRACTID "@nyapc.com/XPCOM/nsDOMTest;1"
#define NS_DOMTEST_CLASSNAME "nsDOMTest"
#define NS_DOMTEST_CID {0x95a0d173, 0x23f7, 0x4412, \
    { 0x8b, 0x59, 0x7b, 0x0e, 0x8a, 0xc6, 0x46, 0x68 }}


using namespace std;

class nsDOMTest : nsIDOMCluster
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDOMCLUSTER
	
	nsDOMTest();
	~nsDOMTest();
	
private:
	void load_document(BlockList & bl, int * uid);
	void LoadDBConfig(const nsACString & location);
        void collect_wrapper_rules();
        void write_con_type_into_db(int uid, int type);

        void serialize();
	void deserialize();

	void load_wrap_rules_from_db(int type, BlockCluster & bc);
	void load_wrap_rules(string & rules, BlockCluster & bc);
	void load_wrap_rules();
        void load_cluster();
        int get_num_of_cluster();

	void find_sim_cluster(BlockList & bl, BlockCluster ** bc);
	int analyze_page_type(BlockList & bl);
	int wrapping(BlockList & bl, BlockCluster * bc);
//	void wrap_content_page(BlockList & bl, BlockCluster * bc);
	void wrap_content_page2(BlockList & bl, BlockCluster * bc);
	void wrap_nextpage(int type);

	nsCString wrap_title(BlockList & bl);
	nsCString wrap_content(BlockList & bl, BlockCluster * bc);
	nsCString wrap_date(BlockList & bl, string & date_format);
	nsCString wrap_author(BlockList & bl);
	nsCString wrap_source(BlockList & bl);
private:
	//url
	nsIUrlAtt * url_att;
	string URL;
	string TITLE;

        //IDX Creator
	nsCOMPtr<nsIDocHandle> idx_handle;

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
        
        //Load cluster
	unsigned int allowed_type;

        set<string> main_node;
        set<string> ad_node;
	set<string> title_node;
	set<string> date_node;
	set<string> source_node;
	set<string> author_node;
	set<string> author_source_node;
};

#endif
