#include "BlockUtils.h"
#include "BlockNode.h"
#include "distance.h"
#include "nsIDOMDocument.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIBoxObject.h"
#include "nsIDOMElement.h"
#include "nsIDOMHTMLElement.h"
#include "nsIDOMNSDocument.h"
#include "nsIDOMNodeList.h"
#include "nsIDOMNode.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsStringAPI.h"
#include "nsIDOM3Node.h"
#include "nsIDOMNamedNodeMap.h"
#include "nsIXpathUtil.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "xpcom-config.h"
#include <string>
#include <iostream>
#include <list>
#include <math.h>
#include <cstdlib>
#include "stringutil.h"

float total_weight(list<BlockNode> lst) {
    float w = 0;
    list<BlockNode>::iterator it;
    for (it = lst.begin(); it != lst.end(); it++) {
        BlockNode bn = *it;
        int len = bn.GetText().length();
        //len = len > BLOCK_MAX_WEIGHT ? BLOCK_MAX_WEIGHT : len;
        //len = len < 1 ? 1:len;
        w += len; //log10(len);
    }
    //w = w > 1 ? w : 1;
    return w; //log10((float)w);
}

float total_weight(list<BlockNode> lst, BlockList & bl1) {
    float w = 0;
    list<BlockNode>::iterator it;
    for (it = lst.begin(); it != lst.end(); it++) {
        BlockNode bn = *it;
        string str = bl1.GetPathText(bn.GetPath());
        string_filter(str);
        //LOG<<str<<"\n";
        int len = str.length();
        w += len;
    }
    return w;
}

float total_weight(list<BlockNode> lst, BlockList & bl1, BlockList & bl2) {
    float w = 0;
    float w1 = 0;
    list<BlockNode>::iterator it;
    for (it = lst.begin(); it != lst.end(); it++) {
        BlockNode bn = *it;
        string str1 = bl1.GetPathText(bn.GetPath());
        string str2 = bl2.GetPathText(bn.GetPath());
        string_filter(str1);
        string_filter(str2);
        //LOG<<"a:"<<str1<<"\nb:"<<str2<<"\n";
        int len1 = str1.length();
        int len2 = str2.length();
        w += len1;
        w1 += len2;
    }
    //LOG<<"w:"<<w<<" w1:"<<w1<<"\n";
    return w + w1;
}

float sim_clusters(BlockCluster & bc1, BlockCluster & bc2) {
    BlockList & bl1 = bc1.GetBestBlockList();
    BlockList & bl2 = bc2.GetBestBlockList();
    float sim = compare_structure(bl1, bl2);
    return sim;
}

/*
   计算cluster中所有block之间的相似度，然后得到一个相似度偏差s
 */
float sim_blocks(list<BlockList> & blocks) {
    if (blocks.size() < 2) return 0.0;
    list<BlockList>::iterator it;
    float score = 0.0;
    int n = 0;
    for (it = blocks.begin(); it != blocks.end(); it++) {
        BlockList & bl1 = *it;
        list<BlockList>::iterator it1 = it;
        it1++;
        for (; it1 != blocks.end(); it1++) {
            BlockList & bl2 = *it1;
            n++;
            score += sim_blocks(bl1, bl2);
            LOG << "sim score " << score << "\n";
        }
    }

    float s = score / (float) n;
    return s;
}

float sim_blocks(BlockList & bn1, BlockList & bn2) {
    string text1 = bn1.GetText();
    string text2 = bn2.GetText();
    //LOG << "text1: " << text1 << endl;
    //LOG << "text2: " << text2 << endl;
    float sim = sim_score(text1, text2);

    return sim;
}

float sim_score(const string & s1, const string & s2) {
    if (s1.compare("") == 0 && s2.compare("") == 0) return 0.0;
    if (s1.compare(s2) == 0) return 1.0;
    float same_count = same_score(s1, s2);
    return 2 * same_count / (float) (s1.length() + s2.length());
}

float same_score(const string & s1, const string & s2) {
    Distance distance;
    int len = s1.size() > s2.size() ? s1.size() : s2.size();
    int d = 0;
    if (s1.compare("") == 0 || s2.compare("") == 0) {
        d = len;
    } else {
        string str1, str2;
        int max_len = 900;
        if (s1.length() <= max_len)
            str1 = s1;
        else
            str2 = s1.substr(0, max_len);

        if (s2.length() <= max_len)
            str2 = s2;
        else
            str2 = s2.substr(0, max_len);
        //LOG<<"s1:"<<s1.length()<<endl;
        //LOG<<"s2:"<<s2.length()<<endl;
        const char * c1 = str1.c_str();
        const char * c2 = str2.c_str();
        len = str1.size() > str2.size() ? str1.size() : str2.size();
        d = distance.LD(c1, c2);
    }
    int same_count = 0;
    same_count = len - d;
    /*
    bool b = s1.length() > s2.length();
    const char* list1;
    const char* list2;
    int len1,len2;
    if(b)
    {
            list1 = s1.data();
            len1 = s1.length();
            list2 = s2.data();
            len2 = s2.length();
    }
    else
    {
            list1 = s2.data();
            len1 = s2.length();
            list2 = s1.data();
            len2 = s1.length();
    }

    char * it1 = (char*)list1;
    char * it2 = (char*)list2;
	
    int same_count = 0;
	
    char lb1,lb2;
    int j = 0;
    int k = 0;
    for( int i = 0 ; i < len1; i++ )
    {
            lb1 = *it1++;
            it2 = (char*)list2 + k;
            for(j = k; j < len2; j++ )
            {
                    lb2 = *it2++;
                    if(lb1 == lb2)
                    {
                            //LOG << "1 " << lb1 << " 2 "<< lb2 << endl;
                            i ++;
                            lb1 = *it1++;
                            same_count++;
                            k = j+1;
                    }
            }
    }
     */
    //LOG << "diff_score ok" << same_count << " " << s1.length()<< " "<<s2.length()<< endl;

    return same_count;
}

