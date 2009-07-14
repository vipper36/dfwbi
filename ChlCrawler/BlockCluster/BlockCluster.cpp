#include "BlockCluster.h"
#include "BlockUtils.h"
#include "BlockNode.h"
#include <string>
#include <iostream>
#include <list>
#include <fstream>
#include "property.h"

using namespace std;

BlockCluster::BlockCluster() {
    name = 0;
    is_important = false;
    is_need_train = false;
    important = 0;
    type = INVALID_BLOCK;
    title_acl.add_deny("SPAN");
    title_acl.add_deny("SCRIPT");
    content_acl.add_deny("SCRIPT");
    content_acl.add_deny("STYLE");
    content_acl.add_deny("TITLE");
    content_acl.add_allow("A");

    links_acl = ACLDB(false);
    links_acl.add_allow("A");
    links_acl.add_allow("EM");

    file_acl = ACLDB(false);
    file_acl.add_allow("html");
    file_acl.add_allow("htm");
    file_acl.add_allow("jsp");
    file_acl.add_allow("shtml");
}

BlockCluster::BlockCluster(int t) {
    name = t;
    is_important = false;
    is_need_train = false;
    important = 0;
    type = INVALID_BLOCK;
    title_acl.add_deny("SPAN");
    title_acl.add_deny("SCRIPT");
    content_acl.add_deny("SCRIPT");
    content_acl.add_deny("STYLE");
    content_acl.add_deny("TITLE");
    content_acl.add_allow("A");

    links_acl = ACLDB(false);
    links_acl.add_allow("A");
    links_acl.add_allow("EM");

    file_acl = ACLDB(false);
    file_acl.add_allow("html");
    file_acl.add_allow("htm");
    file_acl.add_allow("jsp");
    file_acl.add_allow("shtml");
}

BlockCluster::~BlockCluster() {

}

int BlockCluster::insert(BlockList node) {
    int max_block_num = BLOCK_NUMBER_IN_A_CLUSTER;
    if (GetType() != CONTENT_BLOCK) max_block_num = 2;

    if (this->blocks.size() >= max_block_num) {
        LOG << "               This Cluster is full\n";
        return max_block_num;
    }


    list<BlockList>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); it++) {
        BlockList & bl = *it;
        string & url = bl.GetUrl();
        string & path = bl.GetPath();
        if (node.GetUrl().compare(url) == 0) {
            LOG << "            This block has been recorded.." << "\n";
            return this->blocks.size();
        }
    }
    this->blocks.push_front(node);
    is_need_train = true;

    //将统计每个节点在cluster中出现的次数
    list<BlockNode> & lst = node.GetBlockList();
    list<BlockNode>::iterator ite;
    for (ite = lst.begin(); ite != lst.end(); ite++) {
        bool b_allowed = content_acl.allowed(ite->GetName());
        if (!b_allowed)continue;
        int weight = ite->get_weight();
        if (weight <= 0) continue;
        int count = 0;
        string & path = ite->GetPath();
        map<string, int>::iterator iter =
                this->all_valid_node.find(path);
        if (iter != this->all_valid_node.end()) {
            count = iter->second;
        }
        count++;
        this->all_valid_node[path] = count;
    }

    return this->blocks.size();
}

void BlockCluster::statistic_node_occ() {
    list<BlockList>::iterator it = this->blocks.begin();
    for (; it != this->blocks.end(); it++) {
        BlockList & bl = *it;
        list<BlockNode> & lst = bl.GetBlockList();
        list<BlockNode>::iterator ite;
        for (ite = lst.begin(); ite != lst.end(); ite++) {
            bool b_allowed = this->content_acl.allowed(ite->GetName());
            if (!b_allowed)continue;
            int weight = ite->get_weight();
            if (weight <= 0) continue;
            int count = 0;
            string & path = ite->GetPath();
            map<string, int>::iterator iter =
                    this->all_valid_node.find(path);
            if (iter != this->all_valid_node.end()) {
                count = iter->second;
            }
            count++;
            this->all_valid_node[path] = count;
        }
    }
}

