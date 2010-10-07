#include "nsIDocAtt.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDocSet.h"
#include "nsIAttSet.h"
#include "nsIAttDim.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include <map>
#include <string>
#ifndef __NSNDDOCATT_H__
#define __NSNDDOCATT_H__
#define NS_NDDOCATT_CONTRACTID "@nyapc.com/XPCOM/nsNDDocAtt;1"
#define NS_NDDOCATT_CLASSNAME "nsNDDocAtt"

#define NS_NDDOCATT_CID {0xb1b955ca,0x41f2,0x4106,{0xb1,0xaa,0xf3,0xe7,0xee,0xd4,0x9f,0x9e}}


class nsNDDocAtt : public nsIDocAtt
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIDOCATT

  nsNDDocAtt();

private:
  ~nsNDDocAtt();

  nsCOMPtr<nsIDocSet> m_docs;
  nsCOMPtr<nsIDomAttUtil> domUtil;
  nsCOMPtr<nsIAttSet> vset;
  nsCOMPtr<nsIAttDim> vdim;
  bool GetLinkAtt(nsIDOMDocument *domdoc);
protected:
  /* additional members */
};
#endif