float compare_structure(BlockList & b1, BlockList & b2) {
    float sim = 0.0;
    //LOG<<"url1: "<<b1.GetUrl()<<"\n";
    //LOG<<"url2: "<<b2.GetUrl()<<"\n";

    list<BlockNode> l1, l2;
    l1 = b1.GetBlockList();
    l2 = b2.GetBlockList();

    filter(l1);
    filter(l2);
    uniq(l1);
    uniq(l2);

    //list<BlockNode> common = find_common(l1,l2);
    list<BlockNode> common = find_common2(l1, l2);

    float w0 = total_weight(common, b1, b2);
    float w1 = total_weight(l1, b1);
    float w2 = total_weight(l2, b2);

    //	if(common.size() * 2 > l1.size()+l2.size())
    //	{
    //		LOG<<"found abnormal.."<<"\n";
    /*		list<BlockNode>::iterator it;
                    LOG<<"common blocks:"<<"\n";
                    for(it=common.begin();it!=common.end();it++)
                    {
                            LOG<<it->GetPath()<<"-----"<<it->GetText()<<"\n";
                            //LOG<<it->GetPath()<<"\n";
                    }
                    LOG<<"l1 blocks:"<<"\n";
                    for(it=l1.begin();it!=l1.end();it++)
                    {
                            LOG<<it->GetPath()<<"-----"<<it->GetText()<<"\n";
                            //LOG<<it->GetPath()<<"\n";
                    }
                    LOG<<"l2 blocks:"<<"\n";
                    for(it=l2.begin();it!=l2.end();it++)
                    {
                            LOG<<it->GetPath()<<"-----"<<it->GetText()<<"\n";
                            //LOG<<it->GetPath()<<"\n";
                    }
     */
    //	}

    //LOG << "w0 " << w0 << " w1 " << w1 << " w2 " << w2 << endl;
    //LOG << "s0 " << common.size() << " s1 "<<l1.size()<<" s2 "<<l2.size()<<"\n";

    //	if (w0 > -0.000001 && w0 < 0.000001)
    //		return 0.0;

    //	float d = w1 - w0;
    //	d = d > 0.0 ? d : -d;
    //	float max = w1 >= w0 ? w1 : w0;
    //	LOG << "d " <<d<<"\n";
    //	sim = 1 - (d/max);
    sim = w0 / (w1 + w2);

    //sim = common.size() * 2 / (float)(l1.size()+l2.size());

    return sim;
}

ACLDB acl;
static bool init_acl = false;

void filter(list<BlockNode> & lst) {
    if (!init_acl) {
        acl.add_deny("IMG");
        acl.add_deny("STYLE");
        init_acl = true;
    }
    list<BlockNode>::iterator it;
    list<BlockNode>::iterator it1;
    for (it = lst.begin(); it != lst.end();) {
        it1 = it;
        it1++;
        bool b = acl.allowed(it->GetName());
        string text = it->GetText();
        string_filter(text);
        if (!b || text.compare("") == 0) {
            //LOG<<"deleted "<<it->GetName()<<"\n";
            lst.erase(it);
        }
        it = it1;
    }
}

void uniq(list<BlockNode> & lst) {
    list<BlockNode>::iterator it;
    list<BlockNode>::iterator it1;
    for (it = lst.begin(); it != lst.end();) {
        it1 = it;
        it1++;
        if (it1 == lst.end()) return;
        /*
        BlockNode & bn1 = * it;
        BlockNode & bn2 = * it1;
        if(bn1 == bn2)
        {
                //LOG<<"deleted.... "<<"\n";
                lst.erase(it);
        }
        it = it1;
         */
        BlockNode & bn1 = *it;
        list<BlockNode>::iterator it2;
        for (it2 = it1; it2 != lst.end(); it2++) {
            BlockNode & bn2 = *it2;
            if (bn1 == bn2) {
                lst.erase(it);
                break;
            }
        }
        it = it1;
    }
}

