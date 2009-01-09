#!/usr/bin/env python 
# Filename: method.py 
import sys
import os
if len(sys.argv)<2:
    print 'test.py filename'
d={"SOCI":"soci","eExchangeType":"exchange_type","SOCIError":"soci_error","eIndicator":"indicator","eNull":"i_null","eOK":"i_ok","eXChar":"x_char","eXCString":"x_cstring","eXStdString":"x_stdstring","eXShort":"x_short","eXDouble":"x_double","eXStdTm":"x_stdtm"}
cmd="|sed 's/"
tcmd=""
for i in d:
    cmdtmp=cmd+i+"/"+d[i]+"/g'"
    tcmd=tcmd+cmdtmp
rcmd="cat "+sys.argv[1]+tcmd
os.system(rcmd)
# This short example can also be written as Person().sayHi() 