float BlockCluster::IsSimilar(BlockList & node) {
    list<BlockList>::iterator it;
    int num = 0;
    float total_sim = 0.0;
    for (it = blocks.begin(); it != blocks.end(); it++) {
        BlockList bn = *it;
        float sim = compare_structure(bn, node);
        //LOG<<"sim structure "<<sim<<"\n";
        if (sim < SIMILAR_THRESHOLD)
            return sim;
        num++;
        total_sim += sim;
    }
    return total_sim / (float) num;
}

bool BlockCluster::need_training() {
    return is_need_train;
}

void BlockCluster::training_completed() {
    is_need_train = false;
}

BlockList & BlockCluster::GetBestBlockList() {
    list<BlockList>::iterator it = blocks.begin();
    list<BlockList>::iterator it1 = it;
    if (blocks.size() < 2) return *it;

    int max = 0;
    for (; it1 != blocks.end(); it1++) {
        int size = it1->size();
        if (size > max) {
            it = it1;
            max = size;
        }

    }
    return *it;
}

list<BlockNode> & BlockCluster::GetMainBlockPath() {
    return main_node;
}

int BlockCluster::GetBlockSize() {
    return this->blocks.size();
}

int BlockCluster::GetImportant() {
    return this->important;
}

void BlockCluster::SetImportant(int i) {
    this->important = i;
}

void BlockCluster::SetType(int t) {
    this->type = t;
}

int BlockCluster::GetType() {
    return type;
}

int BlockCluster::GetName() {
    return name;
}

void BlockCluster::SetName(int n) {
    name = n;
}

map<string, string> & BlockCluster::GetRule() {
    return this->wrap_rule;
}

list<BlockNode> & BlockCluster::GetMainNode() {
    return this->main_node;
}

void BlockCluster::SetRule(string & k, string & v) {
    map<string, string>::iterator it = wrap_rule.find(k);
    if (it != wrap_rule.end()) {
        wrap_rule.erase(it);
    }
    wrap_rule.insert(pair<string, string > (k, v));
}

string BlockCluster::GetRuleString() {
    string rules;
    map<string, string>::iterator it;
    for (it = wrap_rule.begin(); it != wrap_rule.end(); it++) {
        rules.append(it->first);
        rules.append(RULE_SEPARATOR);
        rules.append(it->second);
        rules.append("\n");
    }
    return rules;
}

list<BlockList> & BlockCluster::GetAllBlocks() {
    return this->blocks;
}

bool BlockCluster::IsImportantBlock() {
    return is_important;
}

void BlockCluster::SetImportant(bool b) {
    this->is_important = b;
}

float BlockCluster::anchor_density() {
    list<BlockList>::iterator it = blocks.begin();
    int n = 0;
    float den = 0.0;
    for (; it != blocks.end(); it++) {
        float d = it->anchor_density(all_ad_node);
        //LOG<<"d: "<<d<<"\n";
        if (d >= 0.0) {
            n++;
            den += d;
        }
    }
    if (n > 0) {
        return den / n;
    } else {
        //没有办法计算连接文本比率
        //可能是Block中没有文本
        return -1;
    }
}

float BlockCluster::avrg_text_length() {
    list<BlockList>::iterator it = blocks.begin();
    int n = 0;
    int total_len = 0;
    for (; it != blocks.end(); it++) {
        string s = it->GetText(all_ad_node);
        string_filter(s);
        total_len += s.length();
        n++;
    }
    important = total_len / n;
    return total_len / (float) n;

}

void BlockCluster::analyze_common() {
    list<BlockList>::iterator it = blocks.begin();
    list<BlockNode> common_node = it->GetBlockList();
    it++;
    for (; it != blocks.end(); it++) {
        common_node = find_common(common_node, it->GetBlockList());
    }

    list<BlockNode>::iterator it_bn;
    for (it_bn = common_node.begin(); it_bn != common_node.end(); it_bn++) {
        string path = it_bn->GetPath();
        list<string>::iterator it_str = common_node_path.begin();
        for (; it_str != common_node_path.end(); it_str++) {
            if (it_str->compare(path) == 0) {
                common_node_path.erase(it_str);
                break;
            }
        }
        common_node_path.push_back(path);
        //LOG << "common path "<<path<<"\n";
    }
}

