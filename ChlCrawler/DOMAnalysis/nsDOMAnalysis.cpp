#include "nsDOMAnalysis.h"
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

NS_IMPL_ISUPPORTS1(nsDOMAnalysis, nsIDOMAnalysis)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsDOMAnalysis)

static nsModuleComponentInfo components[] =
{
     {
          NS_NSDOMANALYSIS_CLASSNAME,
          NS_NSDOMANALYSIS_CID,
          NS_NSDOMANALYSIS_CONTRACTID,
          nsDOMAnalysisConstructor,
     }
};

NS_IMPL_NSGETMODULE("nsDOMAnalysisModule", components)

nsDOMAnalysis::nsDOMAnalysis()
{
	nsresult rv;
	cdb_handle = do_CreateInstance("@nyapc.com/XPCOM/nsClusterDBHandle;1", &rv);
	if (NS_FAILED(rv))
	{
		ERROR<<"Get  mozIStorageService  Error:"<<rv<<"\n";
		cdb_handle = NULL;
	}

	url_att		= NULL;
	doc		= NULL;
}

nsDOMAnalysis::~nsDOMAnalysis()
{
}

NS_IMETHODIMP nsDOMAnalysis::Analysis(nsIDOMDocument *doc, PRUint32 *_retval)
{
	LOG << "          startup... "<< "\n";
	nsCOMPtr<nsIDOMHTMLDocument> html = do_QueryInterface(doc);
	nsString t,u;
	html->GetTitle(t);
	html->GetURL(u);
	string title(NS_ConvertUTF16toUTF8(t).get());
	string url(NS_ConvertUTF16toUTF8(u).get());

	LOG<<"title: "<<title<<" url: "<<url<<"\n";

	list<BlockCluster> & c_lst = clusters;
	BlockList bl;
	convert_html_to_bl(html,bl);
	bl.SetTitle(title);
	bl.SetUrl(url);
	LOG<<"convert ok"<< "\n";

	int con_type = atom_cluster(bl,c_lst);

	analyze_clusters(c_lst);

	write_page_type_into_db(con_type);

	url_att	= NULL;
	doc	= NULL;
	*_retval = con_type;
}

NS_IMETHODIMP nsDOMAnalysis::SetCurUrl(nsIUrlAtt *url_attr)
{
	this->url_att = url_attr;
	return NS_OK;
}

NS_IMETHODIMP nsDOMAnalysis::SaveWrapper()
{
	LOG<<"saving wrapper"<<"\n";
    serialize();
    save_wrap_rules();
    return NS_OK;
}

NS_IMETHODIMP nsDOMAnalysis::SetProperty(nsIPersistentProperties *p)
{
	this->property = p;
	return NS_OK;
}

NS_IMETHODIMP nsDOMAnalysis::SetIdxCreator(nsIIDXCreator * creator)
{
	return NS_OK;
}

NS_IMETHODIMP nsDOMAnalysis::LoadConfig()
{
	if(property!=NULL)
	{
		//Wrapper name
		nsString n;
		property->GetStringProperty(WRAPPER_NAME, n);
		//nsCString name(NS_ConvertUTF16toUTF8(n).get());
		wrapper_name = string(NS_ConvertUTF16toUTF8(n).get());
		LOG << "wrapper name: " << wrapper_name << "\n";
		deserialize();
		
		nsString n1;
		property->GetStringProperty(URL_SOURCE, n1);
		mLocation = NS_ConvertUTF16toUTF8(n1);
		LOG << "target database: " << mLocation.get() << "\n";
		
		if(cdb_handle != NULL)
			cdb_handle->SetLocation(mLocation);

		load_wrap_rules();
	}
	return NS_OK;
}

/* void GetClusterAttr (in PRUint32 cid, out PRUint32 attr); */
NS_IMETHODIMP nsDOMAnalysis::GetClusterAttr(PRUint32 cid, PRUint32 *attr)
{
	*attr = 0;
	list<BlockCluster>::iterator it;
	for(it = clusters.begin(); it != clusters.end(); it++)
	{
		int id = it->GetName();
		if(id == cid)
		{
			*attr = it->GetType();
		}
	}

	return NS_OK;
}

/* void SetClusterType (in PRUint32 type); */
NS_IMETHODIMP nsDOMAnalysis::SetClusterType(PRUint32 cid, PRUint32 type)
{
	list<BlockCluster>::iterator it;
	for(it = clusters.begin(); it != clusters.end(); it++)
	{
		int id = it->GetName();
		if(id == cid)
		{
			it->SetType(type);
		}
	}
	
	return NS_OK;
}

int nsDOMAnalysis::atom_cluster(BlockList & bn, list<BlockCluster> & bc_set)
{
	list<BlockCluster>::iterator it = bc_set.begin();
	if(bc_set.size() > 0)
	{
		bool found_cluster = false;
		float sim = 0.0;
		float max_sim = 0.0;
		list<BlockCluster>::iterator it_bc = it;
		for(; it != bc_set.end(); it++)
		{
			sim = it->IsSimilar(bn);
			LOG << "sim " << sim << "\n";
			if(sim > SIMILAR_THRESHOLD && sim > max_sim)
			{
				//it->insert(bn);
				it_bc = it;
				max_sim = sim;
				found_cluster = true;
				break;
			}
		}
		if(!found_cluster)
		{
			LOG << "create new cluster"<<"\n";
			BlockCluster bc(get_new_cluster_id());
			bc.insert(bn);
			bc_set.push_front(bc);
			return bc.GetName();
		}
		else
		{
			it_bc->insert(bn);
			LOG << "found a same cluster"<< "\n";
			return it_bc->GetName();
		}
	}
	else
	{
		LOG << "create 1st cluster"<<"\n";
		BlockCluster bc(get_new_cluster_id());
		bc.insert(bn);
		bc_set.push_front(bc);
		return bc.GetName();
	}
}