list<BlockNode> find_common(list<BlockNode> & l1, list<BlockNode> & l2) {
    list<BlockNode> lst;

    bool b = l1.size() > l2.size();
    list<BlockNode> list1;
    list<BlockNode> list2;
    int len1, len2;
    if (b) {
        list1 = l1;
        len1 = l1.size();
        list2 = l2;
        len2 = l2.size();
    } else {
        list1 = l2;
        len1 = l2.size();
        list2 = l1;
        len2 = l1.size();
    }

    list<BlockNode>::iterator it1 = list1.begin();
    list<BlockNode>::iterator it2 = list2.begin();
    list<BlockNode>::iterator it;
    BlockNode bn1, bn2;
    int j = 0;
    int k = 0;
    //LOG <<"len1 "<<len1<<" len2 "<<len2<<"\n";
    for (int i = 0; i < len1; i++) {
        bn1 = *it1++;
        it2 = list2.begin();
        for (int n = 0; n < k; n++) it2++;
        //LOG<<"k"<<k<<"\n";

        for (j = k; j < len2; j++) {
            bn2 = *it2++;
            if (bn1 == bn2) {
                //LOG << "i "<<i<<" j "<<j<<" match bn1 "<<bn1.GetPath() << " bn2 " << bn2.GetPath() << endl;
                /*
                BlockNode bn;
                string text = bn1.GetText()+bn2.GetText();
                string path = bn1.GetPath();
                bn.SetText(text);
                bn.SetPath(path);
                lst.push_back(bn);
                 */

                if (!b) {
                    lst.push_back(bn1);
                } else {
                    lst.push_back(bn2);
                }

                it = it1++;
                i++;
                if (it == list1.end()) break;
                bn1 = *it;
                {
                    k = j + 1;
                }

            } else {
                //LOG <<"i "<<i<<" j "<< j <<" unmatch bn1 "<<bn1.GetPath() << " bn2 " << bn2.GetPath() << endl;
            }
        }
        //if(it1 == list1.end()) break;
    }

    /*
            list<BlockNode>::iterator ite;
            for(ite = lst.begin(); ite != lst.end(); ite++)
            {
                    BlockNode bn = *ite;
                    string str = bn.GetPath();
                    LOG << "path "<< str <<" text "<<bn.GetText()<< endl;
            }
     */
    return lst;
}

list<BlockNode> find_common2(list<BlockNode> & l1, list<BlockNode> & l2) {
    list<BlockNode> lst;

    bool b = l1.size() < l2.size();
    list<BlockNode> list1;
    list<BlockNode> list2;
    int len1, len2;
    if (b) {
        list1 = l1;
        len1 = l1.size();
        list2 = l2;
        len2 = l2.size();
    } else {
        list1 = l2;
        len1 = l2.size();
        list2 = l1;
        len2 = l1.size();
    }

    list<BlockNode>::iterator it1 = list1.begin();
    list<BlockNode>::iterator it2;
    list<BlockNode>::iterator it;
    BlockNode bn1, bn2;
    int j = 0;
    int k = 0;
    for (; it1 != list1.end(); it1++) {
        bn1 = *it1;
        if (k >= len2) {
            //如果在list2中找不到相应的标签，则从上一次开始的顺序找
            k = j;
        } else {
            j = k;
        }
        k = k > 4 ? k - 4 : 0;
        it2 = list2.begin();
        for (int n = 0; n < k; n++) it2++;

        for (; it2 != list2.end(); it2++) {
            bn2 = *it2;
            k++;
            if (bn1 == bn2) {
                if (!b) {
                    lst.push_back(bn1);
                } else {
                    lst.push_back(bn2);
                }
                break;
            }
        }
    }

    return lst;
}

void convert_html_to_bl(nsIDOMHTMLDocument * html, BlockList & bl) {
    convert_html_to_bl(html, bl, false);
}

void convert_html_to_bl(nsIDOMHTMLDocument * html, BlockList & bl, bool xpath) {
    if (html != nsnull) {
        nsCOMPtr<nsIDOMNode> node = do_QueryInterface(html);
        nsCOMPtr<nsIDOMNSDocument> nsdoc = do_QueryInterface(html);
        LOG << "start parsing doc" << endl;
        parse_doc(node, bl, nsdoc, xpath);
    }
}

static set<string> ignore_node;

void set_ignore_node(string node) {
    ignore_node.insert(node);
}

static set<string> trusted_unknown_node;

void set_trusted_unknown_node(string node) {
    trusted_unknown_node.insert(node);
}

void parse_doc(nsIDOMNode * node, BlockList & bl, nsIDOMNSDocument * html, bool xpath) {
    if (node == nsnull) {
        LOG << "doc is null" << endl;
        return;
    }
    nsresult rv;
    PRBool has_child = false;
    node->HasChildNodes(&has_child);
    if (has_child) {
        nsCOMPtr<nsIDOMNodeList> children;
        rv = node->GetChildNodes(getter_AddRefs(children));
        if (NS_FAILED(rv)) {
            LOG << "Get domnode Error:" << std::hex << rv << std::endl;
            return;
        }
        PRUint32 len;
        children->GetLength(&len);
        for (int i = 0; i < len; i++) {
            nsIDOMNode * n;
            children->Item(i, &n);
            //nsString value;
            //n->GetNodeValue(value);
            nsString name;
            n->GetNodeName(name);
            unsigned short type;
            n->GetNodeType(&type);

            string node_name(NS_ConvertUTF16toUTF8(name).get());
            //LOG<<"node name:"<<node_name<<" node type:"<<type<<"\n";

            if (type == nsIDOMNode::ELEMENT_NODE) {
                BlockNode b;
                b.SetName(node_name);
                //                LOG<< "##name " << node_name << endl;
                string text = GetNodeText(n);
                //LOG << "#text " << text << endl;
                b.SetText(text);
                if (node_name.compare("HTML") != 0) {
                    map<string, string> & attr = b.GetAttr();
                    ParseAttrs(n, &attr);
                }

                nsCOMPtr<nsIDOMDocument> doc = do_QueryInterface(html);
                string path = get_node_path(n, doc, xpath);
                //path.append(b.GetAttrString());

                //                LOG << "### path..." << path <<"\n";
                b.SetPath(path);

                bool allowed = true;
                set<string>::iterator ite = ignore_node.find(node_name);
                if (ite != ignore_node.end()) allowed = false;
                allowed = allowed && node_name.compare("OPTION") != 0
                        && node_name.compare("SCRIPT") != 0
                        && node_name.compare("STYLE") != 0
                        && node_name.compare("TITLE") != 0;

                if (allowed) {
                    //
                    if (html != NULL) {
                        nsCOMPtr<nsIBoxObject> docbox;
                        nsCOMPtr<nsIDOMElement> docele = do_QueryInterface(n);
                        rv = html->GetBoxObjectFor(docele, getter_AddRefs(docbox));
                        if (!NS_FAILED(rv)) {
                            PRInt32 x, y, w, h;
                            docbox->GetHeight(&h);
                            docbox->GetWidth(&w);
                            docbox->GetX(&x);
                            docbox->GetY(&y);
                            b.SetX(x);
                            b.SetY(y);
                            b.SetW(w);
                            b.SetH(h);
                            //LOG<<"x:"<<x<<"y:"<<y<<"w:"<<w<<"h:"<<h<<endl;
                        }

                    }
                    //
                    bl.AddBlock(b);
                }
                parse_doc(n, bl, html, xpath);
            }
            //parse_doc(n,bl);
        }
    }
}

