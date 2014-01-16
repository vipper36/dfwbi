#ifndef __NS_RCOM_H__
#define __NS_RCOM_H__
#include "nsIRCom.h"
#include "sisocks.h"
#include "Rconnection.h"
#include <json/json.h>
#include <string>
#define NS_RCOM_CONTRACTID "@com.xiao.xpcom/nsIRCom;1"
#define NS_RCOM_CLASSNAME "nsRCom"
#define NS_RCOM_CID NS_IRCOM_IID

class nsRCom : public nsIRCom
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSIRCOM

  nsRCom();

private:
  ~nsRCom();

protected:
  /* additional members */
  Rconnection *rc;
  Json::Value RexpToJson(Rexp *xp);
};
#endif