void BlockCluster::analyze_title() {
    if (main_node.size() == 0) {
        //exception
        LOG << "it isn't a content block, or you must analyze main section first.." << endl;
        if (GetType() == CONTENT_BLOCK) {
            SetType(INVALID_BLOCK);
        }
        return;
    }

    list<BlockNode>::iterator it;
    float max_w = 0.0;
    for (it = main_node.begin(); it != main_node.end(); it++) {
        BlockNode bn = *it;
        string path = bn.GetPath();
        bool b_allowed = title_acl.allowed(bn.GetName());
        if (!b_allowed)continue;
        //标题串应该在内容块之前
        if (path.compare(main_section_path) == 0) break;
        float count = GetPathCount(path);
        //LOG << "main path: "<<path<<" count: "<<count<<"\n";
        //标题块每页只有一个
        if (count > 1) {
            //LOG<<"it is not an unique path<<"\n";"
        } else {
            float w = 0.0;
            float avg_w = 0.0;
            int n = blocks.size();
            list<BlockList>::iterator it_bl;
            for (it_bl = blocks.begin(); it_bl != blocks.end(); it_bl++) {
                string text = it_bl->GetPathText(path);
                string main_text = it_bl->GetPathText(main_section_path);
                string_filter(main_text);
                string_filter(text);
                float same = same_score(text, main_text);
                /*
                LOG << "text: "<<text<<"\n";
                LOG << "main text: "<<main_text<<"\n";
                LOG << "text.length: "<<text.length()<<"\n";
                LOG << "main_text.length: "<<main_text.length()<<"\n";
                LOG << "same: "<<same<<"\n";
                 */
                if (text.length() > 0)
                    w += same / (float) text.length();
                //else
                //	return;
                avg_w += text.length();
            }
            float a = -1 / (float) AVERAGE_TITLE_LENGTH;
            avg_w = avg_w / n - AVERAGE_TITLE_LENGTH;
            avg_w = a * avg_w * avg_w + AVERAGE_TITLE_LENGTH;
            //LOG<<"Ew = "<<w<<" avg_w = "<<avg_w<<"\n";
            w = w / n;
            w = w * avg_w;
            if (w > max_w) {
                //found title...
                string title(RULE_TITLE);
                this->SetRule(title, path);
                max_w = w;
                //	LOG << "W: "<<w<<"title path: " << path << "\ntext: " << GetPathText(path) << endl;
            }
            /*
            else
            {
                    LOG << "W: "<<w<<"path: " << path << " \ntext: " << GetPathText(path) << endl;
            }
             */
        }
    }
}

void BlockCluster::analyze_main_section() {
    if (common_node_path.size() == 0) {
        analyze_common();
    }

    main_node.clear();
    list<string>::iterator comm_it = common_node_path.begin();
    int max_w = 0;
    for (; comm_it != common_node_path.end(); comm_it++) {
        string path = *comm_it;
        list<BlockList>::iterator it = blocks.begin();
        BlockNode bn = it->GetPathNode(path);
        bool b_allowed = content_acl.allowed(bn.GetName());
        if (!b_allowed) {
            continue;
        }
        //LOG << "path "<<path <<" text "<<bn.GetText()<<"\n";

        float score = 0.0;
        int w = 0;
        int c = 0;
        int n = 0;
        for (; it != blocks.end(); it++) {
            string s1 = it->GetPathText(path);
            string_filter(s1);
            w += s1.length();
            c++;
            list<BlockList>::iterator it1 = it;
            for (it1++; it1 != blocks.end(); it1++) {
                BlockList & bl2 = *it1;
                n++;
                string s2 = it1->GetPathText(path);
                string_filter(s2);
                score += sim_score(s1, s2);
            }
        }
        //如果只有一个BlockList，则score等于1
        if (n != 0)
            score = score / (float) n;
        else
            return;
        w = w / c;
        if (score < SIMILAR_NODE_THRESHOLD && w > 5) {
            //此块不为广告块，检查原来有的block
            it = blocks.begin();
            bool is_anchor = bn.is_anchor_mark();
            bool is_single = it->GetPathCount(path) <= 1;
            if (!is_anchor || (is_anchor && is_single)) {
                //LOG<<"insert main node:"<<path<<"\n";
                main_node.push_back(bn);
            } else {
                all_ad_node.insert(path);
            }
            if (w > max_w) {
                max_w = w;
                main_section_path = path;
                //LOG <<"W: "<<max_w<<" main block node: " << path << endl;
            }
            //LOG << "sim: "<< score << " W: "<<w << " text: " << it->GetPathText(path) << endl;
            //LOG << "sim: "<< score << " W: "<<w<<" main block node: " << path << endl;
        } else {
            //发现广告块
            if (w > 0) {
                all_ad_node.insert(path);
                /*
                it = blocks.begin();
                LOG << "sim: "<< score << " W: " << w
                        <<" invalid block node: " << path
                                << " text: "<<it->GetPathText(path)<<"\n";
                 */
            }
        }

    }

    list<BlockNode>::iterator it_mn = main_node.begin();
    string all_main_node;
    string mn(RULE_MAIN_NODE);
    for (; it_mn != main_node.end(); it_mn++) {
        string p = it_mn->GetPath();
        all_main_node.append(p).append("\\n");
    }

    this->SetRule(mn, all_main_node);

    set<string>::iterator it_ad = all_ad_node.begin();
    string ad_node;
    string ad(RULE_AD_NODE);
    for (; it_ad != this->all_ad_node.end(); it_ad++) {
        string p = *it_ad;
        ad_node.append(p).append("\\n");
    }

    this->SetRule(ad, ad_node);
}

