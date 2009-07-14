#include "nsIChlWrapper.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include <map>
#include <string>
#include <list>
#include <set>
#include "nsStringAPI.h"
#include "nsIDOMNode.h"
#include "property.h"
#include "ChlXpath.h"
#ifndef __NSCHLWRAPPER_H__
#define __NSCHLWRAPPER_H__


#define NS_CHLWRAPPER_CONTRACTID "@nyapc.com/XPCOM/nsChlWrapper;1"
#define NS_CHLWRAPPER_CLASSNAME "nsChlWrapper"

#define NS_CHLWRAPPER_CID NS_ICHLWRAPPER_IID
struct NodeAtt
{
     std::string xpath;
     std::set<std::string> tpSet;
     int count;
};
class nsChlWrapper : public nsIChlWrapper
{
public:
     NS_DECL_ISUPPORTS
     NS_DECL_NSICHLWRAPPER
       
     nsChlWrapper();

private:
     ~nsChlWrapper();
     nsITreeNode *mTree;
     nsIDOMDocument *doc;
     std::string CalXpath(nsIDOMNode * node, nsIDOMNode * par);
     std::string CalXpathABS(nsIDOMNode * node,nsIDOMNode * par);
     std::string CalXpathDUL(nsIDOMNode * node, nsIDOMNode * par);
     std::string CalXpathAnc(nsIDOMNode * node, nsIDOMNode * anc);

     void GetXpath(std::map<std::string,NodeAtt> &pathmap,nsITreeNode *ptree);
     int distance(const std::string source, const std::string target);

     bool IsFilterTag(std::string &tag);

     std::string GetXpathAtt(nsIDOMElement *ele);
     bool IsTitle(const std::string &str);
     std::string GetTitlePath(nsIDOMNode *node);
     std::string GetTitlePath1(nsIDOMNode *node);
     void string_filter(std::string & s);
     PRUint16 mType;
protected:
     /* additional members */
};
#endif
