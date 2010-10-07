#! /bin/bash
for file in `ls -l | grep '^d' | awk '{print $8}'`
do
    cd ${file}
    if [ -e runservice.pid ]; then
	rpid=`cat runservice.pid`
	if [ $rpid ]; then

	    srpid=`ps aux|awk -vp=$rpid '$2==p {print $2}'`
	    if [ $srpid ]; then
		kill -9 $srpid
	    fi

	fi
	rm runservice.pid
	
    fi
    	
    if [ -e gtkMain.pid ]; then
	gpid=`cat gtkMain.pid`
	if [ $gpid ]; then
	    grpid=`ps aux|awk -vp=$gpid '$2==p {print $2}'`
	    if [ $grpid ]; then
		kill -9 $grpid
		ppid=`ps -ef|awk -vp=$grpid '$2==p {print $3}'`
		if [ $ppid ]; then
		    kill -9 $ppid
		fi
	    fi
	fi
	rm gtkMain.pid
    fi

    cd ..
done
