#include <map>
#include <list>
#include <set>
#include <string>
#include <fstream>
#include <sstream>
#include <regex.h>

using namespace std;

#ifndef __BLOCKNODE_H__
#define __BLOCKNODE_H__

class ACLDB
{
public:
	ACLDB();
	ACLDB(bool def);
	
	void add_allow(string pat);
	void add_deny(string pat);
	bool allowed(string & mark);

	void serialize(stringstream & os);
	void deserialize(stringstream & ss);
private:
	map<string,bool> pats;
	bool def;
};

class BlockNode
{
public:
	BlockNode();
	~BlockNode();

	string & GetPath();
	string GetText();
	string & GetName();
	string & GetAnchorText();
	map<string,string> & GetAttr();
	string GetAttrString();

	void SetAttr(string k,string v);
	void SetName(string & n);
	void SetPath(string & path);
	void SetText(string & text);
	void SetAnchorText(string & a);
	bool operator==(BlockNode & other);

	void serialize(stringstream & os);
	void deserialize(stringstream & ss);

	bool is_anchor_mark();
	int get_weight();

	void SetX(int i);
	int GetX();
	void SetY(int i);
	int GetY();
	void SetW(int i);
	int GetW();
	void SetH(int i);
	int GetH();

private:
	string name;
	string path;
	string text;
	string anchor_text;
	map<string,string>attr;

	int x,y,w,h;

//	list<BlockNode> children;
};

class BlockList
{
public: 
	BlockList();
	~BlockList();

	list<BlockNode> & GetBlockList();
	int size();
	BlockNode GetBlock(int index);

	void AddBlock(BlockNode bn);

	string GetText();
	string GetText(set<string> & ad_node);
	string GetAnchorText();
	string GetAnchorText(set<string> & ad_node);
	float anchor_density(set<string> & ad_node);
	float anchor_density();
	
	string GetPathText(string & path);
	BlockNode GetPathNode(string & path);
	int GetPathCount(string & path);

	void serialize(stringstream & os);
	void deserialize(stringstream & ss);

	void SetPath(string p);
	string & GetPath();

	void SetUrl(string u);
	string & GetUrl();

	void SetTitle(string title);
	string & GetTitle();

	string find_link(string & link);
	void add_link(string link);

	void * GetClusterPointer();
	void SetClusterPointer(void * c);
private:
	list<BlockNode> blocks;
	string xpath;
	string url;
	string title;
	list<string> links;
	void * cluster;
};

bool operator<(BlockNode a,BlockNode b);

#endif
