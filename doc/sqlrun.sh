#! /bin/sh
ORASTR=fly/fly@orcl
year=2006
toyear=2008
while [ $year -le $toyear ]; do
    
sqlplus -s ${ORASTR}<<EOF
select * from cat;
execute buffdest;

quit
EOF
echo finish process $year
year=`expr $year + 1`;
done
