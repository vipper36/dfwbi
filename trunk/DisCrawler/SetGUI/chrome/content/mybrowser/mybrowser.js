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

function soapTask() {
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);
//     alert(obj);
     var address = document.getElementById("taskAddress");
     if(address.value.length>0)
	  obj.SetAddress(address.value);

     var jobid = document.getElementById("Job-id");
     var jobtype = document.getElementById("Job-type");
     var num = document.getElementById("url-Number");
     var jobid_int;
     var jobtypestr;
     var num_int;
     if(jobid.value.length>0&&jobtype.value.length>0)
     {
	  
	  if(num.value.length>0)
	       num_int=parseInt(num.value);
	  else
	       num_int=5;
	  jobid_int=parseInt(jobid.value);
	  jobtypestr= jobtype.value;
	  var task;
	  alert(num_int);
	  
	  task = obj.getTaskByJobId(1,jobid_int,jobtypestr,num_int);
     
	  if(task==null)
	  {
	       alert("Task is null");
	       return;
	  }
	  var len=task.GetUrlCount();
	  alert(len);
	  var varBox = document.getElementById("browser-box");
	  removeclassitem(varBox,"browser-list");
	  num.value=len;
	  for(var i=0;i<len;i++)
	  {
	       var uid={};
	       var url={};
	       task.GetUrlByIndex(i,uid,url);
	       create_browser(i);
	       var browser = document.getElementById("browser"+i);
      
	       browser.loadURI(url.value, null, null);
	  }
	  var wrapper=document.getElementById("task-wrapper");
	  wrapper.value=obj.getWrapper(task.wrapid);
     }else
     {
	  alert("Please input ID and Type!");
     }
     
     
}
function createvarlist()
{
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var result = document.getElementById("task-wrapper");

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
function create_browser(index)
{
     var browserBox = document.getElementById("browser-box");
     var browserList=document.createElement("vbox");
     browserList.setAttribute("flex","1");
     browserList.setAttribute("class","browser-list");
     var browser=document.createElement("browser");
     browser.setAttribute("flex","1");
     var id="browser"+index;
     browser.setAttribute("id",id);

     browserList.appendChild(browser);
     browserBox.appendChild(browserList);
}
function removeclassitem(list,class)
{
     var cells = list.getElementsByClassName(class);
     var len=cells.length;
     for (var i = 0; i < len; i++) { 
	  list.removeChild(cells[0]);
     }

}
function addvarindex(index) {
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var wrapper=document.getElementById("task-wrapper");
     xsltFetcher.SetXsltDocStr(wrapper.value);

     var varname = document.getElementById("set-name"+index);
     var varvalue = document.getElementById("set-value"+index);
     xsltFetcher.SetXsltVar(varname.value,varvalue.value);
     wrapper.value=xsltFetcher.GetXsltDocStr();
}
function fetchxsltcom() {
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);
     var resultc = document.getElementById("resultc");
     resultc.value = "";

     var wrapperbar = document.getElementById("task-wrapper");

     
     var browser = document.getElementById("browser0");
     xsltFetcher.SetXsltDocStr(wrapperbar.value);
     var doc=browser.contentDocument;

     xsltFetcher.SetDocument(doc);

     xsltFetcher.SetXsltParam("docurl",browser.currentURI.spec);
     xsltFetcher.SetXsltParam("urlid",1111);
     resultc.value=xsltFetcher.GetResultXML();
}

function staudywrap()
{
     var jobtype = document.getElementById("Job-type");
     if(jobtype.value.length>0)
     {
	  
	  var num = document.getElementById("url-Number");
	  var num_int;
	  if(num.value.length>0)
	       num_int=parseInt(num.value);
	  else
	       num_int=5;

	  var cid = "@nyapc.com/XPCOM/nsDocAtt;1";
	  if(jobtype.value==3)
	  {
	      cid = "@nyapc.com/XPCOM/ContentDocAtt;1";
	  }
	  var DocAtt = Components.classes[cid].createInstance();
	  var DocAtt = DocAtt.QueryInterface(Components.interfaces.nsIDocAtt);
	  const did="@nyapc.com/XPCOM/nsAttDim;1";
	  var attdim = Components.classes[did].createInstance();
	  attdim = attdim.QueryInterface(Components.interfaces.nsIAttDim);
	  if(jobtype.value==2)
	  {
	       alert(attdim)
	       attdim.AddDim(0,"AREA_RATE");
	       attdim.AddDim(1,"STYLE_PAR");
	       attdim.AddDim(2,"STYLE_SIB");
	       attdim.AddDim(3,"DEPTH");
	       attdim.AddDim(4,"WH_RATE");
	  }
	  DocAtt.dim=attdim;
	  for(var i=0;i<num_int;i++)
	  {
	       var browser = document.getElementById("browser"+i);
	       DocAtt.AddDocument(browser.contentDocument);
	  }
	  if(jobtype.value==1)
	  {
	       TrainChl(DocAtt);
	       
	  }else if(jobtype.value==2)
	  {
	       TrainCol(DocAtt);
	       
	  }
	  else if(jobtype.value==3)
	  {
	       TrainCont(DocAtt);
	       
	  }
	  
	  
     }
     else
     {
	  alert("Please input ID and Type!");
     }
     
}

