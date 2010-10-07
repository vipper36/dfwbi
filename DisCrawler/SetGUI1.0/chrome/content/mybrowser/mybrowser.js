// nsIWebProgressListener implementation to monitor activity in the browser.
function WebProgressListener() {
}
WebProgressListener.prototype = {
_requestsStarted: 0,
_requestsFinished: 0,

// We need to advertize that we support weak references.  This is done simply
// by saying that we QI to nsISupportsWeakReference.  XPConnect will take
// care of actually implementing that interface on our behalf.
QueryInterface: function(iid) {
	  if (iid.equals(Components.interfaces.nsIWebProgressListener) ||
	      iid.equals(Components.interfaces.nsISupportsWeakReference) ||
	      iid.equals(Components.interfaces.nsISupports))
	       return this;
    
	  throw Components.results.NS_ERROR_NO_INTERFACE;
     },

// This method is called to indicate state changes.
onStateChange: function(webProgress, request, stateFlags, status) {
	  const WPL = Components.interfaces.nsIWebProgressListener;
	  if (stateFlags & WPL.STATE_IS_REQUEST) {
	       if (stateFlags & WPL.STATE_START) {
		    this._requestsStarted++;
	       } else if (stateFlags & WPL.STATE_STOP) {
		    this._requestsFinished++;
	       }
	  }
	  if (stateFlags & WPL.STATE_IS_DOCUMENT)
	  {
	       if (stateFlags & WPL.STATE_STOP) {
		    if (this._requestsStarted==this._requestsFinished)
		    {
//			 alert("hehe");
			 var result = document.getElementById("resultc");
			 var browser = document.getElementById("browser");
			 var doc=browser.contentDocument;
//			 result.value = doc.documentElement.innerHTML;
			 this.onStatusChange(webProgress, request, 0, "Done");
			 this._requestsStarted = this._requestsFinished = 0;
		    }
	       }
	  }
    
     },

// This method is called to indicate progress changes for the currently
// loading page.
onProgressChange: function(webProgress, request, curSelf, maxSelf,
			   curTotal, maxTotal) {
     },

// This method is called to indicate a change to the current location.
onLocationChange: function(webProgress, request, location) {

     },

// This method is called to indicate a status changes for the currently
// loading page.  The message is already formatted for display.
onStatusChange: function(webProgress, request, status, message) {
     },

// This method is called when the security state of the browser changes.
onSecurityChange: function(webProgress, request, state) {

     }
};
var listener;
function go() {
     var urlbar = document.getElementById("urlbar");
     var browser = document.getElementById("browser");
      
     browser.loadURI(urlbar.value, null, null);
}
function Analysis() {
     const cid = "@nyapc.com/XPCOM/nsDocAtt;1";
     var docatt = Components.classes[cid].createInstance();
     docatt = docatt.QueryInterface(Components.interfaces.nsIDocAtt);
     
     const did="@nyapc.com/XPCOM/nsAttDim;1";
     var attdim = Components.classes[did].createInstance();
     attdim = attdim.QueryInterface(Components.interfaces.nsIAttDim);
     attdim.AddDim(0,"AREA_RATE");
     attdim.AddDim(1,"STYLE_PAR");
     attdim.AddDim(2,"STYLE_SIB");
     attdim.AddDim(3,"DEPTH");
     attdim.AddDim(4,"WH_RATE");
     
     var browser = document.getElementById("browser");
     var doc=browser.contentDocument;

     const dsid = "@nyapc.com/XPCOM/nsDocSet;1";
     var docset = Components.classes[dsid].createInstance();
     var docset = docset.QueryInterface(Components.interfaces.nsIDocSet);
     docset.AddDocument(doc);
     docatt.dim=attdim;
     docatt.SetDocSet(docset);

     var resultc = document.getElementById("resultc");
     var len=docatt.GetVectorCount();
     alert(len);
     var resStr="";
     const nid = "@nyapc.com/XPCOM/nsCluster;1";
     var cluster = Components.classes[nid].createInstance();
     cluster = cluster.QueryInterface(Components.interfaces.nsICluster);
     
     cluster.SetDoubleParam("ATTDIM", attdim.GetCount());
     cluster.SetAtt(docatt.GetResult());
     cluster.CaculModel();
     var model=cluster.GetResultModel();
     const chid = "@nyapc.com/XPCOM/nsChlVarGenerator;1";
     var gen = Components.classes[chid].createInstance();
     gen = gen.QueryInterface(Components.interfaces.nsIVarGenerator);

     gen.SetModel(model);
     gen.GenVar();
     var boxpath=gen.GetVar("box");
     alert(boxpath);
     resultc.value=resStr;
}

