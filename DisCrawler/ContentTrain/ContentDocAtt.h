#include "nsIDocAtt.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIAttSet.h"
#include "nsIAttDim.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsIDOMHTMLDocument.h"
#include "nsIDOMNSDocument.h"
#include "inIDOMUtils.h"
#include "nsIDOMViewCSS.h"
#include "nsIDocSet.h"
#include "nsIDimStat.h"
#include "nsIXpathUtil.h"
#include <map>
#include <string>
#ifndef __CONTENTDOCATT_H__
#define __CONTENTDOCATT_H__
#define CONTENTDOCATT_CONTRACTID "@nyapc.com/XPCOM/ContentDocAtt;1"
#define CONTENTDOCATT_CLASSNAME "ContentDocAtt"

#define CONTENTDOCATT_CID {0x23459087,0x9cc9,0x48f8,{0xa6,0x3c,0x38,0xc3,0x43,0x7d,0x70,0x07}}

class ContentDocAtt : public nsIDocAtt
{
public:
    NS_DECL_ISUPPORTS
    NS_DECL_NSIDOCATT

    ContentDocAtt();

private:
    ~ContentDocAtt();
    void DoStatistic(nsIDocSet * docs, PRInt32 doc_counts);
    void PrintStatisticResults();

    void GenerateAttSet(nsIDocSet * docs, PRInt32 doc_counts);
    void WalkTree(nsIDOMNode * node, nsIDOMDocument * doc, nsIAttVec * attvec);
    nsCOMPtr<nsIAttSet> p_attset;
    nsCOMPtr<nsIAttDim> p_attdim;
    nsCOMPtr<nsIDimStat> p_dimstat;
    nsCOMPtr<nsIDocSet> p_docset;
    nsCOMPtr<nsIXpathUtil> p_xpathutil;
protected:
  /* additional members */
};
#endif
