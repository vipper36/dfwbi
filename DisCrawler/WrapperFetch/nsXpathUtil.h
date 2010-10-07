#include "nsIXpathUtil.h"
#include "nsISupportsArray.h"
#include "nsStringAPI.h"
#include "nsIDOMXPathEvaluator.h"
#include "nsIDOMDocument.h"
#include <string>
#include <set>
#ifndef __NS_XPATHUTIL_H__
#define __NS_XPATHUTIL_H__


#define NS_XPATHUTIL_CONTRACTID "@nyapc.com/XPCOM/nsXpathUtil;1"
#define NS_XPATHUTIL_CLASSNAME "nsXpathUtil"

#define NS_XPATHUTIL_CID {0x5c84c0fa,0x4f13,0x49a9,{0xad,0xd3,0x46,0xde,0xf1,0xba,0x41,0x4e}}
const std::string Att_Name[]=
{
     "class",
     "id",
     "valign",
     "halign",
     "align",
     "bgcolor",
     "color",
     "font"
};
class nsXpathUtil : public nsIXpathUtil
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIXPATHUTIL

  nsXpathUtil();

private:
  ~nsXpathUtil();
  nsCOMPtr<nsIDOMDocument> mDoc;
  nsCOMPtr<nsIDOMXPathEvaluator> xpathEV;
  nsCOMPtr<nsISupportsArray> mResult;
  std::set<std::string> attlist;
protected:
  std::string CalXpath(nsIDOMNode * node);
  std::string CalXpathABS(nsIDOMNode * node);
  std::string CalXpathAnc(nsIDOMNode * node, nsIDOMNode * anc);


  std::string GetXpathAtt(nsIDOMElement *ele);
  /* additional members */
};
#endif
