#include "nsIServiceManager.h"
#include "nsIGenericFactory.h"
#include "nsNetUtil.h"
#include "nsCluster.h"
#include "nsIAttSet.h"
#include "nsIAttVec.h"
#include <iostream>
#include <sstream>
#include "property.h"
#include <KMlocal.h>

NS_IMPL_ISUPPORTS1(nsCluster, nsICluster)

NS_GENERIC_FACTORY_CONSTRUCTOR(nsCluster)

static nsModuleComponentInfo components[] =
{
     {
	  NS_CLUSTER_CLASSNAME,
	  NS_CLUSTER_CID,
	
  NS_CLUSTER_CONTRACTID,
	  nsClusterConstructor,
     }
};
NS_IMPL_NSGETMODULE("nsClusterModule", components)


nsCluster::nsCluster()
{
     nsresult rv;
     m_model=do_CreateInstance("@nyapc.com/XPCOM/nsClustModel;1",&rv);
     if (NS_FAILED(rv))
     {
	  LOG<<"Init model error!\n";
     }
}

nsCluster::~nsCluster()
{
     /* destructor code */
}

/* void SetAtt (in nsIAttSet set); */
NS_IMETHODIMP nsCluster::SetAtt(nsIAttSet *set)
{
    
     m_atts=set;
     return NS_OK;
}
/* void SetDoubleParam (in AUTF8String name, in double value); */
NS_IMETHODIMP nsCluster::SetDoubleParam(const nsACString & name, double value)
{
     nsCString nsName(name);
     std::string nameStr(nsName.get());
     dParams.insert(make_pair(nameStr,value));
     return NS_OK;
}


/* void SetStringParam (in AUTF8String name, in AUTF8String value); */
NS_IMETHODIMP nsCluster::SetStringParam(const nsACString & name, const nsACString & value)
{
     nsCString nsName(name);
     nsCString nsValue(value);
     std::string nameStr(nsName.get());
     std::string valueStr(nsValue.get());
     sParams.insert(make_pair(nameStr,valueStr));
     return NS_OK;
}

/* void CaculModel (); */
NS_IMETHODIMP nsCluster::CaculModel()
{
     LOG<<"start cluster.....\n";
     int AttDim=int(dParams["ATTDIM"]);
     int kcent=int(dParams["CLASS_COUNT"]);
     int doccount=int(dParams["DOC_COUNT"]);
     m_model->ClearModel();
     PRInt32 attlen=0;     
     m_atts->GetLength(&attlen);
     int lenAtt=0;
     if(doccount>0)
	  lenAtt=attlen/doccount;
     else
	  lenAtt=attlen;
     if(kcent==0)
     {
	  if(lenAtt<400)
	       kcent=3;
	  else if(lenAtt<400)
	       kcent=4;
	  else if(lenAtt<1400)
	       kcent=5;
	  else if(lenAtt<2400)
	       kcent=6;
	  else if(lenAtt<3400)
	       kcent=7;
	  else
	       kcent=8;

     }
     KMterm  term(50, 0, 50, 0.5,		// run for 100 stages
		  0.01,			// min consec RDL
		  0.01,			// min accum RDL
		  AttDim*20,			// max run stages
		  0.3,			// init. prob. of acceptance
		  AttDim*10,			// temp. run length
		  0.75);			// temp. reduction factor
     

     KMdata *dataPts=new KMdata(AttDim, attlen);		// allocate data storage
     // generate points

     
     for(int nPts=0;nPts<attlen;nPts++)
     {
	  nsCOMPtr<nsIAttVec> vec(nsnull);
	  m_atts->GetVectorByIndex(nPts,getter_AddRefs(vec));
	  if(vec!=nsnull)
	  {
	       for(int i=0;i<AttDim;i++)
	       {
		    double value=.0;
		    vec->GetValueByDim(i,&value );
		    (*dataPts)[nPts][i]=value;
	       }
	  }
     }
     dataPts->setNPts(attlen);			// set actual number of pts
     dataPts->buildKcTree();			// build filtering structure


     KMfilterCenters *ctrs=new KMfilterCenters(kcent, *dataPts);		// allocate centers

     std::string alg=sParams["ALG"];
     if(alg.length()==0)
	  alg=std::string("EZ-Hybrid");
     if(alg=="Lloyd")
     {
	  KMlocalLloyds kmLloyds(*ctrs, term);		// repeated Lloyd's
	  *ctrs = kmLloyds.execute();			// execute
     }else if(alg=="Swap")
     { 
	  KMlocalSwap kmSwap(*ctrs, term);		// Swap heuristic
	  *ctrs = kmSwap.execute();
     }else if(alg=="EZ-Hybrid")
     {
	  KMlocalEZ_Hybrid kmEZ_Hybrid(*ctrs, term);	// EZ-Hybrid heuristic
	  *ctrs = kmEZ_Hybrid.execute();
     }else if(alg=="Hybrid")
     {
	  KMlocalHybrid kmHybrid(*ctrs, term);		// Hybrid heuristic
	  *ctrs = kmHybrid.execute();
     }
    
     KMctrIdxArray closeCtr = new KMctrIdx[dataPts->getNPts()];
     double* sqDist = new double[dataPts->getNPts()];
     
     ctrs->getAssignments(closeCtr, sqDist);

     double* CenDist = ctrs->getDists();
     
     
     for (int j = 0; j < kcent; j++) {

	  nsCOMPtr<nsIAttSet> classSet=do_CreateInstance("@nyapc.com/XPCOM/nsAttSet;1");

	  nsCOMPtr<nsIAttVec> cenVec=do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1");
	  if(cenVec!=nsnull)
	  {
	       int k=0;
	       for(;k<AttDim;k++)
	       {
		    cenVec->AddValue(k,(*ctrs)[j][k]);
	       }
	       cenVec->AddValue(k,CenDist[j]);
	  }
	  if(classSet!=nsnull)
	  {
	       for(int k=0;k<dataPts->getNPts();k++)
	       {
		    if(closeCtr[k]==j)
		    {
			 nsCOMPtr<nsIAttVec> classVec(nsnull);
			 m_atts->GetVectorByIndex(k,getter_AddRefs(classVec));
			 nsCOMPtr<nsIAttVec> newVec=do_CreateInstance("@nyapc.com/XPCOM/nsAttVec;1");
			 if(newVec!=nsnull)
			 {
			      PRInt32 len=0;
			      classVec->GetLength(&len);
			      newVec->SetVector(classVec);
			      newVec->AddValue(len,sqDist[k]);
			      
			      classSet->AppendVector(newVec);
			 }
		    } 
	       }
	  }
	  m_model->AppendClass(classSet, cenVec);
	  
     }
     LOG<<"end cluster.....\n";
     delete sqDist;
     delete closeCtr;
     delete ctrs;
     delete dataPts;
     return NS_OK;
}

/* nsIClustModel GetResultModel (); */
NS_IMETHODIMP nsCluster::GetResultModel(nsIClustModel **_retval )
{
     *_retval=m_model;
     NS_ADDREF(*_retval);
     return NS_OK;
}
