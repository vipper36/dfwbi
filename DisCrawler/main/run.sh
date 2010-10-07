#! /bin/bash
for file in `find . -type d -name \[0-9\]\*`
do
	cd $file
	if [ -e runservice.pid ]; then
		echo "The process is exist!"
	else
		./runService runMulWrap.sh&
		echo "ok"
		sleep 2
	fi

	cd ..
done
