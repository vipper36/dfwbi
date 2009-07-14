#include "nsDOMTest.h"
#include "BlockUtils.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "nsIFileStreams.h"
#include "nsNetUtil.h"
#include "nsILineInputStream.h"
#include <iostream>
#include <math.h>

#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMElement.h"
#include "nsIDOMNodeList.h"
#include "nsVoidArray.h"

NS_IMPL_ISUPPORTS1(nsDOMTest, nsIDOMCluster)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDOMTest)

static nsModuleComponentInfo components[] ={
    {
        NS_DOMTEST_CLASSNAME,
        NS_DOMTEST_CID,
        NS_DOMTEST_CONTRACTID,
        nsDOMTestConstructor,
    }
};

NS_IMPL_NSGETMODULE("nsDOMTestModule", components)

nsDOMTest::nsDOMTest() {
    nsresult rv;
    cdb_handle = do_CreateInstance("@nyapc.com/XPCOM/nsClusterDBHandle;1", &rv);
    if (NS_FAILED(rv)) {
        ERROR << "Get  mozIStorageService  Error:" << rv << "\n";
        cdb_handle = NULL;
    }

    idx_handle = do_CreateInstance("@nyapc.com/XPCOM/nsDocHandle;1", &rv);
    if (NS_FAILED(rv)) {
        ERROR << "Get doc handle Error:" << rv << "\n";
        idx_handle = NULL;
    }

//    url_att = NULL;
    //LOG<<"init object ok\n";
}

nsDOMTest::~nsDOMTest() {
}

NS_IMETHODIMP nsDOMTest::Analysis(const nsACString & location) {
    LOG << "          startup... " << nsCString(location).get() << "\n";

    LoadDBConfig(location);

    load_cluster();
    load_wrap_rules();
    collect_wrapper_rules();

    while (true) {
        LOG << "Analysis begin..\n";
        BlockList bl;
        int url_id;
        load_document(bl, &url_id);
        if (bl.size() <= 0) break;

        nsresult rv;
        nsCOMPtr<nsIUrlAtt> tmp = do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1", &rv);
        if (NS_FAILED(rv)) {
            ERROR << "Get nsIUrlAtt Error:" << rv << "\n";
            break;
        }
        nsCString link(bl.GetUrl().c_str());
        tmp->SetLink(link);
        PRUint32 uid = 0;
        cdb_handle->GetURLID(link,&uid);
        tmp->SetId(uid);

        url_att = tmp;
//        LOG<<"tmp"<<tmp<<endl;

        BlockCluster * bc = NULL;
//        find_sim_cluster(bl, &bc);
//        if(bc != NULL)
//            LOG << "uid: " << url_id << " con_type: " << bc->GetName() << endl;

        int type = wrapping(bl, bc);

        LOG << "Analysis exit..\n";
    }



//    url_att = NULL;

    return NS_OK;
}

void nsDOMTest::load_document(BlockList & bl, int * uid) {
    nsCString page;
    if (cdb_handle != nsnull)
        cdb_handle->GetPage(uid, page);

    if (*uid > 0) {
        stringstream ss;
        ss.str(page.get());

        bl.deserialize(ss);
    }
}

void nsDOMTest::LoadDBConfig(const nsACString & location) {
    mLocation = nsCString(location);
    LOG << "[nsDOMTest] target database: " << mLocation.get() << "\n";

    if (cdb_handle != NULL)
        cdb_handle->SetLocation(mLocation);

    if (idx_handle != NULL)
        idx_handle->SetLocation(mLocation);
}

int nsDOMTest::analyze_page_type(BlockList & bl) {
    //计算连接/文本比
    float anchor_density = bl.anchor_density();
    LOG << "cluster anchor density " << anchor_density << "\n";
    if (anchor_density >= LINK_BLOCK_THRESHOLD) {
        return LINK_BLOCK;
    } else if (anchor_density >= 0.0) {
        float w = bl.GetText().length();
        w = w * (1 - anchor_density);
        if (w > MIN_CONTENT_LENGTH) {
            return CONTENT_BLOCK;
        }
        LOG << "content length too small: " << w << "\n";
    }
    LOG << "invalid_block:无法判定为链接块和内容块" << "\n";
    return INVALID_BLOCK;
}

