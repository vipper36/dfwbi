#! /bin/bash
export DISPLAY=:0.0

/usr/local/xulrunner-sdk/bin/run-mozilla.sh ~/workspace/ChlCrawler/mai~/workspace/ChlCrawler/main/gtkMain -w /root/workspace/ChlCrawler/blog -l "@nyapc.com/XPCOM/nsChlCrawListener;1"

unset DISPLAY