bool get_content(nsIDOMNode * node, nsCString & content, set<string> & main_nodes, set<string> & ad_nodes, string & stop_pos, string & start_pos, nsIDOMDocument * doc, bool xpath) {
    if (node == nsnull) {
        LOG << "doc is null" << endl;
        return false;
    }
    string path, node_name;
    path = get_node_path(node, doc, xpath);
    bool b_stop_tag = is_match_tag(stop_pos, path);
    if (b_stop_tag) return true;

    bool b_start_tag = is_match_tag(start_pos, path);
    if (b_start_tag) {
        content.Cut(0, content.Length());
    }
    bool is_main_node = has_element(main_nodes, path);
    bool is_ad_node = has_element(ad_nodes, path);

    if (!is_main_node && !is_ad_node) {
        nsString name;
        node->GetNodeName(name);
        node_name = string(NS_ConvertUTF16toUTF8(name).get());

        set<string>::iterator ite = trusted_unknown_node.find(node_name);
        if (ite != trusted_unknown_node.end()) is_main_node = true;
    }

    //    LOG<<"path:"<<path<<" main node? "<<is_main_node<<"\n";
    nsString name;
    node->GetNodeName(name);

    nsresult rv;
    PRBool has_child = false;
    node->HasChildNodes(&has_child);
    if (has_child) {
        nsCOMPtr<nsIDOMNodeList> children;
        rv = node->GetChildNodes(getter_AddRefs(children));
        if (NS_FAILED(rv)) {
            LOG << "Get domnode Error:" << std::hex << rv << std::endl;
            return false;
        }
        PRUint32 len;
        children->GetLength(&len);
        for (int i = 0; i < len; i++) {
            nsIDOMNode * n;
            children->Item(i, &n);

            unsigned short type;
            n->GetNodeType(&type);

            string nname(NS_ConvertUTF16toUTF8(name).get());
            nsString value;
            n->GetNodeValue(value);
            if (stop_pos.length() > 0) {
                nsCString v(NS_ConvertUTF16toUTF8(value).get());
                v.Trim(" ");
                string v1(v.get());
                b_stop_tag = is_match_tag(stop_pos, v1);
                //LOG<<"text:"<<v1<<" stop_tag:"<<b_stop_tag<<endl;
                if (b_stop_tag) return true;
            }
            if (start_pos.length() > 0) {
                nsCString v(NS_ConvertUTF16toUTF8(value).get());
                v.Trim(" ");
                string v1(v.get());
                b_start_tag = is_match_tag(start_pos, v1);
                //LOG<<"text:"<<v1<<" stop_tag:"<<b_stop_tag<<endl;
                if (b_start_tag) {
                    content.Cut(0, content.Length());
                }
            }

            if (is_main_node && type == 3) {
                bool allowed = true;
                set<string>::iterator ite = ignore_node.find(nname);
                if (ite != ignore_node.end()) allowed = false;
                allowed = allowed && nname.compare("OPTION") != 0
                        && nname.compare("SCRIPT") != 0
                        && nname.compare("STYLE") != 0
                        && nname.compare("TITLE") != 0;

                if (allowed) {
                    //LOG<<"[get_content2] append:"<<value.get()<<endl;
                    nsCString v(NS_ConvertUTF16toUTF8(value).get());
                    v.Trim(" \r\n");
                    if (v.Length() > 1)
                        content.Append(NS_ConvertUTF16toUTF8(value).get());
                }
            } else {
                //LOG<<"child"<<endl;
                b_stop_tag = get_content(n, content, main_nodes, ad_nodes, stop_pos, start_pos, doc, xpath);
                //LOG<<"child:"<<content.get()<<" stop_tag:"<<b_stop_tag<<endl;
                if (b_stop_tag) return true;
            }
        }
    }
    return b_stop_tag;
}

