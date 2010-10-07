#! /bin/bash
. ./config
Xvfb :$CID +kb -screen 0 1024x768x24 -once -fbdir /tmp&
export DISPLAY=:${CID}.0

echo $MulDocListener
echo $MOZSHELL
$MOZSHELL $KEYPRESS $CrawlerBin -r 1 -c $CID -l $MulDocListener
XID=`cat /tmp/.X${CID}-lock|awk '{print $1}'`
rpid=`ps aux|grep Xvfb|awk -vp=$XID '$2==p {print $2}'`
if [ $rpid ]; then	
    kill -9 $rpid
fi


