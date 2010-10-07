var jobs;
function listJob()
{
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";

     var obj = Components.classes[cid].createInstance();

     obj =obj.QueryInterface(Components.interfaces.nsISoapInter);
     
     var address = document.getElementById("taskAddress");
     if(address.value.length>0)
	  obj.SetAddress(address.value);
     jobs= obj.getJobsWrapStatInvalid();

     if(jobs == null)
     {
	  alert("jobs is null");
	  return;
     }
     var len=jobs.Count();

     var result = document.getElementById("job_list");
     removeclassitem(result,"Aitem");
     for(var i=0;i<len;i++)
     {
	  var job=jobs.GetElementAt(i);
	  job = job.QueryInterface(Components.interfaces.nsISoapJob);
	  appendjob(job);
     }
     var total = document.getElementById("total");
     total.value = "Total:"+len;
}

var taskId;
var taskType;
var wrapId;
function getWrapper()
{
     var fetchWrapper = document.getElementById("resultc");
     fetchWrapper.value = "";
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);
     
     var address = document.getElementById("taskAddress");
     if(address.value.length>0)
	  obj.SetAddress(address.value);
     
     var result = document.getElementById("job_list");
     if(result.selectedItem==null)
	  alert("You must select a job!");
     else
     {
	  var item=result.selectedItem;
	  var cells=item.getElementsByTagName("listcell");
	  var jobid=cells[0].getAttribute("label");
	  var jobtype=cells[3].getAttribute("label");
	  var ret= obj.updateJob(jobid);
	  if(ret == null)
	  {
	       alert("job is null");
	       return;
	  }
	  var task;

	  if(jobid)
	       task = obj.getWrapInvalidTaskByJobId(1,jobid,jobtype,5);
	  else
	       task=obj.getTask(1,5);

	  if(task == null)
	  {
	       alert("task is null");
	       return;
	  }

	  wrapId = task.wrapid;
	  var len=task.GetUrlCount();
	  var menuurl = document.getElementById("URLS");
	  menuurl.removeAllItems();

	  for(var i=0;i<len;i++)
	  {
	       var uid={};
	       var url={};
	       task.GetUrlByIndex(i,uid,url);
	       menuurl.appendItem( url.value, uid.value, null );
	  }
	  if(len > 0)
	  {
	       menuurl.selectedIndex = len -1;
	  }

	  taskId = task.taskId;
	  taskType = task.type;

	  var wrapper=document.getElementById("wrapper");
	  wrapper.value=obj.getWrapper(task.wrapid);
     }
}
function selectedJobEvent()
{
     var joblist = document.getElementById("job_list");
     var item=joblist.selectedItem;
     if(item == null)
	  return;
     var cells=item.getElementsByTagName("listcell");
     var jobid=cells[0].getAttribute("label");
     var comment = cells[2].getAttribute("label");

     var jobidTxt = document.getElementById("jobid");
     jobidTxt.value = jobid;

     var jobCommentTxt= document.getElementById("comment");
     jobCommentTxt.value = comment;

     var menuurl = document.getElementById("URLS");
     menuurl.removeAllItems();

     //var jobtype = document.getElementById("jobType");
     //jobtype.selectedIndex = 0;

     var varBox = document.getElementById("variable-box");
     removeclassitem(varBox,"var-list");

     getWrapper();
}
function selectURLEvent()
{
     var menuurl = document.getElementById("URLS");
     menuurl.removeAllItems();

     var varBox = document.getElementById("variable-box");
     removeclassitem(varBox,"var-list");
}
function accesssel() {

     var url = document.getElementById("URLS");
     var browser = document.getElementById("browser");
     browser.loadURI(url.value,null,null);

}