void get_node_text(nsIDOMNode * node, nsCString & text, string & node_path, nsIDOMDocument * doc, bool use_xpath) {
    if (node == nsnull) {
        LOG << "doc is null" << endl;
        return;
    }
    string path;
    path = get_node_path(node, doc, use_xpath);

    nsString name;
    node->GetNodeName(name);

    nsresult rv;
    PRBool has_child = false;
    node->HasChildNodes(&has_child);
    if (has_child) {
        nsCOMPtr<nsIDOMNodeList> children;
        rv = node->GetChildNodes(getter_AddRefs(children));
        if (NS_FAILED(rv)) {
            LOG << "Get domnode Error:" << std::hex << rv << std::endl;
            return;
        }
        PRUint32 len;
        children->GetLength(&len);
        for (int i = 0; i < len; i++) {
            nsIDOMNode * n;
            children->Item(i, &n);
            unsigned short type;
            n->GetNodeType(&type);
            nsString value;
            n->GetNodeValue(value);

            if (path.find(node_path) == 0) {
                if (type == 3) {
                    nsCString v(NS_ConvertUTF16toUTF8(value).get());
                    v.Trim(" \r\n");
                    if (v.Length() > 0)
                        text.Append(NS_ConvertUTF16toUTF8(value).get());

                    //                    LOG<<"path:"<<path<<"\ntext:"<<NS_ConvertUTF16toUTF8(value).get()<<"\n";
                } else {
                    //                    LOG<<"path:"<<path<<"\nnode_path:"<<node_path<<"\n";
                    get_node_text(n, text, node_path, doc, use_xpath);
                }
            } else if (path.length() < node_path.length()) {
                get_node_text(n, text, node_path, doc, use_xpath);
            }
        }
    }
    return;
}

bool get_content2(nsIDOMNode * node,
        nsCString & content,
        set<string> & collection) {
    string sp;
    string start_pos;
    return get_content2(node, content, collection, sp, start_pos);
}

bool get_content2(nsIDOMNode * node, nsCString & content, set<string> & collection, string & stop_pos, string & start_pos) {
    if (node == nsnull) {
        LOG << "doc is null" << endl;
        return false;
    }
    string path;
    path = get_node_path(node, path);
    bool b_stop_tag = is_match_tag(stop_pos, path);
    //    LOG<<"path:"<<path<<" stop_tag:"<<b_stop_tag<<endl;
    if (b_stop_tag) return true;

    bool b_start_tag = is_match_tag(start_pos, path);
    if (b_start_tag) {
        content.Cut(0, content.Length());
    }
    bool record = has_element(collection, path);
    nsString name;
    node->GetNodeName(name);

    nsresult rv;
    PRBool has_child = false;
    node->HasChildNodes(&has_child);
    if (has_child) {
        nsCOMPtr<nsIDOMNodeList> children;
        rv = node->GetChildNodes(getter_AddRefs(children));
        if (NS_FAILED(rv)) {
            LOG << "Get domnode Error:" << std::hex << rv << std::endl;
            return false;
        }
        PRUint32 len;
        children->GetLength(&len);
        for (int i = 0; i < len; i++) {
            nsIDOMNode * n;
            children->Item(i, &n);

            unsigned short type;
            n->GetNodeType(&type);

            string nname(NS_ConvertUTF16toUTF8(name).get());
            nsString value;
            n->GetNodeValue(value);
            if (stop_pos.length() > 0) {
                nsCString v(NS_ConvertUTF16toUTF8(value).get());
                v.Trim(" ");
                string v1(v.get());
                b_stop_tag = is_match_tag(stop_pos, v1);
                //LOG<<"text:"<<v1<<" stop_tag:"<<b_stop_tag<<endl;
                if (b_stop_tag) return true;
            }
            if (start_pos.length() > 0) {
                nsCString v(NS_ConvertUTF16toUTF8(value).get());
                v.Trim(" ");
                string v1(v.get());
                b_start_tag = is_match_tag(start_pos, v1);
                //LOG<<"text:"<<v1<<" stop_tag:"<<b_stop_tag<<endl;
                if (b_start_tag) {
                    content.Cut(0, content.Length());
                }
            }

            if (!record && type == 3) {
                bool allowed = true;
                set<string>::iterator ite = ignore_node.find(nname);
                if (ite != ignore_node.end()) allowed = false;
                allowed = allowed && nname.compare("OPTION") != 0
                        && nname.compare("SCRIPT") != 0
                        && nname.compare("STYLE") != 0
                        && nname.compare("TITLE") != 0;

                if (allowed) {
                    //LOG<<"[get_content2] append:"<<value.get()<<endl;
                    nsCString v(NS_ConvertUTF16toUTF8(value).get());
                    v.Trim(" \r\n");
                    if (v.Length() > 1)
                        content.Append(NS_ConvertUTF16toUTF8(value).get());
                }
            } else {
                //LOG<<"child"<<endl;
                b_stop_tag = get_content2(n, content, collection, stop_pos, start_pos);
                //LOG<<"child:"<<content.get()<<" stop_tag:"<<b_stop_tag<<endl;
                if (b_stop_tag) return true;
            }
        }
    }
    return b_stop_tag;
}

string GetNodeText(nsIDOMNode * node) {
    nsresult rv;

    PRBool has_child = false;
    node->HasChildNodes(&has_child);
    string ret;
    if (has_child) {
        nsCOMPtr<nsIDOMNodeList> children;
        rv = node->GetChildNodes(getter_AddRefs(children));
        if (NS_FAILED(rv)) {
            LOG << "Get domnode Error:" << std::hex << rv << std::endl;
            return string("");
        }
        PRUint32 len;
        children->GetLength(&len);
        for (int i = 0; i < len; i++) {
            nsIDOMNode * n;
            children->Item(i, &n);
            nsString name;
            n->GetNodeName(name);
            unsigned short type;
            n->GetNodeType(&type);

            string node_name(NS_ConvertUTF16toUTF8(name).get());

            if (type == 3)//TEXT_NODE
            {
                nsString value;
                n->GetNodeValue(value);
                ret.append(NS_ConvertUTF16toUTF8(value).get());
            }
        }
    }
    return ret;
}

