#include "nsDOMWrapper.h"
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
#include "nsIDOMHTMLLinkElement.h"
#include "nsIDOMHTMLAnchorElement.h"
#include "nsIDOMHTMLCollection.h"
#include "nsIDOM3Node.h"
#include "nsVoidArray.h"
//#include "nsEscape.h"

NS_IMPL_ISUPPORTS1(nsDOMWrapper, nsIDOMAnalysis)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDOMWrapper)

static nsModuleComponentInfo components[] ={
    {
        NS_DOMWRAPPER_CLASSNAME,
        NS_DOMWRAPPER_CID,
        NS_DOMWRAPPER_CONTRACTID,
        nsDOMWrapperConstructor,
    }
};

NS_IMPL_NSGETMODULE("nsDOMWrapperModule", components)

nsDOMWrapper::nsDOMWrapper() {
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

    col_handle = do_CreateInstance("@nyapc.com/XPCOM/nsColDBIO;1", &rv);
    if (NS_FAILED(rv)) {
        ERROR << "Get nsColDBIo Error:" << rv << "\n";
        col_handle = NULL;
    }

    bridge = do_CreateInstance("@nyapc.com/XPCOM/nsColBridge;1", &rv);
    if (NS_FAILED(rv))
    {
        LOG<<"Get  nsIColBridge  Error:"<<rv<<"\n";
        bridge = NULL;
    }

    

    url_att = NULL;
    doc = NULL;
    creator = NULL;

    allowed_type = 5;
}

nsDOMWrapper::~nsDOMWrapper() {
}

NS_IMETHODIMP nsDOMWrapper::Analysis(nsIDOMDocument *document, PRUint32 *_retval) {
    LOG << "          startup... " << "\n";
    int type = 0;
    doc = document;
    nsCOMPtr<nsIDOMHTMLDocument> html = do_QueryInterface(doc);
    nsString t, u;
    html->GetTitle(t);
    html->GetURL(u);
    TITLE = string(NS_ConvertUTF16toUTF8(t).get());
    URL = string(NS_ConvertUTF16toUTF8(u).get());

    LOG << "title: " << TITLE << " url: " << URL << "\n";

    bool b = this->is_valid_url(URL);
    if(b){
        list<BlockCluster> & c_lst = clusters;
        BlockList bl;
        convert_html_to_bl(html, bl);
        bl.SetTitle(TITLE);
        bl.SetUrl(URL);
        LOG << "convert ok" << "\n";

        BlockCluster * bc = NULL;
        //find_sim_cluster(bl, &bc);
        type = wrapping(bl, bc);
    }

    url_att = NULL;
    doc = NULL;
    LOG << "Analysis exit..\n";
    *_retval = type;
}

NS_IMETHODIMP nsDOMWrapper::SetCurUrl(nsIUrlAtt *url_attr) {
    url_att = url_attr;
    return NS_OK;
}

NS_IMETHODIMP nsDOMWrapper::SaveWrapper() {
    //LOG<<"saving wrapper"<<"\n";
    //serialize();
    //save_wrap_rules();
    return NS_OK;
}

NS_IMETHODIMP nsDOMWrapper::SetProperty(nsIPersistentProperties *p) {
    this->property = p;
    return NS_OK;
}

NS_IMETHODIMP nsDOMWrapper::SetIdxCreator(nsIIDXCreator * creator) {
    this->creator = creator;
    return NS_OK;
}

void nsDOMWrapper::parse_colunmn_map(nsCString & c_map){
    string column(c_map.get());
    string sep1(";");
    int off = sep1.length();
    size_t sp = 0;
    size_t ep = sp;
    ep = column.find(sep1,sp);
    while(ep != string::npos){
        string line = column.substr(sp,ep-sp);
        LOG<<line<<endl;

        string sep2(RULE_SEPARATOR);
        size_t f = line.find(sep2);
        if (f != string::npos) {
            string k = line.substr(0, f);
            string v = line.substr(f + sep2.size());
            LOG << "key: " << k << " map to: " << v << "\n";
            this->column_map.insert(
                    pair<nsCString,nsCString>(nsCString(k.c_str()),nsCString(v.c_str())));
        }

        sp = ep+off;
        ep = column.find(sep1,sp);
    }
}

