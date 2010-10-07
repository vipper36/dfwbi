#! /bin/bash
CURCID=$1
MAXCID=`expr $1 + $2`
while [ $CURCID -lt $MAXCID ]; do
    mkdir $CURCID
    cp runCrawler.sh runWrapgen.sh runMulWrap.sh runMulCraw.sh runService config $CURCID
    echo "CID=$CURCID" >>$CURCID/config
    CURCID=`expr $CURCID + 1`
done