void ParseAttrs(nsIDOMNode * node, map<string, string> *attr) {
    if (node == nsnull) return;
    nsresult rv;
    nsCOMPtr<nsIDOMNamedNodeMap> attrs_map;
    rv = node->GetAttributes(getter_AddRefs(attrs_map));
    if (NS_FAILED(rv)) {
        LOG << "Get attributes error" << endl;
        return;
    }

    PRUint32 len;
    attrs_map->GetLength(&len);
    for (int i = 0; i < len; i++) {
        nsIDOMNode * n;
        attrs_map->Item(i, &n);
        nsString value;
        n->GetNodeValue(value);
        nsString name;
        n->GetNodeName(name);
        /*LOG<<"attrs name:"<<ToNewUTF8String(name)
                <<" value:"<<ToNewUTF8String(value)
                        <<" index:"<<i<<"\n";*/
        string str_name(NS_ConvertUTF16toUTF8(name).get());
        string str_value(NS_ConvertUTF16toUTF8(value).get());
        attr->insert(pair<string, string > (str_name, str_value));
    }

}

static set<string> ignore_attr;

void set_ignore_attr(string attr) {
    ignore_attr.insert(attr);
}

string & get_node_path(nsIDOMNode * node, string & path) {
    string stop_pos("HTML");
    return get_node_path(node, path, stop_pos);
}

string get_node_path(nsIDOMNode * node, nsIDOMDocument * doc, bool xpath) {
    nsresult rv;
    string path("");
    if (nsnull == node || nsnull == doc) return path;

    unsigned short type;
    node->GetNodeType(&type);
    if (type != nsIDOMNode::ELEMENT_NODE) {
        return path;
    }

    if (!xpath) {
        path = get_node_path(node, path);
    } else {
        nsCOMPtr<nsIXpathUtil> xpathUtil = nsnull;
        if (nsnull == xpathUtil) {
            //                        LOG << "init nsXpathUtil \"@nyapc.com/XPCOM/nsXpathUtil;1\" \n";
            xpathUtil = do_CreateInstance("@nyapc.com/XPCOM/nsXpathUtil;1", &rv);
            if (NS_FAILED(rv)) {
                ERROR << "Get  XpathUtil Error" << rv << "\n";
                exit(-1);
            }
        }
        xpathUtil->SetDocument(doc);
        nsCString xp;
        xpathUtil->GetXpath(node, 1, xp);
        path.append(xp.get());
    }
    return path;
}

string & get_node_path(nsIDOMNode * node, string & path, string & stop_pos) {
    //LOG << "get_node_path" <<path<<"\n";
    nsresult rv;
    nsIDOMNode * parent = nsnull;
    if (node == nsnull)
        return path;

    nsString node_name;
    rv = node->GetNodeName(node_name);
    if (NS_FAILED(rv)) {
        LOG << "Get Node Name Error:" << std::hex << rv << std::endl;
        return path;
    }
    string s(NS_ConvertUTF16toUTF8(node_name).get());
    if (s.compare(stop_pos) == 0) return path;
    if (s.at(0) == '#') return path;
    path.append(s);

    //LOG << "get_node_path" <<path<<"\n";

    rv = node->GetParentNode(&parent);
    if (NS_FAILED(rv)) {
        LOG << "Get Parent Error:" << std::hex << rv << std::endl;
        return path;
    } else {
        if (XPATH_WITH_ATTRIBUTE) {
            //Get Attrs
            nsIDOMNamedNodeMap * attrs_map;
            rv = node->GetAttributes(&attrs_map);
            map<string, string> attr;
            if (NS_FAILED(rv)) {
                LOG << "Get attributes error" << endl;
            } else {
                PRUint32 len;
                attrs_map->GetLength(&len);
                for (int i = 0; i < len; i++) {
                    nsIDOMNode * n;
                    attrs_map->Item(i, &n);
                    nsString value;
                    n->GetNodeValue(value);
                    nsString name;
                    n->GetNodeName(name);

                    string str_name(NS_ConvertUTF16toUTF8(name).get());
                    string str_value(NS_ConvertUTF16toUTF8(value).get());
                    attr.insert(pair<string, string > (str_name, str_value));
                }
            }
            if (s.compare("A") != 0) {
                //如果不是标签A，则路径上需要带属性
                bool bb = false;
                map<string, string>::iterator it;
                for (it = attr.begin(); it != attr.end(); it++) {
                    bool b = it->first.compare("class") == 0
                            || it->first.compare("id") == 0
                            || it->first.compare("name") == 0
                            || it->first.compare("align") == 0
                            || it->first.compare("bgcolor") == 0
                            || it->first.compare("color") == 0;

                    set<string>::iterator ite = ignore_attr.find(it->first);
                    if (ite != ignore_attr.end()) b = false;

                    if (b) {
                        if (!bb) {
                            path.append(":");
                            bb = true;
                        }
                        size_t f = it->second.find('(');
                        if (f == string::npos)
                            path.append(" ").append(it->first).append("=").append(it->second);
                    }
                }
            }
        }
        path.append("/");
        return get_node_path(parent, path);
    }
}

void print_block_list(BlockList & bl) {
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it;
    for (it = lst.begin(); it != lst.end(); it++) {
        LOG << "name " << it->GetName() << " path " << it->GetPath() << " text " << it->GetText() << "\n";
    }
}

