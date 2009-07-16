#! /bin/bash
export DISPLAY=:0.0

/usr/local/xulrunner-sdk/bin/run-mozilla.sh ~/workspace/ChlCrawler/main/gtkMain -r 1 -w /root/workspace/ChlCrawler/blog/chl -l "@nyapc.com/XPCOM/nsChlCrawListener;1"

unset DISPLAY
