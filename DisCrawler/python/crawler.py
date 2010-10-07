#!/usr/bin/env python
# Filename: crawler.py
#  -*- coding: utf-8 -*-
import urllib
import urllib2
import sys
import os
import re
from urllib2 import URLError
from sgmllib import SGMLParser
from lxml import etree
import datetime
import time
import socket
class CfgLister(SGMLParser):
    def reset(self):
        SGMLParser.reset(self)
        self.xmls = []
        self.cols = []
    def unknown_starttag(self,tag, attrs):
        if tag=='page':
            xmlfile = [v for k, v in attrs if k=='xml']
            if xmlfile:
                self.xmls.extend(xmlfile)
            colname = [v for k, v in attrs if k=='name']
            if colname:
                self.cols.extend(colname)
    def printxml(self):
        i=0
        for colname in self.cols:
           print colname
           print self.xmls[i]
           i=i+1
socket.setdefaulttimeout(15)

if len(sys.argv)>1:
    urlfile=open(sys.argv[1])
else:
    quit()
if len(sys.argv)>2:
    idxurl=sys.argv[2]
else:
    idxurl=""
today = datetime.date.today()


while 1:
    urlitems=urlfile.readline()
    if urlitems:
        urlitems="".join(urlitems.split())
        urli=urlitems.split(",")
        name=urli[0]
        url=urli[1]
        jobid=urli[2]
        print name
        print url
        filename="index"
        i=0
        while i<7:
            deltday = datetime.timedelta(days=i)  
            realdate=today-deltday
            todate=str(realdate)
            dates=todate.replace("-","")
            print dates
            swflocate=url+dates+"/"+filename+".swf"
            print  swflocate
#download swf file
            req = urllib2.Request(swflocate)
            try:
                sock=urllib2.urlopen(req)
                break
            except URLError, e:
                i=i+1
                continue
        if i<7:
            try:
                swffile=open(filename+".swf",'w')
                swffile.write(sock.read())
                sock.close()
                swffile.close()
            except:
                continue
        else:
            continue
#Decompile swf
        print "start decompile"
        flarecmd="flare "+filename+".swf"
	print flarecmd
        if os.path.isfile(filename+".swf"):
            os.system(flarecmd)
        if os.path.isfile(filename+".flr"):
            flrfile=open(filename+".flr")
            flrcont=flrfile.read()
            flrfile.close()
            resul=re.search(".{32}\.cfg",flrcont)
            if resul:
                cfgname=resul.group()
            else:
                print 'swf do not have a cfg'
                continue
        print cfgname
#filter cfg get xml
        cfgreq=urllib2.Request(url+dates+"/"+cfgname)
        try:
            cfgsock=urllib2.urlopen(cfgreq)
        except URLError, e:
            continue
        try:
            parser = CfgLister()
            cfgcont=cfgsock.read()
            print cfgcont
            parser.feed(cfgcont)
            sock.close()
#tanselate XML to idx
            xslt_doc =etree.parse("py.xslt")
            transform = etree.XSLT(xslt_doc)
        except:
            continue
        i=0;
        for xml in parser.xmls:
            xmlreq= urllib2.Request(url+dates+"/"+xml)
            print url+dates+"/"+xml
            try:
                xmlsock=urllib2.urlopen(xmlreq)
            except URLError, e:
                xmlsock.close()
                continue
            try:
                doc=etree.parse(xmlsock)
                
                xmlsock.close()
                
                drestr=urllib2.quote(url+dates+"/")
                
                drestr=drestr.replace(".","%2E")
                
                drestr=drestr.replace("-","%2D")
                
                drestr=drestr.replace("/","%2F")
                
                drepa = '"'+drestr+'"'
                
                xmlstr=xml.replace(".","%2E")
                xmlstr=xmlstr.replace("-","%2D")
                xmlpa = '"'+xmlstr+'"'

                datepa='"'+todate+'"'


                epotime=time.strftime("%s",time.localtime())

                datesecpa='"'+epotime+'"'

                colpa='"'+unicode(parser.cols[i],'utf-8')+'"'
                jobpa='"'+jobid+'"'
                result=transform(doc,drereference=drepa,xmlname=xmlpa,colname=colpa,jobname=jobpa,pdate=datepa,sdate=datesecpa)
                if len(str(result))>0:
                    if idxurl:
                        idxreq=urllib2.Request(idxurl,str(result))
                        idx=urllib2.urlopen(idxreq)
                        print idx.read()
                    else:
                        idx=open(xml+".idx","w")
                        idx.write(str(result))
                        idx.close()
                i=i+1
		print "success"
            except:
                continue
#remove temp file
        os.remove(filename+".swf")
        os.remove(filename+".flr")
        
    else:
        break
    
    