function removeclassitem(list,classstr)
{
     var cells = list.getElementsByClassName(classstr);
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

function fetchxsltcom()
{
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);
     
     const did = "@nyapc.com/XPCOM/nsDomAttUtil;1";
     var domUtil = Components.classes[did].createInstance();
     domUtil = domUtil.QueryInterface(Components.interfaces.nsIDomAttUtil);

     var resultc = document.getElementById("resultc");
     resultc.value = "";

     var wrapperbar = document.getElementById("wrapper");

     var uid;
     var menuURL = document.getElementById("URLS");

     if(menuURL.selectedItem==null)
     {

	  alert("no selection");
     }
     else
     {
	  uid = menuURL.selectedItem;
     }
     var browser = document.getElementById("browser");
     xsltFetcher.SetXsltDocStr(wrapperbar.value);
     var doc=browser.contentDocument;
     
     var docArr = Components.classes["@mozilla.org/supports-array;1"]
	  .createInstance(Components.interfaces.nsISupportsArray);
     domUtil.GetALLDocumentArray(doc, docArr);
     var taskStr;
     var len=docArr.Count();
     for (var i = 0; i < len; i++) {
	  var tmpDoc=docArr.GetElementAt(i);

	  if(tmpDoc!=null)
	  {
	       
	       tmpDoc=tmpDoc.QueryInterface(Components.interfaces.nsIDOMDocument);
	       
	       xsltFetcher.SetDocument(tmpDoc);
	       
	       xsltFetcher.SetXsltParam("docurl",browser.currentURI.spec);
	       xsltFetcher.SetXsltParam("urlid",uid.value);
	       var resultStr;
	       resultStr = xsltFetcher.GetResultXML();
	       taskStr= taskStr+resultStr.substring(39);
	  }
	  
     }
     
     //resultc.value=resultStr;

     var taskBgStr = "<?xml version=\"1.0\" encoding=\"UTF-8\"?><Task id =\"" + taskId +"\" "+ "type =\"" +taskType +"\">";
     var taskEdStr = "</Task>";
     
     resultc.value = taskBgStr + taskStr + taskEdStr;
/*
  try //Firefox, Mozilla, Opera, etc.
  {
  parser=new DOMParser();
  xmlDoc=parser.parseFromString(resultStr,"text/xml");
  }
  catch(e)
  {
  alert(e.message);
  return;
  }
  var taskel=xmlDoc.createElement("Task");
  taskel.setAttribute("id",taskId);
  taskel.setAttribute("type",taskType);

  var rootTag = xmlDoc.documentElement;
  var tootNew = rootTag.cloneNode(false);


  var taskTag = xmlDoc.getElementsByTagName("Task");

  var results = xmlDoc.getElementsByTagName("Result");

  //alert(results.length);
  var x = results[0];
  var y = x.cloneNode(true);
  x.parentNode.removeChild(x);

  taskel.appendChild(y);
  xmlDoc.documentElement.appendChild(taskel);

  for(int i = 0; i < results.length; i++)
  {
  rootTag.removeChild(results[i]);
  //taskTag.appendChild(results[i]);
  }


  var xmlstring = (new XMLSerializer()).serializeToString(xmlDoc);
  alert(xmlstring);
*/
}

function modifyJob()
{
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj =obj.QueryInterface(Components.interfaces.nsISoapInter);
     
     var address = document.getElementById("taskAddress");
     if(address.value.length>0)
	  obj.SetAddress(address.value);

     var jobid = document.getElementById("jobid");
     var url = document.getElementById("url");
       
     if(url.value.length == 0)
     {
	  alert("url cannot be null!");
	  return;
     }
     obj.updateJobUrl(jobid.value,url.value);

     getWrapper();
}

function deactiveJob()
{
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj =obj.QueryInterface(Components.interfaces.nsISoapInter);
     
     var address = document.getElementById("taskAddress");
     if(address.value.length>0)
	  obj.SetAddress(address.value);

     var jobid = document.getElementById("jobid");
     obj.delJob(jobid.value);
     listJob();
}
function appendjob(job)
{
     var result = document.getElementById("job_list");
     var item =document.createElement("listitem");
     item.setAttribute("class","Aitem");

     var cell1 =document.createElement("listcell");
     cell1.setAttribute("label",job.id);
     var cell4 =document.createElement("listcell");
     cell4.setAttribute("label",job.name);
     var cell2 =document.createElement("listcell");
     cell2.setAttribute("label",job.comment);
     var cell3 =document.createElement("listcell");
     cell3.setAttribute("label",job.seedType);

     item.appendChild(cell1);
     item.appendChild(cell4);
     item.appendChild(cell2);
     item.appendChild(cell3);
     result.appendChild(item);
}


