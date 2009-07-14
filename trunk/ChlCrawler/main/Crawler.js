// nsIWebProgressListener implementation to monitor activity in the browser.
function doXPCOM() {
     try {
	 const cid = "@nyapc.com/XPCOM/Crawler;1";
	 var obj = Components.classes[cid].createInstance();
	 obj = obj.QueryInterface(Components.interfaces.ICrawler);
     }
     catch (err) {
	  print(err);
	  return;
     }

	obj.CrawSite('http://www.xulplanet.com/references/xpcomref/ifaces/nsIDOMHTMLCollection.html');
     print(link);
}
doXPCOM();