void BlockCluster::analyze_date_author_source() {
    LOG << "analysis date, author and source\n";
    float date_th = 0.5;
    map<string, int>::iterator it;
    for (it = all_valid_node.begin(); it != all_valid_node.end(); it++) {
        string path = it->first;
        int count = it->second;
        LOG << "valid path:" << path << "\n";

        int date_match_count, author_match_count, source_match_count;
        date_match_count = author_match_count = source_match_count = 0;
        bool is_date, is_author, is_source;
        is_date = is_author = is_source = false;

        if (path.compare(main_section_path) == 0) continue;

        list<BlockList>::iterator it_bl;
        for (it_bl = blocks.begin(); it_bl != blocks.end(); it_bl++) {
            string text = it_bl->GetPathText(path);
            int w = text.length();
            if (w <= 0 && w > 200) continue;

            float num = it_bl->GetPathCount(path);
            if (num < 1.5) {
                float p = is_date_node(text);
                //LOG<<text<<"p:"<<p<<"th:"<<date_th<<"\n";
                if (p >= date_th) {
                    date_match_count++;
                    is_date = true;
                    date_th = p;
                    LOG << " match date format " << text << "\n";
                }
            }

            if (is_author_node(text)) {
                author_match_count++;
                is_author = true;
                LOG << "match author format " << text << "\n";
            }

            if (is_source_node(text)) {
                source_match_count++;
                is_source = true;
                LOG << "match source format " << text << "\n";
            }

        }
        if (is_date) {
            if (is_source) date_th = 2.0;
            LOG << "count:" << count << " match:" << date_match_count << " find date node: " << path << "\n";
            string date(RULE_DATE);
            SetRule(date, path);
        }
        if (is_author && is_source) {
            LOG << "author & source: " << path << "\n";
            string author(RULE_AUTHOR_SOURCE);
            SetRule(author, path);
        } else if (is_author) {
            LOG << "author: " << path << "\n";
            string author(RULE_AUTHOR);
            SetRule(author, path);
        } else if (is_source) {
            LOG << "source: " << path << "\n";
            string source(RULE_SOURCE);
            SetRule(source, path);
        }
    }
}

float BlockCluster::is_date_node(string text) {
    bool b = false;
    float S = is_date_format(text);
    b = has_word_copyright(text);

    if (!b && text.size() < 200) {
        return S;
    }
    return 0.0;
}

bool BlockCluster::is_author_node(string text) {
    bool b = false;
    bool S[4];
    S[0] = has_word_author(text);
    string_filter(text);
    S[1] = text.length() < 100;
    //S[2] = bn.has_word_copyright();
    //S[3] = bn.is_anchor_mark();

    if (S[0] && S[1]) {
        return true;
    }
    /*
    if(S[0] && !S[2])
    {
            b = true;
    }
     */
    return b;
}

