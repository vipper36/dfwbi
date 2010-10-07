#ifndef __NS_STAT_MANAGER_H__
#define __NS_STAT_MANAGER_H__
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsIDOMDocument.h"
#include "nsStringAPI.h"
#include "nsIStatManager.h"
#include <vector>
#include <string>
#include <map>
class nsStatManager : public nsIStatManager
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSISTATMANAGER

  nsStatManager();
private:
protected:
  std::map<PRInt32,PRUint16> sMap;
  std::map<int,nsIWebBrowser *> bMap;
  nsCOMPtr<nsISoapInter> m_inter;
  nsCOMPtr<nsISoapTask> m_task;
  virtual ~nsStatManager();
  virtual NS_IMETHODIMP Excute()=0;
  void StopBrowers();
  bool IsReady();
	int cid;
  /* additional members */
};
#endif