NS_IMETHODIMP nsDOMWrapper::LoadConfig() {
    if (property != NULL) {
        //allowed cluster type for wrapper loading
        nsString c;
        property->GetStringProperty(ALLOWED_CLUSTER_TYPE, c);
        allowed_type = atoi(NS_ConvertUTF16toUTF8(c).get());
        LOG << "allowed cluster type:" << allowed_type << "\n";

        //Wrapper name
        nsString n;
        property->GetStringProperty(WRAPPER_NAME, n);
        //nsCString name(NS_ConvertUTF16toUTF8(n).get());
        wrapper_name = string(NS_ConvertUTF16toUTF8(n).get());
        LOG << "wrapper name: " << wrapper_name << "\n";
        //deserialize();

        //IndexURL
        n.Cut(0,n.Length());
        property->GetStringProperty(INDEX_URL, n);
        this->index_addr = NS_ConvertUTF16toUTF8(n);
        n.Cut(0,n.Length());
        property->GetStringProperty(MARK_SOURCEINFO, n);
        this->sourceinfo = NS_ConvertUTF16toUTF8(n);
        n.Cut(0,n.Length());
        property->GetStringProperty(MARK_SITEDOMAIN, n);
        this->sitedomain = NS_ConvertUTF16toUTF8(n);

        //Column Map
        n.Cut(0,n.Length());
        property->GetStringProperty(MARK_COLUMNMAP, n);
        nsCString c_map(NS_ConvertUTF16toUTF8(n).get());
        this->parse_colunmn_map(c_map);

        //MustHave
        n.Cut(0,n.Length());
        property->GetStringProperty(MUST_HAVE_CSV, n);
        this->MustHaveCSV = string(NS_ConvertUTF16toUTF8(n).get());
        n.Cut(0,n.Length());
        property->GetStringProperty(DONT_MUST_HAVE_CSV, n);
        this->DontMustHaveCSV = string(NS_ConvertUTF16toUTF8(n).get());
        LOG << "DontMustHaveCSV: " << DontMustHaveCSV << "\n";
        //StopTag
        n.Cut(0,n.Length());
        property->GetStringProperty(STOP_TAG, n);
        this->StopTag = string(NS_ConvertUTF16toUTF8(n).get());
        LOG << "STOP_TAG: " << StopTag << "\n";
        n.Cut(0,n.Length());
        property->GetStringProperty(START_TAG, n);
        this->StartTag = string(NS_ConvertUTF16toUTF8(n).get());
        LOG << "START_TAG: " << StartTag << "\n";

        n.Cut(0,n.Length());
        property->GetStringProperty(URL_SOURCE, n);
        mLocation = NS_ConvertUTF16toUTF8(n);
        LOG << "target database: " << mLocation.get() << "\n";

        if (cdb_handle != NULL)
            cdb_handle->SetLocation(mLocation);
        if (idx_handle != NULL)
            idx_handle->SetLocation(mLocation);
        if (col_handle != NULL)
            col_handle->SetLocation(mLocation);

        if(bridge != NULL){
            n.Cut(0,n.Length());
            property->GetStringProperty(COL_BRIDGE_SOURCE, n);
            nsCString tmpSrc = NS_ConvertUTF16toUTF8(n);
            nsCString tmpComN("@nyapc.com/XPCOM/nsUrlDBIO;1");
            bridge->SetUrlSource(tmpSrc,tmpComN);
            tmpComN=nsCString("@nyapc.com/XPCOM/nsColDBIO;1");
            bridge->SetColSource(tmpSrc,tmpComN);
        }

        load_cluster();
        load_wrap_rules();
        collect_wrapper_rules();
    }
    return NS_OK;
}

/* void GetClusterAttr (in PRUint32 cid, out PRUint32 attr); */
NS_IMETHODIMP nsDOMWrapper::GetClusterAttr(PRUint32 cid, PRUint32 *attr) {
    *attr = 0;
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        int id = it->GetName();
        if (id == cid) {
            *attr = it->GetType();
        }
    }

    return NS_OK;
}

