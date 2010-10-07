#! /bin/bash
CURCID=$1
MAXCID=`expr $1 + $2`
while [ $CURCID -lt $MAXCID ]; do
    rm -rf $CURCID
    CURCID=`expr $CURCID + 1`
done
