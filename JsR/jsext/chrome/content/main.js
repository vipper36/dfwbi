var jsCom = Components.classes["@xiao.xf.com/JsCom;1"]
                            .getService(Components.interfaces.nsIJsCom);
function jsexcutewin() {
	var mainWindow = window.QueryInterface(Components.interfaces.nsIInterfaceRequestor)
                       .getInterface(Components.interfaces.nsIWebNavigation)
                       .QueryInterface(Components.interfaces.nsIDocShellTreeItem)
                       .rootTreeItem
                       .QueryInterface(Components.interfaces.nsIInterfaceRequestor)
                       .getInterface(Components.interfaces.nsIDOMWindow);
	var browser = mainWindow.gBrowser.selectedBrowser;
	var script=document.getElementById("testscript-jquery");
     	jsCom.execWinJs(script.value,browser.contentWindow);
}
function connR() {
	var ipaddr=document.getElementById("ipaddr");
        var port=document.getElementById("port");
     	var cStatu=jsCom.openR(ipaddr.value,port.value);
	if(cStatu<0)
	{
	    alert("连接出错!");
	}
	else
	{
            var closeb=document.getElementById("close");
	    closeb.disabled=false;
            var openb=document.getElementById("connect");
	    openb.disabled=true;
	}	
}
function closeR() {
     	jsCom.closeR();
        var closeb=document.getElementById("close");
	closeb.disabled=true;
        var openb=document.getElementById("connect");
	openb.disabled=false;

}