void print_cluster(BlockCluster & bc) {
    int type = bc.GetType();
    LOG << "cluster type: " << type << "\n";
    if (type == CONTENT_BLOCK)
        LOG << "cluster title path: " << bc.GetTitlePath() << "\n";
    list<BlockList> lst = bc.GetAllBlocks();
    list<BlockList>::iterator it = lst.begin();
    for (it = lst.begin(); it != lst.end(); it++) {
        BlockList bl = *it;
        //BlockList & bl = bc.GetBestBlockList();
        list<BlockNode> & l1 = bl.GetBlockList();
        //filter(l1);
        //uniq(l1);
        print_block_list(bl);
    }
}

void print_best_bl(BlockCluster & bc) {
    list<BlockList> lst = bc.GetAllBlocks();
    list<BlockList>::iterator it = lst.begin();
    //for(it=lst.begin();it!=lst.end();it++)
    {
        //BlockList & bl = *it;
        BlockList & bl = bc.GetBestBlockList();
        print_block_list(bl);
    }
}

string string_ext_name(string & url) {
    //LOG << "url: "<<url<<"\n";
    size_t p = url.rfind('/');
    if (int(p) == (url.length() - 1)) {
        return string();
    }

    size_t dot = url.rfind('.');
    if (dot != string::npos) {
        if (dot > p) {
            string type = url.substr(dot + 1);
            string_filter(type);
            if (type.length() < 5)
                return type;
        }
    }

    return string();
}

static regex_t regex[1];
static bool init = false;

void init_regex_pat() {
    int flag = 0;
    int r = regcomp(regex, "\\(0\\?[1-9]\\|[1-9][0-9]\\|[1-9][0-9]\\{3\\}\\)\\([^0-9]\\{1,6\\}\\)\\(0\\?[1-9]\\|[1-9][0-9]\\|[1-9][0-9]\\{3\\}\\)\\([^0-9]\\{1,6\\}\\)\\(0\\?[1-9]\\|[1-9][0-9]\\|[1-9][0-9]\\{3\\}\\)\\(\\([^0-9]\\+\\)\\(\\(0\\?[0-9]\\|[1-5][0-9]\\)\\([^0-9]\\+\\)\\(0\\?[0-9]\\|[1-5][0-9]\\)\\(\\([^0-9]\\+\\)\\(0\\?[0-9]\\|[1-5][0-9]\\)\\)\\?\\)\\)\\?", flag);
    if (r != 0) {
        cout << "regexp pattern error" << "\n";
    }
}

const int v_len = 6;
//日期格式的Beyas网络

float p_date(int * S) {
    if (S[0]) {
        if (S[1] && S[2] && S[3]) return 1.0;
        if (S[1] && S[4]) return 0.85;
        if (S[1] && S[5]) return 0.8;
        if (S[1]) return 0.6;
    }
    return 0.0;
}

float is_date_format2(string & d, regex_t * reg) {
    size_t nmatch = 20;
    regmatch_t pm[nmatch];
    int length[nmatch];

    int v[v_len];
    for (int x = 0; x < v_len; x++) {
        v[x] = 0;
    }
    int r = regexec(reg, d.c_str(), nmatch, pm, 0);
    if (!r) {
        //Pattern Match
        v[0] = 1;
        for (int i = 1; i < nmatch; i++) {
            length[i] = -1;
            if (pm[i].rm_so != -1) {
                //LOG<<i<<" so: "<<pm[i].rm_so<<" eo: "<<pm[i].rm_eo<<"\n";
                int n = pm[i].rm_eo - pm[i].rm_so;
                length[i] = n;
                if (i == 2 || i == 10) {
                    string sep("-/:");
                    char * cstr = (char*) d.c_str() + --n;
                    size_t f = sep.find(*cstr);
                    if (f != string::npos) {
                        v[5] = 1;
                    }
                }
            }
        }

        if (length[2] == length[4] && length[2] >= 0) {
            //年月日之间存在分割符
            v[1] = 1;
        }

        if (length[9] > 0 && length[11] > 0 && length[13] > 0) {
            //存在时分秒
            v[2] = 1;
        }

        if (length[10] == length[12] && length[10] > 0) {
            //存在时分秒，且之间存在分割符
            v[3] = 1;
        }

        if (embed_word_year(d)) {
            v[4] = 1;
        }
    }
    return p_date(v);
}

float is_date_format(string & d) {
    if (!init) {
        init_regex_pat();
    }

    regex_t * reg = regex;
    float w = is_date_format2(d, reg);
    return w;
}

bool embed_word_year(string & d) {
    size_t f = d.find("年");
    if (f != string::npos)
        return true;
    f = d.find("月");
    if (f != string::npos)
        return true;
    f = d.find("日");
    if (f != string::npos)
        return true;
    return false;
}

bool is_nextpage_text(string text) {
    bool b = false;

    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, "^\\([0-9]\\+\\|上.\\{,6\\}页\\|下.\\{,6\\}页\\|>\\+\\|<\\+\\)$", flag);
    if (r != 0) {
        char ebuf[128];
        regerror(r, &reg, ebuf, sizeof (ebuf));
        cout << "regexp pattern error: " << ebuf << "\n";
    } else {
        size_t nmatch = 1;
        regmatch_t pm;
        string_filter(text);
        int r = regexec(&reg, text.c_str(), nmatch, &pm, 0);
        if (!r) {
            b = true;
            /*
            int pos = 0;
            if(pm.rm_so != -1)
            {
                    int len = pm.rm_eo - pm.rm_so;
                    s.erase(pm.rm_so, len);
                    string_filter2(s);
            }
             */
        }
    }
    regfree(&reg);

    return b;
}

