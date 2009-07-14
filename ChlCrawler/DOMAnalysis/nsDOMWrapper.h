#include "xpcom-config.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMAnalysis.h"
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
#include "nsIIndexDoc.h"
#include "nsIDocHandle.h"
#include "nsIColAtt.h"
#include "nsIColIO.h"
#include "nsIIDXCreator.h"
#include "nsIColBridge.h"
#include "nsIIDXCreator.h"

#include "BlockUtils.h"
#include "BlockNode.h"

#include <string>
#include <map>
#include <list>
#include <set>
#include <time.h>

#ifndef __NSDOMWRAPPER_H__
#define __NSDOMWRAPPER_H__

#define NS_DOMWRAPPER_CONTRACTID "@nyapc.com/XPCOM/nsDOMWrapper;1"
#define NS_DOMWRAPPER_CLASSNAME "nsDOMWrapper"
#define NS_DOMWRAPPER_CID {0x0c84e22a, 0xe924, 0x4428, { 0x9b, 0xd5, 0xe7, 0xa9, 0x4e, 0x5a, 0xb7, 0xe2}}

using namespace std;

class nsDOMWrapper : nsIDOMAnalysis
{
public:
	NS_DECL_ISUPPORTS
	NS_DECL_NSIDOMANALYSIS
	
	nsDOMWrapper();
	~nsDOMWrapper();

private:
	//DOM
	nsIDOMDocument * doc;

	//url
	nsIUrlAtt * url_att;
	string URL;
	string TITLE;
        string MustHaveCSV;
        string DontMustHaveCSV;
        string StopTag;
        string StartTag;

	//IDX Creator
	nsIIDXCreator *creator;
	nsCOMPtr<nsIDocHandle> idx_handle;

	//Database
	nsCOMPtr<nsIClusterDBHandle> cdb_handle;
        nsCOMPtr<nsIColIO> col_handle;
        nsCOMPtr<nsIColBridge> bridge;
	nsCString mLocation;
	
	//Property
	nsIPersistentProperties * property;
	
	//Page clusters
	list<BlockCluster> clusters;

	//wrapper name
	string wrapper_name;

        //Index URL
        nsCString index_addr;

        //Marks
        //Column Map
        map<nsCString,nsCString> column_map;
        //Sitedomain
        nsCString sitedomain;
        //SOURCEINFO
        nsCString sourceinfo;

	//Load cluster
	unsigned int allowed_type;

	//Wrapper rules
	set<string> main_node;
        set<string> ad_node;
	set<string> title_node;
	set<string> date_node;
	set<string> source_node;
	set<string> author_node;
	set<string> author_source_node;
	void collect_wrapper_rules();

	void serialize();
	void deserialize();

	void save_wrap_rules();
	void save_wrap_rules(int con_type, int con_attr, string & rules);

	void load_wrap_rules_from_db(int type, BlockCluster & bc);
	void load_wrap_rules(string & rules, BlockCluster & bc);
	void load_wrap_rules();
        void load_cluster();
        int get_num_of_cluster();

	void find_sim_cluster(BlockList & bl, BlockCluster ** bc);
	int analyze_page_type(BlockList & bl);
	int wrapping(BlockList & bl, BlockCluster * bc);
	void wrap_content_page(BlockList & bl, BlockCluster * bc);
	void wrap_content_page2(BlockList & bl);
	void wrap_nextpage(int type);

	nsCString wrap_title(BlockList & bl);
	nsCString wrap_content();
	nsCString wrap_date(BlockList & bl, string & date_format);
	nsCString wrap_author(BlockList & bl);
	nsCString wrap_source(BlockList & bl);

        void parse_colunmn_map(nsCString & c_map);
        void set_statdate(nsCString & date, nsIIDXCreator * idx);
        void set_sitedomain(nsCString & domain, nsIIDXCreator * idx);

        bool is_valid_url(string & url);
};

#endif