function soapJob() {


     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";

     var obj = Components.classes[cid].createInstance();

     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);

     var address = document.getElementById("jobAddress");
     obj.SetAddress(address.value);
     var jobs= obj.getJobs();
     var len=jobs.Count();
     var result = document.getElementById("result_list");
     removeclassitem(result,"Aitem");
     for(var i=0;i<len;i++)
     {
	  var job=jobs.GetElementAt(i);
	  job = job.QueryInterface(Components.interfaces.nsISoapJob);
	  appendjob(job);
     }

}

function soapTask() {
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);
     var address = document.getElementById("taskAddress");
     obj.SetAddress(address.value);

     var jobid = document.getElementById("Job-id");
     var jobtype = document.getElementById("Job-type");
     var jobid_int;
     var jobtypestr;
     
     if(jobid.value.length>0)
	  jobid_int=parseInt(jobid.value);
     if(jobtype.value.length>0)
	  jobtypestr= jobtype.value;
     var task=null;
     
     if(jobid_int&&jobtypestr)
	  task = obj.getTaskByJobId(1,jobid_int,jobtypestr,20);
     if(task!=null)
     {
	  
	  var wrapid = document.getElementById("Wrap-id");
	  jobid.value=task.jobId;
	  jobtype.value=task.type;
	  wrapid.value=task.wrapid;
	  var urls=document.getElementById("url_list");
	  removeclassitem(urls,"Aitem")
	       var len=task.GetUrlCount();
	  alert(len);
	  for(var i=0;i<len;i++)
	  {
	       var uid={};
	       var url={};
	       task.GetUrlByIndex(i,uid,url);
	       appendurl(url.value,uid.value);
	  }
	  var wrapper=document.getElementById("soap-wrapper");
	  wrapper.value=obj.getWrapper(task.wrapid);
     }
     
}
function accesssel() {
     var urls=document.getElementById("url_list");
     var urlbar = document.getElementById("urlbar");
     var urlidbar = document.getElementById("url-id");
     var item=urls.getSelectedItem(0);

     if(item!=null)
     {
	  var cells=item.getElementsByTagName("listcell");
	  var uidele=cells[0];

	  var urlele=cells[1];

	  urlbar.value=urlele.getAttribute("label");
	  urlidbar.value=uidele.getAttribute("label");

	  go();
     }else
     {
	  alert("Please sellect a item!")
     }
}

