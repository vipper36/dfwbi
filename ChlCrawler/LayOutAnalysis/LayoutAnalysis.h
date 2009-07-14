#include "xpcom-config.h"
#include "ILayoutAnalysis.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMNode.h"
#include "nsIDOMDocument.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSDocument.h"
#include "inIDOMUtils.h"
#include "nsIDOMViewCSS.h"
#include "nsStringAPI.h"
#include <string>
#include <map>
#include <list>
#include <vector>
#include <KMlocal.h>
#include "nsITreeNode.h"
#include "property.h"
#ifndef __LAYOUTANALYSIS_H__
#define __LAYOUTANALYSIS_H___
#define LAYOUTANALYSIS_CONTRACTID "@nyapc.com/XPCOM/LayoutAnalysis;1"
#define LAYOUTANALYSIS_CLASSNAME "Analysis the html layout"

#define LAYOUTANALYSIS_CID {0xe4b8eac4,0x88ac,0x4c4a,{0xb3,0x8f,0x48,0x6c,0x70,0x35,0x59,0x2e}}

#define VISUALAREA 1024*768
#define ATTDIM 6
typedef vector<double> AttributeVector;
typedef double (*ScaleFun)(double);
class LayoutAnalysis : public ILayoutAnalysis
{
public: 
     NS_DECL_ISUPPORTS 
     NS_DECL_ILAYOUTANALYSIS
     LayoutAnalysis();
     virtual ~LayoutAnalysis(){
	  if(ctrs!=NULL)
	       delete ctrs;
	  if(dataPts!=NULL)
	       delete dataPts;
     };
protected:
     nsCOMPtr<nsIDOMHTMLDocument> htmldoc;
     nsCOMPtr<nsIDOMNSDocument> nsdoc;
     nsCOMPtr<nsIDOMDocument> domdoc;
     nsCOMPtr<inIDOMUtils> domUtils;
     nsCOMPtr<nsIDOMViewCSS> viewCSS;

     nsCString alg;
     nsString xpath;
     KMterm  term;
     bool NeedAly;
     PRUint32 cents;
     
     KMfilterCenters *ctrs;
     KMdata *dataPts;
protected:
     void BlockCollect();


     void GetComLayoutInfo(nsIDOMElement* node,std::map<std::string,std::string> &lmap);
     int CalNodeDepth(nsIDOMNode *node);



     bool BlockCluster(nsITreeNode *tn);
     bool KMeanCluster(std::vector<AttributeVector> &Array,int k,std::string alg="Lloyd");
     bool ScaleData(std::vector<AttributeVector> &Array);
     bool ScaleVector(std::vector<double*> &Array,ScaleFun fun);
     std::string & get_node_path(nsIDOMNode * node, std::string & path);
     std::string & get_node_path(nsIDOMNode * node, std::string & path, std::string & stop_pos);
     bool CalSibParentDist(nsIDOMElement *node,double &pDist,double &lDist);
};

#endif
