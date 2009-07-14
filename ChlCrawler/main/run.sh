#! /bin/bash
export DISPLAY=:0.0
#/usr/local/xulrunner-sdk/bin/run-mozilla.sh ./gtkMain -w /root/workspace/crawler/ -l "@nyapc.com/XPCOM/nsUrlBrowserListener;1"

#/usr/local/xulrunner-sdk/bin/run-mozilla.sh ./gtkMain -w /root/workspace/crawler/ -l "@nyapc.com/XPCOM/nsLinkCollectListener;1"
/usr/local/xulrunner-sdk/bin/run-mozilla.sh ./gtkMain -w /root/workspace/crawler/ -l "@nyapc.com/XPCOM/nsLayoutListener;1"
#/usr/local/xulrunner-sdk/bin/run-mozilla.sh /usr/bin/valgrind --leak-check=full --show-reachable=yes ./gtkMain -w /root/workspace/crawler/ -l "@nyapc.com/XPCOM/nsCrawListener;1"
#/usr/local/xulrunner-sdk/bin/run-mozilla.sh ./gtkMain -w /root/workspace/crawler/ -l "@nyapc.com/XPCOM/nsCrawListener;1"

unset DISPLAY
