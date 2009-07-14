#include "BlockNode.h"
#include "BlockUtils.h"
#include <string>
#include <iostream>
#include <regex.h>

using namespace std;

BlockList::BlockList() {
    cluster = NULL;
}

BlockList::~BlockList() {
}

list<BlockNode> & BlockList::GetBlockList() {
    return this->blocks;
}

int BlockList::size() {
    return blocks.size();
}

BlockNode BlockList::GetBlock(int index) {
    list<BlockNode>::iterator it;
    int i = 0;
    for (it = blocks.begin(); it != blocks.end(); it++) {
        if (i == index) {
            BlockNode bn = *it;
            return bn;
        }
    }
    return BlockNode();
}

void BlockList::AddBlock(BlockNode bn) {
    blocks.push_back(bn);
}

string BlockList::GetText() {
    list<BlockNode>::iterator it;
    string text1("");
    for (it = blocks.begin(); it != blocks.end(); it++) {
        if (it->GetName().compare("SCRIPT") != 0
                && it->GetName().compare("STYLE") != 0) {
            text1.append(it->GetText());
        }
    }
    return text1;
}

string BlockList::GetText(set<string> & ad_node) {
    list<BlockNode>::iterator it;
    string text1("");
    for (it = blocks.begin(); it != blocks.end(); it++) {
        string & path = it->GetPath();
        set<string>::iterator it_ad = ad_node.find(path);
        if (it_ad != ad_node.end()) continue;
        if (it->GetName().compare("SCRIPT") != 0
                && it->GetName().compare("STYLE") != 0) {
            text1.append(it->GetText());
        }
    }
    return text1;
}

string BlockList::GetAnchorText() {
    list<BlockNode>::iterator it;
    string text1("");
    for (it = blocks.begin(); it != blocks.end(); it++) {
        if (it->GetName().compare("SCRIPT") == 0
                || it->GetName().compare("STYLE") == 0)
            continue;

        string & path = it->GetPath();
        size_t found = path.find("A:");
        if (found != string::npos) {
            text1.append(it->GetText());
        } else {
            found = path.find("A/");
            if (found != string::npos)
                text1.append(it->GetText());
        }
    }
    return text1;
}

string BlockList::GetAnchorText(set<string> & ad_node) {
    list<BlockNode>::iterator it;
    string text1("");
    for (it = blocks.begin(); it != blocks.end(); it++) {
        if (it->GetName().compare("SCRIPT") == 0
                || it->GetName().compare("STYLE") == 0)
            continue;

        string & path = it->GetPath();
        set<string>::iterator it_ad = ad_node.find(path);
        if (it_ad != ad_node.end())
            continue;

        size_t found = path.find("A:");
        if (found != string::npos) {
            text1.append(it->GetText());
        } else {
            found = path.find("A/");
            if (found != string::npos)
                text1.append(it->GetText());
        }
    }
    return text1;
}

string BlockList::GetPathText(string & path) {
    list<BlockNode>::iterator it;
    string text1("");
    for (it = blocks.begin(); it != blocks.end(); it++) {
        string & p = it->GetPath();
        if (p.compare(path) == 0) {
            string s = it->GetText();
            text1.append(s);
            text1.append("\n");
        }
    }
    //string_filter(text1);
    return text1;
}

BlockNode BlockList::GetPathNode(string & path) {
    list<BlockNode>::iterator it;

    for (it = blocks.begin(); it != blocks.end(); it++) {
        string & p = it->GetPath();
        if (p.compare(path) == 0)
            return *it;
    }
    return BlockNode();
}

int BlockList::GetPathCount(string & path) {
    list<BlockNode>::iterator it;
    int count = 0;
    for (it = blocks.begin(); it != blocks.end(); it++) {
        string & p = it->GetPath();
        if (p.compare(path) == 0)
            count++;
    }
    return count;
}

float BlockList::anchor_density(set<string> & ad_node) {
    string s1 = GetText(ad_node);
    string s2 = GetAnchorText(ad_node);

    string_filter(s1);
    string_filter(s2);
    int len1 = s1.length();
    int len2 = s2.length();
//    LOG << "text.len: "<<len1<<" text: " << s1 << endl;
//    LOG << "anchor_text.len: "<<len2<<" anchor: "<<s2<<"\n";
    if (len2 > 0) {
        return len2 / (float) len1;
    } else if (len1 == 0) {
        return -1.0;
    } else {
        return 0.0;
    }
}