function updatejob() {
     var result = document.getElementById("result_list");
     if(result.selectedItem==null)
	  alert("You must select a job!");
     else
     {
	  var item=result.selectedItem;
	  var cells=item.getElementsByTagName("listcell");
	  var jobid=cells[0].getAttribute("label");
	  alert(jobid);
	  const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
	  var obj = Components.classes[cid].createInstance();
	  obj = obj.QueryInterface(Components.interfaces.nsISoapInter);
	  
	  var address = document.getElementById("jobAddress");
	  obj.SetAddress(address.value);
	  var ret= obj.updateJob(jobid);
     }
}
function removeclassitem(list,class)
{
     var cells = list.getElementsByClassName(class);
     var len=cells.length;
     for (var i = 0; i < len; i++) { 
	  list.removeChild(cells[0]);
     }

}
function appendurl(url,uid){
     var result = document.getElementById("url_list");
     var item =document.createElement("listitem");
     item.setAttribute("class","Aitem");

     var cell1 =document.createElement("listcell");
     cell1.setAttribute("label",uid);
     var cell2 =document.createElement("listcell");
     cell2.setAttribute("label",url);
     item.appendChild(cell1);
     item.appendChild(cell2);
     result.appendChild(item);
}
function appendjob(job){
     var result = document.getElementById("result_list");
     var item =document.createElement("listitem");
     item.setAttribute("class","Aitem");

     var cell1 =document.createElement("listcell");
     cell1.setAttribute("label",job.id);
     var cell2 =document.createElement("listcell");
     cell2.setAttribute("label",job.name);
     var cell3 =document.createElement("listcell");
     cell3.setAttribute("label",job.comment);
     var cell4 =document.createElement("listcell");
     cell4.setAttribute("label",job.seed);
     var cell5 =document.createElement("listcell");
     cell5.setAttribute("label",job.seedType);
     item.appendChild(cell1);
     item.appendChild(cell2);
     item.appendChild(cell4);
     item.appendChild(cell5);
     item.appendChild(cell3);
     result.appendChild(item);
}
function savewrap()
{
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);
     var address = document.getElementById("taskAddress");
     obj.SetAddress(address.value);
      var wrappid=document.getElementById("Wrap-id");
     var wrapper=document.getElementById("soap-wrapper");
     obj.updateWrapper(wrapper.value,wrappid.value);
}
function createvarlist()
{
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var result = document.getElementById("soap-wrapper");

     if(result.value.length>0)
	  xsltFetcher.SetXsltDocStr(result.value);

     var len=xsltFetcher.GetVarCount();
     var varBox = document.getElementById("variable-box");
     removeclassitem(varBox,"var-list");
     for(var i=0;i<len;i++)
     {
	  var name={};
	  var value={};
	  xsltFetcher.GetVarByIndex(i,name,value);	  
	  create_varbox(name.value,value.value,i);
     }
}
function create_varbox(name,value,index)
{
     var varBox = document.getElementById("variable-box");
     var varList=document.createElement("vbox");
     varList.setAttribute("class","var-list");
     var hbox=document.createElement("hbox");
     var hbox2=document.createElement("hbox");
     hbox2.setAttribute("height","10");

     var lable1=document.createElement("label");
     lable1.setAttribute("value","Variable Name:");
     var lable2=document.createElement("label");
     lable2.setAttribute("value","Variable Value:");

     var textbox1=document.createElement("textbox");
     textbox1.setAttribute("id","set-name"+index);
     textbox1.setAttribute("value",name);
     textbox1.setAttribute("disabled","true");

     var textbox2=document.createElement("textbox");
     textbox2.setAttribute("id","set-value"+index);
     textbox2.setAttribute("value",value);
     textbox2.setAttribute("flex","1");

     var vbox=document.createElement("vbox");
     var botton=document.createElement("button");
     botton.setAttribute("label","Set");
     botton.setAttribute("id","set-var"+index);
     botton.setAttribute("oncommand","addvarindex("+index+");");

     hbox.appendChild(lable1);
     hbox.appendChild(textbox1);
     hbox.appendChild(lable2);
     hbox.appendChild(textbox2);
     vbox.appendChild(botton);
     hbox.appendChild(vbox);
     varList.appendChild(hbox);
     varList.appendChild(hbox2);
     varBox.appendChild(varList);
}
function addvarindex(index) {
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var wrapper=document.getElementById("soap-wrapper");
     xsltFetcher.SetXsltDocStr(wrapper.value);
     var varname = document.getElementById("set-name"+index);
     var varvalue = document.getElementById("set-value"+index);
     xsltFetcher.SetXsltVar(varname.value,varvalue.value);
     wrapper.value=xsltFetcher.GetXsltDocStr();
}

function setxslt()
{
     var wrapperbar = document.getElementById("wrapper");
     var result = document.getElementById("soap-wrapper");
     wrapperbar.value=result.value;
}
function fetchxsltcom() {
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);
     var resultc = document.getElementById("resultc");
     
     var wrapperbar = document.getElementById("wrapper");
     var uid=document.getElementById("url-id");
     
     var browser = document.getElementById("browser");
     xsltFetcher.SetXsltDocStr(wrapperbar.value);
     var doc=browser.contentDocument;

     xsltFetcher.SetDocument(doc);

     xsltFetcher.SetXsltParam("docurl",browser.currentURI.spec);
     xsltFetcher.SetXsltParam("urlid",uid.value);
     resultc.value=xsltFetcher.GetResultXML();
}

function sendresult()
{
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);

     var address = document.getElementById("resAddress");
     var resultc = document.getElementById("resultc");

     obj.SetAddress(address.value);
     obj.putResult(resultc.value,1);
}
function onload() {
     var urlbar = document.getElementById("urlbar");

     urlbar.value = "http://www.google.com/";
     listener = new WebProgressListener();
     
     var browser = document.getElementById("browser");
     browser.addProgressListener(listener,
				 Components.interfaces.nsIWebProgress.NOTIFY_ALL);

     go();

}

addEventListener("load", onload, false);