void nsDOMAnalysis::analyze_clusters(list<BlockCluster> & bc_set)
{
	list<BlockCluster>::iterator it;
	if(bc_set.size() > 0)
	{
		for(it = bc_set.begin(); it != bc_set.end(); it++)
		{
			BlockCluster & bc = *it;
			
			if(bc.need_training())
			{
				LOG << "analyzing cluster " << "\n";
				bc.analyze_common();
				bc.analyze_main_section();
				analyze_cluster_type(bc);

				int type = bc.GetType();
				if(type == LINK_BLOCK)
				{
					LOG<<"cluster type:链接页"<<"\n";
					//bc.analyze_links();
				}
				else if(type == CONTENT_BLOCK)
				{
					LOG<<"cluster type:内容页"<<"\n";
					bc.analyze_title();
					bc.analyze_date_author_source();
				}
				else
				{
					LOG << "cluster is invalid..." << "\n";
				}

				bc.training_completed();
			}
		}
	}
}

void nsDOMAnalysis::analyze_cluster_type(BlockCluster & bc)
{
	//计算连接/文本比
	float anchor_density = bc.anchor_density();
	LOG<< "cluster anchor density "<<anchor_density<<"\n";
	if(anchor_density >= LINK_BLOCK_THRESHOLD)
	{
		if(bc.GetType() != CHANNEL_BLOCK)
			bc.SetType(LINK_BLOCK);
	}
	else if(anchor_density >= 0.0)
	{
		float w = bc.avrg_text_length();
		w = w * (1-anchor_density);
		//LOG << "content length "<<w<<"\n";
		if(w > MIN_CONTENT_LENGTH)
		{
			bc.SetType(CONTENT_BLOCK);
		}
	}
	else
	{
		LOG<<"invalid_block:无法判定为链接块和内容块"<<"\n";
	}
}

void nsDOMAnalysis::serialize()
{
	if(wrapper_name.compare("")==0) return;
	ofstream os(wrapper_name.c_str(), ios::binary|ios::trunc);
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
		for(it_bc=lst.begin(); it_bc != lst.end(); it_bc++)
			it_bc->serialize(ss);
	}
	os << ss.str();
	os.close();
}

void nsDOMAnalysis::deserialize()
{
	if(wrapper_name.compare("")==0) return;
	ifstream is(wrapper_name.c_str(), ios::binary);
	is.seekg (0, ios::end);
	int length = is.tellg();
	if(length<1) return;
	is.seekg (0, ios::beg);
	// allocate memory:
	char * buffer = new char [length];

	// read data as a block:
	is.read (buffer,length);
	is.close();

	stringstream ss;
	ss.write(buffer,length);
	delete[] buffer;

	int size = 0; 
	{
		int len = 0;
		len = get_integer(ss);
		LOG<<"there are "<<len<<" BlockCluster"<<"\n";
		list<BlockCluster> & lst = clusters;
		for(int j=0; j<len; j++)
		{
			BlockCluster bc;
			bc.deserialize(ss);
			lst.push_back(bc);
		}
	}
}

void nsDOMAnalysis::save_wrap_rules()
{
	list<BlockCluster> & lst = clusters;
	list<BlockCluster>::iterator it_bc;
	for(it_bc=lst.begin(); it_bc != lst.end(); it_bc++)
	{
		string rules = it_bc->GetRuleString();
		LOG<<"rule:"<<rules<<"\n";
		save_wrap_rules(it_bc->GetName(), it_bc->GetType(),rules);
	}
}


void nsDOMAnalysis::save_wrap_rules(int con_type, int con_attr, string & rules)
{
	if(cdb_handle == NULL) return;

	nsCString r(rules.c_str());
	cdb_handle->SaveWrapRules(con_type, con_attr, r);
}

void nsDOMAnalysis::load_wrap_rules_from_db(int type, BlockCluster & bc)
{
	if(cdb_handle == NULL) return;

	nsCString rules;
	cdb_handle->LoadWrapRules(type,rules);
	string r(rules.get());
	if(r.compare("")!=0) 
		load_wrap_rules(r,bc);
}

void nsDOMAnalysis::load_wrap_rules(string & rules, BlockCluster & bc)
{
	stringstream ss;
	ss << rules;
	string line = get_line(ss);
	while(line.compare("") != 0)
	{
		string sp(RULE_SEPARATOR);
		size_t f = line.find(sp);
		if(f != string::npos)
		{
			string k = line.substr(0,f);
			string v = line.substr(f+sp.size());
			LOG<< "key: "<<k<<" value: "<<v<<"\n";
			bc.SetRule(k,v);
		}
		line = get_line(ss);
	}
}

void nsDOMAnalysis::load_wrap_rules()
{
	PRInt32 size;
	list<BlockCluster>::iterator it;
	for(it = clusters.begin(); it != clusters.end(); it++)
	{
		BlockCluster & bc = *it;
		load_wrap_rules_from_db(bc.GetName(),bc);
	}
}

void nsDOMAnalysis::write_page_type_into_db(int type)
{
	cdb_handle->SetPageType(url_att,type);
}

int nsDOMAnalysis::get_new_cluster_id()
{
	int nid = 0;
	list<BlockCluster>::iterator it;
	for(it = clusters.begin(); it != clusters.end(); it++)
	{
		int id = it->GetName();
		if(id >= nid)
		{
			nid = id;
		}
	}
	nid++;
	return nid;
}