float BlockList::anchor_density() {
    string s1 = GetText();
    string s2 = GetAnchorText();

    string_filter(s1);
    string_filter(s2);
    int len1 = s1.length();
    int len2 = s2.length();
    //LOG << "text.len: "<<len1<<" text: " << s1 << endl;
    //LOG << "anchor_text.len: "<<len2<<" anchor: "<<s2<<"\n";
    if (len2 > 0) {
        return len2 / (float) len1;
    } else if (len1 == 0) {
        return -1.0;
    } else {
        return 0.0;
    }
}

void BlockList::SetPath(string p) {
    this->xpath = p;
}

string & BlockList::GetPath() {
    return xpath;
}

void BlockList::SetUrl(string u) {
    this->url = u;
}

string & BlockList::GetUrl() {
    return url;
}

void BlockList::SetTitle(string title) {
    this->title = title;
}

string & BlockList::GetTitle() {
    return title;
}

void * BlockList::GetClusterPointer() {
    return cluster;
}

void BlockList::SetClusterPointer(void * c) {
    cluster = c;
}

/*
   如果link是相对路径，使用此方法找到完整路径
 */
string BlockList::find_link(string & link) {
    size_t f1 = link.find("http");
    if (f1 != string::npos) {
        //不是相对路径
        return link;
    }

    size_t f2 = link.rfind("./");
    string l1 = link;
    if (f2 != string::npos) {
        l1 = link.substr(f2 + 2);
        //LOG << link <<" : "<<l1<<"\n";
    }

    list<string>::iterator it;
    for (it = links.begin(); it != links.end(); it++) {
        string & l2 = *it;
        size_t f3 = l2.find(l1);
        if (f3 != string::npos) {
            return l2;
        }
    }
    return string();
}

void BlockList::add_link(string link) {
    this->links.push_back(link);
}

/*
   BlockNode
 */
BlockNode::BlockNode() {
    x = y = w = h = 0;
}

BlockNode::~BlockNode() {
}

string & BlockNode::GetPath() {
    return this->path;
}

string BlockNode::GetText() {
    return this->text;
}

string & BlockNode::GetName() {
    return this->name;
}

string & BlockNode::GetAnchorText() {
    return this->anchor_text;
}

map<string, string> & BlockNode::GetAttr() {
    return this->attr;
}

string BlockNode::GetAttrString() {
    map<string, string>::iterator it;
    string s;
    if (attr.size() > 0) s.append(":");
    for (it = attr.begin(); it != attr.end(); it++) {
        if (it->first.compare("href") == 0) continue;
        s.append(" ");
        s.append(it->first);
        s.append("=");
        s.append(it->second);
    }
    return s;
}

void BlockNode::SetAttr(string k, string v) {
    this->attr.insert(pair<string, string > (k, v));
}

void BlockNode::SetName(string & n) {
    this->name = n;
}

void BlockNode::SetPath(string & path) {
    this->path = path;
}

void BlockNode::SetText(string & text) {
    this->text = text;
}

void BlockNode::SetAnchorText(string & a) {
    this->anchor_text = a;
}

bool BlockNode::is_anchor_mark() {
    if (name.compare("A") == 0) return true;
    size_t f = path.find("/A/");
    if (f != string::npos)
        return true;
    f = path.find("/A:");
    if (f != string::npos)
        return true;
    return false;
}

int BlockNode::get_weight() {
    string t = text;
    string_filter(t);
    return t.length();
}

void BlockNode::SetX(int i) {
    x = i;
}

int BlockNode::GetX() {
    return x;
}

void BlockNode::SetY(int i) {
    y = i;
}

int BlockNode::GetY() {
    return y;
}

void BlockNode::SetW(int i) {
    w = i;
}

int BlockNode::GetW() {
    return w;
}

void BlockNode::SetH(int i) {
    h = i;
}

int BlockNode::GetH() {
    return h;
}