function createvarlist()
{
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var result = document.getElementById("wrapper");

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
     lable1.setAttribute("value","Variable:");
     var lable2=document.createElement("label");
     lable2.setAttribute("value","Value:");

     var textbox1=document.createElement("textbox");
     textbox1.setAttribute("id","set-name"+index);
     textbox1.setAttribute("value",name);
     textbox1.setAttribute("disabled","true");
     textbox1.setAttribute("minwidth","60");
     textbox1.setAttribute("maxwidth","60");

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
function addvarindex(index)
{
     const cid = "@nyapc.com/XPCOM/nsXSLTFetcher;1";
     var xsltFetcher = Components.classes[cid].createInstance();
     xsltFetcher = xsltFetcher.QueryInterface(Components.interfaces.nsIXSLTFetcher);

     var wrapper=document.getElementById("wrapper");
     xsltFetcher.SetXsltDocStr(wrapper.value);

     var varname = document.getElementById("set-name"+index);
     var varvalue = document.getElementById("set-value"+index);

     xsltFetcher.SetXsltVar(varname.value,varvalue.value);
     wrapper.value=xsltFetcher.GetXsltDocStr();
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

function savevarlist()
{
     const cid = "@nyapc.com/XPCOM/nsSoapInter;1";
     var obj = Components.classes[cid].createInstance();
     obj = obj.QueryInterface(Components.interfaces.nsISoapInter);
     var address = document.getElementById("taskAddress");
     if(address.value.length>0)
	  obj.SetAddress(address.value);

     var wrapper=document.getElementById("wrapper");
     var rv = obj.updateWrapperCheckOk(wrapper.value,wrapId,taskId);
     if(rv)
	  alert("Success!");
     else
	  alert("Failure!");
}
function searchJob()
{
     var txtJobId = document.getElementById("searchJobID");
     var jobList = document.getElementById("job_list");
     var URLS = document.getElementById("URLS");
     var wrapper = document.getElementById("wrapper");
     URLS.removeAllItems();
     wrapper.value = "";
     jobList.clearSelection();
     if(txtJobId.value.length == 0)
     {
	  alert("please enter jobid!");
	  return;
     }
     if(jobs == null)
     {
	  alert("jobs is null");
	  return;
     }
     var len=jobs.Count();
     var flag = false;
     for(var i=0;i<len;i++)
     {
	  var job=jobs.GetElementAt(i);
	  job = job.QueryInterface(Components.interfaces.nsISoapJob);
	  if(job.id == txtJobId.value)
	  {
	       jobList.selectedIndex = i;
	       getWrapper();
	       flag = true;
	  }
       
     }
     if(!flag)
     {
	  alert("no job!");

     }
}
function addJobs()
{
     var jobList = document.getElementById("job_list");
     var workJob = document.getElementById("workJob");
     if(jobList.selectedItem==null)
     {
	  alert("You must select a job!");
	  return;
     }

     var items = jobList.selectedItems;
     if(items.length > 0)
     {
	  for(var i = 0; i < items.length; i++)
	  {

	       var cells=items[i].getElementsByTagName("listcell");
	       var jobid=cells[0].getAttribute("label");
	       var jobname = cells[1].getAttribute("label");
	       var comment = cells[2].getAttribute("label");

	       var jobStr = String(workJob.value);
	       if(jobStr.search(jobid) > -1)
	       {
		    continue;
	       }
	       else
	       {
		    workJob.value += jobid;
		    workJob.value += " ";
		    workJob.value += jobname;
		    workJob.value += " ";
		    workJob.value += comment;
		    workJob.value += "\n";
	       }
	  }
     }

}
function clearWorkJob()
{
     var workJob = document.getElementById("workJob");
     workJob.value = "";
}
var sortType = true;
function sortIdEvent()
{
     if(sortType)
	  sortType = false;
     else
	  sortType = true;
    
     if(jobs == null)
     {
	  alert("jobs is null");
	  return;
     }
     var len=jobs.Count();
     var jobarr = new Array();
     for(var n = 0; n < len; n++)
     {
	  var job = jobs.GetElementAt(n).QueryInterface(Components.interfaces.nsISoapJob);
	  jobarr.push(job);
     }
     var result = document.getElementById("job_list");
     removeclassitem(result,"Aitem");
     var maxPos;
     for(var i=len-1; i>=1; i--)
     {
	  maxPos = i;
	  for(var j=0; j<i; j++)
	  {
	       var maxJob = jobarr[maxPos];
	       var posJob = jobarr[j];
	       if(sortType)
	       {
		    if(maxJob.id <  posJob.id)
			 maxPos = j;
	       }
	       else
	       {
		    if(maxJob.id >  posJob.id)
			 maxPos = j;
	       }
	  }
        
	  var jobTmp = jobarr[maxPos];
	  jobarr[maxPos] = jobarr[i];
	  jobarr[i] = jobTmp;
	  appendjob(jobTmp);
         

     }
     appendjob(jobarr[0]);
}

function sortTypeEvent()
{
     if(sortType)
	  sortType = false;
     else
	  sortType = true;

     if(jobs == null)
     {
	  alert("jobs is null");
	  return;
     }
     var len=jobs.Count();
     var jobarr = new Array();
     for(var n = 0; n < len; n++)
     {
	  var job = jobs.GetElementAt(n).QueryInterface(Components.interfaces.nsISoapJob);
	  jobarr.push(job);
     }
     var result = document.getElementById("job_list");
     removeclassitem(result,"Aitem");
     var maxPos;
     for(var i=len-1; i>=1; i--)
     {
	  maxPos = i;
	  for(var j=0; j<i; j++)
	  {
	       var maxJob = jobarr[maxPos];
	       var posJob = jobarr[j];

	       if(sortType)
	       {
		    if(maxJob.seedType >  posJob.seedType)
			 maxPos = j;
	       }
	       else
	       {
		    if(maxJob.seedType <  posJob.seedType)
			 maxPos = j;
	       } 
	  }
         
	  var jobTmp = jobarr[maxPos];
	  jobarr[maxPos] = jobarr[i];
	  jobarr[i] = jobTmp;
	  appendjob(jobTmp);
        
     }
     appendjob(jobarr[0]);
}
function keyEnterEvent(e)
{
     if(e.keyCode == 13)
	  searchJob();
}