bool BlockCluster::is_source_node(string text) {
    bool b = false;
    bool S[4];
    S[0] = has_word_source(text);
    string_filter(text);
    S[1] = text.length() < 100;
    //S[2] = has_word_site_or_paper(text);

    if (S[0] && S[1]) {
        return true;
    }
    return b;
}

string BlockCluster::GetPathText(string & path) {
    list<BlockList>::iterator it_bl;
    string text;
    for (it_bl = blocks.begin(); it_bl != blocks.end(); it_bl++) {
        BlockList & bl = *it_bl;
        text.append(bl.GetPathText(path));
    }
    return text;
}

float BlockCluster::GetPathCount(string & path) {
    list<BlockList>::iterator it_bl;
    float count = 0.0;
    int n = 0;
    for (it_bl = blocks.begin(); it_bl != blocks.end(); it_bl++) {
        BlockList & bl = *it_bl;
        count += bl.GetPathCount(path);
        n++;
    }
    return count / (float) n;

}

string BlockCluster::GetTitlePath() {
    string title("title");
    map<string, string>::iterator iter = wrap_rule.find(title);
    if (iter != wrap_rule.end()) {
        return iter->second;
    }
    return string();
}

string BlockCluster::GetDatePath() {
    string date("date");
    map<string, string>::iterator iter = wrap_rule.find(date);
    if (iter != wrap_rule.end()) {
        return iter->second;
    }
    return string();
}

string BlockCluster::GetAuthorPath() {
    string s("a&s");
    map<string, string>::iterator iter = wrap_rule.find(s);
    if (iter != wrap_rule.end()) {
        return iter->second;
    }

    s = string("author");
    iter = wrap_rule.find(s);
    if (iter != wrap_rule.end()) {
        return iter->second;
    }

    return string();
}

string BlockCluster::GetSourcePath() {
    string s("a&s");
    map<string, string>::iterator iter = wrap_rule.find(s);
    if (iter != wrap_rule.end()) {
        return iter->second;
    }

    s = string("source");
    iter = wrap_rule.find(s);
    if (iter != wrap_rule.end()) {
        return iter->second;
    }

    return string();
}

string BlockCluster::wrap_title(BlockList & bl) {
    LOG << "Wrap title" << "\n";
    string path = GetTitlePath();
    if (path.length() > 0) {
        string title = bl.GetPathText(path);
        LOG << title << "\n";
        return title;
    }
    return string();
}

string BlockCluster::wrap_content(BlockList & bl) {
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    string content;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        if (is_main_node(path)) {
            //LOG<<"main node:"<<bn.GetText()<<endl;
            content.append(bn.GetText());
        }
    }
    return content;
}

string BlockCluster::wrap_date(BlockList & bl, string & date_format) {
    string date;
    LOG << "Wrap date\n";
    string path = GetDatePath();
    if (path.length() > 0) {
        string d = bl.GetPathText(path);
        LOG << d << "\n";
        date = get_date(d, date_format);
    }
    return date;
}

string BlockCluster::wrap_author(BlockList & bl) {
    string author;
    LOG << "Wrap author\n";
    /*	string path = GetAuthorPath();
            if(path.length()>0)
            {
                    string text = bl.GetPathText(path);
                    //LOG<<text<<"\n";
                    author = extract_author(text);
            }
     */
    string s_path = GetAuthorPath();
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        if (path.compare(s_path) == 0) {
            string text = bl.GetPathText(path);
            author = extract_author(text);
            if (author.length() < 1) {
                if (has_word_author(text)) {
                    list<BlockNode>::iterator it = it_bn;
                    it++;
                    if (it != lst.end()) {
                        BlockNode & bn1 = *it;
                        string & p = bn1.GetPath();
                        size_t found = p.find(path);
                        if (found != string::npos)
                            author = bn1.GetText();
                    }
                }
            } else {
                return author;
            }
        }
    }

    return author;
}