bool BlockNode::operator==(BlockNode & other) {
    bool b = false;
    if (this->path.compare(other.GetPath()) == 0) {
        b = true;
    }
    return b;
}

bool operator<(BlockNode a, BlockNode b) {
    return a.GetText().length() < b.GetText().length();
}

/**
 * ACLDB
 */
ACLDB::ACLDB() {
    this->def = true;
    string a("A");
    string script("SCRIPT");
    add_deny(a);
    add_deny(script);
}

ACLDB::ACLDB(bool def) {
    this->def = def;
    string a("A");
    string script("SCRIPT");
    add_deny(a);
    add_deny(script);
}

void ACLDB::add_allow(string pat) {
    map<string, bool>::iterator iter = pats.find(pat);
    if (iter != pats.end()) {
        pats.erase(iter);
    }

    pats.insert(pair<string, bool>(pat, true));
}

void ACLDB::add_deny(string pat) {
    map<string, bool>::iterator iter = pats.find(pat);
    if (iter != pats.end()) {
        pats.erase(iter);
    }

    pats.insert(pair<string, bool>(pat, false));
}

bool ACLDB::allowed(string & mark) {
    map<string, bool>::iterator iter = pats.find(mark);
    if (iter != pats.end()) {
        return iter->second;
    }

    return def;
}

void ACLDB::serialize(stringstream & ss) {
    int size = pats.size();
    ss << size << endl;
    map<string, bool>::iterator iter = pats.begin();
    for (; iter != pats.end(); iter++) {
        string a = iter->first;
        bool b = iter->second;
        ss << a << endl;
        ss << b << endl;
    }
}

void ACLDB::deserialize(stringstream & ss) {
    int size = 0;
    size = get_integer(ss);
    for (int i = 0; i < size; i++) {
        string a;
        bool b;
        a = get_line(ss);
        b = get_integer(ss);
        this->pats.insert(pair<string, bool>(a, b));
    }
}

/*
   list<BlockNode> blocks;
 */
void BlockList::serialize(stringstream & ss) {
    ss << xpath << endl;
    ss << url << endl;
    int size = blocks.size();
    ss << size << endl;
    list<BlockNode>::iterator it;
//    LOG << "    there are " << size << " nodes\n";
    for (it = blocks.begin(); it != blocks.end(); it++) {
        BlockNode & bn = *it;
        bn.serialize(ss);
    }
//    LOG << "block list serialization ok\n";
}

void BlockList::deserialize(stringstream & ss) {
    xpath = get_line(ss);
    url = get_line(ss);
    LOG << "url:" << url << "\n";
    int size = 0;
    size = get_integer(ss);
    //LOG<<"    there are "<<size<<" nodes\n";
    for (int i = 0; i < size; i++) {
        BlockNode bn;
        bn.deserialize(ss);
        blocks.push_back(bn);
    }
}

/*
   string name;
   string path;
   string text;
   string anchor_text;
   map<string,string>attr;
 */
string invalid_characters("\n\t\r#");

void BlockNode::serialize(stringstream & ss) {
//    LOG << "block node serialization start\n";
    ss << name << endl;
    ss << path << endl;
    string_filter(text, invalid_characters);
//    LOG << text << endl;
    ss << text << endl;
    ss << x << endl;
    ss << y << endl;
    ss << w << endl;
    ss << h << endl;
    /*
    int size = attr.size();
    ss << size << endl;
    map<string,string>::iterator  it = attr.begin();
    for(; it!=attr.end(); it++)
    {
            string a = it->first;
            string b = it->second;
		
            ss << a << endl;
            ss << b << endl;
    }
     */
//    LOG << "block node serialization ok\n";
}

void BlockNode::deserialize(stringstream & ss) {
    name = get_line(ss);
    path = get_line(ss);
    text = get_line(ss);
    x = get_integer(ss);
    y = get_integer(ss);
    w = get_integer(ss);
    h = get_integer(ss);
    /*
    int size = 0;
    size = get_integer(ss);
    LOG<<"        "<<name<<" has "<<size<<" attrs\n";
    for(int i = 0; i < size; i++)
    {
            string a;
            string b;
		
            a = get_line(ss);
            b = get_line(ss);

            attr.insert(pair<string,string>(a,b));
    }
     */
}