function TrainCont(DocAtt) {
     alert("Start Train");
     var result = document.getElementById("resultc");
     if(null != DocAtt)
     {
	  {
	       var dim = DocAtt.dim;
	       const nid = "@nyapc.com/XPCOM/ThresholdCluster;1";
	       var cluster = Components.classes[nid].createInstance();
	       cluster = cluster.QueryInterface(Components.interfaces.nsICluster);
	       cluster.SetAtt(DocAtt.GetResult());
	       alert("statistic ok");
	       cluster.CaculModel();

	       var model = cluster.GetResultModel();
	       alert("clustering ok");
	       const chid = "@nyapc.com/XPCOM/ContentVarGen;1";
	       var gen = Components.classes[chid].createInstance();
	       gen = gen.QueryInterface(Components.interfaces.nsIVarGenerator);
	       gen.SetModel(model);
	       gen.SetAttDim(dim);
	       gen.SetParam("similar_node_th","0.7");
	       alert("start generate variables");
	       gen.GenVar();
	       const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
	       var xsltFetcher = Components.classes[cid].createInstance();
	       xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);
	       
	       var result = document.getElementById("task-wrapper");
	       
	       if(result.value.length>0)
	       {
		    
		    xsltFetcher.SetXsltDocStr(result.value);
		    
		    var len=xsltFetcher.GetVarCount();
		    for(var i=0;i<len;i++)
		    {
			 var name={};
			 var value={};
			 xsltFetcher.GetVarByIndex(i,name,value);
			 alert(name.value);
			 var tmpvalue=gen.GetVar(name.value);
			 alert(tmpvalue);
			 xsltFetcher.SetXsltVar(name.value,tmpvalue);
		    }
	       }
	       result.value = xsltFetcher.GetXsltDocStr();
	  }
     }

}

function TrainCol(DocAtt) {
     alert("hehe");
     var result = document.getElementById("resultc");
     if(null != DocAtt)
     {
	  alert("1");
	  var dim = DocAtt.dim;
	  const nid = "@nyapc.com/XPCOM/nsCluster;1";
	  var cluster = Components.classes[nid].createInstance();
	  cluster = cluster.QueryInterface(Components.interfaces.nsICluster);
	  cluster.SetAtt(DocAtt.GetResult());
	  cluster.SetDoubleParam("CLASS_COUNT",3);
	  cluster.SetDoubleParam("ATTDIM", DocAtt.dim.GetCount());
	  cluster.CaculModel();
	  alert("2");
	  var model=cluster.GetResultModel();
	  const chid = "@nyapc.com/XPCOM/nsColVarGenerator;1";
	  var gen = Components.classes[chid].createInstance();
	  gen = gen.QueryInterface(Components.interfaces.nsIVarGenerator);
	  gen.SetAttDim(dim);
	  gen.SetModel(model);
	  gen.GenVar();
	  alert("3");
	  const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
	  var xsltFetcher = Components.classes[cid].createInstance();
	  xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

	  var result = document.getElementById("task-wrapper");
     
	  if(result.value.length>0)
	  {
	  
	       xsltFetcher.SetXsltDocStr(result.value);
	       
	       var len=xsltFetcher.GetVarCount();
	       for(var i=0;i<len;i++)
	       {
		    var name={};
		    var value={};
		    xsltFetcher.GetVarByIndex(i,name,value);	  
		    var tmpvalue=gen.GetVar(name.value);
		    xsltFetcher.SetXsltVar(name.value,tmpvalue);
	       }
	  }
	  result.value = fetcher.GetXsltDocStr();
     }

}
function TrainChl(Docatt) {
     var dim = Docatt.dim;
     var resultc = document.getElementById("resultc");
     var len=Docatt.GetVectorCount();
     alert(len);
     var resStr="";

     const nid = "@nyapc.com/XPCOM/nsUrlCluster;1";
     var cluster = Components.classes[nid].createInstance();
     cluster = cluster.QueryInterface(Components.interfaces.nsICluster);
     
     cluster.SetAtt(Docatt.GetResult());
     cluster.CaculModel();
     var model=cluster.GetResultModel();
     const chid = "@nyapc.com/XPCOM/nsChlVarGenerator_1;1";
     var gen = Components.classes[chid].createInstance();
     gen = gen.QueryInterface(Components.interfaces.nsIVarGenerator);
     gen.SetAttDim(dim);
     gen.SetModel(model);
     gen.GenVar();

     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var result = document.getElementById("task-wrapper");

     if(result.value.length>0)
     {
	  
	  xsltFetcher.SetXsltDocStr(result.value);
	  
	  var len=xsltFetcher.GetVarCount();
	  for(var i=0;i<len;i++)
	  {
	       var name={};
	       var value={};
	       xsltFetcher.GetVarByIndex(i,name,value);	  
	       var tmpvalue=gen.GetVar(name.value);
	       xsltFetcher.SetXsltVar(name.value,tmpvalue);
	  }
     }
     result.value = fetcher.GetXsltDocStr();
}