void nsDOMTest::serialize() {
    if (wrapper_name.compare("") == 0) return;
    ofstream os(wrapper_name.c_str(), ios::binary | ios::trunc);
    stringstream ss;
    //int size = clusters.size();
    //ss << size << "\n";
    //map<int, list<BlockCluster> >::iterator it;
    //for(it = clusters.begin(); it != clusters.end(); it++)
    {
        //int type = it->first;
        //ss << type << "\n";
        //list<BlockCluster> & lst = it->second;
        list<BlockCluster> & lst = clusters;
        int len = lst.size();
        ss << len << "\n";
        list<BlockCluster>::iterator it_bc;
        for (it_bc = lst.begin(); it_bc != lst.end(); it_bc++)
            it_bc->serialize(ss);
    }
    os << ss.str();
    os.close();
}

void nsDOMTest::deserialize() {
    if (wrapper_name.compare("") == 0) return;
    ifstream is(wrapper_name.c_str(), ios::binary);
    is.seekg(0, ios::end);
    int length = is.tellg();
    if (length < 1) return;
    is.seekg(0, ios::beg);
    // allocate memory:
    char * buffer = new char [length];

    // read data as a block:
    is.read(buffer, length);
    is.close();

    stringstream ss;
    ss.write(buffer, length);
    delete[] buffer;

    int size = 0;
    {
        int len = 0;
        len = get_integer(ss);
        LOG << "there are " << len << " BlockCluster" << "\n";
        list<BlockCluster> & lst = clusters;
        for (int j = 0; j < len; j++) {
            BlockCluster bc;
            bc.deserialize(ss);
            lst.push_back(bc);
        }
    }
}

void nsDOMTest::load_wrap_rules_from_db(int type, BlockCluster & bc) {
    if (cdb_handle == NULL) return;

    nsCString rules;
    cdb_handle->LoadWrapRules(type, rules);
    string r(rules.get());
    if (r.compare("") != 0)
        load_wrap_rules(r, bc);
}

void nsDOMTest::load_wrap_rules(string & rules, BlockCluster & bc) {
    stringstream ss;
    ss << rules;
    string line = get_line(ss);
    while (line.compare("") != 0) {
        string sp(RULE_SEPARATOR);
        size_t f = line.find(sp);
        if (f != string::npos) {
            string k = line.substr(0, f);
            string v = line.substr(f + sp.size());
            //LOG << "key: " << k << " value: " << v << "\n";
            bc.SetRule(k, v);
        }
        line = get_line(ss);
    }
}

void nsDOMTest::load_wrap_rules() {
    PRInt32 size;
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        BlockCluster & bc = *it;
        load_wrap_rules_from_db(bc.GetName(), bc);
    }
}

void nsDOMTest::load_cluster() {
    if (cdb_handle == NULL) return;

    int num = get_num_of_cluster();
    PRUint32 *ids = new PRUint32[num + 1];
    PRUint32 count = 0;

    cdb_handle->GetClusterID(&ids, &count);
    for (int i = 0; i < count; i++) {
        LOG << "load cluster " << ids[i] << endl;
        //Create BlockCluster
        BlockCluster bc(ids[i]);
        //Load Cluster type from database
        PRUint32 type = INVALID_BLOCK;
        cdb_handle->GetClusterType(ids[i],&type);
        LOG<<"Cluster "<<ids[i]<<" type :"<<type<<endl;
        bc.SetType(type);

        //Load BlockList from database
        list<BlockList> & blocks = bc.GetAllBlocks();

        nsCStringArray array;
        PRUint32 page_count = 0;
        cdb_handle->GetPageByConType(ids[i], 5, &array, &page_count);
        for (int j = 0; j < page_count; j++) {
            nsCString * page = array.CStringAt(j);
            if (page != NULL) {
                BlockList bl;
                stringstream ss;
                ss << page->get();
                bl.deserialize(ss);

                list<BlockList>::iterator it_bl;
                bool insert = true;
                for (it_bl = blocks.begin(); it_bl != blocks.end(); it_bl++) {
                    if (bl.GetUrl().compare(it_bl->GetUrl()) == 0)
                        insert = false;
                }
                if (insert) blocks.push_back(bl);
            }
        }

        clusters.push_back(bc);
    }
}

