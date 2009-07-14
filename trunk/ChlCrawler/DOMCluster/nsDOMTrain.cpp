
#include <string>

#include "nsDOMTrain.h"
#include "BlockUtils.h"
#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsStringAPI.h"
#include "nsILocalFile.h"
#include "nsIFileStreams.h"
#include "nsNetUtil.h"
#include "nsILineInputStream.h"
#include <iostream>
#include <sstream>
#include <math.h>

#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMElement.h"
#include "nsIDOMNodeList.h"
#include "nsVoidArray.h"

NS_IMPL_ISUPPORTS1(nsDOMTrain, nsIDOMCluster)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDOMTrain)

static nsModuleComponentInfo components[] ={
    {
        NS_DOMTRAIN_CLASSNAME,
        NS_DOMTRAIN_CID,
        NS_DOMTRAIN_CONTRACTID,
        nsDOMTrainConstructor,
    }
};

NS_IMPL_NSGETMODULE("nsDOMTrainModule", components)

nsDOMTrain::nsDOMTrain() {
    nsresult rv;
    cdb_handle = do_CreateInstance("@nyapc.com/XPCOM/nsClusterDBHandle;1", &rv);
    if (NS_FAILED(rv)) {
        ERROR << "Get  mozIStorageService  Error:" << rv << "\n";
        cdb_handle = NULL;
    }

    url_att = NULL;
    //LOG<<"init object ok\n";
}

nsDOMTrain::~nsDOMTrain() {
}

NS_IMETHODIMP nsDOMTrain::Analysis(const nsACString & location) {
    LOG << "          start training... " << nsCString(location).get() << "\n";

    LoadDBConfig(location);

    load_cluster();
    load_wrap_rules();

    analyze_clusters(clusters);

    save_wrapper();
    /*
            while(true)
            {
                    BlockList bl;
                    int url_id;
                    load_document(bl,&url_id);
                    if(bl.size()<=0) break;

                    int con_type = atom_cluster(bl,clusters);
                    LOG<<"uid:"<<url_id<<"con_type:"<<con_type<<endl;
                    write_con_type_into_db(url_id, con_type);
                    //save_wrap(con_type);
            }
     */


    url_att = NULL;

    return NS_OK;
}

void nsDOMTrain::load_document(BlockList & bl, int * uid) {
    nsCString page;
    if (cdb_handle != nsnull)
        cdb_handle->GetPage(uid, page);

    if (*uid > 0) {
        stringstream ss;
        ss.str(page.get());

        bl.deserialize(ss);
    }
}

void nsDOMTrain::load_cluster() {
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
        bc.SetType(type);

        //Load BlockList from database
        list<BlockList> & blocks = bc.GetAllBlocks();

        nsCStringArray array;
        PRUint32 page_count = 0;
        cdb_handle->GetPageByConType(ids[i], 20, &array, &page_count);
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

void nsDOMTrain::LoadDBConfig(const nsACString & location) {
    mLocation = nsCString(location);
    LOG << "target database: " << mLocation.get() << "\n";

    if (cdb_handle != NULL)
        cdb_handle->SetLocation(mLocation);
}

void nsDOMTrain::analyze_clusters(list<BlockCluster> & bc_set) {
    list<BlockCluster>::iterator it;
    if (bc_set.size() > 0) {
        for (it = bc_set.begin(); it != bc_set.end(); it++) {
            BlockCluster & bc = *it;

            {
                LOG << "analyzing cluster " << "\n";
                bc.analyze_common();
                bc.analyze_main_section();
                analyze_cluster_type(bc);

                int type = bc.GetType();
                if (type == LINK_BLOCK) {
                    LOG << "cluster type:链接页" << "\n";
                    //bc.analyze_links();
                } else if (type == CONTENT_BLOCK) {
                    LOG << "cluster type:内容页" << "\n";
                    bc.analyze_title();
                    bc.statistic_node_occ();
                    bc.analyze_date_author_source();
                } else {
                    LOG << "cluster is invalid..." << "\n";
                }

                bc.training_completed();
            }
        }
    }
}

void nsDOMTrain::analyze_cluster_type(BlockCluster & bc) {
    //计算连接/文本比
    float anchor_density = bc.anchor_density();
    LOG << "cluster anchor density " << anchor_density << "\n";
    if (anchor_density >= LINK_BLOCK_THRESHOLD) {
        if (bc.GetType() != CHANNEL_BLOCK)
            bc.SetType(LINK_BLOCK);
    } else if (anchor_density >= 0.0) {
        float w = bc.avrg_text_length();
        w = w * (1 - anchor_density);
        //LOG << "content length "<<w<<"\n";
        if (w > MIN_CONTENT_LENGTH) {
            bc.SetType(CONTENT_BLOCK);
        }
    } else {
        LOG << "invalid_block:无法判定为链接块和内容块" << "\n";
    }
}

void nsDOMTrain::serialize() {
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

void nsDOMTrain::deserialize() {
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

void nsDOMTrain::save_wrapper() {
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        BlockCluster & bc = *it;
        string rule = bc.GetRuleString();
        save_wrap_rules(bc.GetName(),bc.GetType(),rule);
    }
}

void nsDOMTrain::save_wrap_rules(int con_type, int con_att, string & rules) {
    if (cdb_handle == NULL) return;

    nsCString r(rules.c_str());
    cdb_handle->SaveWrapRules(con_type, con_att, r);
}

void nsDOMTrain::load_wrap_rules_from_db(int type, BlockCluster & bc) {
    if (cdb_handle == NULL) return;

    nsCString rules;
    cdb_handle->LoadWrapRules(type, rules);
    string r(rules.get());
    if (r.compare("") != 0)
        load_wrap_rules(r, bc);
}

void nsDOMTrain::load_wrap_rules(string & rules, BlockCluster & bc) {
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
            bc.SetRule(k,v);
        }
        line = get_line(ss);
    }
}

void nsDOMTrain::load_wrap_rules() {
    PRInt32 size;
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        BlockCluster & bc = *it;
        load_wrap_rules_from_db(bc.GetName(), bc);
    }
}

void nsDOMTrain::write_con_type_into_db(int uid, int type) {
    cdb_handle->SetConType(uid, type);
}

int nsDOMTrain::get_new_cluster_id() {
    int nid = 0;
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        int id = it->GetName();
        if (id >= nid) {
            nid = id;
        }
    }
    nid++;
    return nid;
}

int nsDOMTrain::get_num_of_cluster() {
    PRInt32 num = 0;
    if (cdb_handle != NULL)
        cdb_handle->GetNumberOfCluster(&num);
    return num;
}
