#include <map>
#include <set>
#include <fstream>
#include <sstream>
#include "BlockNode.h"
#include "date.h"
#include "analysis.h"

#ifndef __BLOCKCLUSTER_H__
#define __BLOCKCLUSTER_H__

class BlockCluster
{
public:
	BlockCluster();
	BlockCluster(int t);
	~BlockCluster();

	int insert(BlockList node);
        void statistic_node_occ();
	float IsSimilar(BlockList & node);
	bool need_training();
	void training_completed();
	BlockList & GetBestBlockList();
	list<BlockNode> & GetMainBlockPath();

	int GetBlockSize();
	int GetImportant();

	void SetImportant(int i);
	void SetType(int t);
	int GetType();
	int GetName();
	void SetName(int n);
	
	map<string,string> & GetRule();
	list<BlockNode> & GetMainNode();
	void SetRule(string & k, string & v);
	string GetRuleString();
	list<BlockList> & GetAllBlocks();

	bool IsImportantBlock();
	void SetImportant(bool b);

	float anchor_density();
	float avrg_text_length();

	void analyze_common();
	void analyze_title();
	void analyze_main_section();
	void analyze_date_author_source();
	//void analyze_date();
	//void analyze_author();

	string GetPathText(string & path);
	float GetPathCount(string & path);

	string wrap_title(BlockList & bl);
	string wrap_content(BlockList & bl);
	string wrap_date(BlockList & bl, string & date_format);
	string wrap_author(BlockList & bl);
	string wrap_source(BlockList & bl);

	string GetTitlePath();
	string GetDatePath();
	string GetAuthorPath();
	string GetSourcePath();
	bool is_main_node(string & path);

	void serialize(stringstream & ss);
	void deserialize(stringstream & ss);
private:
	bool is_important;
	bool is_need_train;
	int important;
	int type;
	int name;
	string main_section_path;
	list<BlockList> blocks;
	list<string> common_node_path;
	map<string,string> wrap_rule;
	list<BlockNode> main_node;
	map<string,int> all_valid_node;
	set<string> all_ad_node;
	string date_node;
	
	ACLDB content_acl;
	ACLDB title_acl;
	ACLDB links_acl;
	ACLDB file_acl;

	float is_date_node(string text);
	bool is_author_node(string text);
	bool is_source_node(string text);
};

bool operator<(BlockCluster a,BlockCluster b);
#endif
