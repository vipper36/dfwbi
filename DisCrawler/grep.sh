#! /bin/bash
ret=`grep $1 $2`
l=`echo $ret|wc -c`

if [ $l -gt 1 ]; then
    echo $2
    echo $ret
    
fi