/* void SetClusterType (in PRUint32 type); */
NS_IMETHODIMP nsDOMWrapper::SetClusterType(PRUint32 cid, PRUint32 type) {
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        int id = it->GetName();
        if (id == cid) {
            it->SetType(type);
        }
    }

    return NS_OK;
}

void nsDOMWrapper::find_sim_cluster(BlockList & bl, BlockCluster ** bc) {
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

int nsDOMWrapper::analyze_page_type(BlockList & bl) {
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

void nsDOMWrapper::wrap_content_page(BlockList & bl, BlockCluster * bc) {
    nsCString title;
    nsCString content;
    nsCString date;
    nsCString author;
    nsCString source;

    if (bc == NULL || idx_handle == NULL) return;

    if (bc->GetType() == CONTENT_BLOCK) {
        title = nsCString(bc->wrap_title(bl).c_str());
        content = nsCString(bc->wrap_content(bl).c_str());
    }
    if (title.Length() == 0) title = nsCString(bl.GetTitle().c_str());

    string format("YYYY-MM-DD HH:mm:SS");
    date = nsCString(bc->wrap_date(bl, format).c_str());

    author = nsCString(bc->wrap_author(bl).c_str());
    source = nsCString(bc->wrap_source(bl).c_str());

    string con(content.get());
    if (author.Length() == 0) author = nsCString(find_author(con).c_str());
    if (source.Length() == 0) source = nsCString(find_source(con).c_str());

    /*
    creator->SetTitle(nsCString(title.c_str()));
    creator->SetDate(nsCString(date.c_str()));
    LOG<<"insert author "<<author<<endl;
    if(author.compare("")!=0) creator->SetField(nsCString("AUTHOR"),nsCString(author.c_str()));
    LOG<<"insert source "<<source<<endl;
    if(source.compare("")!=0) creator->SetField(nsCString("SOURCENAME"),nsCString(source.c_str()));
    creator->SetReference(nsCString(ref.c_str()));
    creator->SetContent(nsCString(content.c_str()));
    nsCString idx;
    creator->GetIDX(idx);
    LOG << "IDX:\n" << idx.get() << endl;
     */
    nsresult rv;
    nsCOMPtr<nsIIndexDoc> idx = do_CreateInstance("@nyapc.com/XPCOM/nsIndexDoc;1", &rv);
    if (!NS_FAILED(rv)) {
        idx->SetUrl(url_att);
        idx->SetTitle(nsCString(title));
        idx->SetPublishDate(nsCString(date));
        idx->SetSource(nsCString(source));
        idx->SetAuthor(nsCString(author));
        idx->SetContent(nsCString(content));

        idx_handle->SaveIDX(idx);
    }
}

void nsDOMWrapper::wrap_content_page2(BlockList & bl) {
    LOG << "extract content\n";
    nsCString title;
    nsCString content;
    nsCString date;
    nsCString author;
    nsCString source;

    if (idx_handle == NULL) return;
    
    {
//        title = wrap_title(bl);
        content = wrap_content();
    }
    if (title.Length() == 0 && url_att != NULL) url_att->GetTitle(title);
    if (title.Length() == 0) title = nsCString(bl.GetTitle().c_str());

    string format("YYYY-MM-DD HH:mm:SS");
    date = wrap_date(bl, format);

    author = wrap_author(bl);
    source = wrap_source(bl);

    LOG<<"wrap author and source ok\n";

    string con(content.get());
    if (author.Length() == 0) author = nsCString(find_author(con).c_str());
    if (source.Length() == 0) source = nsCString(find_source(con).c_str());

    nsresult rv;
    nsCString col_name, col_alias, col_url, chl, rchl, url;
    url_att->GetLink(url);
    bridge->GetColName(url,chl);
    nsCOMPtr<nsIColAtt> col_att = do_CreateInstance("@nyapc.com/XPCOM/nsColAtt;1", &rv);
    if (!NS_FAILED(rv)) {
        PRInt32 uid = 0;
        url_att->GetColId(&uid);
        LOG<<"col_id: " << uid<<endl;
        col_handle->GetColByID(getter_AddRefs(col_att), uid);
        LOG<<"col_att: " << col_att<<endl;
        if(col_att != nsnull) {
            col_att->GetName(col_name);
            col_att->GetAlias(col_alias);
            col_att->GetUrl(col_url);
        }
        
        LOG<<"blog name: "<<col_name.get()<<" blog alias: "<<col_alias.get()<<endl;

        if(chl.Length()>0){
            map<nsCString,nsCString>::iterator ite = this->column_map.begin();
            for(;ite != column_map.end(); ite++)
            {
                if(ite->first.Compare(chl)){
                    rchl = ite->second;
                    break;
                }
            }
        }
    }

//    nsCOMPtr<nsIIndexDoc> idx = do_CreateInstance("@nyapc.com/XPCOM/nsIndexDoc;1", &rv);
//    if (!NS_FAILED(rv)) {
//        idx->SetUrl(url_att);
//        idx->SetTitle(title);
//        idx->SetPublishDate(date);
//        idx->SetSource(source);
//        idx->SetAuthor(author);
//        idx->SetContent(content);
//        LOG << "save idx\n";
//        idx_handle->SaveIDX(idx);
//        LOG << "save idx ok.\n";
//    }

    nsCOMPtr<nsIIDXCreator> idx_creator = do_CreateInstance("@nyapc.com/XPCOM/nsIIDXCreator;1", &rv);
    if (!NS_FAILED(rv)) {
        LOG<<"IDX Creator\n";
        time_t seconds;
        string sec;
        seconds = time (NULL);
        stringstream ss;
        ss << seconds;
        ss >> sec;

        nsCString escaped_ref, col_url1;
        escape(url,escaped_ref);
        escape(col_url,col_url1);
//        LOG<<"escaped string: "<<escaped_ref.get()<<endl;
        idx_creator->SetReference(escaped_ref);
        idx_creator->SetContent(content);
        idx_creator->SetTitle(title);
        idx_creator->SetDate(nsCString(sec.c_str()));
        idx_creator->SetField(nsCString("PUBLISHDATE"), date);
        this->set_statdate(date,idx_creator);
        this->set_sitedomain(this->sitedomain,idx_creator);
        idx_creator->SetField(nsCString("SOURCEINFO"),this->sourceinfo);
        if(true){
            idx_creator->SetDB(nsCString("BLOG"));
            idx_creator->SetField(nsCString("BLOGCHANNEL"),chl);
            idx_creator->SetField(nsCString("REGALCHANNEL_ONE"),rchl);
            idx_creator->SetField(nsCString("AUTHOR"),col_name);
            idx_creator->SetField(nsCString("BLOGNAME"),col_name);
            idx_creator->SetField(nsCString("BLOGALIAS"),col_alias);
            idx_creator->SetField(nsCString("BLOGURL"),col_url1);
            
        }

        if(index_addr.Length()>0) {
            idx_creator->SendIDX(index_addr);
        } else {
            LOG<<"There is No valid IndexURL\n";
        }
    }
}

int nsDOMWrapper::wrapping(BlockList & bl, BlockCluster * bc) {
    int page_type = INVALID_BLOCK;
    int con_type = 0;
    if (bc == NULL) {
        page_type = analyze_page_type(bl);
    } else {
        page_type = bc->GetType();
        con_type = bc->GetName();
    }

    if (page_type != INVALID_BLOCK) {
        if (page_type == CONTENT_BLOCK) {
            LOG << "This is a content page" << endl;
            wrap_content_page2(bl);
            wrap_nextpage(page_type);

        } else {
            LOG << "This is a link page" << endl;
        }
    } else {
        LOG << "This is an invalid page" << endl;
    }

    stringstream ss;
    ss << con_type << endl;
    string c_type;
    ss >> c_type;
    nsCString ctype(c_type.c_str());
    url_att->SetConType(ctype);

    cdb_handle->SetPageType(url_att, page_type);
    return con_type;
}

void nsDOMWrapper::wrap_nextpage(int type) {
    LOG << "wrap nextpage\n";
    if (doc == NULL || cdb_handle == NULL || url_att == NULL) return;
    nsresult rv;

    string ext = string_ext_name(URL);
    if (ext.compare("") == 0) return;
    nsCString u(URL.substr(0, URL.length()-(ext.length() + 1)).c_str());
    LOG << "find " << u.get() << "\n";
    list<string> urls;
    list<string>::iterator it;

    nsCOMPtr<nsIDOMHTMLDocument> domhtml = do_QueryInterface(doc);
    //bool hasb=HasBody(domhtml);
    //if(!hasb) return;

    nsCOMPtr<nsIDOMHTMLCollection> links;
    domhtml->GetLinks(getter_AddRefs(links));
    PRUint32 len;
    links->GetLength(&len);
    for (int i = 0; i < len; i++) {
        nsCOMPtr<nsIDOMNode> aLink(nsnull);
        links->Item(i, getter_AddRefs(aLink));
        if (aLink != nsnull) {
            nsString Value;
            nsString linkUrl;
            nsCOMPtr<nsIDOM3Node> nsEle = do_QueryInterface(aLink);
            if (nsEle == nsnull) continue;
            nsEle->GetTextContent(Value);

            nsCOMPtr<nsIDOMHTMLAnchorElement> linkEle = do_QueryInterface(aLink);
            if (linkEle != nsnull) {
                linkEle->GetHref(linkUrl);
            } else {
                nsCOMPtr<nsIDOMHTMLLinkElement> linkEle2 = do_QueryInterface(aLink);
                if (linkEle != nsnull) {
                    linkEle->GetHref(linkUrl);
                }
            }


            nsCString tmpURL = NS_ConvertUTF16toUTF8(linkUrl);
            nsCString tmpValue = NS_ConvertUTF16toUTF8(Value);
            //LOG<<tmpURL.get()<<endl;
            PRBool b = false;
            PRInt32 pos = tmpURL.Find(u, b);
            if (pos == 0) {
                string value(tmpValue.get());
                string url(tmpURL.get());
                bool b1 = is_nextpage_text(value);
                if (b1) {
                    urls.remove(url);
                    urls.push_front(url);

                    LOG << "url:" << tmpURL.get() << "txt:" << tmpValue.get() << "\n";
                }
            }
        }
    }
    if (urls.size() > 0) {
        urls.sort();
        urls.reverse();

        PRInt32 nextpage = -1;
        PRUint32 parent_id = 0;
        nsCString cur_url, cur_title;
        url_att->GetLink(cur_url);
        url_att->GetTitle(cur_title);

        cdb_handle->GetURLID(cur_url, &parent_id);
        for (it = urls.begin(); it != urls.end(); it++) {
            LOG << *it << "\n";
            nsCOMPtr<nsIUrlAtt> tmp = do_CreateInstance("@nyapc.com/XPCOM/nsUrlAtt;1", &rv);
            if (NS_FAILED(rv)) {
                ERROR << "Get nsIUrlAtt Error:" << rv << "\n";
                return;
            }

            stringstream ss;
            ss << type << endl;
            ss << CONTENT_BLOCK << endl;
            string c_type;
            string c_att;
            ss >> c_type;
            ss >> c_att;
            nsCString page_type(c_att.c_str());
            tmp->SetConAtt(page_type);
            nsCString con_type(c_type.c_str());
            tmp->SetConType(con_type);

            nsCString link(it->c_str());
            tmp->SetLink(link);
            tmp->SetTitle(cur_title);

            tmp->SetNextId(nextpage);
            tmp->SetParId(parent_id);

            cdb_handle->InsertNewPage(tmp);

            PRUint32 id = 0;
            cdb_handle->GetURLID(link, &id);
            nextpage = id;
        }
        url_att->SetNextId(nextpage);

    }
}

void nsDOMWrapper::serialize() {
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

void nsDOMWrapper::deserialize() {
    LOG << "          Loading clusters\n";
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
            int type = bc.GetType();
            //LOG<<"this cluster type is:"<<type<<"\n";
            if (type & allowed_type)
                lst.push_back(bc);
        }
    }
}

void nsDOMWrapper::save_wrap_rules() {
    list<BlockCluster> & lst = clusters;
    list<BlockCluster>::iterator it_bc;
    for (it_bc = lst.begin(); it_bc != lst.end(); it_bc++) {
        string rules = it_bc->GetRuleString();
        //LOG<<"rule:"<<rules<<"\n";
        save_wrap_rules(it_bc->GetName(), it_bc->GetType(), rules);
    }
}

void nsDOMWrapper::save_wrap_rules(int con_type, int con_attr, string & rules) {
    if (cdb_handle == NULL) return;

    nsCString r(rules.c_str());
    cdb_handle->SaveWrapRules(con_type, con_attr, r);
}

void nsDOMWrapper::load_wrap_rules_from_db(int type, BlockCluster & bc) {
    if (cdb_handle == NULL) return;

    nsCString rules;
    cdb_handle->LoadWrapRules(type, rules);
    string r(rules.get());
    if (r.compare("") != 0)
        load_wrap_rules(r, bc);
}

void nsDOMWrapper::load_wrap_rules(string & rules, BlockCluster & bc) {
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

void nsDOMWrapper::load_wrap_rules() {
    PRInt32 size;
    list<BlockCluster>::iterator it;
    for (it = clusters.begin(); it != clusters.end(); it++) {
        BlockCluster & bc = *it;
        load_wrap_rules_from_db(bc.GetName(), bc);
    }
}

void nsDOMWrapper::load_cluster() {
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

int nsDOMWrapper::get_num_of_cluster() {
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

void nsDOMWrapper::collect_wrapper_rules() {
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

    nsString n;
    property->GetStringProperty(ADVERTISE_NODE, n);
    string ad = string(NS_ConvertUTF16toUTF8(n).get());
    LOG << "AdvertiseNode: " << ad << "\n";
    n.Cut(0,n.Length());
    property->GetStringProperty(DATE_NODE, n);
    string date = string(NS_ConvertUTF16toUTF8(n).get());
    n.Cut(0,n.Length());
    property->GetStringProperty(AUTHOR_NODE, n);
    string author = string(NS_ConvertUTF16toUTF8(n).get());
    n.Cut(0,n.Length());
    property->GetStringProperty(SOURCE_NODE, n);
    string source = string(NS_ConvertUTF16toUTF8(n).get());
    n.Cut(0,n.Length());
    property->GetStringProperty(TITLE_NODE, n);
    string title = string(NS_ConvertUTF16toUTF8(n).get());
    if(ad.length()>0)
        ad_node.insert(ad);
    if(date.length()>0)
        date_node.insert(date);
    if(author.length()>0)
        author_node.insert(author);
    if(source.length()>0)
        source_node.insert(source);
    if(title.length()>0)
        title_node.insert(title);
}

nsCString nsDOMWrapper::wrap_title(BlockList & bl) {
    LOG << "Wrap title" << "\n";
    nsCString title;
    set<string>::iterator it;
    list<string> t_set;
    for (it = title_node.begin(); it != title_node.end(); it++) {
        string path = *it;
        string str = bl.GetPathText(path);
        LOG << str << "\n";
        if (str.compare("") != 0) {
            t_set.push_back(str);
            break;
        }
    }

    if (t_set.size() >= 1) {
        title.Append(t_set.begin()->c_str());
    }

    return title;
}

nsCString nsDOMWrapper::wrap_author(BlockList & bl) {
    LOG << "Wrap author" << "\n";
    nsCString author;
    set<string>::iterator it;
    list<string> t_set;
    for (it = author_source_node.begin(); it != author_source_node.end(); it++) {
        string path = *it;
        string str = tool_wrap_author(bl, path);
        LOG << "path:" << path << " text:" << str << "\n";
        if (str.compare("") != 0) {
            t_set.push_back(str);
            break;
        }
    }

    if (t_set.size() >= 1) {
        author.Append(t_set.begin()->c_str());
    } else {
        for (it = author_node.begin(); it != author_node.end(); it++) {
            string path = *it;
            string str = tool_wrap_author(bl, path);
            LOG << "path:" << path << " text:" << str << "\n";
            if (str.compare("") != 0)
                t_set.push_back(str);
        }

        if (t_set.size() >= 1) {
            author.Append(t_set.begin()->c_str());
        }
    }

    return author;
}

nsCString nsDOMWrapper::wrap_source(BlockList & bl) {
    LOG << "Wrap source1" << "\n";
    nsCString source;
    set<string>::iterator it;
    list<string> t_set;
    for (it = author_source_node.begin(); it != author_source_node.end(); it++) {
        string path = *it;
        string str = tool_wrap_source(bl, path);
        if (str.compare("") != 0) {
            t_set.push_back(str);
            break;
        }
    }

//    LOG << "Wrap source2" << "\n";
    if (t_set.size() >= 1) {
        source.Append(t_set.begin()->c_str());
    } else {
//        LOG << "Wrap source3" << "\n";
        for (it = source_node.begin(); it != source_node.end(); it++) {
            string path = *it;
            string str = tool_wrap_source(bl, path);
            if (str.compare("") != 0)
                t_set.push_back(str);
        }
//        LOG << "Wrap source4" << "\n";
        if (t_set.size() >= 1) {
            source.Append(t_set.begin()->c_str());
        }
    }
//    LOG << "Wrap source5" << "\n";
    return source;
}

nsCString nsDOMWrapper::wrap_date(BlockList & bl, string & date_format) {
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
        LOG << d << " : " << str << "\n";
        if (str.compare("") != 0) {
            t_set.push_back(str);
            break;
        }
    }

    if (t_set.size() >= 1) {
        date.Append(t_set.begin()->c_str());
    }

    return date;
}

nsCString nsDOMWrapper::wrap_content() {
    LOG << "Wrap content\n";
    nsCString content;

//    get_content(doc, content, main_node);
    get_content2(doc, content, ad_node, StopTag, StartTag);
    return content;
}

void nsDOMWrapper::set_statdate(nsCString & date, nsIIDXCreator* idx)
{
    if(date.Length() <= 0 || idx == NULL) return;
    PRUint32 sp = 0;
    sp = (PRUint32) date.FindChar('-', sp);
    nsCString year(date.get(),sp);
    sp++;
    sp = (PRUint32) date.FindChar('-', sp);
    nsCString month(date.get(),sp);

    sp = (PRUint32) date.FindChar(' ', 0);
    nsCString day(date.get(),sp);

    idx->SetField(nsCString("STATYEAR"), year);
    idx->SetField(nsCString("STATMONTH"), month);
    idx->SetField(nsCString("STATDATE"), day);
}

void nsDOMWrapper::set_sitedomain(nsCString & domain, nsIIDXCreator * idx)
{
    if(domain.Length() <= 0 || idx == NULL) return;
    idx->SetField(nsCString("SITEDOMAIN"), domain);
    size_t sp = 0;
    char * d = (char*)domain.get();
    PRInt32 len = domain.Length();
//    DEBUG<<"[set_sitedomain] "<<d<<endl;
    while(len-- > 0){
        if(*d == '.'){
            char * next = d+1;
            if(*next != '\0'){
                nsCString sd(next);
                idx->SetField(nsCString("SITEDOMAIN"), sd);
//                DEBUG<<"[set_sitedomain] "<<sd.get()<<endl;
            }
        }
        d++;
    }

}

bool nsDOMWrapper::is_valid_url(string & url) {
    if(this->MustHaveCSV.length()>0) {
        size_t p = url.find(this->MustHaveCSV);
        if(p == string::npos)
            return false;
    }

    if(this->DontMustHaveCSV.length()>0) {
        size_t p = url.find(this->DontMustHaveCSV);
        if(p != string::npos)
            return false;
    }

    return true;
}