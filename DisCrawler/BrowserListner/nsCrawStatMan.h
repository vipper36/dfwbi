#ifndef __NS_CRAWSTATMAN_H__
#define __NS_CRAWSTATMAN_H__
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsStatManager.h"
#include "nsIDomAttUtil.h"
#include <vector>
#include <string>
#include <map>

#define NS_CRAWSTATMAN_CONTRACTID "@nyapc.com/XPCOM/nsCrawStatMan;1"
#define NS_CRAWSTATMAN_CLASSNAME "nsCrawStatMan"

#define NS_CRAWSTATMAN_CID {0x28d1cc5b,0xf509,0x4127,{0x8f,0xd2,0xb3,0xa4,0x3d,0x76,0x57,0x0a}}


class nsCrawStatMan : public nsStatManager
{
public:
  nsCrawStatMan();

private:
  ~nsCrawStatMan();
  nsCOMPtr<nsIDomAttUtil> domUtil;
protected:
  virtual NS_IMETHODIMP Excute();
  /* additional members */
};
#endif
