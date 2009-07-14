#ifndef __NSTREENODE_H__
#define __NSTREENODE_H__
#include "nsITreeNode.h"
#include "nsXPCOM.h"
#include "nsCOMPtr.h"
#include "nsIDOMParser.h"
#include "nsStringAPI.h"
#include "nsISupportsArray.h"
#include <set>
#define NS_TREENODE_CONTRACTID "@nyapc.com/XPCOM/nsTreeNode;1"
#define NS_TREENODE_CLASSNAME "nsTreeNode"

#define NS_TREENODE_CID NS_ITREENODE_IID

class nsTreeNode : public nsITreeNode
{
public:
  NS_DECL_ISUPPORTS
  NS_DECL_NSITREENODE

  nsTreeNode();

private:
  PRInt32 mX;
  PRInt32 mY;
  PRInt32 mW;
  PRInt32 mH;
  PRInt32 index;
  PRInt32 classid;
  nsIDOMNode *node;
  std::set<PRInt32> ids;
  nsCOMPtr<nsISupportsArray> subTrees;
  ~nsTreeNode();

protected:
  /* additional members */
};
#endif
