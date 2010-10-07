#! /bin/bash
. ./config
Xvfb :$CID +kb -screen 0 1024x768x24 -once -fbdir /tmp&
export DISPLAY=:${CID}.0
echo $MulBin 
echo $CrawStatMan
$MOZSHELL $KEYPRESS $MulBin -r 2 -c $CID -l $WrapStatMan -G -S "http://10.8.0.55:8081/WebServiceCrawler/services/CrawlerCtrl?wsdl"
XID=`cat /tmp/.X${CID}-lock|awk '{print $1}'`
rpid=`ps aux|grep Xvfb|awk -vp=$XID '$2==p {print $2}'`
if [ $rpid ]; then	
    kill -9 $rpid
fi