void nsDOMTest::find_sim_cluster(BlockList & bl, BlockCluster ** bc) {
    list<BlockCluster> & bc_set = clusters;
    list<BlockCluster>::iterator it = bc_set.begin();
    if (bc_set.size() > 0) {
        bool found_cluster = false;
        float sim = 0.0;
        float max_sim = 0.0;
        list<BlockCluster>::iterator it_bc = it;
        //int allowed_cluster_type = 7;
        for (it = bc_set.begin(); it != bc_set.end(); it++) {
            //int type = it->GetType();
            //if(type & allowed_cluster_type)
            {
                if(it->GetType() == INVALID_BLOCK) continue;
                sim = it->IsSimilar(bl);
                LOG << "sim " << it->GetName() <<" : "<< sim << endl;
                if (sim > WRAP_SIMILAR_THRESHOLD && sim > max_sim) {
                    it_bc = it;
                    max_sim = sim;
                    found_cluster = true;
                    if (sim >= 0.97)
                        break;
                }
            }
        }
        if (!found_cluster) {
            LOG << "there is not similar cluster, maybe you need retrain this wrapper." << endl;
        } else {
            *bc = &(*it_bc);
            return;
        }
    } else {
        LOG << "There is not any clusters.. please check run mode or training wrapper first" << endl;
    }

    return;
}

void nsDOMTest::write_con_type_into_db(int uid, int type) {
    cdb_handle->SetConType(uid, type);
}

int nsDOMTest::get_num_of_cluster() {
    PRInt32 num = 0;
    if (cdb_handle != NULL)
        cdb_handle->GetNumberOfCluster(&num);
    return num;
}

void splite_rule(string & mn, set<string> & collection)
{
    //LOG<<"mn:"<<mn<<endl;
    string sep(RULE_LINE_SEPARATOR);
    int off = sep.length();
    size_t sp = 0;
    size_t ep = sp;
    ep = mn.find(sep,sp);
    while(ep != string::npos){
        string sub = mn.substr(sp,ep-sp);
        //LOG<<sub<<endl;
        collection.insert(sub);
        sp = ep+off;
        ep = mn.find(sep,sp);
    }
}

void nsDOMTest::collect_wrapper_rules() {
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        BlockCluster & bc = *it;
        if (bc.GetType() != CONTENT_BLOCK) continue;

        list<BlockNode> & m_node = bc.GetMainNode();
        list<BlockNode>::iterator it_bn;
        for (it_bn = m_node.begin(); it_bn != m_node.end(); it_bn++) {
            this->main_node.insert(it_bn->GetPath());
        }

        map<string, string> & rules = bc.GetRule();
        map<string, string>::iterator it_rule;
        for (it_rule = rules.begin(); it_rule != rules.end(); it_rule++) {
            string k = it_rule->first;
            string v = it_rule->second;
            //LOG << k << " : " << v << "\n";
            if (k.compare("title") == 0) {
                this->title_node.insert(v);
            } else if (k.compare("date") == 0) {
                this->date_node.insert(v);
            } else if (k.compare("a&s") == 0) {
                this->author_source_node.insert(v);
                author_node.erase(v);
                source_node.erase(v);
            } else if (k.compare("author") == 0) {
                this->author_node.insert(v);
            } else if (k.compare("source") == 0) {
                this->source_node.insert(v);
            } else if (k.compare("mn") == 0) {
                splite_rule(v,main_node);
                //this->main_node.insert(v);
            } else if (k.compare("ad") == 0) {
                splite_rule(v,ad_node);
            }
             
        }

        set<string>::iterator it_mn;
        for(it_mn = main_node.begin(); it_mn != main_node.end(); it_mn++){
            string mn = *it_mn;
            ad_node.erase(mn);
        }
    }
}

nsCString nsDOMTest::wrap_title(BlockList & bl) {
    LOG << "Wrap title" << "\n";
    nsCString title;
    set<string>::iterator it;
    list<string> t_set;
    for (it = title_node.begin(); it != title_node.end(); it++) {
        string path = *it;
        string str = bl.GetPathText(path);
        LOG << str << "\n";
        if (str.compare("") != 0)
            t_set.push_back(str);
    }

    if (t_set.size() >= 1) {
        title.Append(t_set.begin()->c_str());
    }

    return title;
}

nsCString nsDOMTest::wrap_author(BlockList & bl) {
    LOG << "Wrap author begin\n";
    nsCString author;
    set<string>::iterator it;
    list<string> t_set;
    for (it = author_source_node.begin(); it != author_source_node.end(); it++) {
        string path = *it;
//        LOG << "path:" << path;
        string str = tool_wrap_author(bl, path);
//        LOG << " text:" << str << "\n";
        if (str.compare("") != 0)
            t_set.push_back(str);
    }

    if (t_set.size() >= 1) {
        author.Append(t_set.begin()->c_str());
    } else {
        for (it = author_node.begin(); it != author_node.end(); it++) {
            string path = *it;
//            LOG << "path:" << path;
            string str = tool_wrap_author(bl, path);
//            LOG << " text:" << str << "\n";
            if (str.compare("") != 0)
                t_set.push_back(str);
        }

        if (t_set.size() >= 1) {
            author.Append(t_set.begin()->c_str());
        }
    }
    LOG << "Wrap author end\n";
    return author;
}

