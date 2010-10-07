cat $1|
while read line
do
    lineCount=`echo $line|wc -c`
    if [ $lineCount -gt 0 ]; then
	url=`echo $line | awk -F"," '{print $2}'`;
	jobname=`echo $line | awk -F"," '{print $3}'`;
	name=`echo $line | awk -F"," '{print $1}'`;
	while [ 1 ]; do
	    jobid=`./soaptool -J -n $jobname -t 1 -u $url -c $name`
	    if [ $jobid ]; then
		while [ 1 ]; do
		ret=`./soaptool -W -i $jobid -t 1 -v "docatt=@nyapc.com/XPCOM/nsNDDocAtt;1###cluster=@nyapc.com/XPCOM/nsUrlCluster;1###generator=@nyapc.com/XPCOM/nsChlVarGenerator_1;1###doccount=1###path_atts=class;id" -f chl.xslt`
		if [ $ret -eq 1 ]; then
                        break
                fi
		done
		while [ 1 ]; do
		ret=`./soaptool -W -i $jobid -t 2 -v "docatt=@nyapc.com/XPCOM/nsDocAtt;1###cluster=@nyapc.com/XPCOM/nsCluster;1###generator=@nyapc.com/XPCOM/nsColVarGenerator;1###doccount=2###dim=AREA_RATE;STYLE_PAR;STYLE_SIB;DEPTH;WH_RATE###classcount=3###res_path_atts=class;valign;halign;align;font" -f col.xslt`
		if [ $ret -eq 1 ]; then
			break
		fi
		done
		while [ 1 ]; do
		ret=`./soaptool -W -i $jobid -t 3 -v "docatt=@nyapc.com/XPCOM/ContentDocAtt;1###cluster=@nyapc.com/XPCOM/ThresholdCluster;1###generator=@nyapc.com/XPCOM/ContentVarGen;1###doccount=5###similar_node_th=0.7" -f con.xslt`
		if [ $ret -eq 1 ]; then
                        break
                fi
		done
		echo $jobid
		break	
	    fi
	    
	done
	
    fi
done