string BlockCluster::wrap_source(BlockList & bl) {
    string source;
    /*	LOG<<"Wrap source\n";
            string path = GetSourcePath();
            if(path.length()>0)
            {
                    string text = bl.GetPathText(path);
                    //LOG<<text<<"\n";
                    source = extract_source(text);
            }
     */
    string s_path = GetSourcePath();
    LOG << "Wrap source " << s_path << "\n";
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        if (path.compare(s_path) == 0) {
            string text = bl.GetPathText(path);
            source = extract_source(text);
            {
                if (has_word_source(text)) {
                    list<BlockNode>::iterator it = it_bn;
                    it++;
                    if (it != lst.end()) {
                        //寻找所有子节点
                        while (it != lst.end()) {
                            BlockNode & bn1 = *it++;
                            if (bn1.GetName().compare("A") != 0)
                                continue;
                            string & p = bn1.GetPath();
                            size_t found = p.find(path);
                            if (found != string::npos) {
                                source = bn1.GetText();
                                LOG << "found child node:" << p << "text:" << source << "\n";
                                //if(has_word_site_or_paper(source))
                                break;

                            } else {
                                break;
                            }
                        }
                    }

                    return source;
                }
            }
        }
    }

    return source;
}

bool BlockCluster::is_main_node(string & path) {
    //    if (path.compare(GetTitlePath()) == 0) return false;
    //    list<BlockNode>::iterator it;
    //    for (it = main_node.begin(); it != main_node.end(); it++) {
    //        BlockNode & bn = *it;
    //        if (path.compare(bn.GetPath()) == 0)
    //            return true;
    //    }
    string main_node = wrap_rule[RULE_MAIN_NODE];
    string p(path);
    p.append("\\n");
    size_t f = main_node.find(p);
    if (f != string::npos) return true;
    return false;
}

void BlockCluster::serialize(stringstream & ss) {
    ss << is_important << endl;
    ss << important << endl;
    ss << type << endl;
    ss << name << endl;
    //LOG<<"main_section_path:"<<main_section_path<<endl;
    ss << main_section_path << endl;
    int size = blocks.size();
    size = size > 5 ? 5 : size;
    ss << size << endl;
    list<BlockList>::iterator it_bl = blocks.begin();
    for (int i = 0; i < size; i++) {
        BlockList & bl = *it_bl++;
        bl.serialize(ss);
    }
    /*
    size = common_node_path.size();
    ss << size << endl;
    list<string>::iterator it_str;
    for(it_str = common_node_path.begin(); it_str != common_node_path.end(); it_str++)
    {
            string path = *it_str;
            ss << path << endl;
    }
     */
    size = wrap_rule.size();
    ss << size << endl;
    map<string, string>::iterator it_wr = wrap_rule.begin();
    for (int i = 0; i < size; i++) {
        string a = it_wr->first;
        string b = it_wr->second;
        ss << a << endl;
        ss << b << endl;
        it_wr++;
    }

    size = main_node.size();
    ss << size << endl;
    list<BlockNode>::iterator it_bn = main_node.begin();
    for (int i = 0; i < size; i++) {
        it_bn->serialize(ss);
        it_bn++;
    }
}

void BlockCluster::deserialize(stringstream & ss) {
    is_important = get_integer(ss);
    important = get_integer(ss);
    type = get_integer(ss);
    name = get_integer(ss);
    main_section_path = get_line(ss);
    int size = 0;
    size = get_integer(ss);
    LOG << "there are " << size << " blocklist in a cluster" << "\n";
    for (int i = 0; i < size; i++) {
        BlockList bl;
        bl.deserialize(ss);
        blocks.push_back(bl);
    }
    /*
    size = 0;
    size = get_integer(ss);
    LOG << "number of common node path: "<<size<<"\n";
    for(int i = 0; i < size; i++)
    {
            string path;
            path = get_line(ss);
            LOG<<"common node path: "<<path<<"\n";
            common_node_path.push_back(path);
    }
     */
    size = 0;
    size = get_integer(ss);
    //LOG << "number of wrapper rules: "<<size<<"\n";
    for (int i = 0; i < size; i++) {
        string a, b;
        a = get_line(ss);
        b = get_line(ss);
        //LOG<<"wrap rule:"<<a<<"value:"<<b<<endl;
        wrap_rule.insert(pair<string, string > (a, b));
    }
    size = 0;
    size = get_integer(ss);
    //LOG << "number of main node: "<<size<<"\n";
    for (int i = 0; i < size; i++) {
        BlockNode bn;
        bn.deserialize(ss);
        main_node.push_back(bn);
    }
}

bool operator<(BlockCluster a, BlockCluster b) {
    return a.GetImportant() < b.GetImportant();
}