nsCString nsDOMTest::wrap_source(BlockList & bl) {
    LOG << "Wrap source" << "\n";
    nsCString source;
    set<string>::iterator it;
    list<string> t_set;
    for (it = author_source_node.begin(); it != author_source_node.end(); it++) {
        string path = *it;
        string str = tool_wrap_source(bl, path);
        if (str.compare("") != 0)
            t_set.push_back(str);
    }

    if (t_set.size() >= 1) {
        source.Append(t_set.begin()->c_str());
    } else {
        for (it = source_node.begin(); it != source_node.end(); it++) {
            string path = *it;
            string str = tool_wrap_source(bl, path);
            if (str.compare("") != 0)
                t_set.push_back(str);
        }

        if (t_set.size() >= 1) {
            source.Append(t_set.begin()->c_str());
        }
    }
    return source;
}

nsCString nsDOMTest::wrap_date(BlockList & bl, string & date_format) {
    LOG << "Wrap date" << "\n";
    nsCString date;
    set<string>::iterator it;
    list<string> t_set;
    for (it = date_node.begin(); it != date_node.end(); it++) {
        string path = *it;
        string d = bl.GetPathText(path);
        string str;
        if (d.compare("") != 0)
            str = get_date(d, date_format);
        //LOG << d << " : " << str << "\n";
        if (str.compare("") != 0)
            t_set.push_back(str);
    }

    if (t_set.size() >= 1) {
        date.Append(t_set.begin()->c_str());
    }

    return date;
}

nsCString nsDOMTest::wrap_content(BlockList & bl, BlockCluster * bc) {
    LOG << "Wrap content\n";
    nsCString content;

//    get_content(doc, content, main_node);
//    if(bc != NULL)
//        content = nsCString(bc->wrap_content(bl).c_str());
        content = nsCString(tool_wrap_content2(bl,ad_node).c_str());
    return content;
}

int nsDOMTest::wrapping(BlockList & bl, BlockCluster * bc) {
    int page_type = INVALID_BLOCK;
    int con_type = 0;
    if (bc == NULL) {
        LOG<<"Can not find similar cluster, analysis page type\n";
        page_type = analyze_page_type(bl);
    } else {
        page_type = bc->GetType();
        con_type = bc->GetName();
    }

    if (page_type != INVALID_BLOCK) {
        if (page_type == CONTENT_BLOCK) {
            LOG << "This is a content page" << endl;
            wrap_content_page2(bl,bc);
//            wrap_nextpage(page_type);

        } else {
            LOG << "This is a link page" << endl;
        }
    } else {
        LOG << "This is an invalid page" << endl;
    }

    return con_type;
}

void nsDOMTest::wrap_content_page2(BlockList & bl, BlockCluster * bc) {
    LOG << "extract content\n";
    nsCString title;
    nsCString content;
    nsCString date;
    nsCString author;
    nsCString source;

    if (idx_handle == NULL) return;

    {
        title = wrap_title(bl);
        content = wrap_content(bl,bc);
    }
    if (title.Length() == 0) title = nsCString(bl.GetTitle().c_str());

    string format("YYYY-MM-DD HH:mm:SS");
    date = wrap_date(bl, format);

    author = wrap_author(bl);
    source = wrap_source(bl);

    string con(content.get());
    if (author.Length() == 0) author = nsCString(find_author(con).c_str());
    if (source.Length() == 0) source = nsCString(find_source(con).c_str());

    nsresult rv;
    nsCOMPtr<nsIIndexDoc> idx = do_CreateInstance("@nyapc.com/XPCOM/nsIndexDoc;1", &rv);
    if (!NS_FAILED(rv)) {

        idx->SetUrl(url_att);
        idx->SetTitle(nsCString(title));
//        LOG<<"title:"<<title.get()<<endl;
        idx->SetPublishDate(nsCString(date));
//        LOG<<"date:"<<date.get()<<endl;
        idx->SetSource(nsCString(source));
//        LOG<<"source:"<<source.get()<<endl;
        idx->SetAuthor(nsCString(author));
//        LOG<<"author:"<<author.get()<<endl;
        idx->SetContent(nsCString(content));
//        LOG<<"content:"<<content.get()<<endl;
        LOG << "save idx\n";
        idx_handle->SaveIDX(idx);
        LOG << "save idx ok.\n";
    }
}