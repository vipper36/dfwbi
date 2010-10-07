#ifndef __NS_WRAPSTATMAN_H__
#define __NS_WRAPSTATMAN_H__
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsIDomAttUtil.h"
#include "nsStatManager.h"
#include <vector>
#include <string>
#include <map>

#define NS_WRAPSTATMAN_CONTRACTID "@nyapc.com/XPCOM/nsWrapStatMan;1"
#define NS_WRAPSTATMAN_CLASSNAME "nsWrapStatMan"

#define NS_WRAPSTATMAN_CID {0x85d44518,0x5279,0x4066,{0x88,0x79,0x1c,0x09,0x46,0x01,0xce,0x0e}}


class nsWrapStatMan : public nsStatManager
{
public:
  nsWrapStatMan();

private:
  ~nsWrapStatMan();
  bool split(const std::string& s, std::string c,std::vector<std::string>& v);
  bool GetParam(const std::string& s, std::map<std::string,std::string>& map);
  nsCOMPtr<nsIDomAttUtil> domUtil;
protected:
  virtual NS_IMETHODIMP Excute();
  /* additional members */
};
#endif
