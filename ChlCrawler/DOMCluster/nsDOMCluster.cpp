#include "nsDOMCluster.h"
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
#include <unistd.h>

#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSHTMLElement.h"
#include "nsIDOMElement.h"
#include "nsIDOMNodeList.h"

NS_IMPL_ISUPPORTS1(nsDOMCluster, nsIDOMCluster)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDOMCluster)

static nsModuleComponentInfo components[] ={
    {
        NS_DOMCLUSTER_CLASSNAME,
        NS_DOMCLUSTER_CID,
        NS_DOMCLUSTER_CONTRACTID,
        nsDOMClusterConstructor,
    }
};

NS_IMPL_NSGETMODULE("nsDOMClusterModule", components)

nsDOMCluster::nsDOMCluster() {
    nsresult rv;
    cdb_handle = do_CreateInstance("@nyapc.com/XPCOM/nsClusterDBHandle;1", &rv);
    if (NS_FAILED(rv)) {
        ERROR << "Get  mozIStorageService  Error:" << rv << "\n";
        cdb_handle = NULL;
    }

    url_att = NULL;
    //LOG<<"init object ok\n";
}

nsDOMCluster::~nsDOMCluster() {
}

NS_IMETHODIMP nsDOMCluster::Analysis(const nsACString & location) {
    LOG << "          startup... " << nsCString(location).get() << "\n";

    LoadDBConfig(location);

    while (true) {
        BlockList bl;
        int url_id;
        load_document(bl, &url_id);
        if (bl.size() <= 0) break;

        int con_type = atom_cluster(bl, clusters);
        LOG << "uid:" << url_id << "con_type:" << con_type << endl;
        write_con_type_into_db(url_id, con_type);
        save_wrap(con_type);
    }



    url_att = NULL;

    return NS_OK;
}

void nsDOMCluster::load_document(BlockList & bl, int * uid) {
    nsCString page;
    if (cdb_handle != nsnull)
        cdb_handle->GetPage(uid, page);

    if (*uid > 0) {
        stringstream ss;
        ss.str(page.get());

        bl.deserialize(ss);
    }
}

void nsDOMCluster::LoadDBConfig(const nsACString & location) {
    mLocation = nsCString(location);
    LOG << "[nsDOMCluster] target database: " << mLocation.get() << "\n";

    if (cdb_handle != NULL)
        cdb_handle->SetLocation(mLocation);

    nsresult rv;
    nsCOMPtr<nsIPersistentProperties>property=do_CreateInstance("@mozilla.org/persistent-properties;1", &rv);
    if (NS_FAILED(rv))
    {
        std::cout<<"Get property Error:"<<rv<<std::endl;
    }

    size_t l = 200;
    char workspace[l];
    char * w = NULL;
#if (OS == LINUX_SUSE)
    w = getcwd(workspace,l);
#endif
    LOG<<"Current Work Directory"<<workspace<<"\n";
    if(w != NULL) {
        nsCString fileName(workspace);
        fileName.Append("/Crawler.ini");
        nsCOMPtr<nsILocalFile> file;
        rv = NS_NewLocalFile(NS_ConvertUTF8toUTF16(fileName), PR_FALSE,
                getter_AddRefs(file));
        if (NS_FAILED(rv))
            return;
        nsCOMPtr<nsIInputStream> fistream;
        rv = NS_NewLocalFileInputStream(getter_AddRefs(fistream), file);
        if (NS_FAILED(rv)) {
            return;
        }
        property->Load(fistream);

        nsString n;
        property->GetStringProperty(STOP_TAG, n);
        this->StopTag = string(NS_ConvertUTF16toUTF8(n).get());
        LOG << "STOP_TAG: " << StopTag << "\n";
    }
}

int nsDOMCluster::atom_cluster(BlockList & bn, list<BlockCluster> & bc_set) {
    list<BlockCluster>::iterator it = bc_set.begin();
    if (bc_set.size() > 0) {
        bool found_cluster = false;
        float sim = 0.0;
        float max_sim = 0.0;
        list<BlockCluster>::iterator it_bc = it;
        for (; it != bc_set.end(); it++) {
            sim = it->IsSimilar(bn);
            LOG << "sim "<<it->GetName()<<" : " << sim << "\n";
            if (sim > SIMILAR_THRESHOLD && sim > max_sim) {
                //it->insert(bn);
                it_bc = it;
                max_sim = sim;
                found_cluster = true;
                break;
            }
        }
        if (!found_cluster) {
            LOG << "create new cluster" << "\n";
            BlockCluster bc(get_new_cluster_id());
            bc.insert(bn);
            bc_set.push_front(bc);
            return bc.GetName();
        } else {
            it_bc->insert(bn);
            LOG << "found a same cluster" << "\n";
            return it_bc->GetName();
        }
    } else {
        LOG << "create 1st cluster" << "\n";
        BlockCluster bc(get_new_cluster_id());
        bc.insert(bn);
        bc_set.push_front(bc);
        return bc.GetName();
    }
}

void nsDOMCluster::serialize() {
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

void nsDOMCluster::deserialize() {
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

void nsDOMCluster::save_wrap(int con_type) {
    if (cdb_handle == NULL) return;

    cdb_handle->UpdateClusterType(con_type, 0);
}

void nsDOMCluster::load_wrap_rules_from_db(int type, BlockCluster & bc) {
    if (cdb_handle == NULL) return;

    nsCString rules;
    cdb_handle->LoadWrapRules(type, rules);
    string r(rules.get());
    if (r.compare("") != 0)
        load_wrap_rules(r, bc);
}

void nsDOMCluster::load_wrap_rules(string & rules, BlockCluster & bc) {
    stringstream ss;
    ss << rules;
    string line = get_line(ss);
    while (line.compare("") != 0) {
        string sp(RULE_SEPARATOR);
        size_t f = line.find(sp);
        if (f != string::npos) {
            string k = line.substr(0, f);
            string v = line.substr(f + sp.size());
            LOG << "key: " << k << " value: " << v << "\n";
            bc.SetRule(k, v);
        }
        line = get_line(ss);
    }
}

void nsDOMCluster::load_wrap_rules() {
    PRInt32 size;
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        BlockCluster & bc = *it;
        load_wrap_rules_from_db(bc.GetName(), bc);
    }
}

void nsDOMCluster::write_con_type_into_db(int uid, int type) {
    cdb_handle->SetConType(uid, type);
}

int nsDOMCluster::get_new_cluster_id() {
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
