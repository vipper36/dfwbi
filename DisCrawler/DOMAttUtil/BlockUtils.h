#include "BlockNode.h"
#include "nsIDOMNode.h"
#include "nsStringAPI.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSDocument.h"
#include "BlockCluster.h"
#include "property.h"
#include <sstream>
#include <list>
#include <regex.h>


#ifndef __BLOCKUTILS_H__
#define __BLOCKUTILS_H__
using namespace std;
float compare_structure(BlockList & b1, BlockList & b2);

//list<BlockNode> find_common(list<BlockNode> & l1, list<BlockNode> & l2);
list<BlockNode> find_common2(list<BlockNode> & l1, list<BlockNode> & l2);

float sim_clusters(BlockCluster & bc1, BlockCluster & bc2);

float sim_blocks(list<BlockList> & blocks);
float sim_blocks(BlockList & bn1, BlockList & bn2);
float sim_score(const string & s1, const string & s2);
float same_score(const string & s1, const string & s2);

void convert_html_to_bl(nsIDOMHTMLDocument * html, BlockList & bl);
void convert_html_to_bl(nsIDOMHTMLDocument * html, BlockList & bl, bool xpath);
void parse_doc(nsIDOMNode * node, BlockList & bl, nsIDOMNSDocument * html, bool xpath);

bool get_content(nsIDOMNode * node, nsCString & content, set<string> & main_nodes, set<string> & ad_nodes,
        string & stop_pos, string & start_pos,
        nsIDOMDocument * doc, bool xpath);
bool get_content2(nsIDOMNode * node, nsCString & content, set<string> & collection);
bool get_content2(nsIDOMNode * node, nsCString & content, set<string> & collection,
        string & stop_pos, string & start_pos);

void get_node_text(nsIDOMNode * node, nsCString & text, string & path, nsIDOMDocument * doc, bool use_xpath);

bool is_match_tag(string & pattern, string & tag_value);

string GetNodeText(nsIDOMNode * node);
void ParseAttrs(nsIDOMNode * node, map<string,string> *attr);
void set_ignore_attr(string attr);
void set_ignore_node(string node);
void set_trusted_unknown_node(string node);
string get_node_path(nsIDOMNode * node, nsIDOMDocument * doc, bool xpath);
string & get_node_path(nsIDOMNode * node, string & path);
string & get_node_path(nsIDOMNode * node, string & path, string & stop_pos);

void print_block_list(BlockList & bl);
void print_cluster(BlockCluster & bc);
void print_best_bl(BlockCluster & bc);
void uniq(list<BlockNode> & lst);
void filter(list<BlockNode> & lst);


string string_ext_name(string & url);

void init_regex_pat();
float is_date_format(string & d);
bool embed_word_year(string & d);

bool is_nextpage_text(string text);

bool has_element(const set<string> & s, string & path);

string tool_wrap_author(BlockList & bl, const string & author_path);
string tool_wrap_source(BlockList & bl, const string & source_path);
string tool_wrap_content(BlockList & bl, const set<string> & mn);
string tool_wrap_content2(BlockList & bl, const set<string> & ad);

string escape(string & str);
void escape(const nsCString & str, nsCString & ret);

void split(string & str, string & sep, set<string> & collection);
#endif
