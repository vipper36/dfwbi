#! /bin/bash
export DISPLAY=:0.0

/usr/local/xulrunner-sdk/bin/run-mozilla.sh ./gtkMain -r 1 -w /root/workspace/ChlCrawler/blog/chl -l "@nyapc.com/XPCOM/nsColCrawListener;1"

unset DISPLAY