bool has_element(const set<string> & s, string & path) {
    set<string>::iterator it;
    it = s.find(path);
    if (it != s.end())
        return true;
    return false;
}

string tool_wrap_author(BlockList & bl, const string & author_path) {
    string author;
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        if (path.compare(author_path) == 0) {
            //            string text = bl.GetPathText(path);
            string text = bn.GetText();
            author = extract_author(text);
            //            LOG<<"text: "<<text<<"\nauthor: "<<author<<endl;
            //            if (author.length() < 1) {
            //                if (has_word_author(text)) {
            //                    list<BlockNode>::iterator it = it_bn;
            //                    it++;
            //                    if (it != lst.end()) {
            //                        //寻找所有子节点
            //                        while (it != lst.end()) {
            //                            BlockNode & bn1 = *it++;
            //                            if (bn1.GetName().compare("A") != 0)
            //                                continue;
            //                            string & p = bn1.GetPath();
            //                            size_t found = p.find(path);
            //                            if (found != string::npos) {
            //                                author = bn1.GetText();
            //                                LOG << "found child node:" << p << "text:" << author << "\n";
            //                                break;
            //
            //                            } else {
            //                                break;
            //                            }
            //                        }
            //                    }
            //                }
            //            } else {
            //                return author;
            //            }
        }
    }

    return author;
}

string tool_wrap_source(BlockList & bl, const string & source_path) {
    string source;
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        if (path.compare(source_path) == 0) {
            //            string text = bl.GetPathText(path);
            string text = bn.GetText();
            string source_tmp = extract_source(text);
            if (has_word_site_or_paper(source_tmp)) {
                source = source_tmp;
            }
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
                                string src = bn1.GetText();
                                if (has_word_site_or_paper(src)) {
                                    source = src;
                                    LOG << "found child node:" << p << "text:" << source << "\n";
                                    break;
                                }

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

string tool_wrap_content(BlockList & bl, const set<string> & mn) {
    string content;
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        bool record = has_element(mn, path);
        if (record) {
            content.append(bn.GetText());
        }
    }
    return content;
}

string tool_wrap_content2(BlockList & bl, const set<string> & ad) {
    LOG << "tool_wrap_content2" << endl;
    string content;
    list<BlockNode> lst = bl.GetBlockList();
    list<BlockNode>::iterator it_bn;
    for (it_bn = lst.begin(); it_bn != lst.end(); it_bn++) {
        BlockNode & bn = *it_bn;
        string & path = bn.GetPath();
        bool record = has_element(ad, path);
        if (!record) {
            if (bn.get_weight() > 0) {
                string & name = bn.GetName();
                //                LOG<<name<<endl;
                if (name.compare("SCRIPT") != 0 && name.compare("STYLE") != 0 && name.compare("TITLE") != 0)
                    content.append(bn.GetText());
            }
        }
    }

    return content;
}

string escape(string & str) {
    string ret;
    char * chs = (char*) str.c_str();
    int len = str.length();
    for (int i = 0; i < len; i++) {
        char ch = *chs++;
        if (('0' <= ch && ch <= '9')
                || ('a' <= ch && ch <= 'z')
                || ('A' <= ch && ch <= 'Z')) {
            ret.push_back(ch);
        } else {
            stringstream ss;
            ss << std::uppercase << std::hex << (int) ch;
            ret.append("%");
            ret.append(ss.str());
        }
        //        LOG<<ret<<"\n";
    }
    return ret;
}

void escape(const nsCString & str, nsCString & ret) {
    string r;
    char * chs = (char*) str.get();
    int len = str.Length();
    for (int i = 0; i < len; i++) {
        char ch = *chs++;
        if (('0' <= ch && ch <= '9')
                || ('a' <= ch && ch <= 'z')
                || ('A' <= ch && ch <= 'Z')) {
            r.push_back(ch);
        } else {
            stringstream ss;
            ss << std::uppercase << std::hex << (int) ch;
            r.append("%");
            r.append(ss.str());
        }
        //        LOG<<ret<<"\n";
    }

    ret = nsCString(r.c_str());
    return;
}

bool is_match_tag(string & pattern, string & tag_value) {
    bool b = false;
    if (pattern.length() <= 0 || tag_value.length() <= 0) return b;

    int flag = 0;
    regex_t reg;
    int r = regcomp(&reg, pattern.c_str(), flag);
    if (r != 0) {
        char ebuf[128];
        regerror(r, &reg, ebuf, sizeof (ebuf));
        //        LOG << "[is_match_tag] regexp pattern error: " << ebuf << "\n";
    } else {
        size_t nmatch = 1;
        regmatch_t pm;
        int r = regexec(&reg, tag_value.c_str(), nmatch, &pm, 0);
        if (!r) {
            b = true;
            //            LOG<<"[is_match_tag] pattern:"<<pattern<<" value:"<<tag_value<<endl;
        }
    }

    regfree(&reg);

    return b;
}

void split(string & str, string & sep, set<string> & collection) {
    int off = sep.length();
    size_t sp = 0;
    size_t ep = sp;
    ep = str.find(sep, sp);
    if (ep == string::npos) collection.insert(string(str));
    while (ep != string::npos) {
        string sub = str.substr(sp, ep - sp);
        //LOG<<sub<<endl;
        collection.insert(sub);
        sp = ep + off;
        ep = str.find(sep, sp);
    }
}